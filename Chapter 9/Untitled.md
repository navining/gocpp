# 临时对象

```cpp
class Test {
public:
    Test(int a = 10) : ma(a){
        cout << "Test(int)" << endl;
    }
    ~Test() {
        cout << "~Test()" << endl;
    }
    Test(const Test &t) : ma(t.ma) {
        cout << "Test(const Test &)" << endl;
    }
    Test &operator=(const Test &t) {
        cout << "operator=" << endl;
        ma = t.ma;
        return *this;
    }
    int getData() const {return ma;}
private:
    int ma;
}
```

```cpp
int main() {
    Test t1;	// Test(int)
    Test t2(t1);	// Test(const Test&)
    Test t3 = t1;	// Test(const Test&)
    Test t4 = Test(20);	// Test(int)
    ...
}
```

编译器对于对象构造的优化：用临时对象生成新对象时，临时对象不产生，直接构造新对象

相当于t4(20)

临时对象生成周期：当前语句

显式生成临时对象:

```cpp
int main() {
    ...
    t4 = Test(30);
    ...
}
```

此时临时对象要被完整地创建、赋值、析构

```
Test(int)
operator=
~Test()
```

隐式转换。编译器去看t4有没有int的构造函数，同样需要完整的临时对象

```cpp
int main() {
    ...
    t4 = 30;
	...  
}
```

如果用指针或者变量：

```cpp
int main() {
    ...
    Test *p = &Test(40);
    const Test &ref = Test(50);
    ...
}
```

用指针引用临时对象，出语句就析构了。引用不析构。不要用指针指向临时变量!

```
Test(int)
~Test()
Test(int)
```

