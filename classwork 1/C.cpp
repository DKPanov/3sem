/*(C) Написать быструю сортировку с использованием произвольного компоратора.
Сигнатура сортировки следующая
void qsort(blank arr, int left, int right, int (*compare)(void *, void *)).
Реализовать несколько типов компораторов.
Компораторы использовать из массива указателей на функции.*/

#include <iostream>
#include <cmath>

using namespace std;

int sum_of_digits(int a){
    int sum = 0;
    while (a != 0){
        sum += a%10;
        a = a / 10;
    }
    return sum;
}

int comparator_1(void* first, void* second){
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

int comparator_2(void* first, void* second){
    int* int_first = reinterpret_cast<int*>(first);
    int* int_second = reinterpret_cast<int*>(second);
    if (*int_first < *int_second){
        return 1;
    }
    if (*int_first > *int_second){
        return -1;
    }
    return 0;
}

int comparator_3(void* first, void* second){
    int* int_first = reinterpret_cast<int*>(first);
    int* int_second = reinterpret_cast<int*>(second);

    if (sum_of_digits(*int_first) < sum_of_digits(*int_second)){
        return -1;
    }
    if (sum_of_digits(*int_first) > sum_of_digits(*int_second)){
        return 1;
    }
    return 0;
}


void swap(void* p, void* q, int type_size){
   unsigned char* char_p = reinterpret_cast<unsigned char*>(p);
   unsigned char* char_q = reinterpret_cast<unsigned char*>(q);

   for (int i = 0; i < type_size; i++){
     unsigned char tmp = char_p[i];
     char_p[i] = char_q[i];
     char_q[i] = tmp;
   }
}

void qsort(void* arr, int left, int right, int type_size, int (*compare)(void *, void *)){

    if (left >= right){
        return;
    }

    unsigned char* char_arr = reinterpret_cast<unsigned char*>(arr);

    int index = (left + right)/2;
    int i = left;
    int j = right;

    while (i < j){
        while(compare(char_arr + i*type_size, char_arr + type_size * index)  <  0){
            i++;
        }
        while(compare(char_arr + j*type_size, char_arr + type_size * index)  >  0){
            j--;
        }
        if (i >= j){
            break;
        }
        swap(char_arr + i*type_size, char_arr + j*type_size, type_size);
        i++;
        j--;
    }

    qsort(arr, left, j, type_size, compare);
    qsort(arr, j+1, right, type_size, compare);
}


int main() {
  int arr[5] = {71, 19, 43, 11, 54};
  int (*comparator_arr[3])(void*, void*) = {comparator_1, comparator_2, comparator_3};

  //По возрастанию
  qsort(arr, 0, 4, sizeof(int), comparator_arr[0]);

  for (int i = 0; i < 5; i++){
    cout << arr[i] << " ";
  }
  cout << endl;

  //По убыванию
  qsort(arr, 0, 4, sizeof(int), comparator_arr[1]);

  for (int i = 0; i < 5; i++){
    cout << arr[i] << " ";
  }
  cout << endl;


  //По сумме цифр
  qsort(arr, 0, 4, sizeof(int), comparator_arr[2]);

  for (int i = 0; i < 5; i++){
    cout << arr[i] << " ";
  }


  return 0;
}

