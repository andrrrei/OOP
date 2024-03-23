#include <iostream>

class A {
    int a; // Private member variable 'a'
    A(int i = 0) : a(i) {}; // Private constructor with default argument
    A(const A& x) { // Private copy constructor
        this->a = x.a;
    }
public:
    static A* ptr; // Static pointer to manage singleton instance
    static int cnt; 
    static A* create(int x = 0) { // Static method to create an instance of A
        if (cnt == 0) { 
            ptr = new A(x); 
            cnt++; /
        }
        return ptr;
    }
    void print() const { // Public method to print the value of 'a'
        std::cout << a << std::endl;
    }
};

// Initialize static members
int A::cnt = 0;
A* A::ptr = nullptr;

int main() {

    A* a1 = A::create(1);
    (*a1).print();


    A* a2 = A::create(2);
    (*a2).print(); 

    return 0;
}

