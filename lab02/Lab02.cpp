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
     Rectangle();
     Rectangle(Point const &right_up_angle);

     Rectangle operator+(Rectangle const &other) const;
     Rectangle operator*(Rectangle const &other) const;

     void print() const;

     Point RightUpAngle() const;

 };

 Rectangle::Rectangle() : right_up_angle_(0,0) {};
 Rectangle::Rectangle(Point const &right_up_angle) : right_up_angle_(right_up_angle) {};

 Rectangle Rectangle::operator+(Rectangle const &other) const{
     Point maxy = other.right_up_angle_.maxy(right_up_angle_);
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
 std::stack <char> stack;

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

 std::stack <std::pair<unsigned long long, unsigned long long>> result;
 for (size_t i = 0; i < parsed.size(); i++){
    if(parsed[i] == '('){
        std::pair<unsigned long long, unsigned long long> pair = {0,0}; //pair - это структура
        i++;
        while(parsed[i] != ','){
            pair.first *= 10;
            pair.first += parsed[i++] - '0'; //т.к. parsed[i] - это char, чтобы получить нужное нам значение, нужно вычесть код нуля
        }
        i++;
        while(parsed[i] != ')'){
            pair.second *= 10;
            pair.second += parsed[i++] - '0';
        }
        result.push(pair);
    }

    if(parsed[i] == '+'){
        Point first(result.top().first, result.top().second);
        result.pop();
        Point second(result.top().first, result.top().second);
        result.pop();
        Rectangle first_rec(first);
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

