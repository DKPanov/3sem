#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>

std::vector<std::string> findRepeatedDnaSequences(const std::string& s) {
    if (s.size() < 10) {
        return {};
    }
    std::unordered_map<std::string, int> map;
    for (size_t i = 0; i < s.size() - 9; ++i) {
        auto sub = s.substr(i, 10);
        ++map[sub];
    }
    std::vector<std::string> answer;
    for (const auto& elem : map) {
        if (elem.second > 1) {
            answer.push_back(elem.first);
        }
    }

    return answer;
    
}

int main(){

    std::string s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
    auto result = findRepeatedDnaSequences(s);
    for (const auto& elem : result) {
        std::cout << elem << " ";
    }
}

