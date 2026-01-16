#include "PmergeMe.hpp"
#include <algorithm>
#include <sstream> // std::istringstream

/**
use move if dont need original container
Avoids allocating new memory, only transfers ownership of the internal buffer, O(1) instead of O(n)
*/

PmergeMe::PmergeMe(const std::vector<int> arrV, const std::deque<int> arrD) : _arrVec(std::move(arrV)), _arrDeq(std::move(arrD)), __totalComparisons(0) {}

PmergeMe::PmergeMe(const PmergeMe& other) : _arrVec(other._arrVec), _arrDeq(other._arrDeq){}

PmergeMe::~PmergeMe(){}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        _arrVec = other._arrVec;
        _arrDeq = other._arrDeq;
		__totalComparisons = other.__totalComparisons;
    }
    return *this;
}

const std::vector<int>& PmergeMe::getArrV() const { return _arrVec; }

const std::deque<int>& PmergeMe::getArrD() const { return _arrDeq; }

void PmergeMe::validateToken(const std::string& token) {
	if (token.empty())
		throw std::invalid_argument("Invalid input");

	size_t i = 0;
	if (token[0] == '+' && token.size() == 1) {
		throw std::invalid_argument("Invalid input");
		i = 1;
	}

	for (; i < token.size(); ++i) {
		if (!std::isdigit(static_cast<unsigned char>(token[i])))
			throw std::invalid_argument("Invalid input");
	}
}

// let exception propagate to main
void PmergeMe::setArrV(const std::string& input) {
	_arrVec.clear();

	std::istringstream 	iss(input);
	std::string 		token;

	while (iss >> token) {
		validateToken(token);
		_arrVec.push_back(std::stoi(token));
}
	if (_arrVec.empty()) {
		throw std::invalid_argument("Invalid input: no nums provided");
	}
}

void PmergeMe::setArrD(const std::string& input) {
	_arrDeq.clear();

	std::istringstream iss(input);
	std::string token;

	while (iss >> token) {
			validateToken(token);
			_arrDeq.push_back(std::stoi(token)); // exception propagate
	}
	if (_arrDeq.empty()) {
		throw std::invalid_argument("Invalid input: no nums provided");
	}
}

// ** PARSE INPUT **
std::string PmergeMe::joinArgs(int argc, char* argv[]) {
    std::ostringstream oss;
    for (int i = 1; i < argc; ++i) {
        oss << argv[i] << " ";
    }
    return oss.str();
}

/** VECTOR **
  * step 1: make pairs of each consequtive elements and
  * place on first place the bigger num
*/
std::vector<std::pair<int, int>> PmergeMe::makePairsVector(int& oddEl) {
			std::vector<std::pair<int, int>> pairs;

	for (size_t i = 0; i < _arrVec.size() - 1; i += 2) {
		__totalComparisons++;
		if (_arrVec[i] < _arrVec[i+1]) {
			pairs.push_back({_arrVec[i+1], _arrVec[i]}); 
		} else {
			pairs.push_back({_arrVec[i], _arrVec[i+1]});
		}
	}
	oddEl = (_arrVec.size() % 2 == 1 ? _arrVec.back() : -1);
	return pairs;
}

// recursion helpers:
std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> PmergeMe::makeMetaPairs(std::vector<std::pair<int,int>>& pairs) {
	std::vector<std::pair<std::pair<int,int>, std::pair<int,int>>> metaPairs;
		for (size_t i = 0; i < pairs.size() - 1; i += 2) {
		__totalComparisons++;
		if (pairs[i].first < pairs[i+1].first) {
			metaPairs.push_back({pairs[i+1], pairs[i]});
		} else {
			metaPairs.push_back({pairs[i], pairs[i+1]});
		}
	}
	return metaPairs;
}

/** Step 2:take the vector of pairs with bigger number first.
* 	Returns sorted on first num the vector of pairs
*/
std::vector<std::pair<int, int>> PmergeMe::recursiveSortOnBigger(std::vector<std::pair<int, int>> pairs) {
	if (pairs.size() <= 1)
		return pairs;
	
	std::pair<int,int> oddPair;
	bool hasOdd = (pairs.size() % 2 == 1);
	if (hasOdd)
		oddPair = pairs.back();

	std::vector<std::pair<std::pair<int,int>, std::pair<int,int>>> metaPairs = makeMetaPairs(pairs);

	// Step 2: Recursively sort larger pairs
	if (metaPairs.size() > 0) {
		std::vector<std::pair<int,int>> largerPairs;
		for (auto& meta : metaPairs)
			largerPairs.push_back(meta.first);
		
		largerPairs = recursiveSortOnBigger(largerPairs);
		
		// Rebuild metaPairs in sorted order
		std::vector<std::pair<std::pair<int,int>, std::pair<int,int>>> sortedMeta;
		for (auto& sorted : largerPairs) {
			for (auto& mp : metaPairs) {
				if (mp.first.first == sorted.first && mp.first.second == sorted.second) {
					sortedMeta.push_back(mp);
					break;
				}
			}
		}
		metaPairs = sortedMeta;
	}
	
	// Step 3: Build main chain (larger pairs) and pending (smaller pairs)
	std::vector<std::pair<int,int>> mainChain;
	std::vector<std::pair<int,int>> pending;
	
	for (auto& mp : metaPairs) {
		mainChain.push_back(mp.first);
		pending.push_back(mp.second);
	}
	
	// Step 4: Insert pending pairs using Jacobsthal order
	if (!pending.empty()) {
		std::vector<size_t> order = buildJacobInsertionOrderVector(pending.size());
		
		for (size_t idx : order) {
			// Find paired max for bounded binary search
			std::pair<int,int> pairedMax;
			for (auto& mp : metaPairs) {
				if (mp.second.first == pending[idx].first && mp.second.second == pending[idx].second) {
					pairedMax = mp.first;
					break;
				}
			}
			
			// Binary search up to pairedMax
			auto maxPos = std::find(mainChain.begin(), mainChain.end(), pairedMax);
			auto left = mainChain.begin();
			auto right = maxPos;
			
			while (left < right) {
				auto mid = left + (right - left) / 2;
				__totalComparisons++;
				if (mid->first < pending[idx].first)
					left = mid + 1;
				else
					right = mid;
			}
			mainChain.insert(left, pending[idx]);
		}
	}
	
	// Step 5: Insert odd pair if exists
	if (hasOdd) {
		auto left = mainChain.begin();
		auto right = mainChain.end();
		
		while (left < right) {
			auto mid = left + (right - left) / 2;
			__totalComparisons++;
			if (mid->first < oddPair.first)
				left = mid + 1;
			else
				right = mid;
		}
		mainChain.insert(left, oddPair);
	}
	
	return mainChain;
}

