#include <iostream>
using namespace std;

class Car {
 public:
  virtual void show() = 0;
};

class Bmw : public Car {
 public:
  void show() { cout << "This is a BMW" << endl; }
};

class Audi : public Car {
 public:
  void show() { cout << "This is an Audi" << endl; }
};

class Benz : public Car {
 public:
  void show() { cout << "This is a Benz" << endl; }
};

class CarDecorator1 : public Car {
 public:
  CarDecorator1(Car *p) : pCar(p) {}
  ~CarDecorator1() { delete pCar; }
  void show() {
    pCar->show();
    cout << "Feature 1" << endl;
  }

 private:
  Car *pCar;
};

class CarDecorator2 : public Car {
 public:
  CarDecorator2(Car *p) : pCar(p) {}
  ~CarDecorator2() { delete pCar; }
  void show() {
    pCar->show();
    cout << "Feature 2" << endl;
  }

 private:
  Car *pCar;
};

class CarDecorator3 : public Car {
 public:
  CarDecorator3(Car *p) : pCar(p) {}
  ~CarDecorator3() { delete pCar; }
  void show() {
    pCar->show();
    cout << "Feature 3" << endl;
  }

 private:
  Car *pCar;
};