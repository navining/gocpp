# More about Virtual Functions

## More about `virtual`

Now we already learn the ability of `virtual`. But is there any function that cannot be implemented as virtual function? Notice that a virtual function must meet two conditions:

1. It has an address and can be stored in the virtual function table.
2. Its existence depends on the object.

Obviously, the constructor can not be virtual, since no object exists before its constructor is called. In this case, any function called in the constructor is a static binding. Moreover, a static member function can not be virtual, since it belongs to the class itself instead of its objects.

Is there any function that should always be virtual? Let's look at the following case:

```cpp
class Base{
public:
    Base(int data) : ma(data) {
        cout << "Base()" << endl;
    }
    ~Base() {
    	cout << "~Base()" << endl;
    }
protected:
    int ma;
};

class Derived : public Base {
public:
    Derived(int data) : Base(data), mb(data) {
        cout << "Derived()" << endl;
    }
    ~Derived() {
        cout << "~Derived()" << endl;
    }
private:
    int mb;
};
```

Now we use a *Base* pointer to point to a *Derived* object, and delete it after then.

```cpp
int main() {
    Base *pb = new Derived(10);
    delete pb;
    return 0;
}
```

If we look at the output, we may find that only the destructor for class *Base* is called. The destructor of class *Derived* is not called, which will probably cause memory leak.

```
Base()
Derive()
~Base()
```

In the example above, the destructor of the base class is not marked as `virtual`, so there is a static binding. Good programming practice is to always marked the destructor of a base class as `virtual`, in which case the destructor of the derived class becomes virtual automatically.

## More about Dynamic Binding

There is another question: is the call of a virtual function is always a dynamic binding? We already know that any function call in a constructor is static binding, even if the constructor is marked as `virtual`. Let's look at more examples.

```cpp
class Base {
public:
    Base(int data = 10) : ma(data) {}
    virtual void show() {
        cout << "Base::show()" << endl;
    }
protected:
    int ma;
};

class Derived : public Base {
public:
    Derive(int data = 20) : Base(data), mb(data) {}
    void show() {
        cout << "Derived::show()" << endl;
    }
private:
    int mb;
}
```

Here we create two objects, and call the *show()* method directly with the object. In this case, the function calls are static binding.

```cpp
int main() {
    Base b;
    Derived d;
    b.show();	// Base::show()
    d.show();	// Derived::show()
    return 0;
}
```

Now if we use a *Base* pointer to point to objects, it is a dynamic binding, no matter the object we point at is a *Base* object or a *Derived* object.

```cpp
int main() {
    Base b;
    Derived d;
    Base *pb1 = &b;
    pb1->show();	// Base::show()
    Base *pb2 = &d;
    pb2->show();	// Derived::show()
    return 0;
}
```

References have the same underlying implementation as pointers, so it is also a dynamic binding.

```cpp
int main() {
    Base b;
    Derived d;
    Base &rb1 = b;
    rb1.show();	// Base::show()
    Base &rb2 = d;
    rb2.show();	// Derived::show()
    return 0;
}
```

Now we know that dynamic binding is a way to achieve polymorphism. Therefore, only with pointers and references is the function call a dynamic binding.

