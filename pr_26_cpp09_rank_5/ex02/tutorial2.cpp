#include <iostream>
#include <vector>
#include <climits>
#include <cmath> // log2()

int comparisons = 0;  // Global variable to track comparisons

// Merge function: Merges two sorted subarrays and counts comparisons
std::vector<int> mergeAndCount(const std::vector<int>& left, const std::vector<int>& right) {
    std::vector<int> result;
    int i = 0, j = 0;

    while (i < left.size() && j < right.size()) {
        comparisons++;
        if (left[i] < right[j]) {
            result.push_back(left[i]);
            i++;
        } else {
            result.push_back(right[j]);
            j++;
        }
    }

    // Add remaining elements if any
    while (i < left.size()) {
        result.push_back(left[i]);
        i++;
    }
    while (j < right.size()) {
        result.push_back(right[j]);
        j++;
    }

    return result;
}

// Function to split the array into pairs and merge them
std::vector<int> fordJohnsonMergeSort(std::vector<int>& arr) {
    // If the array has only one element, it's already sorted
    if (arr.size() <= 1) {
        return arr;
    }

    // Split the array into pairs (for Ford-Johnson)
    std::vector<std::vector<int>> pairs;
    for (int i = 0; i < arr.size(); i += 2) {
        if (i + 1 < arr.size()) {
            // Pair two elements and sort them individually (merge-insertion)
            std::vector<int> pair = {arr[i], arr[i + 1]};
            if (pair[0] > pair[1]) std::swap(pair[0], pair[1]);  // Ensure pair is sorted
            pairs.push_back(pair);
        } else {
            // Single element left (if array size is odd)
            pairs.push_back({arr[i]});
        }
    }

    // Now we merge pairs together in a smart way to reduce comparisons
    while (pairs.size() > 1) {
        std::vector<std::vector<int>> newPairs;
        for (int i = 0; i < pairs.size(); i += 2) {
            if (i + 1 < pairs.size()) {
                newPairs.push_back(mergeAndCount(pairs[i], pairs[i + 1]));
            } else {
                newPairs.push_back(pairs[i]);
            }
        }
        pairs = newPairs;
    }

    return pairs[0];  // The final sorted result is the only pair left
}

int main() {
    std::vector<int> arr = {2, 11, 6, 15, 0, 17, 8, 16, 3, 10, 9, 18, 1, 21, 14, 19, 5, 12, 4, 20, 7, 13};
    
    // Print the original array
    std::cout << "Original array (" << arr.size() << " elements):\n";
    for (int num : arr) std::cout << num << " ";
    std::cout << std::endl;

    // Perform the sorting
    std::vector<int> sortedArr = fordJohnsonMergeSort(arr);

    // Print the sorted array
    std::cout << "Sorted array:\n";
    for (int num : sortedArr) std::cout << num << " ";
    std::cout << std::endl;

    // Print the number of comparisons
    std::cout << "Comparisons used: " << comparisons << std::endl;

    // Define the maximum allowed comparisons (based on array size)
    int maxAllowedComparisons = 2 * arr.size() * log2(arr.size());
    std::cout << "Maximum allowed: " << maxAllowedComparisons << std::endl;

    // Check if the array is sorted correctly
    bool isSorted = true;
    for (size_t i = 1; i < sortedArr.size(); ++i) {
        if (sortedArr[i] < sortedArr[i - 1]) {
            isSorted = false;
            break;
        }
    }
    std::cout << "Array is sorted: " << (isSorted ? "YES" : "NO") << std::endl;

    return 0;
}