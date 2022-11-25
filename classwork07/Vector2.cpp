#include <iostream>

template <typename T>
class Buffer {
private:
    size_t capacity = 0;
    T* buffer = nullptr;
public:

    Buffer() = default;

    Buffer(const Buffer& other) : capacity(other.capacity), buffer(new T[capacity]) {
        for (int i = 0; i < capacity; ++i) {
            buffer[i] = other.buffer[i];
        }
    };

    Buffer(Buffer&& other) : capacity(other.capacity), buffer(other.buffer) {
        other.buffer = nullptr;
    };


    void add_memory() {
        if (capacity != 0) {
            T* new_buffer = new T[2 * capacity];
            for (int i = 0; i < capacity; ++i) {
                new_buffer[i] = buffer[i];
            }

            delete[] buffer;
            buffer = new_buffer;

            capacity *= 2;
            return;
        }
        T* new_buffer = new T[capacity + 1];
        buffer = new_buffer;
        capacity += 1;
    };

    T& operator[](size_t index) {
        return buffer[index];
    };

    const T& operator[](size_t index) const {
        return buffer[index];
    };

    size_t Capacity() const {
        return capacity;
    };

    ~Buffer() {
        delete[] buffer;
    };

};


template <typename T>
class Vector {
private:
    size_t size = 0;
    Buffer<T> buffer;
public:
    Vector() = default;

    Vector(const Vector& vec) = default;
    Vector(Vector&& vec) noexcept = default;
    

    void push_back(const T& value) {
        if (size == buffer.Capacity()) {
            buffer.add_memory();
        }
        buffer[size] = value;
        ++size;
    };

    void pop() {
        --size;
    };

    bool is_empty() const {
        return size == 0;
    };

    size_t capacity() const {
        return buffer.Capacity();
    };

    size_t Size() const {
        return size;
    };

    T& operator[](size_t index) {
        return buffer[index];
    };

    const T& operator[](size_t index) const {
        return buffer[index];
    };

    ~Vector() = default; //деструктор вызовет деструктор наших полей, а деструктор buffer уже есть
};

int main() {
    Vector<int> vec;
    for (int i = 1; i <= 10; ++i) {
        vec.push_back(i);
    }
    std::cout << vec.capacity() << std::endl;
    std::cout << vec[9] << std::endl;
    for (int i = 0; i <= 9; ++i) {
        vec.pop();
    }
    std::cout << vec.is_empty() << std::endl;


    return 0;
}