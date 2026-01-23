/*
================================================================================
                    TWO POINTERS ALGORITHM TUTORIAL - C++
================================================================================

WHAT IS THE TWO POINTERS TECHNIQUE?
-----------------------------------
Two pointers is an efficient algorithmic pattern that uses two pointers to 
iterate through a data structure (typically arrays/strings) to solve problems
in linear time instead of nested loops (quadratic time).

WHEN TO USE TWO POINTERS?
--------------------------
✓ Searching for pairs in a sorted array
✓ Removing duplicates from sorted arrays
✓ Reversing arrays/strings
✓ Finding subarrays/substrings with specific properties
✓ Merging sorted arrays
✓ Partitioning arrays (like in quicksort)

TWO MAIN PATTERNS:
------------------
1. OPPOSITE DIRECTION: Pointers move towards each other (start & end)
2. SAME DIRECTION: Both pointers move in same direction (fast & slow)

================================================================================
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>

using namespace std;

/* bool std::isalnum(char); tolower() from <cctype> or:  <string> or <algorithm> which internally include <cctype>
Non-zero (true) if the character is:
A letter: a-z or A-Z
A digit: 0-9
Zero (false) for anything else:
Spaces:  
Punctuation: ., ,, !, ?, ;, :
Special characters: @, #, $, %, &, etc.
*/

/*
================================================================================
PATTERN 1: OPPOSITE DIRECTION (LEFT & RIGHT POINTERS)
================================================================================
*/

// EXAMPLE 1: Two Sum in Sorted Array
// Problem: Find two numbers that add up to target
// Time Complexity: O(n) - single pass through array
// Space Complexity: O(1) - only two pointers used
vector<int> twoSum(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    
    while (left < right) {
        int sum = nums[left] + nums[right];
        
        if (sum == target) {
            return {left, right};  // Found!
        }
        else if (sum < target) {
            left++;   // Need larger sum, move left pointer right
        }
        else {
            right--;  // Need smaller sum, move right pointer left
        }
    }
    
    return {-1, -1};  // Not found
}

// EXAMPLE 2: Reverse String
// Time Complexity: O(n) - visit each element once
// Space Complexity: O(1) - in-place modification
void reverseString(string& s) {
    int left = 0;
    int right = s.length() - 1;
    
    while (left < right) {
        swap(s[left], s[right]);
        left++;
        right--;
    }
}

// EXAMPLE 3: Valid Palindrome
// Time Complexity: O(n)
// Space Complexity: O(1)
bool isPalindrome(string s) {
    int left = 0;
    int right = s.length() - 1;
    
    while (left < right) {
        // Skip non-alphanumeric characters
        //while (left < right && !isalnum(s[left])) left++;
        //while (left < right && !isalnum(s[right])) right--;
        
        if (tolower(s[left]) != tolower(s[right])) {
            return false;
        }
        
        left++;
        right--;
    }
    
    return true;
}

// EXAMPLE 4: Container With Most Water
// Time Complexity: O(n)
// Space Complexity: O(1)
int maxArea(vector<int>& height) {
    int left = 0;
    int right = height.size() - 1;
    int maxWater = 0;
    
    while (left < right) {
        // Calculate area with current pointers
        int width = right - left;
        int h = min(height[left], height[right]);
        maxWater = max(maxWater, width * h);
        
        // Move the pointer with smaller height
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }
    
    return maxWater;
}

/*
================================================================================
PATTERN 2: SAME DIRECTION (FAST & SLOW POINTERS)
================================================================================
*/

// EXAMPLE 5: Remove Duplicates from Sorted Array
// Time Complexity: O(n) - single pass
// Space Complexity: O(1) - in-place modification
int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;
    
    int slow = 0;  // Position for next unique element
    
    for (int fast = 1; fast < nums.size(); fast++) {
        if (nums[fast] != nums[slow]) {
            slow++;
            nums[slow] = nums[fast];
        }
    }
    
    return slow + 1;  // Length of unique elements
}

// EXAMPLE 6: Remove Element
// Time Complexity: O(n)
// Space Complexity: O(1)
int removeElement(vector<int>& nums, int val) {
    int slow = 0;
    
    for (int fast = 0; fast < nums.size(); fast++) {
        if (nums[fast] != val) {
            nums[slow] = nums[fast];
            slow++;
        }
    }
    
    return slow;
}

// EXAMPLE 7: Move Zeroes
// Time Complexity: O(n)
// Space Complexity: O(1)
void moveZeroes(vector<int>& nums) {
    int slow = 0;  // Position for next non-zero element
    
    // Move all non-zero elements to front
    for (int fast = 0; fast < nums.size(); fast++) {
        if (nums[fast] != 0) {
            nums[slow] = nums[fast];
            slow++;
        }
    }
    
    // Fill remaining positions with zeros
    while (slow < nums.size()) {
        nums[slow] = 0;
        slow++;
    }
}

/*
================================================================================
PATTERN 3: SLIDING WINDOW (SPECIAL CASE OF TWO POINTERS)
================================================================================
*/

// EXAMPLE 8: Longest Substring Without Repeating Characters
// Time Complexity: O(n) - each character visited at most twice
// Space Complexity: O(min(n, m)) where m is charset size
int lengthOfLongestSubstring(string s) {
    unordered_set<char> charSet;
    int left = 0;
    int maxLen = 0;
    
    for (int right = 0; right < s.length(); right++) {
        // Shrink window until no duplicates
        while (charSet.count(s[right])) {
            charSet.erase(s[left]);
            left++;
        }
        
        charSet.insert(s[right]);
        maxLen = max(maxLen, right - left + 1);
    }
    
    return maxLen;
}

