#include<iostream>
#include<cassert>
template <typename T, size_t Size>
class Grid final {
public:
    using value_type = T;
    using size_type = unsigned;
private:
    Grid<T, Size - 1>* data;
    size_type size; //кол-во (Size-1)-мерных пространств
public:
    Grid(Grid<T, Size-1>* data, size_type size) : //size - размер блока
        data(new Grid<T, Size-1>[size]), size(size) {
        for (size_type i = 0; i < size; ++i) {
            this->data[i] = data[i];
        }
    }

    Grid(Grid<T, Size> const& other) : //конструктор копирования
        data(new Grid<T, Size-1>[other.size]),
        size(other.size) {//при копировании создаем копию и туда помещаем
        for (size_type i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    };

    Grid(Grid<T, Size>&& other) : data(other.data), size(other.size) { //конструктор перемещения
        other.data = nullptr;
    };

    Grid<T, Size>& operator=(const Grid<T, Size>& other) { //оператор копирующего присваивания
        if (this == &other) {//если адреса объектов слева и справа от равно совпадают
            return *this;
        }
        Grid<T, Size - 1>* new_data = new Grid<T, Size - 1>[other.size]; //выделяем память под новый блок
        for (size_type i = 0; i < other.size; ++i) {
            new_data[i] = other.data[i];
        }
        delete[] data;
        data = new_data;
        size = other.size;
        return *this;
    };

    Grid<T, Size>& operator=(Grid<T, Size>&& other) { //оператор перемещающего присваивания
        if (this == &other) {//если адреса объектов слева и справа от равно совпадают
            return *this;
        }
        delete[] data;
        data = other.data;
        size = other.size;
        other.data = nullptr;
        return *this;
    };

    ~Grid() { //деструктор
        delete[] data;
    };

    const Grid<T, Size - 1>& operator[] (size_type x_idx) const {
        return data[x_idx];
    }

    Grid<T, Size - 1>& operator[] (size_type x_idx) {
        return data[x_idx];
    }

    template<typename... Args>
    const T& operator() (size_type x_idx, Args...args ) const {//возврвщвлвсь копия объекта
        return data[x_idx](args...);
    }

    template<typename... Args>
    T& operator() (size_type x_idx, Args...args) {//возвращаентся ссылка на оригинальный объект, объект можно поменять(метод не константный)
        return data[x_idx](args...);
    }

    Grid<T, Size>& operator=(T const& t) {
        for (auto it = data, end = data + size; //end - указатель на первую ячейку, которая нам не принадлежит
            it != end; ++it) *it = t;
        return *this;
    }

    Grid(T const& t) : data(new Grid<T, Size-1>[1]), size(1) {
        data[0] = Grid<T, Size - 1>(t);
    }

    template<typename... Args>
    Grid(size_type size, Args...args) : data(new Grid<T, Size - 1>[size]), size(size) {
        for (int i = 0; i < size; ++i) {
            data[i] = Grid<T, Size - 1>(args...);
        }
    }

    //конструктор по умолчанию
    Grid() : data(nullptr), size(0) {};

    size_type get_size() const { return size; };
};

template <typename T>
class Grid<T, 1> final {
public:
    using value_type = T;
    using size_type = unsigned;
private:
    T* data;
    size_type x_size; //убрали const, так как хотим написать конструктор перемещения
public:

    Grid(T* data, size_type x_size) :
        data(new T[x_size]), x_size(x_size) {
        for (size_type i = 0; i < x_size; ++i) {
            this->data[i] = data[i];
        }
    }

    //правило пяти
    Grid(Grid<T, 1> const& other) : //конструктор копирования
        data(new T[other.x_size]),
        x_size(other.x_size) {//при копировании создаем копию и туда помещаем
        for (size_type i = 0; i < x_size; ++i) {
            data[i] = other.data[i];
        }
    };

    Grid(Grid<T, 1>&& other) : data(other.data), x_size(other.x_size) { //конструктор перемещения
        other.data = nullptr;
    };

    Grid<T, 1>& operator=(const Grid<T, 1>& other) { //оператор копирующего присваивания
        if (this == &other) {//если адреса объектов слева и справа от равно совпадают
            return *this;
        }
        T* new_data = new T[other.x_size]; //выделяем память под новый блок
        for (size_type i = 0; i < other.x_size; ++i) {
            new_data[i] = other.data[i];
        }
        delete[] data;
        data = new_data;
        x_size = other.x_size;
        return *this;
    };

    Grid<T,1>& operator=(Grid<T, 1>&& other) { //оператор перемещающего присваивания
        if (this == &other) {//если адреса объектов слева и справа от равно совпадают
            return *this;
        }
        delete[] data;
        data = other.data;
        x_size = other.x_size;
        other.data = nullptr;
        return *this;
    };

    ~Grid() { //деструктор
        delete[] data;
    }

    const T& operator() (size_type x_idx) const {//возврвщвлвсь копия объекта
        return data[x_idx];
    }

    T& operator() (size_type x_idx) {//возвращаентся ссылка на оригинальный объект, объект можно поменять(метод не константный)
        return data[x_idx];
    }

    const T& operator[] (size_type x_idx) const {
        return data[x_idx];
    }

    T& operator[] (size_type x_idx) {
        return data[x_idx];
    }

    Grid<T, 1>& operator=(T const& t) {
        for (auto it = data, end = data + x_size; //end - указатель на первую ячейку, которая нам не принадлежит
            it != end; ++it) *it = t;
        return *this;
    }

    Grid(T const& t) : data(new T[1]), x_size(1) {
        data[0] = t;
    }

    Grid(size_type x_size) : data(new T[x_size]), x_size(x_size) {} //при выделении пямяти через new конструктор класса по умолчанию вызывается сам

    Grid(size_type x_size, T const& t) : data(new T[x_size]), x_size(x_size) {
        for (size_type i = 0; i < x_size; ++i) {
            data[i] = t;
        }
    }

    //конструктор по умолчанию
    Grid() : data(nullptr), x_size(0) {};

    size_type get_size() const { return x_size; }
};


int main() {
    Grid<float, 3> const g3(2, 3, 4, 1.0f);
    assert(1.0f == g3(1, 1, 1));

    Grid<float, 2> g2(2, 5, 2.0f);
    assert(2.0f == g2(1, 1));

    g2 = g3[1];
    assert(1.0f == g2(1, 1));

    return 0;
}
