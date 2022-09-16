#include <iostream>
#include <cmath>

class Fraction {
    public:
        Fraction(int numerator, int denominator) : numerator_(numerator), denominator_(denominator) {}

        Fraction(int numerator) : Fraction(numerator, 1) {}
        Fraction() = delete; // ����������� �� ��������� ������ ���� ������

        Fraction(const Fraction& other) = default; // ����������� �����������

        void printFraction() {  // ������� ����� � ������� 'numerator / denominator'
            std::cout << numerator_ << " / " << denominator_ << std::endl;
         }

        double calc() {  // ���������� �������� ����� � ���������� ����
            return static_cast<double>(numerator_) / denominator_;
        }

        int getNumerator() {  // ���������� �������� ���������
            return numerator_;
        }

        int getDenominator() {  // ���������� ���������� �����������
            return denominator_;
        }

    private:
        int numerator_;
        int denominator_;
};

int main() {

  Fraction a(5, 3);
  Fraction b(a); //����� ���e��� �
  a.printFraction();
  b.printFraction();
  std::cout << a.calc() << std::endl;
  std::cout << a.getNumerator() << std::endl;
  std::cout << a.getDenominator() << std::endl;

  Fraction c(7);
  c.printFraction();
  std::cout << c.calc() << std::endl;
  std::cout << c.getNumerator() << std::endl;
  std::cout << c.getDenominator() << std::endl;

//  Fraction d;

  return 0;
}

