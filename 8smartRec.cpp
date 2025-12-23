#include <vector>
#include <iostream>

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

class Rectangle {
private:
    double width, height;
    Point bottomLeft;

public:
    explicit Rectangle(double w = 2, double h = 3, double x = 0, double y = 0)
    : width(w), height(h), bottomLeft(x, y) {}

    Rectangle(const Rectangle& other)
            : width(other.width), height(other.height), bottomLeft(other.bottomLeft) {
        std::cout << "Конструктор копирования" << std::endl;
    }

    Rectangle& operator=(const Rectangle& other) {
        if (this != &other) {
            width = other.width;
            height = other.height;
            bottomLeft = other.bottomLeft;
        }
        std::cout<<"Оператор присваниявания"<<std::endl;
        return *this;
    }

    double getPositionX() {

        return bottomLeft.x;
    }
    double getPositionY() {

        return bottomLeft.y;
    }

    double getArea() const {
        return width * height;
    }

    std::vector<Point> getAllCorners() const {
        return {
            bottomLeft, Point(bottomLeft.x + width, bottomLeft.y), Point(bottomLeft.x + width, bottomLeft.y + height), Point(bottomLeft.x, bottomLeft.y + height)
        };
    }

    bool intersects(const Rectangle& other) const {
        double l1 = bottomLeft.x, r1 = l1 + width;
        double b1 = bottomLeft.y, t1 = b1 + height;
        double l2 = other.bottomLeft.x, r2 = l2 + other.width;
        double b2 = other.bottomLeft.y, t2 = b2 + other.height;
        return !(r1 <= l2 || r2 <= l1 || t1 <= b2 || t2 <= b1);
    }

    bool contains(const Point& p) const {
        return (p.x >= bottomLeft.x && p.x <= bottomLeft.x + width && p.y >= bottomLeft.y && p.y <= bottomLeft.y + height);
    }

    Rectangle& moveTo(double x, double y) {
        bottomLeft.x = x;
        bottomLeft.y = y;
        return *this;
    }

    Rectangle& resize(double w, double h) {
        width = w;
        height = h;
        return *this;
    }
};

int main() {
    Rectangle r1(4, 3, 1, 1);
    Rectangle r2 = r1;
    Rectangle r3;
    r3 = r1;
    Point p(6, 6);

    std::cout << "Площадь: " << r1.getArea() << std::endl;

    std::cout << "Точка лежит?: " <<  r1.contains(p) << std::endl;

    r1.resize(5, 5);
    std::cout << "Новая площадь: " << r1.getArea() << std::endl;

    r1.moveTo(2,2);
    std::cout<< "Нижний левый угол перенесен в точку: "<< r1.getPositionX() << " "<< r1.getPositionY() << std::endl;

    std::cout << "Точка лежит?: " <<  r1.contains(p) << std::endl;

    Rectangle r4(2, 2, 1, 1);
    std::cout << "Пересечение: " << r1.intersects(r4) << std::endl;

    return 0;
};