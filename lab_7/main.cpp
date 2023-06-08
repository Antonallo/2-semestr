#include <iostream>

const double PI = 3.14;

class Shape {
protected:
    double x, y; // координаты центра фигуры
    std::string color; // цвет фигуры
public:
    Shape(double x, double y, std::string color) : x(x), y(y), color(color) {}
    virtual double area() = 0; // чисто виртуальная функция для вычисления площади фигуры
};

class Triangle : public Shape {
private:
    double a, b, c; // стороны треугольника
public:
    Triangle(double x, double y, std::string color, double a, double b, double c) : Shape(x, y, color), a(a), b(b), c(c) {}
    double area() override {
        double p = (a + b + c) / 2; // полупериметр
        return std::sqrt(p * (p - a) * (p - b) * (p - c)); // формула Герона для вычисления площади
    }
};

class Rectangle : public Shape {
private:
    double width, height; // ширина и высота прямоугольника
public:
    Rectangle(double x, double y, std::string color, double width, double height) : Shape(x, y, color), width(width), height(height) {}
    double area() override {
        return width * height; // площадь прямоугольника
    }
};

class Circle : public Shape {
private:
    double radius; // радиус круга
public:
    Circle(double x, double y, std::string color, double radius) : Shape(x, y, color), radius(radius) {}
    double area() override {
        return  PI * radius * radius; // площадь круга
    }
};

int main() {
    Shape* shapes[3];
    shapes[0] = new Triangle(0, 0,"blue", 3, 4, 5);
    shapes[1] = new Rectangle(0, 0,"red", 5, 6);
    shapes[2] = new Circle(0, 0, "green", 7);

    for (int i = 0; i < 3; i++) {
        std::cout << "Area of shape " << i << " is " << shapes[i]->area() << std::endl;
    }

    return 0;
}