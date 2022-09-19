#include <iostream>
#include <cmath>
#include <iomanip>

class Matrix {
    public:
        Matrix(int arr[], size_t n_elements) : mat(new int*[static_cast<size_t>(std::sqrt(n_elements))]), size(std::sqrt(n_elements))   { //deep copy
            for (size_t i = 0; i < size; i++){
                mat[i] = new int[size];
                for (size_t j = 0; j < size; j++){
                    mat[i][j] = arr[i*size + j];
                }
            }
        }

        Matrix(int element, size_t n_elements) : mat(new int*[static_cast<size_t>(std::sqrt(n_elements))]), size(std::sqrt(n_elements))  {
            for (size_t i = 0; i < size; i++){
                mat[i] = new int[size];
                for (size_t j = 0; j < size; j++){
                    mat[i][j] = element;
                }
            }
        }

        Matrix() : Matrix(1,1) {}

        Matrix(const Matrix& other) : mat(new int*[other.size]), size(other.size) {
            for (size_t i = 0; i < size; i++){
                mat[i] = new int[size];
                for (size_t j = 0; j < size; j++){
                    mat[i][j] = other.mat[i][j];
                }
            }
        }

        void printMatrix() {
            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                        std::cout << std::setw(5) << mat[i][j];
                }
                std::cout << std::endl;
            }
        }

        /*int calcDeterminant() {
            ...  // Вычислить детерминант
        }*/

        void calcSquare() {
            int** new_mat = new int* [size];
            for (int i = 0; i < size; i++){
                new_mat[i] = new int[size];
                for (int j = 0; j < size; j++){
                    new_mat[i][j] = 0;
                    for (int k = 0; k < size; k++){
                        new_mat[i][j] += mat[i][k]*mat[k][j];
                    }
                }

            }
            for (size_t i = 0; i < size; i++){
                delete[] mat[i];
            }
            delete[] mat;

            mat = new_mat;

        }

        void matTranspose() {
            for (int i = 0; i < size; i++){
                for(int j = 0; j < i; j++){
                    int x = mat[i][j];
                    mat[i][j] = mat[j][i];
                    mat[j][i] = x;
                }
            }
        }

        ~Matrix() {
            for (size_t i = 0; i < size; i++){
                delete[] mat[i];
            }
            delete[] mat;

        }

    private:
        int** mat;  // массив для хранения значений матрицы
        int size;  // размер стороны матрицы
};

int main() {

  int arr[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  Matrix A(arr, 16);
  A.printMatrix();
  std::cout << std::endl;
  //std::cout << A.calcDeterminant() << std::endl;
  A.calcSquare();
  A.printMatrix();
  std::cout << std::endl;

  Matrix B(3, 16);
  B.printMatrix();
  std::cout << std::endl;

  Matrix C;
  C.printMatrix();
  std::cout << std::endl;

  Matrix D(A);
  D.printMatrix();
  std::cout << std::endl;
  D.matTranspose();
  D.printMatrix();
  std::cout << std::endl;

  return 0;
}
