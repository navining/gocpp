#include <iostream>
#include <string>
using namespace std;

class Car {
 public:
  Car(string name) : _name(name) {}
  virtual void show() = 0;

 protected:
  string _name;
};

class Bmw : public Car {
 public:
  Bmw(string name) : Car(name) {}
  void show() { cout << "BMW: " << _name << endl; }
};

class Audi : public Car {
 public:
  Audi(string name) : Car(name) {}
  void show() { cout << "Audi: " << _name << endl; }
};

enum CarType { BMW, AUDI };

class SimpleFactory {
 public:
  Car* createCar(CarType ct) {
    switch (ct) {
      case BMW:
        return new Bmw("X1");
      case AUDI:
        return new Audi("A6");
    }
    return nullptr;
  }
};