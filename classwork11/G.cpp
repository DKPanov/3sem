#include<iostream>
#include<vector>
#include<unordered_map>
#include<map>

std::vector<std::vector<std::string>> groupByName(std::vector<std::string>& strs) {
    std::unordered_map <std::string, std::vector<std::string>> map;
    for (size_t i = 0; i < strs.size(); ++i) {
        std::map<char, size_t> anagram; //буква и скольео раз она встречаетчся в имени
        for (size_t j = 0; j < strs[i].size(); ++j) {
            ++anagram[strs[i][j]]; //по ключу jой буквы увеличили значение
        }
        std::string anagram_res;
        for (const auto& elem : anagram) {
            for (size_t j = 0; j < elem.second; ++j) {
                anagram_res += elem.first;
            }
        }
        map[anagram_res].push_back(strs[i]);
    }

    std::vector<std::vector<std::string>> answer;
    for (auto& elem : map) {
        answer.push_back(std::move(elem.second));
    }

    return answer;
}

int main(){
    std::vector<std::string> strs = { "eat","tea","tan","ate","nat","bat" };
    auto result = groupByName(strs);
    for (const auto& elem : result) {
        for (const auto& str : elem) {
            std::cout << str << " ";
        }
        std::cout << std::endl;
    }
}