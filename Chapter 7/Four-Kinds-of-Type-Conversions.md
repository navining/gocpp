# Four Kinds of Type Conversions

In C, we can cast a variable into a different type in such way:

```c
void main() {
    double a = 10.0;
    int b = (int)a;
}
```

However, this compulsory type conversion might be dangerous, and the compiler won't check its validity. In C++, we have four kinds of type conversions provided by the language which are safer and more powerful. Their general format is:

```cpp
cast_type<target type>(converted object);
```

## `const_cast`	

`const_cast` is used to remove the constant attribute of a pointer of a reference:

```cpp
int main() {
    const int a = 10;
    int *p1 = (int *)&a;
    int *p2 = const_cast<int*>(&a);
    return 0;
}
```

The compiled assembly commands of these two conversions, one in a traditional C way and the other a modern C++ way, is completely the same. However, `const_cast` is safer, since the compiler makes sure the type conversion is consistent under compilation. For example, the following example won't compile:

```cpp
int main() {
    const int a = 10;
    double *p1 = (double *)&a;
    double *p2 = const_cast<double*>(&a);	// ERROR
    return 0;
}
```

Notice that the target type in `const_cast` has to be a pointer or a reference. It is invalid to cast a constant into a variable:

```cpp
int main() {
    const int a = 10;
    int p = const_cast<int>(a);	// ERROR
    return 0;
}
```

## `static_cast`

`static_cast` provides type conversions that are considered safe by the compiler. It is the most commonly used type conversion and can replace the traditional conversion in C in most instances.

```cpp
int main() {
    int a = 10;
    char b = static_cast<char>(a);
    return 0;
}
```

Conversion between types without any connection can not be compiled, which ensures safety:

```cpp
int main() {
    int *p = nullptr;
    double *b = static_cast<double*>(p);	// ERROR
    return 0;
}
```

The base class and the derived class can also be converted with `static_cast`:

```cpp
int main() {
    Derived *d = new Derived();
    Base *b = static_cast<Base*>(d);
    return 0;
}
```

## `reinterpret_cast`

`reinterpret_cast` is similar to the C-style type conversion, without safety check by the complier:

```cpp
int main() {
    int *p = nullptr;
    double *b = reinterpret_cast<double*>(p);
    return 0;
}
```

The code above is able to compile, but error occurred when *b* is dereferenced, for **b* should be 8 bytes but what it points to is only 4 bytes.

## `dynamic_cast`	

`dynamic_cast` is widely used in an inheritance structure. Unlike `static_cast` which is done at compilation, `dynamic_cast` is a runtime type conversion, which means it supports recognition of the RTTI type. Let's look at an example. Here we have a base class *Base* and two derived classes *Derived1* and *Derived2* which inherit from *Base*. There is a pure virtual function *func()* inside *Base*, and *Derived1* and *Derived2* override it respectively.

```cpp
class Base {
public:
    virtual void func() = 0;
};

class Derived1 : public Base {
public:
    void func() {
        cout << "Derived1::func()" << endl;
    }
};

class Derived2 : public Base {
public:
    void func() {
        cout << "Derived2::func()" << endl;
    }
};
```

Now we have a interface *show()* which takes a *Base* pointer and calls *func()*. We already know that this is an example of polymorphism, in which the corresponding function of *Derived1* and *Derived2* will be called respectively.

```cpp
void show(Base *p) {
    p->func();
}

int main() {
    Derived1 d1;
    Derived2 d2;
    show(&d1);	// Derived1::func()
    show(&d2);	// Derived2::func()
    return 0;
}
```

Now suppose we want to expand the functionality of *Derived2* by adding another method *func2()*. What's more, in the interface we provided, we want *func2()* to be called if the pointer points to *Derived2*, and *func()* to be called if the pointer points to  *Derived1*. How can we modify our interface?

```cpp
class Derived2 : public Base {
public:
    void func() {
        cout << "Derived2::func()" << endl;
    }
    void func2() {
        cout << "Derived2::func2()" << endl;
    }
};
```

Apparently, we need to identify the object type here. One approach is to use `typeid(p).name()` to compare the strings. A better way to implement this is to use `dynamic_cast`:

```cpp
void show(Base *p) {
    Derived2 *pd2 = dynamic_cast<Derived2*>(p);
    if (pd2 != nullptr) {
        pd2->func2();
    } else {
    	p->func();
    }
}
```

`dynamic_cast` will take use of the RTTI information stored in the object's vftable, and check if it matches the target type in the angle brackets. If it matches, the address of the object will be returned. Otherwise, it will return a nullptr. At last, we have the following output:

```
Derived1::func()
Derived2::func2()
```

