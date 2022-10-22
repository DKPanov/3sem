
#include<iostream>
#include<cassert>

template <typename T>
class Grid final {
public:
    using value_type = T;
    using size_type = unsigned;
private:
    T* data;
    size_type y_size, x_size; //убрали const, так как хотим написать конструктор перемещения
public:

    Grid(T* data, size_type y_size, size_type x_size) :
        data(new T[x_size*y_size]), y_size(y_size), x_size(x_size) {
        for (size_type i = 0; i < x_size * y_size; ++i) {
            this->data[i] = data[i];
        }
    }

    //правило пяти
    Grid(Grid<T> const& other) : 
        data(new T[other.x_size * other.y_size]), 
        y_size(other.y_size), 
        x_size(other.x_size) {//при копировании создаем копию и туда помещаем
        for (size_type i = 0; i < x_size * y_size; ++i) {
            data[i] = other.data[i];
        }
    };

    Grid(Grid<T>&& other) : data(other.data), y_size(other.y_size), x_size(other.x_size) {
        other.data = nullptr;
    };
    Grid<T>& operator=(Grid<T>& other) {
        if (this == &other){//если адреса объектов слева и справа от рано совпадают
            return *this;
        }
        T* new_data = new T[other.x_size * other.y_size]; //выделяем память под новый блок
        for (size_type i = 0; i < other.x_size * other.y_size; ++i) {
            new_data[i] = other.data[i];
        }
        delete[] data;
        data = new_data;
        x_size = other.x_size;
        y_size = other.y_size;
        return *this;
    };

    Grid<T>& operator=(Grid<T>&& other) {
        if (this == &other) {//если адреса объектов слева и справа от рано совпадают
            return *this;
        }
        delete[] data;
        data = other.data;
        x_size = other.x_size;
        y_size = other.y_size;
        other.data = nullptr;
        return *this;
    };

    ~Grid() {
        delete[] data;
    }

    const T& operator() (size_type y_idx, size_type x_idx) const {//возврвщвлвсь копия объекта
        return data[y_idx * x_size + x_idx];
    }

    T& operator() (size_type y_idx, size_type x_idx) {//возвращаентся ссылка нв оригинадьный объект, объект можно поменять(метод не константный)
        return data[y_idx * x_size + x_idx];
    }

    const T* operator[] (size_type y_idx) const {
        return data + y_idx * x_size;
    }

    T* operator[] (size_type y_idx) {
        return data + y_idx * x_size;
    }

    Grid<T>& operator=(T const& t) {
        for (auto it = data, end = data + x_size * y_size; //end - указатель на первую ячейку, кот нам не принадлежит
            it != end; ++it) *it = t;
        return *this;
    }

    Grid(T const& t) : data(new T[1]), y_size(1), x_size(1) {
        data[0] = t;
    }

    Grid(size_type y_size, size_type x_size) : data(new T[x_size * y_size]), x_size(x_size), y_size(y_size){} //при выделении пямяти через new конструктор класса по умолчанию вызывается сам

    Grid(size_type y_size, size_type x_size, T const& t) : data(new T[x_size * y_size]), x_size(x_size), y_size(y_size) {
        for (size_type i = 0; i < x_size * y_size; ++i) {
            data[i] = t;
        }
    }
    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }
};


int main() {
    Grid<float> g(3, 2, 0.0f);
    assert(3 == g.get_y_size()); //если условие неверно, программа падает
    assert(2 == g.get_x_size());

    using gsize_t = Grid<int>::size_type;

    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            assert(0.0f == g[y_idx][x_idx]);

    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            g[y_idx][x_idx] = 1.0f;

    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            assert(1.0f == g(y_idx, x_idx));
    return 0;
}


