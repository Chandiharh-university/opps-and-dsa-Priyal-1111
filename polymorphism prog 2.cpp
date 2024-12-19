#include <iostream>
#include <cmath> // For mathematical functions
using namespace std;

// Base class
class Shape {
public:
    // Virtual function to calculate area
    virtual void calculateArea() {
        cout << "This is a generic shape.\n";
    }

    // Virtual destructor
    virtual ~Shape() {}
};

// Derived class: Circle
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    void calculateArea() override {
        double area = M_PI * radius * radius; // Area = π * r^2
        cout << "Circle Area: " << area << endl;
    }
};

// Derived class: Rectangle
class Rectangle : public Shape {
private:
    double length, width;

public:
    Rectangle(double l, double w) : length(l), width(w) {}

    void calculateArea() override {
        double area = length * width; // Area = length * width
        cout << "Rectangle Area: " << area << endl;
    }
};

int main() {
    Shape* shape; // Base class pointer

    // Circle object
    Circle circle(5.0);
    shape = &circle;
    cout << "Circle:\n";
    shape->calculateArea();

    // Rectangle object
    Rectangle rectangle(4.0, 6.0);
    shape = &rectangle;
    cout << "\nRectangle:\n";
    shape->calculateArea();

    return 0;
}
