#include <iostream>
using namespace std;

class Goods {
 public:  // Methods
  // Initialize goods information
  Goods(const char *name, double price, int amount);
  // Print goods information
  void show();
  // Getters
  void setName(const char *name) { strcpy(_name, name); }
  void setPrice(double price) { _price = price; };
  void setAmount(int amount) { _amount = amount; };
  // Setters
  const char *getName() { return _name; };
  double getPrice() { return _price; };
  int getAmount() { return _amount; };
  static void showCounts();

 private:  // Variables
  char _name[20];
  double _price;
  int _amount;
  Date _date;
  static int _count;
};

int Goods::_count = 0;

Goods::Goods(const char *name, double price, int amount, int y, int m, int d)
    : _date(y, m, d), _price(price), _amount(amount) {
  strcpy(_name, name);
  count++;
}

void Goods::show() {
  cout << "name: " << _name << endl;
  cout << "price: " << _price << endl;
  cout << "amount: " << _amount << endl;
  _date.show();
};

void Goods::show() const {
  cout << "name: " << _name << endl;
  cout << "price: " << _price << endl;
  cout << "amount: " << _amount << endl;
  _date.show();
};

static void Goods::showCounts() { cout << "Counts: " << _count << endl; }

class Date {
 public:
  Date(int y, int m, int d) {
    _year = y;
    _month = m;
    _date = d;
  }

  void show() { cout << _year << "/" << _month << "/" << _day << endl; }

  void show() const { cout << _year << "/" << _month << "/" << _day << endl; }

 private:
  int _yead;
  int _month;
  int _date;
}