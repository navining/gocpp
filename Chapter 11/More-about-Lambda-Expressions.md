# More about Lambda Expressions

Function objects are powerful, but every time we use a function object we need to define a class for it, which has a poor flexibility. In many cases we don't want to explicitly define a class, then we can use lambda expressions instead.

In previous chapters we have already used lambda expressions a lot. Lambda expression is also known as an anonymous function since it can serve as a function without being given a name. A lambda function has the following syntax:

```
[External variables](Parameters)->Retuen value {Function Content}
```

The following example is a lambda expression which prints "Hello World" to the console. We use a function object to store it and call the function with operator `=`.

```cpp
int main() {
    auto f1 = []()->void {cout << "Hello World!" << endl;};
    f1();	// Hello World!
    return 0;
}
```

With lambda expression, the compiler will automatically generate a function object class for as, something like this:

```cpp
template <typename T = void>
class Lambda1 {
public:
    Lambda1() {}
    void operator() const {
        cout << "Hello World!" << endl;
    }
};
```

Another example use lambda expression to calculate the sum of two integers:

```cpp
int main() {
    auto f2 = [](int a, int b)->void {return a};
    cout << f2(10,20) << endl;	// 30
    return 0;
}
```

This expression is equivalent to using a function object looks like:

```cpp
template <typename T = void>
class Lambda2 {
public:
    Lambda2() {}
    int operator(int a, int b) const {
    	return a + b;
    }
};
```

Inside the square brackets `[]` is the external variables we want to lambda expression to capture. Its usage is as follows:

- `[]`: No external variable is captured.

- `[=]`: All external variables are captured and passed by value.

- `[&]`: All external variables are captured and passed by reference.

- `[this]`: `*this` pointer of an object is captured.

- `[=, &a]`: All external variables are captured and passed by value, but *a* is passed by reference.

- `[a, b]`: *a* and *b* are captured and passed by value.

Now if we have lambda expression which takes two value and swap their values. Obviously, we should pass these two values by reference here:

```cpp
int main() {
    int a = 10;
    int b = 20;
    auto f3 = [&a, &b]()->void {
        int tmp = a;
        a = b;
        b = tmp;       
    };
    f3();
    cout << a << endl;	// 20
    cout << b << endl;	// 10
    return 0;
}
```

It is equal to have a function object with two member variables which are initialized by reference, and operator `()` swap these two variables.

```cpp
template <typename T = void>
class Lambda3 {
public:
    Lambda3(int &a, int &b) : ma(a), mb(b) {}
    int operator(int a, int b) const {
    	int tmp = ma;
        ma = mb;
        mb = tmp;    
    }
private:
    int &ma;
    int &mb;
};
```

Since lambda expression is actually a function object, we can use *std::function* to store it as well. The following example is a map whose key is an integer and value is a *std::function* object with two *int* parameters and return type *int*. Then we can use this map to store lambda expressions of arithmetic operations.

```cpp
int main() {
    map<int, function<int(int, int)>> m;
    map[1] = [](int a, int b)->int{ return a + b;};
    map[2] = [](int a, int b)->int{ return a - b;};
    map[3] = [](int a, int b)->int{ return a * b;};
    map[4] = [](int a, int b)->int{ return a / b;};
    cout << m[1](10, 20) << endl;	// 30
    cout << m[2](10, 20) << endl;	// -10
    return 0;
}
```

