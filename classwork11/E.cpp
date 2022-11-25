#include<iostream>
#include<vector>

size_t removeDuplicates(std::vector<int>& nums) {
    size_t j = 1;
    for (size_t i = 1; i < nums.size(); ++i) {
        if (nums[i] != nums[j - 1]) {
            nums[j] = nums[i];
            ++j;
        }
    }
    return j;
}

int main(){
    std::vector<int> nums = { 1,1,1,1,1 };
    size_t n = removeDuplicates(nums);
    std::cout << n << std::endl;
    for (size_t i = 0; i < n; ++i) {
        std::cout << nums[i] << " ";
    };
    return 0;
}