# Template Specialization and Argument Deduction

Before exploring the underlying implementation of *std::function*, there are a couple of things that need to be illustrated about templates. 

In previous chapter, we have already known about template specialization. In the following example, we provide a specialized template function for type *const char \** which uses *strcmp()* to compare two strings instead of operator `>`.

```cpp
template <typename T>
bool compare(T a, T b) {
    return a > b;
}

template<>
bool compare<const char*>(const char *a, const char *b) {
	return strcmp(a, b) > 0;    
}

int main() {
    compare(10, 20);
    compare("aaa", "bbb");
    return 0;
}
```

It is similar in class templates. In the following example, we provide a specialized template class for type *char \**. And initialization of object with type *Test<char \*>* will call the specialized constructor.

```cpp
template <typename T>
class Test {
public:
    Test() {
        cout << "Test<T>()" endl;
    }
};

template <>
class Test<char *> {
public:
    Test() {
        cout << "Test<char *>()" endl;
    }
};

int main() {
    Test<int> t1;	// Test<T>()
    Test<char *> t2;	// Test<char *>()
    return 0;
}
```

This kind of template specialization is called an **explicit** (or full) **template specialization**, in which the type inside the brackets should match the specialized template exactly. Now let's look at another example. Here we want all the pointer types to behavior differently than normal types. Then we can write another specialized template class as follow:

```cpp
template <typename T>
class Test<T *> {
public:
    Test() {
        cout << "Test<T *>()" endl;
    }
};

int main() {
    Test<int> t1;	// Test<T>()
    Test<char *> t2;	// Test<char *>()
    Test<int *> t3;	// Test<T *>()
    return 0;
}
```

The above template class matches any type in form as *T \**. So if we initialize an object of type *Test<int \*>*, the constructor of our newly written class will be called. This kind of template specialization is called a **partial template specialization**. Notice that *char \** is also of type *T \**, but the explicit template class's constructor is called. Therefore, explicit template class has a higher priority than partial template specialization.

Partial template specialization can also be used to match a function pointer type. In the following example, we have a specialized template class with a function pointer with two parameters and one return value:

```cpp
template <typename R, typename A1, typename A2>
class Test<R (*)(A1, A2)> {
public:
    Test() {
        cout << "Test<R (*)(A1, A2)>()" endl;
    }
};

int main() {
    Test<int(*) (int, int)> t4;	// Test<R (*)(A1, A2)>()
    return 0;
}
```

Notice that a function pointer type is not the same as a function type. Remember in *std::function*, the template type should be a function. We can define another specialized class with function type:

```cpp
template <typename R, typename A1, typename A2>
class Test<R (A1, A2)> {
public:
    Test() {
        cout << "Test<R (A1, A2)>()" endl;
    }
};

int main() {
    Test<int (*)(int, int)> t4;	// Test<R (*)(A1, A2)>()
    Test<int (int, int)> t5;	// Test<R (A1, A2)>();
    return 0;
}
```

We also learnt another feature of templates which is called the **template argument deduction**. In some cases we don't need to explicitly state the types with brackets, the compiler can deduce the template parameter types from the argument types. In the following example, *func1* with different types of parameters are called according to the arguments we pass in.

```cpp
template <typename T>
void func1(T a) {
    cout << typeid(T).name() << endl;
}

int sum(int a, int b) {
    return a + b;
}

int main() {
    func1(10);	// int
    func1("aaa");	// char const *
    func1(sum);	// int (*)(int, int)
    return 0;
}
```

With partial specialization and argument deduction, templates can achieve more powerful functionalities. In the previous example, *func1(sum)* is deducted into a function pointer type *int (\*)(int, int)*. But with partial specialization, we can separate parameter types and return type apart:

```cpp
template <typename R, typename A1, typename A2>
void func2(R (*a)(A1, A2)) {
    cout << typeid(R).name() << endl;
    cout << typeid(A1).name() << endl;
    cout << typeid(A2).name() << endl;
}

int sum(int a, int b) {
    return a + b;
}

int main() {
    func2(sum);
    /*  int 
        int 
        int  */
    return 0;
}
```

We can also use this feature to deal with member functions. Compared to normal function pointers, member function pointers have a class scope, so we also need to have the class name as template parameter: 

```cpp
template <typename R, typename T, typename A1, typename A2>
void func3(R (T::*a)(A1, A2)) {
    cout << typeid(R).name() << endl;
    cout << typeid(T).name() << endl;
    cout << typeid(A1).name() << endl;
    cout << typeid(A2).name() << endl;
}

template <typename T>
class Test {
public:
    int sum(int a, int b) {
    	return a + b;
	}
}


int main() {
    func3(&Test::sum);
    /*  int 
    	class Test 
        int 
        int  */
    return 0;
}
```

In the next article, we will look at how template specialization and argument deduction are used in implementing *std::function*.