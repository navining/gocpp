# 虚析构函数

哪些函数不能实现成虚函数？

虚函数依赖：

1. 能产生地址，储存在vftable中
2. 对象必须存在

构造函数本身不能virtual，且构造函数中调用的任何函数都是静态绑定的

静态成员方法不行

虚析构函数

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

```cpp
int main() {
    Base *pb = new Derived(10);
    delete pb;
    return 0;
}
```

```
Base()
Derive()
~Base()
```

派生类的析构函数没有被调用！可能出现内存泄漏

因为基类没加virtual，是静态绑定，

因此基类的析构函数需要virtual，此时派生类的析构函数自动成为virtual

# 再谈动态绑定

问题：是不是虚函数的调用一定是动态绑定

构造函数中调用任何函数都是静态绑定

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

```cpp
int main() {
    Base b;
    Derived d;
    b.show();	// Base::show()
    d.show();	// Derived::show()
    return 0;
}
```

用对象本身调用虚函数，是静态绑定

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

由指针调用虚函数，动态绑定，无论指向的是基类对象还是派生类对象

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

引用和指针一样，都是动态绑定

