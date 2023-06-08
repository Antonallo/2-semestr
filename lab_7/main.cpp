#include <iostream>

const double PI = 3.14;

class Shape {
protected:
    double x, y; // ���������� ������ ������
    std::string color; // ���� ������
public:
    Shape(double x, double y, std::string color) : x(x), y(y), color(color) {}
    virtual double area() = 0; // ����� ����������� ������� ��� ���������� ������� ������
};

class Triangle : public Shape {
private:
    double a, b, c; // ������� ������������
public:
    Triangle(double x, double y, std::string color, double a, double b, double c) : Shape(x, y, color), a(a), b(b), c(c) {}
    double area() override {
        double p = (a + b + c) / 2; // ������������
        return std::sqrt(p * (p - a) * (p - b) * (p - c)); // ������� ������ ��� ���������� �������
    }
};

class Rectangle : public Shape {
private:
    double width, height; // ������ � ������ ��������������
public:
    Rectangle(double x, double y, std::string color, double width, double height) : Shape(x, y, color), width(width), height(height) {}
    double area() override {
        return width * height; // ������� ��������������
    }
};

class Circle : public Shape {
private:
    double radius; // ������ �����
public:
    Circle(double x, double y, std::string color, double radius) : Shape(x, y, color), radius(radius) {}
    double area() override {
        return  PI * radius * radius; // ������� �����
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