#include <iostream>
#include <string>
#include <unistd.h>


class ElectronicStandard {
protected:
    static inline int cord_type;
    std::string standard_name;
    const int device_type;

public: 
    ElectronicStandard() : device_type(0) {
        standard_name = "zero";
    }
    ElectronicStandard(int newelem) : device_type(newelem) {
    }
    void set_cord(int num) {
        cord_type = num;
    }
    std::string get_name() {
        return standard_name;
    }
    int get_cord() {
        return cord_type;
    }
    int get_device() {
        return device_type;
    }
    friend void get_standard(ElectronicStandard *x);
};


class Phone : protected virtual ElectronicStandard {
    int number;
public:
    void call(int x) {
        std::cout << x << " Audio call" << std::endl;
    }
    int get_number() {
        return number;
    }
    Phone() : ElectronicStandard(1) {
        number = 1234;
        standard_name = "one";
        set_cord(10);
    }
};


class Monitor : protected virtual ElectronicStandard {
    int resolution[2];
    int frequency;
public:
    virtual void draw() {
        for(int i = 0; i < resolution[0]; i++) {
            for(int j = 0; j < resolution[1]; j++) {
                std::cout << "*";
            }
            std::cout << "\n";
        }
    }
    double get_latency() {
        return 100/frequency;
    }
    int get_resolution() {
        return resolution[1];
    }
    Monitor() : ElectronicStandard(0) {
        resolution[0] = 18;
        resolution[1] = 9;
        frequency = 120;
        standard_name = "two";
        set_cord(20);
    }
};


class Smartphone : public Monitor, public Phone {
public:
    void call(int x) {
        std::cout << x << " Video call" << std::endl;
    }
    void firmware() {
        std::cout << get_name() << std::endl;
        std::cout << get_resolution() << std::endl;
        std::cout << get_number() << std::endl;
    }
    void draw() {
        sleep(get_latency());
        Monitor::draw();
    }

    Smartphone() : ElectronicStandard(0) {}
};

void display(Monitor *x) {
    x->draw();
}

void get_standard(ElectronicStandard *x){
    std::cout << "Standard name: " << x->get_name() << std::endl;
    std::cout << "Cord type: " << x->get_cord() << std::endl;
    std::cout << "Device type: " << x->get_device() << std::endl;
}


int main() {

    ElectronicStandard X1;
    X1.set_cord(20);

    Smartphone iPhone;
    iPhone.call(8800555);

    Phone Siemens;
    Siemens.call(8985935);

    Monitor LG;
    std::cout << "Monitor looks like:" << std::endl;
    display(&LG);
    
    std::cout << "Smartphone looks like:" << std::endl;
    iPhone.draw();

    get_standard(&X1);
    get_standard((ElectronicStandard*) &Siemens);
    get_standard((ElectronicStandard*) &LG);
}
