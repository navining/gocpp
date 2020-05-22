# More about Binders

In previous chapter we briefly introduced binders and how they can be used in generic algorithms. With binders, we can convert a binary function object into a unitary function object. Among them, *bind1st()* binds the first parameter of operator`()` into a fixed value, while *bind2st()* binds the second parameter into a fixed value.

The following example sorts an array from largest to smallest. Then we want to insert 48 inside the array and keep the array sorted. *bind1st()* is used here to bind  *greater* with 48 in order to find the first element smaller than 48.

```cpp
#include <functional>
int main() {
    int arr[] = {12, 4, 78, 9, 21, 43, 56, 52, 42, 31};
    vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));
    sort(vec.begin(), vec.end(), greater<int>());
    for (int v : vec) {
        cout << v << " ";	// 78 56 52 43 42 31 21 12 9 4
    }
    auto it = find_if(vec.begin(), vec.end(), bind1st(greater<int>(), 48));
    vec.insert(it, 48);
    for (int v : vec) {
        cout << v << " ";	// 78 56 52 48 43 42 31 21 12 9 4
    }
    ...
    return 0;
}
```

What is the underlying principle of a binder? Here we try to implement *bind1st()* ourselves. First we write our own *my_find_if()* function, which takes two iterators and a function object for the criterion. Then in the function, we call operator`()` of the function object on every elements within the range until we find the proper one. Apparently, the function object here should be unitary since it only takes one parameter.

```cpp
template <typename Iterator, typename Compare>
Iterator my_find_if(Iterator first, Iterator last, Compare comp) {
    for (; first != last; ++first) {
        if (comp(*first)) {
            return first;
        }
    }
    return last;
}
```

Now let's implement *mybind1st()*. In general, this function takes a binary function object and returns a unitary one. Let's name the returned unitary function object as *_mybind1st*. Here we don't implement it directly, but encapsulate once with template. This enables the type deduction of template function so that we don't need to pass in template parameters explicitly.

```cpp
template <typename Compare, typename T>
_mybind1st<Compare, T> mybind1st(Compare comp, const T &val) {
    return _mybind1st<Compare, T>(comp, val);
}
```

Next is the *_mybind1st* class, which takes a binary function object and a value to be fixed as member variables. Then the operator`()` takes one parameter, and simple returns the binary function object with the first parameter fixed to the value.

```cpp
template <typename Compare, typename T>
class _mybind1st {
public:
    _mybind1st(Compare comp, T val) : _comp(comp), _val(val) {}
    bool operator()(const T &second) {
        return _comp(_val, second);
    }
private:
    Compare _comp;
    T _val;
}
```

As we can see, the underlying implementation of *bind1st()* and *bind2nd()* is simply a multi-layer encapsulation of function objects. However, their limitation is obvious: they are only for binary objects. What if the function object is more complicated, for example with multiple parameters? Fortunately, C++ 11 introduces two classes *std::function* and *std::bind*, which is more convenient and powerful. 

