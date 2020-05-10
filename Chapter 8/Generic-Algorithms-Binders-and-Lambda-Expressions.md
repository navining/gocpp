# Generic Algorithms, Binders and Lambda Expressions

STL provides us powerful generic algorithms that can be used in containers.

```cpp
#include <algorithm>
```

Generic algorithms accepts iterators as parameters. Iterators provide uniform interfaces of containers for traverse. What's more, function objects can also be parameters to customize the algorithm.

**sort()**

*sort()* can sort the elements inside a container. Its default order is form small to large using operator *<* for comparison. We can also pass inside a function object *greater* to sort elements from large to small.

```cpp
int main() {
    int arr[] = {12, 4, 78, 9, 21, 43, 56, 52, 42, 31};
    vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));
    sort(vec.begin(), vec.end());
    for (int v : vec) {
        cout << v << " ";	// 4 9 12 21 31 42 43 52 56 78
    }
    sort(vec.begin(), vec.end(), greater<int>());
    for (int v : vec) {
        cout << v << " ";	// 78 56 52 43 42 31 21 12 9 4
    }
    ...
    return 0;
}
```

**binary_search()** 

*binary_search* is used to search for an element in a ordered container, which returns a bool value. The time complexity is *O(log(n))*.

```cpp
int main() {
    ...
    if (binary_search(vec.begin(), vec.end(), 21)) {
        cout << "21 exists" << endl;	// 21 exists
    }
    ...
    return 0;
}
```

**find()** 

*find()* can also searches for an element inside the container, which returns the iterator to it. If the element is not found, the *end()* iterator is returned. *find()* searches for the element sequentially, and the time complexity is *O(n)*.

```cpp
int main() {
    ...
    auto it = find(vec.begin(), vec.end(), 21);
    if (it != vec.end()) {
        cout << "21 exists" << endl;	// 21 exists
    }
    ...
    return 0;
}
```

**find_if** 

*find_if* searches for elements that meet the criteria. Let's illustrate it with an example. Suppose the vector is in reverse order. We want to insert number 48 inside it, and keep the vector ordered. To do so, we need to find the first element smaller than 48. In this case, every element should be compared with 48 using operator `>`. Apparently, we want to use the function object *greater*. But notice that *greater* is a binary function which takes two elements and compares them, but here we only need a unary function with only one parameter since the other one is fixed to 48. Unfortunately, there are not other function objects in STL that meets our requirement. To achieve this, we need to use a **binder**.

```cpp
#include <functional>
```

There are two types of binders to bind binary function into unary function: *bind1st()* and *bind2st()*. The former binds the first parameter of the binary function objects, while the latter binds the second parameter. In this example, we need to bind the first parameter in *greater()* as 48, therefore every element will be compared with 48.

```cpp
int main() {
    ...
    auto it = find_if(vec.begin(), vec.end(), bind1st(greater<int>(), 48));
    vec.insert(it, 48);
    for (int v : vec) {
        cout << v << " ";	// 78 56 52 48 43 42 31 21 12 9 4
    }
    ...
    return 0;
}
```

Similarly, it has the same effect if we use *less* instead and bind its second parameter as 48:

```cpp
auto it = find_if(vec.begin(), vec.end(), bind2nd(less<int>(), 48));
```

Binders are powerful but may be hard to understand for beginners. Fortunately, C++11 introduces **lambda expressions** that can achieve this in a much more elegant way:

```cpp
auto it = find_if(vec.begin(), vec.end(),[](int val) -> bool { return val < 48; });
```

See if you can understand the above expression. We will not elaborate the underlying principles of lambda expressions here.

**for_each** 

*for_each* traverses all the elements in the container, and apply customized functions to each of them. We can use function objects, or lambda expressions as well. Similarly, a unary function object is required here.

```cpp
int main() {
    ...
    for_each(vec.begin(), vec.end(), 
             [](int val) -> void {
                 if (val % 2 == 0) {
                     cout << val << " ";
                 }
             });	// 78 56 52 48 42 12 4
	return 0;
}
```

In the above example, we use a lambda expression to print out all even numbers in the vector.

> Lambda expressions are widely used in dynamic programming languages such as python. More details about lambda expressions will be illustrated in the future.