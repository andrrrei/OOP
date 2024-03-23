#include <iostream>

class Arr {
    int *arr;
    int size;

public:
    // Constructor
    Arr(int s, int date = 0) : size(s) {
        arr = new int[s];
        for (int i = 0; i < size; arr[i++] = date);
    }

    // Copy assignment operator
    void operator= (const Arr &mas) { // if size not equal
        for (int i = 0; i < mas.size; i++) {
            arr[i] = mas.arr[i];
        }
    }

    // Subscript operator for reading and writing
    int& operator[](int j) {
        return arr[j];
    }

    // Bitwise OR assignment operator
    void operator|= (int num) {
        num = ~(this->arr[0]);
        for (int i = 0; i < this->size; i++) {
            this->arr[i] = this->arr[i] | num;
        }
    }

    // Friend function for overloading output operator
    friend std::ostream& operator<< (std::ostream &out, const Arr &mas);

    // Friend functions for overloading bitwise OR operator
    friend Arr operator| (const Arr& mas1, const Arr& mas2);
    friend Arr operator| (const Arr& mas1, int num);

    // Friend function for overloading unary minus operator
    friend Arr operator- (const Arr& mas);

    // Destructor
    ~Arr() { delete[] arr; }
};

// Overloading output operator to print array elements
std::ostream& operator<< (std::ostream &out, const Arr &mas) {
    for (int i = 0; i < mas.size; i++) {
        out << mas.arr[i] << ' ';
    }
    out << std::endl;
    return out;
}

// Overloading bitwise OR operator for two arrays
Arr operator| (const Arr& mas1, const Arr& mas2) {
    int size = std::min(mas1.size, mas2.size);
    Arr res(size);
    for (int i = 0; i < size; i++) {
        res[i] = mas1.arr[i] | mas2.arr[i];
    }
    return res;
}

// Overloading bitwise OR operator for an array and an integer
Arr operator| (const Arr& mas, int num) {
    Arr res(mas.size);
    num = 0;
    for (int i = 0; i < mas.size; i++) {
        res[i] = mas.arr[i] | num;
    }
    return res;
}

// Overloading unary minus operator
Arr operator- (const Arr& mas) {
    Arr res(mas.size);
    for (int i = 0; i < mas.size; i++) {
        res[i] = -mas.arr[i];
    }
    return res;
}

int main() {
    // Creating array objects with different sizes and initial values
    Arr a1(15), a2(20, 5), a3(30, 3);
    const Arr a4(5);

    // Printing the arrays
    std::cout << "a1: " << a1 << "a2: " << a2 << "a3: " << a3 << "a4: " << a4;

    // Using bitwise OR operator with an integer
    a2 = a2 | 2; // object a2 does not change here
    std::cout << "a2: " << a2;

    // Using bitwise OR assignment operator with an integer
    a2 |= 1; // object a2 changes here
    a3 = (-a2) | (-a4);
    a3[5] = 10;
    a1 = a4 | a3;

    // Printing the arrays after operations
    std::cout << "a1: " << a1 << "a2: " << a2 << "a3: " << a3 << "a4: " << a4;

    return 0; // Exit with success status
}

