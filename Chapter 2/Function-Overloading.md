# Function Overloading

In the following code, we have three compare functions that compare the value of two arguments. Notice that their function names are the same, but the arguments types are different. This pattern is called **function overloading**.

```cpp
bool compare(int a, int b) {
    cout << "compare_int_int" << endl;
    return a > b;
}

bool compare(double a, double b) {
    cout << "compare_double_double" << endl;
    return a > b;
}

bool compare(const char *a, const char *b) {
    cout << "compare_char*_char*" << endl;
    return strcmp(a, b);
}

int main() {
    compare(10, 20);
    compare(10.0, 20.0);
    compare("aaa", "bbb");
    return 0;
}
```

Function overloading refers to a set of functions with the same function name, but different arguments list,  either in number or type. Moreover, these functions have to be in the same scope. For example, the following code won't compile, because all three statements call the same function which is declared in the first line of main().

```cpp
int main() {
    bool compare(int a, int b);	
    
    compare(10, 20);
    compare(10.0, 20.0);
    compare("aaa", "bbb");	// ERROR
    return 0;
}
```

Arguments modified with *const* or *volatile* need special attention. For example, in the following codes, the former will cause an compile error, but the latter is valid. We will take more about these two keywords in the future.

```cpp
void func(int a) {}
void func(const int a) {}	// ERROR
```

```cpp
void func(int *a) {}
void func(const int *a) {}	// Valid
```

In addition, if a set of functions have the same function name and the same arguments list, but their return types are different, this is not regarded as a function overloading, and will raise compile error.

Function overloading is considered as a behavior of polymorphism. There are two types of polymorphism, static and dynamic. The former is compile-time, and the latter is runtime. Function overloading is a static polymorphism, because function call is proceeded in compiling.

It is worth mentioning that function overloading is only supported in C++ but not in C. This is due to the different strategy in generating function symbols. We can compile the code above and take a look at the symbol table with ```objdump -t main.o | grep compare```. In C++, function symbols are named by both the function name and the arguments list, while function symbols are only named by function name in C. Thus, functions with the same name but different arguments are considered the same in C.

```shell
0000000000000000 g     F .text  0000000000000041 _Z7compareii
0000000000000041 g     F .text  0000000000000049 _Z7comparedd
000000000000008a g     F .text  0000000000000052 _Z7comparePKcS0_
```

What if we have the object file compiled in C and we want to use it in C++? Assume we have two file as follow:

**sum.c**

```c
int sum(int a, int b) {
    return a + b;
}
```

**main.cpp**

```cpp
int sum(int a, int b);

int main() {
    int ret = sum(10, 20);
    cout << "return: " << ret << endl;
    return 0;
}
```

An error has occurred! There is an undefined reference to `sum(int, int)` inside main.cpp. This is because the function sum is named *sum* in the symbol table of sum.o, but is *_Z3sumii* in main.o. To fix this, we can rewrite main.cpp like this.

```cpp
extern "C" {
int sum(int a, int b);
}

int main() {
    int ret = sum(10, 20);
    cout << "return: " << ret << endl;
    return 0;
}
```

```extern "C"``` tells the compiler to generate the function symbol as the way C does. In this way sum() is named *sum* now and the linker can find it's definition. Similarly, if we want to use C++ code in C, we also need to put function declarations inside ```extern "C"``` brackets in our C++ file (There's no such things like ```extern "C++"``` in C).

In actual project codes, we often do this in a cleverer way:

```cpp
#ifdef __cplusplus
extern "C" {
#endif
    int sum(int a, int b) {
        return a + b;
    }
#ifdef __cplusplus
}
#endif
```

`__cplusplus` is a built-in macro in all C++ compilers. By using compiler macros, the code above can be compiled with either C or C++ compilers.