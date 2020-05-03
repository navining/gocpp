# Diamond Problem

The benefit of multiple inheritance is that more code can be reused in this inheritance structure. But it brings up another problem, which is known as **diamond problem**. Let's look at this example.

Here we have a base class *A*, and two derived class *B* and *C* that inherit from it. Then we have another class that multiply inherits from *B* and *C*.

```cpp
class A {
public:
    A(int data) : ma(data) {
        cout << "A()" << endl;
    }
    ~A() {
        cout << "~A()" << endl;
    }
protected:
    int ma;
};

class B : public A {
public:
    B(int data) : A(data), mb(data) {
        cout << "B()" << endl;
    }
    ~B() {
        cout << "~B()" << endl;
    }
protected:
    int mb;
};

class C : public A {
public:
    C(int data) : A(data), mc(data) {
        cout << "C()" << endl;
    }
    ~C() {
        cout << "~C()" << endl;
    }
protected:
    int mc;
};

class D : public B, public C {
public:
    D(int data) : B(data), C(data), md(data) {
        cout << "D()" << endl;
    }
    ~D() {
        cout << "~D()" << endl;
    }
protected:
    int md;
};

int main() {
    D d(10);
    return 0;
}
```

Now in the main function we defined an object of class *D*. The output shows as follow:

```
A()
B()
A()
C()
D()
~D()
~C()
~A()
~B()
~A()
```

We can find that the constructor and destructor of class *A* have been called twice. Therefore, there are multiple copies of class *A*'s member *ma* in *D* as well. 

![diamond problem 2](../assets/Diamond-Problem-2.png)

This is apparently a waste of resources, and may cause ambiguity in using the base class's member variables. This problem is called the diamond problem, which happens in two common inheritance structures:

![diamond problem](../assets/Diamond-Problem.png)

Virtual inheritance is used to solve these kinds of problems in multiple inheritance. Here we can use virtual inheritance in class *B* and *C*. In this case, class *A* is a virtual base class.

```cpp
class B : virtual public A {
public:
    B(int data) : A(data), mb(data) {
        cout << "B()" << endl;
    }
    ~B() {
        cout << "~B()" << endl;
    }
protected:
    int mb;
};

class C : virtual public A {
public:
    C(int data) : A(data), mc(data) {
        cout << "C()" << endl;
    }
    ~C() {
        cout << "~C()" << endl;
    }
protected:
    int mc;
};
```

Remember that in virtual inheritance, the members of the base class is moved to the end of the memory, and their original locations are replaced with a vbptr which points to the vbtable. Now in class *D* we only have one copy of *ma*, and two vbptrs that point to the vbtables for class *B* and class *C*, respectively. There are no more repeated members here.

![diamond problem 3](../assets/Diamond-Problem-3.png)

Since *ma* is moved to the end of the memory, it is no longer within the scope of *B::* or *C::* anymore. Instead, it is now within the scope of class *D*. Therefore, *ma* is required to be initialized by *D* itself:

```
class D : public B, public C {
public:
    D(int data) : A(data), B(data), C(data), md(data) {
        cout << "D()" << endl;
    }
    ~D() {
        cout << "~D()" << endl;
    }
protected:
    int md;
};
```

