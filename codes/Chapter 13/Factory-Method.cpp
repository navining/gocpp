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

class Factory {
 public:
  virtual Car* createCar(string name) = 0;
};

class BMWFactory : public Factory {
 public:
  Car* createCar(string name) { return new Bmw(name); }
};

class AudiFactory : public Factory {
 public:
  Car* createCar(string name) { return new Audi(name); }
};