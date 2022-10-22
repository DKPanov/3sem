#include<iostream>
#include<vector>

template<typename T>
struct Comparator{
    virtual bool operator() (T const&, T const&) const = 0;
};

struct IntComparator final : Comparator<int>{
    bool operator() (int const& lha , int const& rha) const override {
        return lha < rha;
    }
};

template<typename T>
void QuickSort(std::vector<T>& vec, size_t begin, size_t end, const Comparator<T>& comp) {
    if (begin + 1 >= end) {
        return;
    }
    size_t mid = (begin + end) / 2;
    size_t left = begin;
    size_t right = end - 1;

    while (left < right) {
        while (comp(vec[left], vec[mid])) {
            left++;
        }
        while (comp(vec[mid], vec[right])) {
            right--;
        }
        if (left >= right) {
            break;
        }
        std::swap(vec[left++], vec[right--]);
    }
    QuickSort(vec, begin, right, comp);
    QuickSort(vec, right, end, comp);
}


int main() {
    std::vector<int> arr = { 3, 1, 7, 4, 6, 9, 2};
    QuickSort(arr, 0, arr.size(), IntComparator());
    for (const auto& elem : arr) {
        std::cout << elem << " ";
    }

    return 0;
}


