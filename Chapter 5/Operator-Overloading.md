# Operator Overloading

Operator overloading is one of the most fancy feature in C++. It is  is a specific case of polymorphism, where different operators can be overloaded so that object operations are the same as the built-in types of the compiler, which greatly facilitate programmers.

Here we defined a class *MyComplex* which represents a complex number. The complex number has a real part *mreal* and an image part *mimage*. 

```cpp
class MyComplex {
 public:
  MyComplex(int r = 0, int i = 0) : mreal(r), mimage(i) {}

 private:
  int mreal;
  int mimage;
};

int main() {
  MyComplex c1(10, 10);
  MyComplex c2(20, 20);
  MyComplex c3 = c1 + c2;  // c1.operator+(c2)
  return 0;
}
```

Now in the main function we would like to add two *MyComplex* objects. For object types, `a + b` is just `a.operator+(b)`, so we need to overload operator `+`, which simply add the real part and image part of two complex numbers separately.

```cpp
MyComplex MyComplex::operator+(const MyComplex &other) {
    return MyComplex(this->mreal + other.mreal, this->mimage + other.mimage);
  }
```

It is also valid to add *MyComplex* with a number. In the following case, number 20 is converted into a temporary object *c(20, 0)* when passed inside.

```cpp
int main() {
  MyComplex c1(10, 10);
  MyComplex c2 = c1 + 20;	// c1.operator+(20)
  return 0;
}
```

But it won't work if the constant is before the operator `+`. Since 20 is a constant, there's not any evidence for the compiler to call the overloaded function of *MyComplex*. In this case, the compiler will call the global operator `+`, so we also need to overload it.

```cpp
int main() {
  MyComplex c1(10, 10);
  MyComplex c2 = 20 + c1;	// ::operator+(20, c1)
  return 0;
}
```

The global operator takes the object before it and after it as parameters. When the compiler does object operations, it will first call the overloaded function of the member method. If it is not found, the compiler will go on finding the appropriate overloaded function in the global scope.

```cpp
MyComplex operator+(const MyComplex &c1, const MyComplex &c2) {
  return MyComplex(c1.mreal + c2.mreal, c1.mimage + c2.mimage);
}
```

Here inside this function we use the private member variables of *MyComplex*, which is apparently not allowed. To fix this, we can use keyword `friend` inside *MyComplex*, to give the function access to private members.

```cpp
class MyComplex {
  	...
private:
  int mreal;
  int mimage;
  friend MyComplex operator+(const MyComplex &c1, const MyComplex &c2);
}
```

Now our global overloaded function can also handle the sum of two *MyComplex* objects, so the overloaded member function is no longer needed.

Now let's deal with the self growth operator `++`. There are two types of them, one is before the object and the other is after the object. The former adds one to the object, and returns its value, while the latter returns the original value, and then adds one.

```cpp
int main() {
  MyComplex c1(10, 10);
  MyComplex c2 = c1++;	// c1.operator++(int)
  MyComplex c3 = ++c1;	// c1.operator++()
  return 0;
}
```

The one before the object is represented as `a.operator++()`, and the one after the object is represented as `a.operator++(int)`. The *int* parameter is not used. It is solely for the compiler to distinguish them.

```cpp
MyComplex MyComplex::operator++(int) {
    return MyComplex(mreal++, mimage++);
}

MyComplex &MyComplex::operator++() {
    mreal += 1;
    mimage += 1;
    return *this;
}
```

We can also overload operator `+=`, which is simple in this case:

```cpp
void MyComplex::operator+=(const MyComplex &other) {
    mreal += other.mreal;
    mimage += other.mimage;
}
```

We can also overload the stream output operator `<<`. It is also a global function, which takes the *ostream* object as the first parameter, and our *MyComplex* object as the second. Similarly, it should also be defined as friend inside *MyComplex*.

```cpp
std::ostream &operator<<(std::ostream &out, const MyComplex &c) {
  return out << c.mreal << "+" << c.mimage << "i";
}
```

Now we can use stream output to print our self-defined complex class.

```cpp
int main() {
  MyComplex c1(10, 10);
  MyComplex c2(20, 20);
  std::cout << c1 << " " << c2 << std::endl;	// 10+10i 20+20i
  return 0;
}
```

