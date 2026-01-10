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
        size_t              _insertCounter;
        size_t              _compareCounter;
       
        template<typename Container>
        void printPairs(const Container& pairs) {
            std::cout << "Pairs: ";
            for (const auto& p : pairs) {
                std::cout << "(" << p.first << ", " << p.second << ")";
            }
            std::cout << "\n";
        }

        // manual binary search(=lower_bound) in order to count comparrisons on sorted arr, runs in O(log n) comparissons
        template<typename It, typename T>
        It lowerBoundCount(It begin, It end, T val) {
            It left = begin;
            It right = end;

            while (left < right) {
                It mid = left+(right-left)/2;
                _compareCounter++;
                if (*mid < val)
                    left = mid + 1;
                else
                    right = mid;
            }
            return left;
        }

        void                                validateToken(const std::string& s);
       // VECTOR
        std::vector<std::pair<int, int>>    makePairsVector(int& oddEl);
        void                                sortPairsVector(std::vector<std::pair<int, int>>& pairs);
        std::vector<int>                    extractMainChainVector(const std::vector<std::pair<int, int>>& pairs);
        std::vector<int>                    extractPendingElsVector(const std::vector<std::pair<int, int>>& pairs);
        int                                 getPairedMax(std::vector<std::pair<int, int>> pairedV, int lowerNum);
        std::vector<size_t>                 buildJacobInsertionOrderVector(size_t n);
        void                                insertElVector(std::vector<int>& mainChain, int num, int pairedMax);
        void                                insertElVector(std::vector<int>& mainChain, int num);
        void                                insertPendingVector(std::vector<int>& mainChain, const std::vector<int>& pendingChain, const std::vector<std::pair<int, int>>& pairs);

        // DEQUE
        std::deque<size_t>                  buildJacobInsertionOrderDeque(size_t n);
        std::deque<std::pair<int, int>>     makePairsDeque(int& oddEl);
        void                                insertElDeque(std::deque<int>& mainChainD, int val);

    public:
        PmergeMe(const std::vector<int> arrV, const std::deque<int> arrD);
        PmergeMe(const PmergeMe& other);
        ~PmergeMe();

        PmergeMe&                           operator=(const PmergeMe& other);
        void                                setArrV(const std::string& input);
        void                                setArrD(const std::string& input);
        const std::vector<int>&             getArrV() const;
        const std::deque<int>&              getArrD() const;

        std::string                         joinArgs(int argc, char* argv[]);
        void                                fordJohnsonSortVector();
        void                                fordJohnsonSortDeque();
        static long                         elapsedUs(timespec start, timespec end);      
        
        template <typename Container>
        void printContainer(const Container& c) {
            for (size_t i = 0; i < c.size(); i++) {
                std::cout << c[i];
                if (i < c.size() - 1) std::cout << " ";
            }
            std::cout << "\n";
        };
};

#endif
