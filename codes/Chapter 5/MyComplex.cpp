#include <iostream>

class MyComplex {
 public:
  MyComplex(int r = 0, int i = 0) : mreal(r), mimage(i) {}

  MyComplex operator+(const MyComplex &other) {
    return MyComplex(this->mreal + other.mreal, this->mimage + other.mimage);
  }

  MyComplex operator++(int) { return MyComplex(mreal++, mimage++); }

  MyComplex &operator++() {
    mreal += 1;
    mimage += 1;
    return *this;
  }

  void operator+=(const MyComplex &other) {
    mreal += other.mreal;
    mimage += other.mimage;
  }

 private:
  int mreal;
  int mimage;
  friend MyComplex operator+(const MyComplex &c1, const MyComplex &c2);
  friend std::ostream &operator<<(std::ostream &out, const MyComplex &c);
};

MyComplex operator+(const MyComplex &c1, const MyComplex &c2) {
  return MyComplex(c1.mreal + c2.mreal, c1.mimage + c2.mimage);
}

std::ostream &operator<<(std::ostream &out, const MyComplex &c) {
  return out << c.mreal << "+" << c.mimage << "i";
}

int main() {
  MyComplex c1(10, 10);
  MyComplex c2(20, 20);
  std::cout << c1 << " " << c2 << std::endl;
  return 0;
}