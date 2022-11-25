#include<unordered_set>
#include<iostream>
#include<random>

class RandomizedSet {
private: std::unordered_set<int> set_;
public:
    RandomizedSet() = default;

    bool insert(int val) {
        if (set_.find(val) == set_.end()) {
            set_.insert(val);
            return true;
        }
        return false;
    };

    bool remove(int val) {
        if (set_.find(val) != set_.end()) {
            set_.erase(val);
            return true;
        }
        return false;
    }

    int getRandom() {
        std::random_device rd;
        size_t index = rd() % set_.size();
        size_t i = 0;
        for (const auto& elem : set_) {
            if (i == index) {
                return elem;
            }
            ++i;
        }
    };

};

int main(){
    RandomizedSet randomizedSet;
    randomizedSet.insert(1); // Inserts 1 to the set. Returns true as 1 was inserted successfully.
    randomizedSet.remove(2); // Returns false as 2 does not exist in the set.
    randomizedSet.insert(2); // Inserts 2 to the set, returns true. Set now contains [1,2].
    std::cout << randomizedSet.getRandom() << std::endl; // getRandom() should return either 1 or 2 randomly.
    randomizedSet.remove(1); // Removes 1 from the set, returns true. Set now contains [2].
    randomizedSet.insert(2); // 2 was already in the set, so return false.
    std::cout << randomizedSet.getRandom() << std::endl; // Since 2 is the only number in the set, getRandom() will always return 2.
}
