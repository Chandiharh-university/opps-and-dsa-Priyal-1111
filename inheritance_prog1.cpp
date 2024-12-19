#include <iostream>
#include <string>
using namespace std;

// Base class
class Vehicle {
protected:
    string brand;
    int wheels;

public:
    Vehicle(string b, int w) : brand(b), wheels(w) {}

    void displayInfo() {
        cout << "Brand: " << brand << ", Wheels: " << wheels << endl;
    }
};

// Derived class for Cars
class Car : public Vehicle {
private:
    int numDoors;

public:
    Car(string b, int w, int d) : Vehicle(b, w), numDoors(d) {}

    void displayCarInfo() {
        displayInfo();
        cout << "Number of Doors: " << numDoors << endl;
    }
};

// Derived class for Bikes
class Bike : public Vehicle {
private:
    bool hasCarrier;

public:
    Bike(string b, int w, bool carrier) : Vehicle(b, w), hasCarrier(carrier) {}

    void displayBikeInfo() {
        displayInfo();
        cout << "Has Carrier: " << (hasCarrier ? "Yes" : "No") << endl;
    }
};

int main() {
    // Create a Car object
    Car car("Toyota", 4, 4);
    cout << "Car Information:\n";
    car.displayCarInfo();

    // Create a Bike object
    Bike bike("Yamaha", 2, true);
    cout << "\nBike Information:\n";
    bike.displayBikeInfo();

    return 0;
}
