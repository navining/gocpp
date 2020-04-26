# Look inside Inheritance

**Inheritance** is the core of object-oriented programming. The essence of inheritance is code reuse. Let's take a look at the following example:

```cpp
class A {
public:
    int ma;
protected:
    int mb;
private:
    int mc;
};

class B : public A {
public:
    int md;
protected:
    int me;
private:
    int mf;
}
```

*A* is called a **base class**, and *B* is a **derived class**. Besides *B*'s own member variables *md*, *me* and *mf*, it also inherit  *ma* and *mb* from *A*. Now if *B* has its own member variable *ma*, it does not conflict with *ma* from *A*, since their scopes are different.

We should be able to tell the differences between combination and inheritance. The former can be described as class *B* is **a past of** class *A*, while the latter is described as class *B* is **a kind of** class *A*. For example, *vehicle* and *wheels* belongs to combination relationship, while *vehicle* and *truck* is an inheritance relationship.

### Access Limitations of Different Inheritance Types 

There are three types of inheritance: public, protected and private. There differences is the access authority of base class's members, which is listed as follow:

#### Public Inheritance

| Base Class | Derived Class | External Access |
| :--------: | :-----------: | :-------------: |
|   public   |    public     |       Yes       |
| protected  |   protected   |       No        |
|  private   | Inaccessible  |       No        |

#### Protected Inheritance

| Base Class | Derived Class | External Access |
| :--------: | :-----------: | :-------------: |
|   public   |    public     |       No        |
| protected  |   protected   |       No        |
|  private   | Inaccessible  |       No        |

#### Private Inheritance

| Base Class | Derived Class | External Access |
| :--------: | :-----------: | :-------------: |
|   public   |    private    |       No        |
| protected  |    private    |       No        |
|  private   | Inaccessible  |       No        |

From this, we can conclude the law of access limitations with different inheritance types:

1. The access limit of the derived class cannot exceed the access limit of the base class.
2. Only public members can be accessed externally.
3. Derived class can inherent base class's private members, but can not access it directly.
4. Members defined as protected in the base class can be access by its derived classes, but cannot be accessed externally.

The default inheritance type is same as the default access limitation of members. In classes, the default inheritance is private, while in structs it is public. 

### Construction and Destruction of the Derived Class

In the following example, we create a base class and another class inherited from it.

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

int main() {
    Derived a(10);	
    return 0;
}
```

Notice that a derived classes cannot directly initialize member variables inherited from the base class. In this case we need to call the corresponding constructor of the base class. The constructor and destructor of the derived class is only responsible for the members of the derived class, and the members of the base class is handled by the constructor and destructor of the base class. The program above has the following output:

```
Base()
Derived()
~Derived()
Base()
```

That is, the construction order and destruction order of a derived class is:

1. The derived class calls the constructor of the base class to initialize the members inherited from the base class
2. Then the derived class's own constructor is called to initialize its own members
3. The destructor of the derived class is called to release the external resources of the derived class members
4. Then the destructor of the base class is called to release the external resources of the members inherited from the base class

