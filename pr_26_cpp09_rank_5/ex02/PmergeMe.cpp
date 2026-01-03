#include "PmergeMe.hpp"
#include <iostream>
#include <algorithm>
#include <sstream> // std::istringstream

// basic set up class
PmergeMe::PmergeMe(const std::vector<int>& arrV, const std::deque<int>& arrD) : _arrVec(arrV), _arrDeq(arrD), _insertCounter(0), _compareCounter(0) {}

PmergeMe::PmergeMe(const PmergeMe& other) : _arrVec(other._arrVec), _arrDeq(other._arrDeq){}

PmergeMe::~PmergeMe(){}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        _arrVec = other._arrVec;
        _arrDeq = other._arrDeq;
		_insertCounter = other._insertCounter;
		_compareCounter = other._compareCounter;
    }
    return *this;
}

const std::vector<int>& PmergeMe::getArrV() const { return _arrVec; }

const std::deque<int>& PmergeMe::getArrD() const { return _arrDeq; }

void PmergeMe::setArrV(const std::string& input) {
	_arrVec.clear();

	std::istringstream iss(input);
	std::string token;

	while (iss >> token) {
		for (char c : token) {
			if (!std::isdigit(c) && c != '+') { // no negative nums allowed
				throw std::invalid_argument("Invalid input");
			}
		}

		try {
			int num = std::stoi(token);
			_arrVec.push_back(num);
		} catch (const std::out_of_range&) {
			throw std::out_of_range("Invalid input: int out of range");
		} catch (const std::invalid_argument& e) {
			throw std::invalid_argument("Invalid input: cant convert to int");
		}
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
		for (char c : token) {
			if (!std::isdigit(c) && c != '+') { // no negative nums allowed
				throw std::invalid_argument("Invalid input");
			}
		}

		try {
			int num = std::stoi(token);
			_arrDeq.push_back(num);
		} catch (const std::out_of_range&) {
			throw std::out_of_range("Invalid input: int out of range");
		} catch (const std::invalid_argument& e) {
			throw std::invalid_argument("Invalid input: cant convert to int");
		}
	}
	if (_arrDeq.empty()) {
		throw std::invalid_argument("Invalid input: no nums provided");
	}
}

// ** end basic set up class

 /** VECTOR **
  * step 1: make pairs of each consequtive elements and
  * place on first place the bigger num
  */
std::vector<std::pair<int, int>> PmergeMe::makePairsVector(int& oddEl) {
			std::vector<std::pair<int, int>> pairs;

	for (size_t i = 0; i < _arrVec.size() - 1; i += 2) {
		if (_arrVec[i] < _arrVec[i+1]) {
			pairs.push_back({_arrVec[i+1], _arrVec[i]}); 
		} else {
			pairs.push_back({_arrVec[i], _arrVec[i+1]});
		}
	}
	oddEl = (_arrVec.size() % 2 == 1 ? _arrVec.back() : -1); // save odd el if _arrV has odd len
	return pairs;
}

