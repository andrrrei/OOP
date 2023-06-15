/* Не изменяя оператор return и не используя символов /, \, ", %, #, добавьте всё
необходимое в описание класса А так, чтобы компиляция прошла без ошибок.
*/

#include <iostream>

class A {
    int a;
public:
    A(int x = 0) { 
        this-> a = x; 
    }
    A operator [] (int i) { 
        return *this;
    }
    A operator , (A a) {
        return a;
    }
    int operator () (A a1, A a2) {
        return 1;
    }
    operator int() {
        return a; 
    }
    int f() {
        A i, j;
        return (i, j)[i, j](i, j);
    }
};

int main() {
    A x;
    x.f();
}