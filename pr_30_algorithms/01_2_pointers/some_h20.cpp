#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
   // Brute Force Approach: O(n^2) time complexity
    int maxArea_brutForce(std::vector<int>& height) {
        int maxAr = 0;
        for (int i = 0; i < height.size(); ++i) {
            for (int j = height.size()-1; j > i; --j) {
                int area = (j - i) * std::min(height[i], height[j]);
                if (area > maxAr)
                    maxAr = area;
            }
        }
        return maxAr;
    }

    // Two Pointer Approach: O(n) time complexity, O(1) space complexity
    // Start with the widest container (left=0, right=n-1)
    // Move the pointer pointing to the shorter line inward, as moving the taller line can only decrease area
    int maxArea_twoPointer(std::vector<int>& height) {
        int maxAr = 0;
        int left = 0;
        int right = height.size() - 1;
        
        while (left < right) {
            // Calculate current area
            int width = right - left;
            int area = width * std::min(height[left], height[right]);
            maxAr = std::max(maxAr, area);
            
            // Move the pointer pointing to shorter line
            if (height[left] < height[right])
                left++;
            else
                right--;
        }
        
        return maxAr;
    }
};

int main() {
    std::vector<int> height = {1,8,6,2,5,4,8,3,7};
    Solution sol;
    
    int resultBrute = sol.maxArea_brutForce(height);
    std::cout << "Brute Force Result: " << resultBrute << std::endl;
    
    int resultTwoPtr = sol.maxArea_twoPointer(height);
    std::cout << "Two Pointer Result: " << resultTwoPtr << std::endl;
    
    return 0;
}

/**
You are given an integer array height of length n. There are n 
vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).

Find two lines that together with the x-axis form a container, such that the container contains the most water.

Return the maximum amount of water a container can store.

Notice that you may not slant the container.
Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.
Example 2:

Input: height = [1,1]
Output: 1
 

Constraints:

n == height.length
2 <= n <= 105
0 <= height[i] <= 104
*/