# Frequently Asked Interview Questions: Polymorphism

## Question 1

Here we defined a base class *Animal*, which has a member variable *_name* and a virtual function *bark()*. Then we defined three derived classes *Cat*, *Dog* and *Bear* which inherit from *Animal*.

```cpp
class Animal {
public:
    Animal(string name) : _name(name) {}
    virtual void bark() {}
protected:
    string _name;
};

class Cat : public Animal {
public:
    Cat(string name) : Animal(name) {}
    void bark() {
        cout << _name << "Meow!" << endl;
    }
};

class Dog : public Animal {
public:
    Dog(string name) : Animal(name) {}
    void bark() {
        cout << _name << "Woof!" << endl;
    }
};
```

Now what is the output of the following code?

```cpp
int main() {
    Animal *p1 = new Cat("Kitty");
    Animal *p2 = new Dog("Puppy");
    
    int *p11 = (int *)p1;
    int *p22 = (int *)p2;
    int tmp = p11[0];
    p11[0] = p22[0];
    p22[0] = tmp;
    
    p1->bark();
    p2->bark();
    delete p1;
    delete p2;
    return 0;
}
```

Here we use two *Animal* pointers to point to two derived objects respectively. Next, we convert them into pointers of *int \**, and switch the first element of it. We all know that type *int* is 4 bytes in size, and the first 4 bytes of an object with virtual methods store the virtual function pointer. Therefore, the above code simply switch their vfptrs. So the output should be:

```
Woof!
Meow!
```

## Question 2

Now we have a *Base* class and a *Derived* class which inherits *Base*. *Base* has a virtual function *Base::show()* which has a default parameter *i = 0*. *Derived* has an overridden method *Derived::show()* which has a default parameter *i = 20*.

```cpp
class Base {
public:
    virtual void show(int i = 0) {
        cout << "Base::show() i = " << i << endl; 
    }
};

class Derived : public Base {
public:
    void show(int i = 20) {
        cout << "Derived::show() i = " << i << endl;
    }
};
```

Now what is the output of the following code?

```cpp
int main() {
    Base *p = new Derived();
    p->show();
    delete p;
    return 0;
}
```

Here we use a *Base* pointer to point to a *Derived* object, which is apparently a dynamic binding, so *Derived::show()* is called here. But what is the value of *i*? Remember that when a function is called, its parameters need to be pushed inside the function stack, and this process is done during compilation. But dynamic binding is a runtime behavior, which means the parameters won't be affected. Since we are calling *show()* through a *Base* pointer, the compiler simply pushed the parameters of *Base::show()* inside. So the output should be:

```
Derived::show() i = 10
```

Moreover, if *Derived::show()* is modified with `private`, can it be compiled? The answer is yes, because the access limitation is also determined under compilation, and the compiler only checks the permission of *Base*'s methods. Instead, if *Base::show()* is modified with `private`, it cannot be compiled.

## Question 3

Here we also have a *Base* class and a *Derived* class. But inside the constructor of *Base*, we call a function *clear()* which set all the memory of *Base* as 0.

```cpp
class Base {
public:
    Base() {
        cout << "Base()" << endl;
        clear();
    }
    void clear() {
        memset(this, 0, sizeof(*this));
    }
    virtual void show() {
        cout << "Base::show()" << endl;
    }
};

class Derived : public Base {
public:
    Derive() {
        cout << "Derived()" << endl;
    }
    void show() {
        cout << "Derived::show()" << endl;
    }
};
```

Now what is the output of these two programs?

```cpp
int main() {
    Base *pb1 = new Base();
    pb1->show();
    delete pb1;
    return 0;
}
```

```cpp
int main() {
    Base *pb2 = new Derived();
    pb2->show();
    delete pb2;
    return 0;
}
```

In the first program, we create a *Base* object on the heap. When its constructor is called, all its memory has been cleared, including its vfptr. Now if we called its virtual method *Base::show()*, the program cannot find its virtual function table, and an error occurs because there is an invalid access of the zero address.

In the second program, we create a *Derived* object on the heap. Notice that when a derived object is created, the constructor of the base class is called first, so its memory gets cleared again. So should there be a error again? The answer is no. We know that vfptr stores the address of vftable, so there must be an assembly instruction that assign the address to it. This instruction is executed just after the program enters the constructor and opens up the function stack frame. Therefore, although the memory is set to 0 when the constructor of *Base* is called, the address of *Derived*'s vftable is assigned to its vfptr again after *Derived*'s constructor is called. The program run normally and has the following output:

```
Base()
Derived()
Derived::show()
```



