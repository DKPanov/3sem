#include<iostream>
#include<vector>
#include<functional>

template<typename T, class Comp>
class PriorityQueue {
private:
    std::vector<T> data_;
    const Comp& comp_;
private:
    void SiftUp(int i);
    void SiftDown(int i);
public:
    PriorityQueue(const Comp& comp);
    void push(const T& elem);
    T peek() const;
    void poll();
    bool is_empty() const;
    void free();
};

template<typename T, class Comp>
void PriorityQueue<T, Comp>::SiftUp(int i) {
    int parent = (i - 1) / 2;
    if (comp_(data_[i], data_[parent])) {
        std::swap(data_[i], data_[parent]);
        SiftUp(parent);
    }
}

template<typename T, class Comp>
void PriorityQueue<T, Comp>::SiftDown(int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left >= data_.size()) {
        return;
    }
    int condidate = i;
    if (comp_(data_[left], data_[condidate])) {
        condidate = left;
    }
    if (right < data_.size() && comp_(data_[right], data_[condidate])) {
        condidate = right;
    }
    if (condidate == i) {
        return;
    }
    std::swap(data_[i], data_[condidate]);
    SiftDown(condidate);
}

template<typename T, class Comp>
PriorityQueue<T, Comp>::PriorityQueue(const Comp& comp) : comp_(comp) {};

template<typename T, class Comp>
void PriorityQueue<T, Comp>::push(const T& elem) {
    data_.push_back(elem);
    SiftUp(data_.size() - 1);
}

template<typename T, class Comp>
T PriorityQueue<T, Comp>::peek() const {
    return data_[0];
}

template<typename T, class Comp>
void PriorityQueue<T, Comp>::poll() {
    std::swap(data_[0], data_.back());
    data_.pop_back();
    SiftDown(0);
}

template<typename T, class Comp>
bool PriorityQueue<T, Comp>::is_empty() const {
    return data_.empty();
}

template<typename T, class Comp>
void PriorityQueue<T, Comp>::free() {
    return data_.clear();
}

int main(){
    std::less<int> c;
    PriorityQueue<int, std::less<int>> h(c);
    h.push(5);
    h.push(3);
    std::cout << h.peek() << std::endl;
    h.poll();
    h.push(4);
    std::cout << h.peek() << std::endl;
    for (int i = 0; i < 10; ++i) {
        h.push(i);
    }
    std::cout << h.peek() << std::endl;
    for (int i = 0; i < 10; ++i) {
        h.poll();
    }
    std::cout << h.peek() << std::endl;
    h.poll();
    std::cout << h.peek() << std::endl;
    h.poll();
    std::cout << h.is_empty() << std::endl;
    h.push(15);
    std::cout << h.peek() << std::endl;

    return 0;
}

