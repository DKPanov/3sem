
#include<iostream>

template <typename T>
class unique_ptr {
public:
    explicit unique_ptr(T* ptr) : ptr_(ptr) { }

    unique_ptr(unique_ptr&& other) : ptr_(other.ptr_) { //конструктор перемещения
        other.ptr_ = nullptr;
    }

    unique_ptr& operator=(unique_ptr&& other) { //перемещающее присваивание
        delete ptr_; //чистим память из-под объекта
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
        return *this;
    }

    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }

    ~unique_ptr() {
        delete ptr_;
    }
private:
    T* ptr_;
};

int main()
{
    unique_ptr<int> ptr(new int(5));
    std::cout << *ptr << std::endl;
}
