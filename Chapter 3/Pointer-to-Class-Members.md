# Pointer to Class Members

## Pointer to Member Variables

We all know that a pointer can used to represent the memory address of a variable. But what if the variable is inside a class? Let' look at this case.

```cpp
class Test {
public:
    int ma;
    static int mb;
};

int Test::mb;
```

Now if we want to access the memory of *Test::ma*, we will get an error: cannot convert ‘int Test::\*’ to ‘int\*’ in initialization.

```cpp
int main() {
    int *p = &Test::ma;	// ERROR
    *p = 20;
    return 0;
}
```

This is because *ma* is within the scope of class *Test*, so the type of our pointer should also be modified with the qualifier. But another error occurs: invalid use of unary ‘*’ on pointer to member. 

```cpp
int main() {
    int Test::*p = &Test::ma;
    *p = 20;		// ERROR
    return 0;
}
```

Remember that class is an abstract of instances, so the member variable is only valid within an object. And the following code is valid when we bound the pointer with an object.

```cpp
int main() {
    Test *t = new Test();
    int Test::*p = &Test::ma;
    t->*p = 20;
    cout << t->ma << endl;	// 20
    delete t;
    return 0;
}
```

Notice that static member variables belong to the class instead of objects. So it is correct to access them with pointers, just like normal variables.

```cpp
int main() {
    int *p = &Test::mb;
    *p = 30;
    cout << t->Test::mb << endl;	// 30
    return 0;
}
```

## Pointer to Member Functions

In C and C++, we can have pointers to functions. This feature enables programmers to avoid code redundancy. Similarly, we can use pointers to access public member functions.

```cpp
class Test {
public:
    void func() {
        cout << "call Test::func" << endl;
    }
    static void static_func() {
        cout << "call Test::static_func" << endl;
    }
};
```

Like member variables, the pointer is within the scope of the class, and has to be bounded with an object.

```cpp
int main() {
    Test *t = new Test();
    void (Test::*pfunc)() = &Test::func;
    (t->*pfunc)();	//	call Test::func
    delete t;
    return 0;
}
```

Like static variables, static member functions can be pointed use normal function pointers.

```cpp
int main() {
    void (*pfunc)() = &Test::static_func;
    (*pfunc)();	// call Test::static_func
    return 0;
}
```

## More About Function Pointers

There may be ambiguity in using function pointers. In the following case all three statements can be compiled.

```cpp
void foo() {...}
void bar() {
    void (*p1)() = foo;		// 1
    void (*p2)() = &foo;	// 2
    void (*p3)() = *foo;	// 3
}
```

But when it comes to member functions, only the second one can be compiled correctly.

```cpp
class Test {
public:
    void foo() {...}
};
void bar() {
    void (Test::*p1)() = Test::foo;		// 1
    void (Test::*p2)() = &Test::foo;	// 2
    void (Test::*p3)() = *Test::foo;	// 3
}
```

The underlying principle is complicated, including implicit type conversion and polymorphism of member functions. Notice that C++ is a language with long history, and there are many historical issues. We don't have to, and can not understand all of them. In the above case, we only need to remember that *&* with function name is always a correct way in using function pointers.

> For more explanations, please refer to C++ standard n3376 - 4.3 - 1 and n3337 - 5.3.1 - 4.