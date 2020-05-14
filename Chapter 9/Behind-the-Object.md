# Behind the Object

In this chapter we are going to learn how to write efficient C++ code. Many performance issues are related to objects, so we must be clear about what is happening when we are using objects. Let's look at this example, where we defined the constructor, destructor, copy constructor and operator`=` of class *Test*.

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

Now in the main function, we defined four objects in four different ways. What are their outputs respectively? The first object is defined directly without any initialization, so the constructor *Test::Test(int)* is called with a default parameter *a* = 10. Next, *t2* is defined with *t1*, so the copy constructor of *Test* is called. *t3* is constructed in the same way as *t2* does, where the copy constructor is called. But how should *t4* be constructed? For this statement, we may think that a temporary object is constructed first with *a* = 20, and *t4* is then constructed with the copy constructor. But the compiler is much more clever than we think it is.

```cpp
int main() {
    Test t1;	// Test(int)
    Test t2(t1);	// Test(const Test&)
    Test t3 = t1;	// Test(const Test&)
    Test t4 = Test(20);	// Test(int)
    ...
}
```

When a temporary object (by temporary we means the object is not named by a variable) is used to defined a new object, the compiler will call its copy constructor directly without constructing any temporary object. In other words, the above statement is the same as `Test t4(20);`.

If a variable is already defined before, and is assigned with a temporary object, then the temporary object should be created completely:

```cpp
int main() {
    ...
    t4 = Test(30);
    ...
}
```

In the above example, a temporary object *Test(30)* is constructed first. Then it is assigned to t4 with operator`=`. After its task is completed, the temporary object is destroyed. So the single statement has three lines of output:

```
Test(int)
operator=
~Test()
```

The lifecycle of a temporary object is just the current statement. It will be destroyed immediately after the statement ends.

Another way to defined an object is to use the implicit conversion:

```cpp
int main() {
    ...
    t4 = 30;
	...  
}
```

Here *t4* is a *Test* object, but 30 is an integer. How can this be compiled? Again, the compiler is much more clever than we think it is. In this case, the compiler goes to see if *t4* has a constructor with a paramter of type *int*. Then a temporary object is constructed with *a* = 30. Then everything is the same as before. Implicit conversion also requires complete construction of temporary objects.

What if we use a pointer or a reference to point to a temporary object? Let's look at this example:

```cpp
int main() {
    ...
    Test *p = &Test(40);
    const Test &ref = Test(50);
    ...
}
```

Remember that a temporary object is destroyed immediately after the current statement ends. In the first case, we use a pointer to store the address of a temporary object. But when the statement ends, the object no longer exists. Then things will go wrong if we continue using the pointer. Then what about references? Though references has the same underlying implementation as pointers, they are different in this case. Remember that a reference is an alias of another object, so the above statement is just the same as `Test ref(50);` Apparently, the object will not be destroyed after the statement ends. The above example has the following output:

```
Test(int)
~Test()
Test(int)
```

Remember: **NEVER** use pointers to point to temporary variables!