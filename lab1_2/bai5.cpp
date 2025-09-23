#include <bits/stdc++.h>

using namespace std;

class Shape {
public:
    virtual double getArea() {}
    virtual double getPerimeter() {}

    virtual ~Shape() {}
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) {
        this->radius = r;
    }

    double getArea() override {
        return M_PI * radius * radius;
    }

    double getPerimeter() override {
        return 2 * M_PI * radius;
    }
};

class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double w, double h) {
        this->width = w;
        this->height = h;
    }

    double getArea() override {
        return width * height;
    }

    double getPerimeter() override {
        return 2 * (width + height);
    }
};

class Triangle : public Shape {
private:
    double a, b, c;
public:
    Triangle(double a, double b, double c) : a(a), b(b), c(c) {
        if (a + b < c || a + c < b || b + c < a) {
            this->a = 0;
            this->b = 0;
            this->c = 0;
        }
    }

    double getPerimeter() override {
        return a + b + c;
    }

    double getArea() override {
        double p = getPerimeter() / 2.0; 
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
};

void printShapeInfo(Shape &shape) {
    cout << shape.getArea() << endl
         << shape.getPerimeter() << endl;
}


int main() {
    Shape *shape[3]; 

    shape[0] = new Circle(2.0);
    shape[1] = new Rectangle(2.0, 3.0);
    shape[2] = new Triangle(3.0, 4.0, 5.0);

    double sum = 0;
    for (auto x : shape) {
        printShapeInfo(*x);
        sum += x->getArea();
    } 

    cout << sum << endl;

    for (auto x : shape) {
        delete x;
    }
}
