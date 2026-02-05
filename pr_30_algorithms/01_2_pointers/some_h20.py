class Solution:
    # Brute Force Approach: O(n^2) time complexity
    def maxArea_brutForce(self, height):
        max_ar = 0
        for i in range(len(height)):
            # range(start, stop, step)
            # step -1 to go backwards
            # stop before reaching i (exclusive)
            for j in range(len(height) - 1, i, -1):
                area = (j - i) * min(height[i], height[j])
                max_ar = max(max_ar, area)
        return max_ar

    # Two Pointer Approach: O(n) time complexity, O(1) space complexity
    # Start with the widest container (left=0, right=n-1)
    # Move the pointer pointing to the shorter line inward, as moving the taller line can only decrease area
    def maxArea_twoPointer(self, height):
        max_ar = 0
        left = 0
        right = len(height) - 1
        
        while left < right:
            # Calculate current area
            width = right - left
            area = width * min(height[left], height[right])
            max_ar = max(max_ar, area)
            
            # Move the pointer pointing to shorter line
            if height[left] < height[right]:
                left += 1
            else:
                right -= 1
        
        return max_ar


if __name__ == "__main__":
    height = [1, 8, 6, 2, 5, 4, 8, 3, 7]
    sol = Solution()
    
    result_brute = sol.maxArea_brutForce(height)
    print(f"Brute Force Result: {result_brute}")
    
    result_two_ptr = sol.maxArea_twoPointer(height)
    print(f"Two Pointer Result: {result_two_ptr}")
    
    # Test with second example
    height2 = [1, 1]
    print(f"\nTest case 2 - Brute Force: {sol.maxArea_brutForce(height2)}")
    print(f"Test case 2 - Two Pointer: {sol.maxArea_twoPointer(height2)}")
