#include <iostream>
#include <string>
#include <unistd.h>

// Base class representing an electronic standard
class ElectronicStandard {
protected:
    static inline int cord_type; // Static member variable for cord type
    std::string standard_name; // Name of the standard
    const int device_type; // Type of the device

public:
    // Constructors
    ElectronicStandard() : device_type(0) {
        standard_name = "zero";
    }
    ElectronicStandard(int newelem) : device_type(newelem) {
    }

    // Method to set the cord type
    void set_cord(int num) {
        cord_type = num;
    }

    // Getter methods
    std::string get_name() {
        return standard_name;
    }
    int get_cord() {
        return cord_type;
    }
    int get_device() {
        return device_type;
    }

    // Friend function declaration
    friend void get_standard(ElectronicStandard *x);
};

// Class representing a phone
class Phone : protected virtual ElectronicStandard {
    int number; // Phone number

public:
    // Method to make a call
    void call(int x) {
        std::cout << x << " Audio call" << std::endl;
    }

    // Getter method for the phone number
    int get_number() {
        return number;
    }

    // Constructor
    Phone() : ElectronicStandard(1) {
        number = 1234;
        standard_name = "one";
        set_cord(10);
    }
};

// Class representing a monitor
class Monitor : protected virtual ElectronicStandard {
    int resolution[2]; // Resolution of the monitor
    int frequency; // Refresh frequency

public:
    // Method to draw on the monitor
    virtual void draw() {
        for(int i = 0; i < resolution[0]; i++) {
            for(int j = 0; j < resolution[1]; j++) {
                std::cout << "*";
            }
            std::cout << "\n";
        }
    }

    // Getter methods
    double get_latency() {
        return 100.0 / frequency;
    }
    int get_resolution() {
        return resolution[1];
    }

    // Constructor
    Monitor() : ElectronicStandard(0) {
        resolution[0] = 18;
        resolution[1] = 9;
        frequency = 120;
        standard_name = "two";
        set_cord(20);
    }
};

// Class representing a smartphone, inheriting from both Monitor and Phone
class Smartphone : public Monitor, public Phone {
public:
    // Method to make a video call
    void call(int x) {
        std::cout << x << " Video call" << std::endl;
    }

    // Method to display firmware information
    void firmware() {
        std::cout << get_name() << std::endl;
        std::cout << get_resolution() << std::endl;
        std::cout << get_number() << std::endl;
    }

    // Method to draw on the smartphone
    void draw() {
        sleep(get_latency());
        Monitor::draw();
    }

    // Constructor
    Smartphone() : ElectronicStandard(0) {}
};

// Function to display a monitor
void display(Monitor *x) {
    x->draw();
}

// Friend function to get standard information
void get_standard(ElectronicStandard *x) {
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

    // Get standard information for each device
    get_standard(&X1);
    get_standard((ElectronicStandard*)&Siemens);
    get_standard((ElectronicStandard*)&LG);

    return 0; 
}

