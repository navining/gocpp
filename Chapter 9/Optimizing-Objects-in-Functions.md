# Optimizing Objects in Functions

This article continues from the previous one. Here we defined a function *getObject()*, which takes a *Test* object as parameter, constructs an object *tmp* and returns it. Remember that objects on the function stack will be destroyed after the function returns, so we cannot returns a pointer or reference to an object. 

```cpp
Test getObject(Test t) {
    int val = t.getData();
    Test tmp(val);
    return tmp;
}
```

Now in the main function, we defined two *Test* objects *t1* and *t2*. Then we call *getObject()* with *t1* as argument, and assign the return value to *t2*. In this case, how many member functions will be called in total? Obviously, the constructors for *t1* and *t2* should be called first.

```cpp
int main() {
    Test t1;	// 1. Test(int)
    Test t2;	// 2. Test(int)
    t2 = getObject(t1);
    return 0;
}
```

Then we pass *t1* inside the function. Here *t1* is an argument, but *t* is a parameter, so *t* has to be constructed with the copy constructor. Then we get the data of *t*, and use that value to create a new object *tmp*. Now *tmp* needs to be returned, but it is an object on the stack, which means it is going to be destroyed after the function returns. Therefore, we need to create a temporary object on the stack of *main()*, and construct it with the copy constructor. After the function returns, object *tmp* and parameter *t* is destroyed in turn.

```cpp
Test getObject(Test t) {	// 3. Test(const Test &)
    int val = t.getData();
    Test tmp(val);	// 4. Test(int)
    return tmp;	// 5. Test(const Test&)
    // 6. ~Test()
    // 7. ~Test()
}
```

Then the temporary object is assigned to *t2* with operator`=`. After the statement ends, the temporary object is destroyed immediately. At last, *t2* and *t1* are destroyed one by one.

```cpp
int main() {
    Test t1;	// 1. Test(int)
    Test t2;	// 2. Test(int)
    t2 = getObject(t1);	// 8. operator=
    // 9. ~Test()
    // 10. ~Test()
    // 11. ~Test()
    return 0;
}
```

In the previous example we only call a single function, but eleven member functions have been called. Let's try to optimize them in order to reduce the number of calls.

## Optimization 1

First, we can pass the argument by reference. It is most commonly used when objects are involved in parameters. In doing so, we don't need to construct the parameter, therefore initialization and destruction of the parameter are eliminated.

```cpp
Test getObject(Test &t) {
    int val = t.getData();
    Test tmp(val);	// 3. Test(int)
    return tmp;	// 4. Test(const Test&)
    // 5. ~Test()
}

int main() {
    Test t1;	// 1. Test(int)
    Test t2;	// 2. Test(int)
    t2 = getObject(t1);	// 6. operator=
    // 7. ~Test()
    // 8. ~Test()
    // 9. ~Test()
    return 0;
}
```

## Optimization 2

Before in function *getObject()*, we first construct an object *tmp*, and then return it. Actually, this action is unnecessary. Instead, we can return a temporary object. In this way, the returned object is constructed in *main()* directly. Now the construction and destruction of *tmp* can be eliminated.

```cpp
Test getObject(Test &t) {
    int val = t.getData();
    return Test(val);	// 3. Test(int)
}

int main() {
    Test t1;	// 1. Test(int)
    Test t2;	// 2. Test(int)
    t2 = getObject(t1);	// 4. operator=
    // 5. ~Test()
    // 6. ~Test()
    // 7. ~Test()
    return 0;
}
```

## Optimization 3

Since the function returns a temporary object, we can directly use the object to construct *t2*. Remember that when a temporary object is used to defined a new object, the compiler will call its copy constructor directly without constructing any temporary object. In other words, the function *getObject()* directly constructs *t2* without creating a temporary object on the stack of *main()*. In this way, we eliminate the construction and destruction of temporary object, and the call of operator`=` .

```cpp
Test getObject(Test &t) {
    int val = t.getData();
    return Test(tmp);	// 2. Test(int)
}

int main() {
    Test t1;	// 1. Test(int)
    Test t2 = getObject(t1);
    // 3. ~Test()
    // 4. ~Test()
    return 0;
}
```

## Summary

After these three optimizations, the number of member function calls has been reduced from 11 to 4. It may seems trivial, but the performance will be greatly improved if function *getObject()* is called hundreds and thousands of times. Therefore, when using objects in functions, we should remember three principles:

1. In passing arguments, objects should be preferably passed by reference, not by value.
2. Functions should preferably return temporary objects directly instead of defining them first.
3. When receiving from function whose return value is an object, it is preferably to receive by initialization, not by assignment.