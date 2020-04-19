# Function Templates

**Function templates** are special functions that can operate with generic types. This allows us to create a function template whose functionality can be adapted to more than one type without repeating the entire code for each type. An basic example shows as follow:

```cpp
template<typename T>
bool compare(T a, T b) {
    return a > b;
}
```

Now in we can call this function by specifying type name *T* within angle brackets.

```cpp
int main() {
    compare<int>(10, 12);
    compare<double>(10.5, 20.5);
    return 0;
}
```

When a template function is called, the compiler instantiates the code of the function by replacing type names with the types specified by programmers. Function template itself can not be compiled. It is only compiled after being instantiated at function call points.

Sometimes we don't need to explicitly state the types with brackets, the compiler can deduce the template parameter types from the argument types. This is called the **template argument deduction**. But sometimes there are problems. In the following case, the two arguments are *int* and *double* respectively. But there is only one type for the template parameter. In this case a compile error arises.

```cpp
int main() {
    compare(10, 12);
    compare(10, 20.5);	// ERROR
    return 0;
}
```

In some cases, the default instantiation cause problems. The code below compares two strings. Remember that string type is converted to *const char \** implicitly. So our *compare()* function simply compares the address of these two strings, which is obviously incorrect.

```cpp
int main() {
    compare("aaa", "bbb");
    return 0;
}
```

**Template specialization** provides methods for programmers to handle special cases. By explicitly indicates the parameter types, we can use *strcmp()* to compare two strings.

```cpp
template<>
bool compare(const char *a, const char *b) {
    return strcmp(a, b) > 0;
}
```

Another way to do that is to defined a non-template function, then call the function as normal.

```cpp
bool compare(const char *a, const char *b) {
    return strcmp(a, b) > 0;
}
```

Then if we call `compare("aaa", "bbb")`, the compiler will not use the template function any more. That is because the argument deduction has priority. The compiler first searches for normal functions, and then the specialized template function. If nothing suitable is found, a template function is instantiated.

Moreover, template functions can have non-type parameters as will. In the following case, we specify the second parameter of our *sort()* function as an *int* variable. Then in the main function, we can use the template function by passing the size inside, along with the type name.

```cpp
template<typename T, int SIZE>
void sort(T *arr) {
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; i < SIZE - i - 1; j++) {
            if (arr[j] > arr[j+1]) {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

int main() {
    int arr[] = {12, 5, 7, 89, 32, 21, 35};
    const int size = sizeof(arr) / sizeof(arr[0]);
    sort<int, size>(arr);
    for (int val : arr) {
        cout << val << " ";	// 5 7 12 21 32 35 89
    }
    return 0;
}
```

Non-type parameters of templates have to be a constant, which means it is either an immediate number or an address.

Since a template function can only be compiled with instantiation at the call point, the compiler needs to see the specific implementation of the template. That is, we cannot put the declaration and definition into two separate files. In practice, it is common to put template codes in a single *.hpp* header file, and include the file where we use it.