// step 3: make new vector: only from the all first els from the vector of pairs
std::vector<int> PmergeMe::extractMainChainVector(const std::vector<std::pair<int, int>>& pairs) {
	std::vector<int> mainChain;

	for (auto& pair : pairs) {
		mainChain.push_back(pair.first);
	}
	return mainChain;
}

// step 4: create array of the second int from the pair
std::vector<int> PmergeMe::extractPendingElsVector(const std::vector<std::pair<int, int>>& pairs) {
	std::vector<int> result;

	for (auto&p : pairs) {
		result.push_back(p.second);
	}
	return result;
}

/**
 * step 5:
 * std::lower_bound is a standard algorithm that finds the first position in a sorted range where a given value can be inserted
 *  without violating the ordering, i.e., it returns an iterator to the first element that is not less than the specified value.
 * Insert element using binary search with bounded search up to pairedMax
 */
void PmergeMe::insertElVector(std::vector<int>& mainChain, int num, int pairedMax) {
	auto maxPos = std::find(mainChain.begin(), mainChain.end(), pairedMax);
	// bounded binary search
	auto insertPos = lowerBoundCount(mainChain.begin(), maxPos, num);
	mainChain.insert(insertPos, num);
}

/**
 * Overloaded version for odd element - searches entire main chain
 */
void PmergeMe::insertElVector(std::vector<int>& mainChain, int num) {
	auto insertPos = lowerBoundCount(mainChain.begin(), mainChain.end(), num);
	mainChain.insert(insertPos, num);
}

/**
* Jacobsthal sequence: next = previous(a) + 2 × one-before-previous(b)
		           1, 3, 5, 11, 21, 43
Fibonacci: a + b : 1, 1, 2, 3, 5
Both: Start with small numbers, use the two previous numbers
Jacobsthal multiplies one by 2
this func: tells which element to insert next.
*/
std::vector<size_t> PmergeMe::buildJacobInsertionOrderVector(size_t n) {
	std::vector<size_t> jacob;
	jacob.push_back(1);
	jacob.push_back(3);

	while (jacob.back() < n)
		jacob.push_back(jacob[jacob.size()-1] + 2 * jacob[jacob.size() - 2]);

	std::vector<size_t> order;
	size_t prev = 0;
	for (size_t j : jacob) {
		for (size_t i = std::min(j, n); i > prev; --i)
			order.push_back(i - 1);
		prev = j;
	}
	return order;
}

void PmergeMe::insertPendingVector(std::vector<int>& mainChain, const std::vector<int>& pendingChain, const std::vector<std::pair<int, int>>& pairs) {
	std::vector<size_t> order = buildJacobInsertionOrderVector(pendingChain.size());
	
	for (size_t i : order) {
		int pairedMax = getPairedMax(pairs, pendingChain[i]);
		insertElVector(mainChain, pendingChain[i], pairedMax);
	}
}

void PmergeMe::fordJohnsonSortVector() {
	__totalComparisons = 0;
	int oddEl = -1;
	std::vector<std::pair<int, int>> pairs = PmergeMe::makePairsVector(oddEl);
	recursiveSortOnBigger(pairs); // sorts pairs by first num of each pair
	std::vector<int> mainChain = extractMainChainVector(pairs); // 3 
	std::vector<int> pendingEls = extractPendingElsVector(pairs); // 4
	insertPendingVector(mainChain, pendingEls, pairs); // 5

	if (oddEl != -1)
		insertElVector(mainChain, oddEl);
	
	_arrVec = mainChain;
	std::cout << "Total comparisons: " << __totalComparisons << " (n=" << _arrVec.size() << ")\n";
}

/* returns elapsed tim im microseconds(µs)
but clock_gettime() returns in nanos.
timespec has: tv_sec, tv_nsec; tv=time_value
1 sec = 1.000.000 microseconds
1 ms = 1,000 µs, 1 µs = 1,000 ns(smallest)
*/
long PmergeMe::elapsedUs(timespec start, timespec end)
{
    return (end.tv_sec - start.tv_sec) * 1000000L +
           (end.tv_nsec - start.tv_nsec) / 1000L;
}

