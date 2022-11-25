#include<iostream>
#include<vector>
#include<unordered_map>

std::vector<int> majorityElement(std::vector<int>& nums, int k) {
    
    std::vector<int> answer;
    
    //элемент, встречающийся > n/2 раз
    int number = nums[0];
    int count = 1;
    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] == number) {
            ++count;
            continue;
        }
        if (count > 0) {
            --count;
        }
        else {
            number = nums[i];
            count = 1;
        } 
    }
    answer.push_back(number);

    //элемент, встречающийся > n/3 раз
    int number1 = nums[0];
    int number2;
    int count1 = 1;
    int i = 1;
    for (; i < nums.size(); ++i) {
        if (nums[i] != number1) {
            number2 = nums[i];
            break;
        }
        ++count1;
    }
    int count2 = 1;
    ++i;
    for (; i < nums.size(); ++i) {
        if (nums[i] == number1) {
            ++count1;
            continue;
        }
        if (nums[i] == number2) {
            ++count2;
            continue;
        }
        if (count1 == 0) {
            number1 = nums[i];
            count1 = 1;
            continue;
        }
        if (count2 == 0) {
            number2 = nums[i];
            count2 = 1;
            continue;
        }
        --count1;
        --count2;
    }
    if (count1 > count2) {
        answer.push_back(number1);
    }
    else {
        answer.push_back(number2);
    }



    //элемент, встречающийся > n/k раз
    std::vector < std::pair<int, int> > vec(k-1);
    for (int i = 0; i < k - 1; ++i) {
        vec[i].first = nums[i];
        vec[i].second = 1;
    }
    for (int i = k - 1; i < nums.size(); ++i) {
        bool found = false;
        for (int j = 0; j < k - 1; ++j) {
            if (vec[j].first == nums[i]) {
                ++vec[j].second;
                found = true;
                break;
            }
        }
        if (found){
            continue;
        }
        for (int j = 0; j < k - 1; ++j) {
            if (vec[j].second == 0) {
                vec[j].first = nums[i];
                vec[j].second = 1;
                found = true;
                break;
            }
        }
        if (found) {
            continue;
        }
        for (int j = 0; j < k - 1; ++j) {
            --vec[j].second;
        }

    }
    int index = 0;
    for (int i = 0; i < k - 1; ++i) {
        if (vec[i].second > vec[index].second) {
            index = i;
        }
    }
    answer.push_back(vec[index].first);
    
    return answer;
}



int main(){
    std::vector<int> nums1 = { 1,1,1,2,1,2,1,2,1,4 }; //2
    std::vector<int> nums2 = { 2,5,3,2,1,6,1,2,9,2 }; //3
    std::vector<int> nums3 = { 5,5,5,6,5,6,1,7,9,7 }; //4

    auto result = majorityElement(nums1, 2);
    for (int i = 0; i < result.size(); ++i) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;

    result = majorityElement(nums2, 3);
    for (int i = 0; i < result.size(); ++i) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;

    result = majorityElement(nums3, 4);
    for (int i = 0; i < result.size(); ++i) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;



}

