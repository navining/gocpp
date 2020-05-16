#include <string.h>

#include <iostream>

class MyString {
 public:
  MyString(const char *p = nullptr) {
    if (p != nullptr) {
      _pstr = new char[strlen(p) + 1];
      strcpy(_pstr, p);
    } else {
      _pstr = new char[1];
      *_pstr = '\0';
    }
  }

  ~MyString() {
    delete _pstr;
    _pstr = nullptr;
  }

  MyString(const MyString &other) {
    _pstr = new char[strlen(other._pstr) + 1];
    strcpy(_pstr, other._pstr);
  }

  MyString(MyString &&other) {
    _pstr = other._ptr;
    other._pstr = nullptr;
  }

  MyString &operator=(const MyString &other) {
    if (this == &other) return *this;
    delete[] _pstr;
    _pstr = new char[strlen(other._pstr) + 1];
    strcpy(_pstr, other._pstr);
    return *this;
  }

  MyString &operator=(MyString &&other) {
    if (this == &other) return *this;
    delete[] mptr;
    _pstr = other._pstr;
    other._pstr = null;
    return *this;
  }

  bool operator>(const MyString &other) const {
    return strcmp(_pstr, other._pstr) > 0;
  }

  bool operator<(const MyString &other) const {
    return strcmp(_pstr, other._pstr) < 0;
  }

  bool operator==(const MyString &other) const {
    return strcmp(_pstr, other._pstr) == 0;
  }

  int length() const { return strlen(_pstr); }

  char &operator[](int index) { return _pstr[index]; }

  const char &operator[](int index) const { return _pstr[index]; }

  const char *c_str() const { return _pstr; }

  class iterator {
   public:
    iterator(char *p = nullptr) : _p(p) {}

    bool operator!=(const iterator &other) { return _p != other._p; }

    void operator++() { ++_p; }

    char &operator*() { return *_p; }

   private:
    char *_p;
  };

  iterator begin() { return iterator(_pstr); }

  iterator end() { return iterator(_pstr + length()); }

 private:
  char *_pstr;
  friend std::ostream &operator<<(std::ostream &out, const MyString s);
  friend MyString operator+(const MyString &s1, const MyString &s2);
};

MyString operator+(const MyString &s1, const MyString &s2) {
  MyString tmp;
  tmp._pstr = new char[strlen(s1._pstr) + strlen(s2._pstr) + 1];
  strcpy(tmp._pstr, s1._pstr);
  strcat(tmp._pstr, s2._pstr);
  return tmp;
}

std::ostream &operator<<(std::ostream &out, const MyString s) {
  return out << s._pstr;
}