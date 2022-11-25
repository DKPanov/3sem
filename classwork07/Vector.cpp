#include <iostream>

template <typename T>
class Vector {
private:
    size_t size = 0;
    T* buffer = nullptr;
public:
    Vector() = default;

    Vector(Vector const& vec) : size(vec.size), buffer(new T[size]) {
        for (int i = 0; i < size; ++i) {
            buffer[i] = vec.buffer[i];
        }
    }

    Vector(Vector&& vec) noexcept : size(vec.size), buffer(vec.buffer) {
        vec.buffer = nullptr;
    };

    void add_memory() {
        if (size != 0) {
            T* new_buffer = new T[2 * size];
            for (int i = 0; i < size; ++i) {
                new_buffer[i] = buffer[i];
            }

            delete[] buffer;
            buffer = new_buffer;

            size *= 2;
            return;
        }

        T* new_buffer = new T[1];
        delete[] buffer;
        buffer = new_buffer;

        size += 1;
    };

    void push_back(const T& value) {
        T* new_buffer = new T[size + 1];
        for (int i = 0; i < size; ++i) {
            new_buffer[i] = buffer[i];
        }

        delete[] buffer;
        buffer = new_buffer;
        buffer[size] = value;
        size += 1;
    };

    void pop() {
        --size;
    };

    bool is_empty() const {
        return size == 0;
    };

    size_t capacity() const {
        return size;
    };

    T& operator[](size_t index) {
        return buffer[index];
    };

    const T& operator[](size_t index) const {
        return buffer[index];
    };

    ~Vector() {
        delete[] buffer;
    };
};

int main(){
    Vector<int> vec;
    for (int i = 1; i <= 5; ++i) {
        vec.push_back(i);
    }
    vec.add_memory();
    for (int i = 5; i <= 9; ++i) {
        vec[i] = i + 1;
    }
    std::cout << vec.capacity() << std::endl;
    std::cout << vec[9] << std::endl;
    for (int i = 0; i <= 9; ++i) {
        vec.pop();
    }
    std::cout << vec.is_empty() << std::endl;
    

    return 0;
}