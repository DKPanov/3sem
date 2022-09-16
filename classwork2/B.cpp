#include <iostream>
#include <cmath>
#include <iomanip>

class Matrix {
    public:
        Matrix(int arr[9]) {             //deep copy
            for (int i = 0; i < 9; i++){
                mat[i] = arr[i];
            }
        }

        void printMatrix() {
            for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++){
                        std::cout << std::setw(5) << mat[i*3 + j];
                }
                std::cout << std::endl;
            }
        }

        int calcDeterminant() {
            return mat[0] * (mat[4]*mat[8] - mat[7]*mat[5]) -
                   mat[1] * (mat[3]*mat[8] - mat[6]*mat[5]) +
                   mat[2] * (mat[3]*mat[7] - mat[6]*mat[4]);
        }

        void calcSquare() {
            int new_mat[9] = {0};
            for (int i = 0; i < 9; i++){
                int index_row = i / 3;
                int index_column = i % 3;
                for (int j = 0; j < 3; j++){
                    new_mat[i] += mat[index_row * 3 + j] * mat[j * 3 + index_column];
                }

            }
            Matrix(new_mat).printMatrix(); //создали безымянный объект
        }

    private:
        int mat[9];
};

int main() {

  int arr[9] = {1, 2, 3, 4, 5, 6, 7, 8, 10};
  Matrix A(arr);

  A.printMatrix();
  std::cout << A.calcDeterminant() << std::endl;
  A.calcSquare();

  return 0;
}

