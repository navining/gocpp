# Function Objects

A **Function Object** is simply any object that can be called as if it is a function. Remember in C, we can use function pointers like this:

```c
int sum(int a, int b) {
    return a + b;
}

int main() {
	int ret = sum(10, 20);
	return 0;
}
```

In C++, a function object is any object for which the function call operator `()` is defined. We can call functions from the object:

```cpp
class Sum {
public:
	int operator()(int a, int b) {
        return a + b;
    }
};
int main() {
	Sum sum;
	int ret = sum(10, 20);
}
```

What's the benefit of using function objects? Let's look at the following example, where we defined a template function *compare()* for comparing two elements.

```cpp
template<typemane T>
bool compare(T a, T b) {
    return a < b;
}
int main() {
    cout << compare(10, 20) << endl;	// 0
    cout << compare('b', 'y') << endl;	// 1
    return 0;
}
```

Here we compare the elements using operator `<`. What if we want to use `>` instead? We need to define another comparing function and provide a unified interface. A solution using function pointers in C style looks like this:

```cpp
template<typename T>
bool greater(T a, T b) {
    return a > b;
}
template<typename T>
bool less(T a, T b) {
    return a < b;
}
template<typename T, typename Compare>
bool compare(T a, T b, Compare comp) {
    return comp(a, b);
}
int main() {
    cout << compare(10, 20, greater<int>) << endl;	// 0
    cout << compare('b', 'y', less<int>) << endl;	// 1
    return 0;
}
```

Here we use function pointers as parameter and call the corresponding function through a function pointer. But remember that template functions are expanded at their call points, which means that *greater()* or *less()* can not be inlined inside *compare()*. This reduces efficiency since there is function call overhead.

A better approach is to use function objects:

```cpp
template<typename T>
class greater {
public:
	bool operator()(T a, T b) {
        return a > b;
    }  
};
template<typename T>
class less {
public:
	bool operator()(T a, T b) {
        return a < b;
    }  
};
template<typename T, typename Compare>
bool compare(T a, T b, Compare comp) {
    return comp(a, b);
}
int main() {
    cout << compare(10, 20, greater<int>()) << endl;	// 0
    cout << compare('b', 'y', less<int>()) << endl;	// 1
    return 0;
}
```

Now inside *compare()*, we simply call the member function operator `()` through objects. In this way, the function call overhead can be omitted, thus improving efficiency.

Moreover, since function objects are created from classes, we can add member variables to record other information used when a function object is used, for example the total number of calls. This greatly improves programming flexibility.

Function objects are widely used in STL containers and generic algorithms. For example, we can use function objects *greater* or *less* to change the underlying algorithms of containers:

```cpp
priority_queue<int, vector<int>, greater<int>> pq;
set<int, greater<int>> s;
```



