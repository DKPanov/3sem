#include <iostream>
#include <cmath>
#include <iomanip>
#include <stack>


struct Point {
 unsigned long long const x , y;


 Point(unsigned long long x , unsigned long long y) : x(x), y(y) {}

 Point minx(Point const &rha) const {
 return Point(rha.x < x ? rha.x : x , y);
 }

 Point miny(Point const &rha) const {
 return Point(x , rha.y < y ? rha.y : y);
 }

 Point maxx(Point const &rha) const {
 return Point(rha.x > x ? rha.x : x , y);
 }

 Point maxy(Point const &rha ) const {
 return Point(x, rha.y > y ? rha.y : y);
 }

 void print() const {
 std :: cout << '(' << x << ',' << y << ')';
 }
 } ;


 class Rectangle{
 private:
     Point right_up_angle_;
 public:
     Rectangle(); //объявили конструктор без параметров для создания прямоугольника с правым верхним углом в начале координат
     Rectangle(Point const &right_up_angle); //объявили конструктор конструктор с одним параметром Point const & для создания прямоугольника с правым верхним углом в заданной точке

     Rectangle operator+(Rectangle const &other) const;//объявили метод Rectangle operator+(Rectangle const &rha) const
     Rectangle operator*(Rectangle const &other) const;//объявили метод Rectangle operator*(Rectangle const &rha) const

     void print() const; //для печати на экране координаты правого верхнего угла прямоугольника

     Point RightUpAngle() const; //публичный метод, возвращающий точку прямоугольника

 };

 Rectangle::Rectangle() : right_up_angle_(0,0) {};
 Rectangle::Rectangle(Point const &right_up_angle) : right_up_angle_(right_up_angle) {};

 Rectangle Rectangle::operator+(Rectangle const &other) const{
     Point maxy = other.right_up_angle_.maxy(right_up_angle_); // y берет максимальный из other.right_up_angle_ и right_up_angle_, а x - из other.right_up_angle_
     Point result = maxy.maxx(right_up_angle_);
     return Rectangle(result);
 }

 Rectangle Rectangle::operator*(Rectangle const &other) const{
     Point miny = other.right_up_angle_.miny(right_up_angle_);
     Point result = miny.minx(right_up_angle_);
     return Rectangle(result);
 }

 void Rectangle::print() const{
     right_up_angle_.print();

 }

 Point Rectangle::RightUpAngle() const{
     return right_up_angle_;
 }

int main () {
 std::string expression;
 std::getline (std::cin, expression);

 std::string parsed;
 std::stack <char> stack; //stack - это стек char-ов

 for (size_t i = 0; i < expression.size(); i++){
    if (expression[i] == '('){
            while(expression[i] != ')'){
                parsed += expression[i++];
            }
            parsed += ')';
        }

    if (expression[i] == '+'){
        if (stack.empty()){
            stack.push('+');
        }
        else{
            while(!stack.empty()){
                parsed += stack.top();
                stack.pop();
            }
            stack.push('+');
        }
    }

    if (expression[i] == '*'){
        if (stack.empty() || stack.top() == '+'){  //операцию * можно положить в стек после +
            stack.push('*');
        }
        else{
            while(!stack.empty() && stack.top() == '*'){
                parsed += stack.top();
                stack.pop();
            }
            stack.push('*');
        }
    }
 }
 while(!stack.empty()){
     parsed += stack.top();
     stack.pop();
 }

 //Теперь надо раскодировать строку parsed
 std::stack <std::pair<unsigned long long, unsigned long long>> result; //result - это стек пар
 for (size_t i = 0; i < parsed.size(); i++){
    if(parsed[i] == '('){
        std::pair<unsigned long long, unsigned long long> pair = {0,0}; //pair - это структура
        i++;
        while(parsed[i] != ','){ //добавляем первое число в первое чило пары
            pair.first *= 10;
            pair.first += parsed[i++] - '0'; //т.к. parsed[i] - это char, чтобы получить нужное нам значение, нужно вычесть код нуля
        }
        i++;
        while(parsed[i] != ')'){ //добавляем второе число во второе чило пары
            pair.second *= 10;
            pair.second += parsed[i++] - '0';
        }
        result.push(pair); //добавляем пару (точку прямоугольника) в список пар
    }

    if(parsed[i] == '+'){
        Point first(result.top().first, result.top().second); //достаем из стека result первый прямоугольник (создаем первую точку first)
        result.pop();
        Point second(result.top().first, result.top().second); //достаем из стека result второй прямоугольник (создаем вторую точку second)
        result.pop();
        Rectangle first_rec(first); //создаем прямоугольники по точкам
        Rectangle second_rec(second);
        Rectangle sum = first_rec + second_rec;
        result.push({sum.RightUpAngle().x, sum.RightUpAngle().y});
    }

    if(parsed[i] == '*'){
        Point first(result.top().first, result.top().second);
        result.pop();
        Point second(result.top().first, result.top().second);
        result.pop();
        Rectangle first_rec(first);
        Rectangle second_rec(second);
        Rectangle mult = first_rec * second_rec;
        result.push({mult.RightUpAngle().x, mult.RightUpAngle().y});
    }
  }


  std::cout << '(' << result.top().first << ',' << result.top().second << ')' ;


  return 0;
 }

