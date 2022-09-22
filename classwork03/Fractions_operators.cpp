#include <iostream>
#include <cmath>

class Fraction {
  public:
    friend std::ostream& operator<<(std::ostream& out, const Fraction& obj);  // Оператор вывода << "числитель знаминатель"
    friend std::istream& operator>>(std::istream& is, Fraction& obj);  // Оператор ввода >> числитель >> знаминатель
    Fraction& operator+=(const Fraction& other){
        numerator_ = numerator_ * other.denominator_ + other.numerator_ * denominator_;
        denominator_ *= other.denominator_;
        return *this;
    }
    Fraction& operator-=(const Fraction& other){
        numerator_ = numerator_ * other.denominator_ - other.numerator_ * denominator_;
        denominator_ *= other.denominator_;
        return *this;
    }
    Fraction& operator*=(const Fraction& other){
        numerator_ *= other.numerator_;
        denominator_ *= other.denominator_;
        return *this;
    }

    Fraction& operator++(){
        numerator_+=denominator_;
        return *this;
    }
    Fraction operator++(int){
        Fraction copy(*this);
        numerator_+=denominator_;
        return copy;
    }
    Fraction& operator--(){
        numerator_-=denominator_;
        return *this;
    }
    Fraction operator--(int){
        Fraction copy(*this);
        numerator_-=denominator_;
        return copy;
    }

    Fraction(int numerator, int denominator) : numerator_(numerator), denominator_(denominator) {}

    explicit Fraction(int numerator) : Fraction(numerator, 1) {}

    Fraction() = delete; // Конструктор по умолчанию должен быть удален

    Fraction(const Fraction& other) = default; // Конструктор копирования

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

Fraction operator+(const Fraction& lhs, const Fraction& rhs){
    return Fraction(lhs) += rhs;
}

Fraction operator*(const Fraction& lhs, const Fraction& rhs){
    return Fraction(lhs) *= rhs;
}

Fraction operator-(const Fraction& lhs, const Fraction& rhs){
    return Fraction(lhs) -= rhs;
}

std::ostream& operator<<(std::ostream& out, const Fraction& obj){
    out<<obj.numerator_<<' '<<obj.denominator_;
    return out;
}

std::istream& operator>>(std::istream& is, Fraction& obj){
    is>>obj.numerator_>>obj.denominator_;
    return is;
}
int main() {

  Fraction a(5, 3);
  Fraction b(a); //копия объeкта а


  std::cout << a.calc() << std::endl;
  std::cout << a << std::endl;


  //b.multByNumber(2);
  b*=Fraction(2);
  std::cout << b << std::endl;

  Fraction d(-3, 21);
  d.fracSimplify();
  std::cout << d << std::endl;

  Fraction c(7);
  std::cout << c.calc() << std::endl;
  std::cout << c << std::endl;

  std::cout << a + d << std::endl;
  a+=d;
  std::cout << a << std::endl;

  Fraction e(1,2);
  Fraction f(2,-3);
  std::cout << e * f << std::endl;
  std::cout << ++e << std::endl;
  std::cout << e++ << std::endl;
  std::cout << e << std::endl;
  std::cout << ++f << std::endl;
  std::cout << f++ << std::endl;
  std::cout << f << std::endl;


  return 0;
}
