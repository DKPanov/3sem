/*(D) Ќапишите простую программу, котора€ выводит размер типа в битах и его минимальное и максимальное значение.
¬ывести значени€ дл€ char, short int, int, long int, float, double.*/

#include <iostream>
#include <cmath>
#include <limits>


int main() {

  std::cout << "short int" << std::endl;
  std::cout << sizeof(short int) * CHAR_BIT << std::endl;
  std::cout << "min " << std::numeric_limits<short int>::lowest() << std::endl;
  std::cout << "max " << std::numeric_limits<short int>::max() << std::endl;
  std::cout << std::endl;

  std::cout << "int" << std::endl;
  std::cout << sizeof(int) * CHAR_BIT << std::endl;
  std::cout << "min " << std::numeric_limits<int>::lowest() << std::endl;
  std::cout << "max " << std::numeric_limits<int>::max() << std::endl;
  std::cout << std::endl;

  std::cout << "long int" << std::endl;
  std::cout << sizeof(long int) * CHAR_BIT << std::endl;
  std::cout << "min " << std::numeric_limits<long int>::lowest() << std::endl;
  std::cout << "max " << std::numeric_limits<long int>::max() << std::endl;
  std::cout << std::endl;

  std::cout << "char" << std::endl;
  std::cout << sizeof(char) * CHAR_BIT << std::endl;
  std::cout << "min " << int(std::numeric_limits<char>::lowest()) << std::endl;
  std::cout << "max " << int(std::numeric_limits<char>::max()) << std::endl;
  std::cout << std::endl;

  std::cout << "double" << std::endl;
  std::cout << sizeof(double) * CHAR_BIT << std::endl;
  std::cout << "min " << std::numeric_limits<double>::lowest() << std::endl;
  std::cout << "max " << std::numeric_limits<double>::max() << std::endl;
  std::cout << std::endl;

  std::cout << "float" << std::endl;
  std::cout << sizeof(float) * CHAR_BIT << std::endl;
  std::cout << "min " << std::numeric_limits<float>::lowest() << std::endl;
  std::cout << "max " << std::numeric_limits<float>::max() << std::endl;
  std::cout << std::endl;

  return 0;
}

