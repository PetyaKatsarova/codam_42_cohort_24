#include <iostream>
#include <vector>

using namespace std;

// Remove duplicates from sorted array
// Two-pointer approach
int removeDuplicates(vector<int>& arr) {
    // Handle empty array
    if (arr.empty()) {
        return 0;
    }

    // slow: position where next unique element goes
    // fast: scanning through array to find unique elements
    int slow = 0;

    // Start fast at 1 because arr[0] is already in place
    for (int fast = 1; fast < arr.size(); fast++) {
        // Found a new unique element
        if (arr[fast] != arr[slow]) {
            slow++;              // move slow to next position
            arr[slow] = arr[fast]; // place unique element
        }
    }

    // slow is index of last unique element
    // length of unique portion is slow + 1
    return slow + 1;
}

class Solution {
public:
    string removeDuplicateLetters(string s) {
        
    }
};

/**
rmv dup from sorted arr leetcode
Given a string s, remove duplicate letters so that every letter appears once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.
*/