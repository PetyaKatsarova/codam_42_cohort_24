#include "PmergeMe.hpp"
#include <iostream>
#include <algorithm>

// basic set up class
PmergeMe::PmergeMe(const std::vector<int>& arrV, const std::deque<int>& arrD) : _arrVec(arrV), _arrDeq(arrD){}

PmergeMe::PmergeMe(const PmergeMe& other) : _arrVec(other._arrVec), _arrDeq(other._arrDeq){}

PmergeMe::~PmergeMe(){}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        _arrVec = other._arrVec;
        _arrDeq = other._arrDeq;
    }
    return *this;
}

// ** end basic set up class

 /**
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
	auto pos = std::lower_bound(mainChain.begin(), mainChain.end(), num); // auto will be iterator, not int
	mainChain.insert(pos, num);
}

/**
 * step 6: 
 */
void PmergeMe::insertPendingVector(std::vector<int>& mainChain, const std::vector<int>& pendingChain) {
	for (auto& p : pendingChain) {
		PmergeMe::insertElVector(mainChain, p);
	}
}

void PmergeMe::fordJohnsonSortVector() {
	int oddEl = -1;
	std::vector<std::pair<int, int>> pairs = PmergeMe::makePairsVector(oddEl); // 1
	std::cout << "Vector:   ";
	printPairs(pairs);
	sortPairsVector(pairs); // 2
	std::cout << "Sorted v: ";
	printPairs(pairs);
	std::vector<int> mainChain = extractMainChainVector(pairs); // 3 
	// printContainer(mainChain);
	std::vector<int> pendingEls = extractPendingElsVector(pairs); // 4
	// printContainer(pendingEls);
	insertPendingVector(mainChain, pendingEls); // 5

	if (oddEl != -1) {
		insertElVector(mainChain, oddEl);
	}
	_arrVec = mainChain;
	printContainer(_arrVec);
}

// deque

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

void PmergeMe::insertElDeque(std::deque<int>& mainChainD, int val)
{
    std::deque<int>::iterator pos =
        std::lower_bound(mainChainD.begin(), mainChainD.end(), val);
    mainChainD.insert(pos, val);
}

void PmergeMe::fordJohnsonSortDeque() {
    int oddEl = -1;
    std::deque<std::pair<int, int>> pairs = makePairsDeque(oddEl);
    std::sort(pairs.begin(), pairs.end());

    std::deque<int> mainChain; // make 2 arrs with first and second nums from the arr of pairs
    std::deque<int> pendingChain;
    for (auto& p : pairs) {
        mainChain.push_back(p.first);
        pendingChain.push_back(p.second);
    }

    for (auto& p : pendingChain)
        insertElDeque(mainChain, p);
    
    if (oddEl != -1)
        insertElDeque(mainChain, oddEl);
    
    _arrDeq = mainChain;
    printContainer(_arrDeq);
}

long PmergeMe::elapsedUs(timespec start, timespec end)
{
    return (end.tv_sec - start.tv_sec) * 1000000L +
           (end.tv_nsec - start.tv_nsec) / 1000L;
}

