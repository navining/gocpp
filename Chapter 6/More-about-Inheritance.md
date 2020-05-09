# More about Inheritance

## Function Hiding

In the following example, class *Base* has two overloaded member functions *show()* and *show(int)*. Class *Derived* inherit from *Base*, and has a member function *show()*.

```cpp
class Base {
public:
    Base(int data = 10) : ma(data) {}
    void show() {
        cout << "Base::show()" << endl;
    }
    void show(int) {
        cout << "Base::show(int)" << endl;
    }
protected:
    int ma;
};

class Derived : public Base {
public:
    Derived(int data = 20) : Base(data), mb(data) {}
    void show() {
        cout << "Derived::show()" << endl;
    }
private:
    int mb;
};
```

Now in the main function we defined an object of class *Derived*. But when the function *show(int)* is called, an error occurs. Since *Derived* inherits *show(int)* from *Base*, why can't the compiler find it?

```cpp
int main() {
    Derived d;
    d.show();	// Derived::show()
    d.show(10);	// ERROR
    return 0;
}
```

Notice that when a member function is called, the compiler first search for it inside the derived class itself. Only if no definition is found within this scope does the compiler goes inside the base class. In this case, function *Derived::show()* hides the functions with the same name *Base::show()* and *Base::show(int)*, which is called **function hiding**. To fix this, we may use `d.Base::show(10)` to call the corresponding function within the scope of *Base*. 

Notice that function hiding refers to the hiding of functions with the same name defined **in different scopes**, which is very different from function overloading. Recall that the definition of **function overloading** is that, there are functions **in the same scope** whose names are the same, but their parameter lists are different. In the example above, *Base::show()* and *Base::show(int)* are a couple of overloaded functions.

## Conversions of Base and Derived

Can a base class and a derived class be converted into each other? Let's see the following example:

```cpp
int main() {
    Base b(10);
    Derived d(20);
    b = d;	// Yes
    d = b;	// No
    return 0;
}
```

Here we defined a *Base* object and a *Derived* object. Assume we have overloaded operator `=`, then it is valid to assign *Derived* to *Base*, but invalid to assign *Base* to *Derived*.

Object pointers are similar:

```cpp
int main() {
    Base b(10);
    Derived d(20);
    Base *pb = &d;	// Yes
    pb->show();	// Base::show()
    Derived *pd = &b;	// No
    return 0;
}
```

Here we can let a *Base* pointer pointing to a *Derived* object, but not vice versa. Moreover, if we use a *Base* pointer which points to a *Derived* object, we can only access the members of *Base*. It is able to compile if we force a *Derived* pointer to point to a *Base* object using type conversion `Derived *pd = (Derived *)&b`, but it is unsafe, since there is not actually a *Derived* object, which may involve illegal memory access.

In all, in inheritance, only type conversion from bottom (base class) to top (derived class) is supported. Since derived class is a type of base class, which means that a base class is more generic, it make sense if we use something generic to point to something specific, but not the other way around.