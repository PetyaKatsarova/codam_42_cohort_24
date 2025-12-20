/**
 * our program must be able to use a positive integer sequence as an argument.
• Your program must use the merge-insert sort algorithm to sort the positive integer
sequence.
To clarify, yes, you need to use the Ford-Johnson algorithm.
(source: Art Of Computer Programming, Vol.3. Merge Insertion,
Page 184.)
• If an error occurs during program execution, an error message should be displayed
on the standard error.
You must use at least two different containers in your code to
validate this exercise. Your program must be able to handle at
least 3000 different integers.
It is strongly advised to implement your algorithm for each container
and thus to avoid using a generic function.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

void printArr(const std::vector<int>& arr, const std::string& label = "") {
    if (!label.empty()) {
        std::cout << label << ": ";
    }
    std::cout << "[";
    for (size_t i = 0; i < arr.size(); i++) {
        std::cout << arr[i];
        if (i < arr.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
}

void printPairs(const std::vector<std::pair<int, int>>& pairs) {
    std::cout << "Pairs: ";
    for (const auto& p : pairs) {
        std::cout << "(" << p.first << ", " << p.second << ") ";
    }
    std::cout << "\n";
}

// Step 1: Create pairs with larger element first
std::vector<std::pair<int, int>> makePairs(const std::vector<int>& arr, int& oddElement) {
    std::vector<std::pair<int, int>> pairs;
    
    // Create pairs, ensuring larger element is first
    for (size_t i = 0; i + 1 < arr.size(); i += 2) {
        if (arr[i] < arr[i + 1]) {
            pairs.push_back({arr[i + 1], arr[i]});  // larger first
        } else {
            pairs.push_back({arr[i], arr[i + 1]});
        }
    }
    
    // Save odd element if array has odd length
    oddElement = (arr.size() % 2 == 1) ? arr.back() : -1;
    
    return pairs;
}

// Step 2: Sort pairs by their first (larger) element
void sortPairs(std::vector<std::pair<int, int>>& pairs) {
    std::sort(pairs.begin(), pairs.end());
}

// Step 3: Extract main chain (all larger elements)
std::vector<int> createMainChain(const std::vector<std::pair<int, int>>& pairs) {
    std::vector<int> mainChain;
    for (const auto& p : pairs) {
        mainChain.push_back(p.first);
    }
    return mainChain;
}

// Step 4: Extract pending elements (all smaller elements)
std::vector<int> createPending(const std::vector<std::pair<int, int>>& pairs) {
    std::vector<int> pending;
    for (const auto& p : pairs) {
        pending.push_back(p.second);
    }
    return pending;
}

// Step 5: Insert element using binary search
void insertElement(std::vector<int>& mainChain, int element) {
    auto pos = std::lower_bound(mainChain.begin(), mainChain.end(), element);
    mainChain.insert(pos, element);
}

// Step 6: Insert all pending elements
void insertPending(std::vector<int>& mainChain, const std::vector<int>& pending) {
    for (int num : pending) {
        insertElement(mainChain, num);
        std::cout << "Inserted " << num << " → ";
        printArr(mainChain);
    }
}

// Main Ford-Johnson Sort Algorithm
void fordJohnsonSort(std::vector<int>& arr) {
    if (arr.size() <= 1) {
        return;
    }
    
    std::cout << "\n=== Ford-Johnson Sort ===" << std::endl;
    
    // Step 1: Make pairs
    int oddElement = -1;
    std::vector<std::pair<int, int>> pairs = makePairs(arr, oddElement);
    std::cout << "\nStep 1: ";
    printPairs(pairs);
    
    // Step 2: Sort pairs by first element
    sortPairs(pairs);
    std::cout << "Step 2 (sorted): ";
    printPairs(pairs);
    
    // Step 3: Create main chain
    std::vector<int> mainChain = createMainChain(pairs);
    std::cout << "Step 3: ";
    printArr(mainChain, "Main Chain");
    
    // Step 4: Get pending elements
    std::vector<int> pending = createPending(pairs);
    std::cout << "Step 4: ";
    printArr(pending, "Pending");
    
    // Step 5: Insert pending elements
    std::cout << "\nStep 5: Inserting pending elements\n";
    insertPending(mainChain, pending);
    
    // Insert odd element if exists
    if (oddElement != -1) {
        std::cout << "Inserting odd element: " << oddElement << std::endl;
        insertElement(mainChain, oddElement);
    }
    
    arr = mainChain;
}

// c++ main.cpp && ./a.out
int main() {
    std::vector<int> arr = {1, 3, 442, 3, 43, 8};
    
    printArr(arr, "Original");
    
    fordJohnsonSort(arr);
    
    printArr(arr, "\nFinal Sorted");
    
    return 0;
}