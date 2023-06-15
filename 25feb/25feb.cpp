#include <iostream>

class Arr { 
    int * arr;
    int size;
public:
    Arr(int s, int date = 0) : size(s) {
        arr = new int[s];
        for (int i = 0; i < size; arr[i++] = date);
    }
    /*Arr(const Arr &mas) {
        size = mas.size;
		arr = new int[size];
		for(int i = 0; i < size; i++){
			arr[i] = mas.arr[i];
		}
        std::cout << "cc" << std::endl;
	}*/

    void operator= (const Arr &mas) { // if size not equal
        for (int i = 0; i < mas.size; i++) {
            arr[i] = mas.arr[i];
        }
    }

    int& operator[](int j)
    {
        return arr[j];
    }
    
    void operator|= (int num) {
        num = ~(this->arr[0]);
        for (int i = 0; i < this->size; i++) {
            this->arr[i] = this->arr[i] | num;
        }
    }

    friend std::ostream& operator<< (std::ostream &out, const Arr &mas);
    friend Arr operator| (const Arr& mas1, const Arr& mas2);
    friend Arr operator| (const Arr& mas1, int num);
    friend Arr operator- (const Arr& mas);

    ~Arr() { delete [] arr; }
};


std::ostream& operator<< (std::ostream &out, const Arr &mas)
{
    for (int i = 0; i < mas.size; i++) {
        out << mas.arr[i] << ' ';
    }
    out << std::endl;
    return out; 
}

Arr operator| (const Arr& mas1, const Arr& mas2) {
    int size = std::min(mas1.size, mas2.size);
    Arr res(size);
    for (int i = 0; i < size; i++) {
        res[i] = mas1.arr[i] | mas2.arr[i];
    }
    return res;
}

Arr operator| (const Arr& mas, int num) {
    Arr res(mas.size);
    num = 0;
    for (int i = 0; i < mas.size; i++) {
        res[i] = mas.arr[i] | num;
    }
    return res;
}


Arr operator- (const Arr& mas) {
    Arr res(mas.size);
    for (int i = 0; i < mas.size; i++) {
        res[i] = -mas.arr[i];
    }
    return res;
}


int main() {
    Arr a1(15), a2(20, 5), a3(30, 3);
    const Arr a4(5);
    std::cout << "a1: " << a1 << "a2: " << a2 << "a3: " << a3 << "a4: " << a4;
    a2 = a2 | 2; // объект a2 здесь не меняется
    std::cout << "a2: " << a2;
    a2 |= 1; // а здесь меняется
    a3 = (-a2) | (-a4);
    a3[5] = 10;
    a1 = a4 | a3;
    std::cout << "a1: " << a1 << "a2: " << a2 << "a3: " << a3 << "a4: " << a4;
    return 0;
}