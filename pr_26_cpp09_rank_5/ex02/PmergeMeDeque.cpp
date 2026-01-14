#include "PmergeMe.hpp"
#include <algorithm>

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

void PmergeMe::insertElDeque(std::deque<int>& mainChainD, int val, int pairedMax)
{
	auto maxPos = std::find(mainChainD.begin(), mainChainD.end(), pairedMax);
	auto insertPos = std::lower_bound(mainChainD.begin(), maxPos, val);
    mainChainD.insert(insertPos, val);
}

/**
 * Overloaded version for odd element - searches entire deque main chain
 */
void PmergeMe::insertElDeque(std::deque<int>& mainChainD, int val) {
	auto insertPos = std::lower_bound(mainChainD.begin(), mainChainD.end(), val);
	mainChainD.insert(insertPos, val);
}

// sort() O(n log n) guranteed, uses diff sorts for diff cases
void PmergeMe::fordJohnsonSortDeque() {
    int								oddEl = -1;
    std::deque<std::pair<int, int>> pairs = makePairsDeque(oddEl);
    std::sort(pairs.begin(), pairs.end(), [](const auto& a, const auto& b) {
		return a.first < b.first;
	});

    std::deque<int> mainChain;
    std::deque<int> pendingChain;
    for (auto& p : pairs) {
        mainChain.push_back(p.first);
        pendingChain.push_back(p.second);
    }

	std::deque<size_t> order = buildJacobInsertionOrderDeque(pendingChain.size());
    for (size_t i : order) {
		int pairedMax = getPairedMax(pairs, pendingChain[i]);
		insertElDeque(mainChain, pendingChain[i], pairedMax);
	}
    
    if (oddEl != -1)
        insertElDeque(mainChain, oddEl);
    
    _arrDeq = mainChain;
}