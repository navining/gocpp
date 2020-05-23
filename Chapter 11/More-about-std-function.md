# More about *std::function*

*std::function* can be used to bind a function into a function object. Then corresponding functions can be called through function objects.

```cpp
void foo(string str) {
    cout << str << endl;
}

int main() {
    function<void(string)> f = foo;
    foo("foo()");	// foo()
    return 0;
}
```

Now let's implement our own *myfunction* class for *foo()*. Since *foo()* takes one parameter and a return value, we have two parameters for the template as well. First we need to have a basic template class, and then write the specialized one. The class stores a function pointer of type *R(\*)(A1)*, and operator`()` simply calls the function with the pointer, and returns its return value.

```cpp
template <typename R, typename A1>
class myfunction {};

template <typename R, typename A1>
class myfunction<R(A1)> {
public:
    using PFUNC = R(*)(A1);
    myfunction(PFUNC pfunc) : _pfunc(pfunc) {}
    R operator()(A1 a1) {
        return _pfunc(a1);
    }
private:
    PFUNC _pfunc;
};

int main() {
    myfunction<void(string)> f = foo;
    f("foo()");	// foo()
    return 0;
}
```

Similarly, if we have a function *sum()* which takes two arguments, we need to write another specialized template class as well. This time the template has three parameters.

```cpp
template <typename R, typename A1, typename A2>
class myfunction<R(A1, A2)> {
public:
    using PFUNC = R(*)(A1, A2);
    myfunction(PFUNC pfunc) : _pfunc(pfunc) {}
    R operator()(A1 a1, A2 a2) {
        return _pfunc(a1, a1);
    }
private:
    PFUNC _pfunc;
};

int sum(int a, int b) {
    return a + b;
}

int main() {
    myfunction<void(string)> f = sum;
    cout << f(10, 20) << endl;	// 30
    return 0;
}
```

There is a problem here: functions with different number of parameters should have different version of *myfunction*. Should we write all of them? It seems impossible. Fortunately, templates are so powerful in C++ that they support variable number of parameters with operator `...`. We need to add `...` wherever the parameters are uncertain:

```cpp
template <typename R, typename... A>
class myfunction<R(A...)> {
public:
    using PFUNC = R(*)(A...);
    myfunction(PFUNC pfunc) : _pfunc(pfunc) {}
    R operator()(A... a) {
        return _pfunc(a...);
    }
private:
    PFUNC _pfunc;
};
```

Now the compiler will automatically generate the correct version of *myfunction* when instantiating objects.