#include<iostream>
#include<unordered_map>
#include<vector>

std::vector<size_t> twoSum(const std::vector<int>& nums, int target) {
    std::unordered_map<int, size_t> map;
    for (size_t i = 0; i < nums.size(); ++i) {  
        if (map.find(target - nums[i]) != map.end()) { //find возвращает итератор  н а элемент, если он найдени, иначе - на end
            return{ map[target - nums[i]], i }; //в квадратных скобках у map ключ, таким образом находим значение
        }
        map[nums[i]] = i;
    }
};

int main(){
    std::vector<int> nums = { 2,7,11,15 };
    int target = 9;
    auto res = twoSum(nums, target);
    for (const auto& elem : res) {
        std::cout << elem << " ";
    }
}

