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

class Light {
 public:
  virtual void show() = 0;
};

class BmwLight : public Light {
 public:
  void show() { cout << "BMW Light" << endl; }
};

class AudiLight : public Light {
 public:
  void show() { cout << "Audi Light" << endl; }
};

class AbstractFactory {
 public:
  virtual Car* createCar(string name) = 0;
  virtual Light* createLight() = 0;
};

class BMWFactory : public AbstractFactory {
 public:
  Car* createCar(string name) { return new Bmw(name); }
  Light* createLight() { return new BmwLight(); }
};

class AudiFactory : public AbstractFactory {
 public:
  Car* createCar(string name) { return new Audi(name); }
  Light* createLight() { return new AudiLight(); }
};