# Introduction to *std::function*

*std::function* is a powerful class in C++ 11 which is able to bind a function with a function object. To use it  we need to include the functional library:

```cpp
#include <functional>
```

*std::function* takes a function, and binds it into a function objects. Types of function parameters and return value need to be provided as the template parameter. Then the function can be called with operator`()` of the corresponding function object. The following example shows the usage of *std::function*:

```cpp
void foo() {
    cout << "foo()" << endl;
}
void bar(string str) {
    cout << str << endl;
}
int sum(int a, int b) {
    return a + b;
}
int main() {
    function<void()> f1 = foo;
    f1();	// foo()
    function<void(string)> f2 = bar;
    f2("bar()");	// bar()
    function<int(int, int)> f3 = sum;
    cout << f3(20, 30) << endl;	// 50
    return 0;
}
```

Besides normal functions, *std::function* can be used to bind other function objects as well. Notice the underlying implementation of the lambda expression is also a function object. In the following example, we use *std::function* to bind a lambda expression which returns the sum of two values.

```cpp
int main() {
    function<int(int, int)> f4 = [](int a, int b)->int {return a + b;};
    cout << f4(100, 200) << endl;	// 300
    return 0;
}
```

Member functions can also be bound with *std::function*. Notice that member functions must rely on an object, and take a **this* pointer to the object as their first parameter. Therefore when using *std::function* we need to pass the type of the object pointer inside. And when calling the member function with operator`()`, we also need to pass in the address of the object.

```cpp
class Test {
public:
    void foo(string str) {
        cout << str << endl;
    }
}

int main() {
    function<void(Test*, string)> f5 = &Test::foo;
    f5(&Test(), "Test::foo()");	// Test::foo()
    return 0;
}
```

*std::function* has a similar functionality to function pointers in C, but is much more powerful. A typical application of *std::function* is the callback function. Suppose we have a program which monitors users' input commands. Then different functions are called with different commands. Here we can create a map with commands as keys, and different function objects as values. We can write the functions elsewhere, and use *std::function* to bind them into function objects. This approach is a good design pattern in actual software development.