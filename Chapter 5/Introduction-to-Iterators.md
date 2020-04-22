# Introduction to Iterators

Using what we have learnt about operator overloading, we write a *MyString* class. This class resembles *std::string*, which maintains a *char \** type pointer, and implement basic string indexing, comparison, and concatenation.

```cpp
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

  MyString &operator=(const MyString &other) {
    if (this == &other) return *this;
    delete[] _pstr;
    _pstr = new char[strlen(other._pstr) + 1];
    strcpy(_pstr, other._pstr);
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
  return s;
}

std::ostream &operator<<(std::ostream &out, const MyString s) {
  return out << s._pstr;
}
```

We can also regard our string class as a container, which contains a series of characters. However, there is another important feature not realized yet, which is the iteration of containers. 

There are many types of containers in C++ Standard Template Libraries whose underlying data structures are different. These data structures are private members and are not exposed to users directly. **Iterators** are pointers pointing to elements inside a container. We can use iterators to move through the contents of the container, without knowing the specific ways of memory storage. In other word, iterators are abstract interfaces that give users transparent access to elements inside the container. Iterators are widely used in C++ generic algorithms. These algorithms need to traverse the container in a uniform way, therefore taking container iterators as parameters.

Iterator is implemented as a nested class of the container, and four methods need to be defined. *begin()* returns the iterator pointing to the first element inside the container. *end()* returns the iterator pointing to the latter of the last element inside the container. *iterator::operator++()* moves to the next element. And *iterator::operator*()* returns the dereference of an iterator, which is the element itself.

```cpp
class MyString {
    ...
 class iterator {
   public:
    iterator(char *p = nullptr) : _p(p) {}

    bool operator!=(const iterator &other) { return _p != other._p; }

    void operator++() { ++_p; }

    char &operator*() { return *_p; }

   private:
    char *_p;
  };

  iterator begin() { 
    return iterator(_pstr); 
  }

  iterator end() {
    return iterator(_pstr + length());
  }
}
```

With iterators, we can traverse *MyString* in such way:

```cpp
int main() {
  MyString s = "1234567890";
  for (MyString::iterator it = s.begin(); it != s.end(); ++it) {
    cout << *it << " ";	// 1 2 3 4 5 6 7 8 9 0
  }
  return 0;
}
```

C++ 11 provides a convenient feature "for each", which can directly loop the elements without the process of dereference.

```cpp
int main() {
  MyString s = "1234567890";
  for (char a : s) {
    cout << a << " ";	// 1 2 3 4 5 6 7 8 9 0
  }
  return 0;
}
```

The underlying implementation of this approach is still an iterator.