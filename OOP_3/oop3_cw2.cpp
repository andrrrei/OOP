#include <iostream>

class A {
    int a;
    ~A() { std::cout << "Destructor" << std :: endl; } // Private destructor
public:
    A(int i = 0): a(i) {} // Public constructor
    int get_a() { return this->a; } // Public method to get 'a'

    // Static method to destroy objects in an array
    static void destroy(A **arr_a, int N) {
        for (int i = 0; i < N; ++i) arr_a[i]->~A(); // Explicitly call destructor
    }
};

int main() {
    int N;
    std::cin >> N; 

    char *memory = new char[N*sizeof(A)];
    A *arr[N];

    for (int i = 0; i < N; i++) {
        arr[i] = new (&memory[i*sizeof(A)]) A(i); // Construct objects using placement new
    }

    for (int i = 0; i < N; i++) {
        std::cout << arr[i]->get_a() << std::endl;
    }
    
    A::destroy(arr, N);
    
    delete[] memory;

    return 0;
}