// step 2: sort pairs by their first(larger) el
void PmergeMe::sortPairsVector(std::vector<std::pair<int, int>>& pairs) {
	std::sort(pairs.begin(), pairs.end());
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
 * Insert element using binary search
 */
void PmergeMe::insertElVector(std::vector<int>& mainChain, int num) {
	// auto pos = std::lower_bound(mainChain.begin(), mainChain.end(), num); // auto will be iterator, not int
	auto pos = lowerBoundCount(mainChain.begin(), mainChain.end(), num);
	mainChain.insert(pos, num);
	_insertCounter++;
}

/**
 * step 6: 
 */
void PmergeMe::insertPendingVector(std::vector<int>& mainChain, const std::vector<int>& pendingChain) {
	std::vector<size_t> order = buildJacobInsertionOrderVector(pendingChain.size());
	
	// std::cout << "Jackobsthal seq:\n";
	for (size_t i : order) {
		// std::cout << i << ", ";
		insertElVector(mainChain, pendingChain[i]);
	}
	// std::cout << "\n";
}

/**
* Jacobsthal sequence: next = previous(a) + 2 × one-before-previous(b)
		           1, 3, 5, 11, 21, 43
Fibonacci: a + b : 1, 1, 2, 3, 5
Both: Start with small numbers, use the two previous numbers
Jacobsthal multiplies one by 2
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

void PmergeMe::fordJohnsonSortVector() {
	_insertCounter = 0; // clear from prev run
	_compareCounter = 0;
	int oddEl = -1;
	std::vector<std::pair<int, int>> pairs = PmergeMe::makePairsVector(oddEl); // 1
	// std::cout << "Vector:   ";
	// printPairs(pairs);
	sortPairsVector(pairs); // 2
	// std::cout << "Sorted v: ";
	// printPairs(pairs);
	std::vector<int> mainChain = extractMainChainVector(pairs); // 3 
	// printContainer(mainChain);
	std::vector<int> pendingEls = extractPendingElsVector(pairs); // 4
	// printContainer(pendingEls);
	insertPendingVector(mainChain, pendingEls); // 5

	if (oddEl != -1)
		insertElVector(mainChain, oddEl);
	
	_arrVec = mainChain;
	// std::cout << "insertions  : " << _insertCounter << "\n";
	// std::cout << "comparisons : " << _compareCounter << "\n";
}

// ** DEQUE **

std::deque<std::pair<int, int>> PmergeMe::makePairsDeque(int& oddEl) {
    std::deque<std::pair<int, int>> pairs;

    for (size_t i = 0; i < _arrDeq.size() - 1; i += 2) {
        if (_arrDeq[i] < _arrDeq[i + 1])
            pairs.push_back({_arrDeq[i+1], _arrDeq[i]});
        else
            pairs.push_back({_arrDeq[i], _arrDeq[i+1]});
    }
	oddEl = (_arrDeq.size() % 2 == 1 ? _arrDeq.back() : -1);
	return pairs;
}

std::deque<size_t> PmergeMe::buildJacobInsertionOrderDeque(size_t n) {
	std::deque<size_t> jacob;
	jacob.push_back(1);
	jacob.push_back(3);

	while (jacob.back() < n)
		jacob.push_back(jacob[jacob.size()-1] + 2 * jacob[jacob.size() - 2]);

	std::deque<size_t> order;
	size_t prev = 0;
	for (size_t j : jacob) {
		for (size_t i = std::min(j, n); i > prev; --i)
			order.push_back(i - 1);
		prev = j;
	}
	return order;
}

void PmergeMe::insertElDeque(std::deque<int>& mainChainD, int val)
{
    std::deque<int>::iterator pos = lowerBoundCount(mainChainD.begin(), mainChainD.end(), val);
        // std::lower_bound(mainChainD.begin(), mainChainD.end(), val);
    mainChainD.insert(pos, val);
	_insertCounter++;
}

void PmergeMe::fordJohnsonSortDeque() {
    int								oddEl = -1;
    std::deque<std::pair<int, int>> pairs = makePairsDeque(oddEl);
    std::sort(pairs.begin(), pairs.end());

    std::deque<int> mainChain;
    std::deque<int> pendingChain;
    for (auto& p : pairs) {
        mainChain.push_back(p.first);
        pendingChain.push_back(p.second);
    }

	std::deque<size_t> order = buildJacobInsertionOrderDeque(pendingChain.size());
    for (size_t i : order)
        insertElDeque(mainChain, pendingChain[i]);
    
    if (oddEl != -1)
        insertElDeque(mainChain, oddEl);
    
    _arrDeq = mainChain;
}

long PmergeMe::elapsedUs(timespec start, timespec end)
{
    return (end.tv_sec - start.tv_sec) * 1000000L +
           (end.tv_nsec - start.tv_nsec) / 1000L;
}

