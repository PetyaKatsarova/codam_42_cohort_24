#ifndef PMERGE_ME_HEADER
#define PMERGE_ME_HEADER

#include <vector>
#include <deque>
#include <utility> // pair<int, int>
#include <ctime>
#include <iostream>

class PmergeMe {
    private:
        std::vector<int>    _arrVec;
        std::deque<int>     _arrDeq;

        // void printArrV(const std::vector<int>& arrV);
        void printPairsV(const std::vector<std::pair<int, int>>& pairs);
       
        template <typename Container>
        void printContainer(const Container& c) {
            std::cout << "[";
            for (size_t i = 0; i < c.size(); i++) {
                std::cout << c[i];
                if (i < c.size() - 1) std::cout << ", ";
            }
            std::cout << "]\n";
        };

        template<typename Container>
        void printPairs(const Container& pairs) {
            std::cout << "Pairs: ";
            for (const auto& p : pairs) { // doesnt take in int
                std::cout << "(" << p.first << ", " << p.second << ")";
            }
            std::cout << "\n";
        }



       // vectors
        std::vector<std::pair<int, int>> makePairsVector(int& oddEl);
        void sortPairsVector(std::vector<std::pair<int, int>>& pairs);
        std::vector<int> extractMainChainVector(const std::vector<std::pair<int, int>>& pairs);
        std::vector<int> extractPendingElsVector(const std::vector<std::pair<int, int>>& pairs);
        void insertElVector(std::vector<int>& mainChain, int num);
        void insertPendingVector(std::vector<int>& mainChain, const std::vector<int>& pendingChain);

        // DEQUE (mirrors vector)
        std::deque<std::pair<int, int>> makePairsDeque(int& oddEl);
        void insertElDeque(std::deque<int>& mainChainD, int val);

    public:
        PmergeMe(const std::vector<int>& arrV, const std::deque<int>& arrD);
        PmergeMe(const PmergeMe& other);
        ~PmergeMe();

        PmergeMe& operator=(const PmergeMe& other);
        void fordJohnsonSortVector();
        void fordJohnsonSortDeque();
        static long elapsedUs(timespec start, timespec end);

        
};


#endif


//there is a bug: this is wrong
// void PmergeMe::sortPairsVectorRecursive(std::vector<std::pair<int, int>>& pairs) {
//     if (pairs.size() <= 1) return;
    
//     // Extract larger elements
//     std::vector<int> largerEls;
//     for (auto& p : pairs)
//         largerEls.push_back(p.first);
    
//     // Recursively sort them
//     std::vector<int> sortedLarger = fordJohnsonSortVectorInternal(largerEls);
    
//     // Rebuild pairs in sorted order
//     std::vector<std::pair<int, int>> sortedPairs;
//     for (size_t i = 0; i < sortedLarger.size(); i++) {
//         for (auto& p : pairs) {
//             if (p.first == sortedLarger[i]) {
//                 sortedPairs.push_back(p);
//                 break;
//             }
//         }
//     }
//     pairs = sortedPairs;
// }