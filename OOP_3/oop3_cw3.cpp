#include <iostream>

class A {
    int a; 
public:
    A(int x = 0) { 
        this-> a = x; 
    }

    // Overloaded subscript operator []
    A operator [] (int i) { 
        return *this; 
    }

    // Overloaded comma operator ,
    A operator , (A a) {
        return a;
    }

    // Overloaded function call operator ()
    int operator () (A a1, A a2) {
        return 1;
    }

    // Conversion operator to int
    operator int() {
        return a;
    }

    // Method which demonstrates the usage of overloaded operators
    int f() {
        A i, j; 
        return (i, j)[i, j](i, j); 
    }
};

int main() {
    A x; 
    x.f(); 
    return 0;
}

