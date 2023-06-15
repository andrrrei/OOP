/*
Дан класс
class A {
    int a;
    ~A() {} // деструктор закрыт
public:
...
Обеспечить возможность создания и удаления обьектов класса, не используя friend-функций.
Создать массив из N объектов в динамической или статической памяти с использованием
placement new (явный вызов конструктора для инициализации обьекта на предварительно
выделенной памяти). Затем уничтожить объекты и освободить память. 
*/

#include <iostream>

class A {

    int a;
    ~A() { std::cout << "Destructor" << std :: endl; }

public:

    A(int i = 0): a(i) {}
    int get_a() { return this->a; }
    
    static void destroy(A **arr_a, int N) {
        for (int i = 0; i < N; ++i) arr_a[i]->~A();
    }
    
};

int main() {

    int N;
    std::cin >> N;

    char *memory = new char[N*sizeof(A)];
    A *arr[N];
    for (int i = 0; i < N; i++) { 
        arr[i] = new (&memory[i*sizeof(A)]) A(i); 
    }
    for (int i = 0; i < N; i++) { 
        std::cout << arr[i]->get_a() << std::endl; 
    }
    
    A::destroy(arr, N);
    
    delete[] memory;

    return 0;

}