#include<unordered_map>
#include<iostream>

int main(){
    std::unordered_map<uint64_t, uint64_t> map; //ключ - ответ; значение - сколько кроликов дали такой ответ
    uint64_t n;
    std::cin >> n; //кол-во ответов
    for (int i = 0; i < n; ++i) {
        uint64_t answer;
        std::cin >> answer;
        ++map[answer]; //еслт пары ключ/значение не было, она создастся со значением 0
    }
    uint64_t result = 0;
    for (const auto& elem : map) {
        if(elem.second % (elem.first + 1) == 0){
            result += elem.first + 1;
        }
        else {
            result += (elem.second/(elem.first + 1)) * (elem.first + 1) + elem.first + 1;
        }
    }
    std::cout << result;
}
