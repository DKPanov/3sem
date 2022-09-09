/*(B) Написать обобщенный поиск минимального значения следующей сигнатуры
 int min(blank arr, int arr_size, int type_size, int (*compare)(void *, void *)).
 На вход получает массив, размер массива, и функцию сравнения (компоратор).
 Функция должна вернуть индекс минимального элемента.
 Сделать аналогичный поиск максимума с использованием того же куска кода.*/

#include <iostream>
#include <cmath>

using namespace std;

int comparator(void* first, void* second){
    int* int_first = reinterpret_cast<int*>(first);
    int* int_second = reinterpret_cast<int*>(second);
    if (*int_first < *int_second){
        return -1;
    }
    if (*int_first > *int_second){
        return 1;
    }
    return 0;
}

int min(void* arr, int arr_size, int type_size, int (*compare)(void*, void*)){
   int min_index = 0;
   unsigned char* char_arr = reinterpret_cast<unsigned char*>(arr);

   for (int i = 1; i < arr_size; i++){
     if (compare(char_arr + i*type_size, char_arr + min_index * type_size) < 0){
        min_index = i;
     }
   }
   return min_index;
}


int main() {
  int arr[5] = {5, 4, 3, 2, 1};

  cout << min(arr, 5, sizeof(int), comparator);

  return 0;
}

