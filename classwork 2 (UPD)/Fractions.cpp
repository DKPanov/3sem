#include <iostream>
#include <cmath>

class Fraction {
    public:
        Fraction(int numerator, int denominator) : numerator_(numerator), denominator_(denominator) {}

        Fraction(int numerator) : Fraction(numerator, 1) {}
        Fraction() = delete; // Конструктор по умолчанию должен быть удален

        Fraction(const Fraction& other) = default; // Конструктор копирования

        void printFraction() {  // Выводит дробь в формате 'numerator / denominator'
            std::cout << numerator_ << " / " << denominator_ << std::endl;
         }


        void fracReverse() {  // Перевернуть дробь, знаменатель<->числитель
            int x = denominator_;
            denominator_ = numerator_;
            numerator_ = x;
        }

        void fracSimplify() {  // Сокращает дробь по возможности
            bool numerator_negative = false;
            bool denominator_negative = false;
            if (numerator_ < 0){
                numerator_negative = true;
                numerator_ *= -1;
            }
            if (denominator_ < 0){
                denominator_negative = true;
                denominator_ *= -1;
            }

            int max = std::max(numerator_, denominator_);
            int min = std::min(numerator_, denominator_);

            while(min != 0){
                int x = min;
                min = max%min;
                max = x;
            }

            numerator_ /= max;
            denominator_ /= max;

            if (numerator_negative){
                numerator_ *= -1;
            }
            if (denominator_negative){
                denominator_ *= -1;
            }
        }

        void multByNumber(int value) {  // Умножить дробь на число
            numerator_ *= value;
        }

        void multByFrac(const Fraction& other) {
            numerator_ *= other.numerator_;
            denominator_ *= other.denominator_;
        }

        Fraction multByFracReturn(const Fraction& other) const {  // умножает дроби и возвращает результат в третью
            return Fraction(numerator_ * other.numerator_, denominator_ * other.denominator_);
        }

        void sumFrac(const Fraction& other) {
            numerator_ = numerator_ * other.denominator_ + other.numerator_ * denominator_;
            denominator_ *= other.denominator_;
        }

        Fraction sumFracReturn(const Fraction& other) const {
            return Fraction (numerator_ * other.denominator_ + other.numerator_ * denominator_,
                             denominator_ * other.denominator_);
        }

        void diffFrac(const Fraction& other) {
            numerator_ = numerator_ * other.denominator_ - other.numerator_ * denominator_;
            denominator_ *= other.denominator_;
        }

        Fraction diffFracReturn(const Fraction& other) const {
             return Fraction (numerator_ * other.denominator_ - other.numerator_ * denominator_,
                             denominator_ * other.denominator_);
        }

        double calc() {  // Возвращает значение дроби в десятичном виде
            return static_cast<double>(numerator_) / denominator_;
        }

        int getNumerator() {  // Возвращает значение числителя
            return numerator_;
        }

        int getDenominator() {  // Возвращает знамечение знаменателя
            return denominator_;
        }

    private:
        int numerator_;
        int denominator_;
};

int main() {

  Fraction a(5, 3);
  Fraction b(a); //копия объeкта а
  a.printFraction();
  b.printFraction();

  std::cout << a.calc() << std::endl;
  std::cout << a.getNumerator() << std::endl;
  std::cout << a.getDenominator() << std::endl;

  a.fracReverse();
  std::cout << a.getNumerator() << std::endl;
  std::cout << a.getDenominator() << std::endl;

  b.multByNumber(2);
  std::cout << b.getNumerator() << std::endl;
  std::cout << b.getDenominator() << std::endl;

  Fraction d(-3, 21);
  d.fracSimplify();
  std::cout << d.getNumerator() << std::endl;
  std::cout << d.getDenominator() << std::endl;

  Fraction c(7);
  c.printFraction();
  std::cout << c.calc() << std::endl;
  std::cout << c.getNumerator() << std::endl;
  std::cout << c.getDenominator() << std::endl;

  std::cout << a.sumFracReturn(d).getNumerator() << " / " << a.sumFracReturn(d).getDenominator() << std::endl;
  a.sumFrac(d);
  std::cout << a.getNumerator() << std::endl;
  std::cout << a.getDenominator() << std::endl;


  return 0;
}