// EXAMPLE 9: Minimum Size Subarray Sum
// Time Complexity: O(n)
// Space Complexity: O(1)
//int minSubArrayLen(int target, vector<int>& nums) {
//    int left = 0;
//    int sum = 0;
//    int minLen = INT_MAX;
    
//    for (int right = 0; right < nums.size(); right++) {
//        sum += nums[right];
        
//        // Shrink window while sum >= target
//        while (sum >= target) {
//            minLen = min(minLen, right - left + 1);
//            sum -= nums[left];
//            left++;
//        }
//    }
    
//    return minLen == INT_MAX ? 0 : minLen;
//}

/*
================================================================================
PATTERN 4: PARTITION (LIKE QUICKSORT)
================================================================================
*/

// EXAMPLE 10: Sort Colors (Dutch National Flag)
// Time Complexity: O(n) - single pass
// Space Complexity: O(1)
void sortColors(vector<int>& nums) {
    int left = 0;      // Boundary for 0s
    int right = nums.size() - 1;  // Boundary for 2s
    int i = 0;
    
    while (i <= right) {
        if (nums[i] == 0) {
            swap(nums[i], nums[left]);
            left++;
            i++;
        }
        else if (nums[i] == 2) {
            swap(nums[i], nums[right]);
            right--;
            // Don't increment i - need to check swapped element
        }
        else {
            i++;  // nums[i] == 1
        }
    }
}

/*
================================================================================
COMPLEXITY ANALYSIS SUMMARY
================================================================================

TIME COMPLEXITY:
----------------
✓ Two Pointers: O(n) - Linear time
  - Each element visited at most once (or twice in sliding window)
  - Much better than nested loops O(n²)
  
✓ Why O(n)?
  - Both pointers traverse the array at most once
  - Even if one pointer backtracks (sliding window), total operations = O(n)

SPACE COMPLEXITY:
-----------------
✓ Usually O(1) - Constant space
  - Only store pointer variables
  - In-place modifications when possible
  
✓ Exceptions:
  - O(k) when using hash table for sliding window
  - Still much better than O(n) for creating new arrays

COMPARISON WITH BRUTE FORCE:
-----------------------------
Problem: Find pair that sums to target

Brute Force (Nested Loops):
  for i in range(n):
    for j in range(i+1, n):
      if nums[i] + nums[j] == target: return
  Time: O(n²), Space: O(1)

Two Pointers (After Sorting):
  while left < right:
    if sum == target: return
  Time: O(n log n) for sort + O(n) = O(n log n)
  Space: O(1)

Two Pointers (Already Sorted):
  while left < right:
    if sum == target: return
  Time: O(n), Space: O(1)

================================================================================
WHEN TWO POINTERS WON'T WORK:
================================================================================
✗ Unsorted array (unless you sort first, adding O(n log n))
✗ Need to maintain order strictly
✗ Problems requiring backtracking
✗ Problems needing all possible combinations

================================================================================
*/

// Test functions
void testTwoPointers() {
    cout << "=== TWO POINTERS ALGORITHM TESTS ===\n\n";
    
    // Test 1: Two Sum
    vector<int> arr1 = {1, 2, 3, 4, 5, 6};
    vector<int> result = twoSum(arr1, 9);
    cout << "Two Sum (target=9): [" << result[0] << ", " << result[1] << "]\n";
    
    // Test 2: Reverse String
    string s1 = "hello";
    reverseString(s1);
    cout << "Reversed: " << s1 << "\n";
    
    // Test 3: Palindrome
    string s2 = "A man, a plan, a canal: Panama";
    cout << "Is palindrome: " << (isPalindrome(s2) ? "Yes" : "No") << "\n";
    
    // Test 4: Remove Duplicates
    vector<int> arr2 = {1, 1, 2, 2, 3, 4, 4, 5};
    int len = removeDuplicates(arr2);
    cout << "Unique elements: " << len << " -> [";
    for (int i = 0; i < len; i++) {
        cout << arr2[i] << (i < len-1 ? ", " : "");
    }
    cout << "]\n";
    
    // Test 5: Longest Substring
    string s3 = "abcabcbb";
    cout << "Longest substring without repeating: " << lengthOfLongestSubstring(s3) << "\n";
    
    cout << "\n=== ALL TESTS COMPLETED ===\n";
}

int main() {
    //testTwoPointers();

	std::cout << "isPalindrome('blalb') = " << isPalindrome(".2blalb2.") << std::endl;
    return 0;
}

/*
================================================================================
KEY TAKEAWAYS:
================================================================================

1. TWO POINTERS reduces O(n²) to O(n) in many cases
2. Works best on SORTED data or when order doesn't matter
3. Two main patterns:
   - Opposite direction (left & right)
   - Same direction (fast & slow)
4. Common applications:
   - Searching pairs
   - Removing elements
   - Reversing
   - Sliding windows
5. Always O(1) space (except when using auxiliary data structures)

PRACTICE PROBLEMS:
------------------
1. Three Sum (extension of Two Sum)
2. Trapping Rain Water
3. Remove Nth Node From End of List
4. Linked List Cycle Detection
5. Merge Sorted Arrays
6. Partition List
7. String Compression
8. Longest Mountain in Array

================================================================================
*/
