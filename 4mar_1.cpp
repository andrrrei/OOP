#include <iostream>

class A {
    int a;
    A(int i = 0) : a(i) {};
    A(const A& x) {
        this->a = x.a;
    }
public:
    /*A(const A& x) {
        this->a = x.a;
    }*/
    static A* ptr;
    static int cnt;
    static A* create(int x = 0) {
        if (cnt == 0) {
            ptr = new A(x);
            cnt++;
        }
        return ptr;
    }
    void print() const {
        std::cout << a << std::endl;
    }

};
int A::cnt = 0;
A* A::ptr = NULL;

int main() {
    A* a1 = A::create(1);
    (*a1).print();
    A* a2 = A::create(2);
    (*a2).print();
    return 0;
}