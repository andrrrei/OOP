#include <iostream>
#include <exception>

const double pi = 3.14159;

class Circle {
private:
    double radius;
    double x;
    double y;
    static int count;
    static int ring_count;

public:
    Circle(double r = 1, double x = 1, double y = 1) : radius(r), x(x), y(y) { count++; }

    ~Circle() { count--; }

    double get_radius() const { return radius; }

    double get_x() const { return x; }

    double get_y() const { return y; }

    virtual void print_info() const {
        std::cout << "Circle: Radius = " << radius << ", Center = (" << x << ", " << y << ")" << std::endl;
    }

    static int Circle_count() { return count - ring_count; }

    virtual double get_area() const { return pi * radius * radius; }

    friend class Ring;
    friend class ShapeScaler;
};

int Circle::count = 0;
int Circle::ring_count = 0;

class Ring : public Circle {
private:
    double inner_radius;
    static int count;

public:
    Ring(double outerRadius = 1, double innerRadius = 0, double x = 1, double y = 1) : Circle(outerRadius, x, y), inner_radius(innerRadius) {
        if (innerRadius > outerRadius) {
            try {
                throw "Inner radius cannot be greater than outer radius";
            }
            catch (const char * s) {
                std::cout << "Exception caught: " << s << std::endl;
                this->inner_radius = outerRadius;
            }
        }
        count++;
        ring_count++;
    }

    ~Ring() {
        count--;
        ring_count--;
    }

    double getInnerRadius() const {
        return inner_radius;
    }

    void print_info() const {
        std::cout << "Ring: Outer Radius = " << get_radius() << ", Inner Radius = " << inner_radius
                  << ", Center = (" << get_x() << ", " << get_y() << ")" << std::endl;
    }

    static int Ring_count() {
        return count;
    }

    double get_area() const {
        double s1 = Circle::get_area(); 
        return s1 - pi * inner_radius * inner_radius;
    }

    friend class ShapeScaler;
};

int Ring::count = 0;


void ptr_to(const Circle* ptr) {
    if (dynamic_cast<const Ring*>(ptr)) {
        std::cout << "Pointer points to a Ring object." << std::endl;
    }
    else {
        std::cout << "Pointer points to a Circle object." << std::endl;
    }
}

class ShapeScaler {
public:
    void scale(Circle& circle, double scaleFactor) {
        circle.radius *= scaleFactor;
    }

    void scale(Ring& ring, double scaleFactor) {
        ring.radius *= scaleFactor;
        ring.inner_radius *= scaleFactor;
    }
};


int main() {
    Circle circle1;
    Circle circle2(2, 3, 4);

    Ring ring1;
    Ring ring2(2, 3, 1);

    Circle circle3(1, 2, 3);

    circle1.print_info();
    circle2.print_info();
    ring1.print_info();
    ring2.print_info();
    circle3.print_info();

    ptr_to(&circle1);
    ptr_to(&ring1);

    ShapeScaler scaler;
    scaler.scale(circle1, 2.5);
    scaler.scale(ring1, 1.8);
    circle1.print_info();
    ring1.print_info();

    std::cout << circle2.get_area() << std::endl;
    std::cout << ring1.get_area() << std::endl;

    std::cout << "Circle count: " << Circle::Circle_count() << std::endl;
    std::cout << "Ring count: " << Ring::Ring_count() << std::endl;

    return 0;
}