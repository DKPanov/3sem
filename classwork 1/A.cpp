/*(A) �������� ���������� void swap(blank, blank).
�� ���� ������� �������� ��� ��������, ������� ����� �������� �������.*/

#include <iostream>
#include <cmath>

using namespace std;

void swap(void* p, void* q, int type_size){
   unsigned char* char_p = reinterpret_cast<unsigned char*>(p);
   unsigned char* char_q = reinterpret_cast<unsigned char*>(q);

   for (int i = 0; i < type_size; i++){
     unsigned char tmp = char_p[i];
     char_p[i] = char_q[i];
     char_q[i] = tmp;
   }
}


int main() {
  int a, b;
  cin >> a >> b;

  swap(&a, &b, sizeof(int)); //�������� ��������

  cout << a << " " << b;

  return 0;
}

