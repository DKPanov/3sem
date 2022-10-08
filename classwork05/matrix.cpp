// matrix.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include<iostream>
#include<array>

template<typename Field, size_t M, size_t N>
class Matrix {
private:
    std::array<std::array<Field, N>, M> data_;
public:
    std::array<Field, N>& operator[](size_t index);
    const std::array<Field, N>& operator[](size_t index) const;
    Matrix() = default;
    Matrix(const Matrix& other);


    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);

};

template<typename Field, size_t M, size_t N> 
std::array<Field, N>& Matrix<Field, M, N>::operator[](size_t index) {
    return data_[index];
}

template<typename Field, size_t M, size_t N>
const std::array<Field, N>& Matrix<Field, M, N>::operator[](size_t index) const {
    return data_[index];
}

template<typename Field, size_t M, size_t N>
Matrix<Field, M, N>& Matrix<Field, M, N>::operator+=(const Matrix& other) {
    for (size_t i = 0; i < M; i++) {
        for (size_t j = 0; j < N; j++) {
            data_[i][j] += other.data_[i][j];
        }
    }
    return *this;
}

template<typename Field, size_t M, size_t N>
Matrix<Field, M, N>::Matrix(const Matrix& other) {
    for (size_t i = 0; i < M; i++) {
        for (size_t j = 0; j < N; j++) {
            data_[i][j] = other.data_[i][j];
        }
    }
}

template<typename Field, size_t M, size_t N>
Matrix<Field, M, N> operator+(const Matrix<Field, M, N>& first, const Matrix<Field, M, N>& second) {
    return Matrix<Field, M, N>(first) += second;
}

template<typename Field, size_t M, size_t N>
Matrix<Field, M, N>& Matrix<Field, M, N>::operator-=(const Matrix& other) {
    for (size_t i = 0; i < M; i++) {
        for (size_t j = 0; j < N; j++) {
            data_[i][j] -= other.data_[i][j];
        }
    }
    return *this;
}

template<typename Field, size_t M, size_t N>
Matrix<Field, M, N> operator-(const Matrix<Field, M, N>& first, const Matrix<Field, M, N>& second) {
    return Matrix<Field, M, N>(first) -= second;
}

template<typename Field, size_t M, size_t N, size_t K>
Matrix<Field, M, K> operator*(const Matrix<Field, M, N>& lha, const Matrix<Field, N, K>& rha) {
    Matrix<Field, M, K> result;
    for (size_t i = 0; i < M; i++) {
        for (size_t j = 0; j < K; j++) {
            result[i][j] = 0;
            for (size_t k = 0; k < N; k++) {
                result[i][j] += lha[i][k] * rha[k][j];
            }
        }
    }
    return result;
}

int main(){
    Matrix<int, 4, 5> A;
    Matrix<int, 4, 5> B;
    Matrix<int, 5, 5> C;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            A[i][j] = i + j;
            B[i][j] = 1;
        }
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            C[i][j] = i + j;
        }
    }

    auto D = A + B;
    auto E = A - B;
    auto F = B * C;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            std::cout << D[i][j];
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            std::cout << E[i][j];
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            std::cout << F[i][j];
        }
        std::cout << std::endl;
    }

    return 0;
}


