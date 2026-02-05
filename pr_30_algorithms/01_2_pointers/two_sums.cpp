#include <iostream>


class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int left_i = 0;
        int right_i = nums.size() - 1;
        while (left_i < right_i) {
            if (nums[left_i] + num[right_i] == target)
                return {nums[left_i], num[right_i]};
            if (nums[left_i] + num[right_i] > target)
                left_i++;
            else
                right_i--;
        }
        return {-1, -1};
    }
};

int main() {
    int[] arr = {1,2,3,4,5,6,7};
    int[] result = 
    for (int i = 0; i < 2; i++) {
        std::cout << 
    }
    std::cout << std::endl;
}