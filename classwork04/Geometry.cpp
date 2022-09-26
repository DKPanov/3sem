// Shape.cpp : Ётот файл содержит функцию "main". «десь начинаетс€ и заканчиваетс€ выполнение программы.
//

#include<iostream>
#include<vector>
#include<cmath>

struct Point {
    int x = 0;
    int y = 0;
};

// Abstract class
class Shape {
protected:
    std::vector<Point> storage_;  // хранилище угловых точек дл€ фигуры
protected:
    double distance(Point first, Point second) const{
        return sqrt((first.x - second.x) * (first.x - second.x) + (first.y - second.y) * (first.y - second.y));
    }
public: // ќбъ€вите методы area, perimeter, center
    virtual double perimeter() const = 0;
    virtual double area() const = 0;
    virtual Point center() const = 0;
    virtual ~Shape() = default;
};

class Triangle : public Shape {
public:
    Triangle(Point first, Point second, Point third) {
        storage_.push_back(first);
        storage_.push_back(second);
        storage_.push_back(third);
    }
    double perimeter() const override{
        return distance(storage_[0], storage_[1]) + distance(storage_[1], storage_[2]) + distance(storage_[0], storage_[2]);
    }
    double area() const override{
        double p = perimeter() / 2;
        return sqrt(p * (p - distance(storage_[0], storage_[1])) * (p - distance(storage_[1], storage_[2])) * (p - distance(storage_[0], storage_[2])));
    }
    Point center() const override{
        return {(storage_[0].x + storage_[1].x + storage_[2].x) / 3,  (storage_[0].y + storage_[1].y + storage_[2].y) / 3};
    }
};


class Square : public Shape {
public:
    Square(Point first, Point second, Point third, Point fourth) {
        storage_.push_back(first);
        storage_.push_back(second);
        storage_.push_back(third);
        storage_.push_back(fourth);
    }
    double perimeter() const override {
        return std::min(distance(storage_[0], storage_[1]), distance(storage_[0], storage_[2])) * 4;
    }
    double area() const override {
        return perimeter() * perimeter() / 16;
    }
    Point center() const override {
        int min_x = std::min(std::min(storage_[0].x, storage_[1].x), storage_[2].x);
        int max_x = std::max(std::max(storage_[0].x, storage_[1].x), storage_[2].x);
        int min_y = std::min(std::min(storage_[0].y, storage_[1].y), storage_[2].y);
        int max_y = std::max(std::max(storage_[0].y, storage_[1].y), storage_[2].y);
        return { (min_x + max_x) / 2, (min_y + max_y) / 2 };
    }
};

class Line : public Shape {
public:
    Line(Point first, Point second) {
        storage_.push_back(first);
        storage_.push_back(second);
    }
    double perimeter() const override {
        return distance(storage_[0], storage_[1]);
    }
    double area() const override {
        return 0;
    }
    Point center() const override {
        return { (storage_[0].x + storage_[1].x) / 2,  (storage_[0].y + storage_[1].y) / 2 };
    }
};

int main(){
    std::vector<Shape*> shapes;
    Point a{ 0, 0 }, b{ 0, 10 }, c{ 10, 10 }, d{ 10 ,0 };
    shapes.push_back(new Triangle(a, b, c));
    shapes.push_back(new Square(a, b, c, d));
    shapes.push_back(new Line(a, c));

    std::cout << "Triangle: " << shapes[0]->perimeter() << " " << shapes[0]->area() << " (" << shapes[0]->center().x << "," << shapes[0]->center().y << ")" << std::endl;
    std::cout << "Square: " << shapes[1]->perimeter() << " " << shapes[1]->area() << " (" << shapes[1]->center().x << "," << shapes[1]->center().y << ")" << std::endl;
    std::cout << "Line: " << shapes[2]->perimeter() << " " << shapes[2]->area() << " (" << shapes[2]->center().x << "," << shapes[2]->center().y << ")" << std::endl;

    delete shapes[0];
    delete shapes[1];
    delete shapes[2];

    return 0;
}
