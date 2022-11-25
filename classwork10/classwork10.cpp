#include<iostream>
#include<iostream>

template<typename Comparator, typename Iterator = int*>
class sorter {
private:
    Iterator it_begin_;
    Iterator it_end_;
    Iterator it_current_;
public:
    sorter(Iterator it_begin, Iterator it_end) : it_begin_(it_begin), it_end_(it_end) {
        it_current_ = it_begin_;
        for (; it_begin != it_end_; ++it_begin) {
            if (Comparator()(*it_begin, *it_current_)) {
                it_current_ = it_begin;
            }
        }
    };

    sorter(Iterator it) : it_begin_(it), it_end_(it), it_current_(it) {};

    auto operator*() const {
        return *it_current_;
    }

    sorter& operator++() {
        Iterator it_next = it_end_;
        for (Iterator it = it_begin_; it != it_end_; ++it) {
            if (!Comparator()(*it, *it_current_) && !Comparator()(*it_current_, *it)) { //*it_current == *it
                if (it_current_ < it) {
                    it_current_ = it;
                    return *this;
                }
            }
            if (Comparator()(*it_current_, *it) && (it_next == it_end_ || Comparator()(*it, *it_next))) {
                it_next = it;
            }
        }
        it_current_ = it_next;
        return *this;
    }

    sorter operator++(int) {
        auto copy = *this;
        ++(*this);
        return copy;
    }

    bool operator!=(sorter other) const {
        return it_current_ != other.it_current_;
    }

    bool operator==(sorter other) const {
        return it_current_ == other.it_current_;
    }
};

class Descending {
public:
    bool operator()(int first, int second) const {
        return first > second;
    }
};

int main()
{
    // A:{ 5,2,1,2,2 } => A:{ 5,2,1,2,2 }
    // B:{ 0,0,0,0,0 } => B:{ 5,2,2,2,1 }
    int input[5] = { 5,2,1,2,2 };
    int output[5] = { 0,0,0,0,0 };
    int* input_ptr = input;
    int* output_ptr = output;

    std::copy(sorter<Descending>(input_ptr, input_ptr + 5),
        sorter<Descending>(input_ptr + 5),
        output_ptr);

    for (int i = 0; i < 5; ++i) {
        std::cout << output[i] << " ";
    }
    // Expect input
    // 5 == input[0]
    // 2 == input[1]
    // 1 == input[2]
    // 2 == input[3]
    // 2 == input[4]

    // Expect output
    // 5 == output[0]
    // 2 == output[1]
    // 2 == output[2]
    // 2 == output[3]
    // 1 == output[4]
}
