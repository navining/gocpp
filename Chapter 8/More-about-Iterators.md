# More about Iterators

As we have already known, iterators are useful to traverse elements in a STL container. However, there are also other types of iterators that are commonly used.

### *iterator*

*iterator* is the normal type of iterators we have learned before. It supports forward traversal of containers. We can use the deference to access the element it points to, and modify it as well.

```cpp
int main() {
    vector<int> v;
    for (int i = 0; i < 10; i++) {
        v.push_back(i);
    }
    vector<int>::iterator it;
    for (it = v.begin(); it != v.end(); ++it) {
        *it += 1;
        cout << *it << " ";	// 1 2 3 4 5 6 7 8 9 10
    }
    return 0;
}
```

### *const_iterator*

*const_iterator* supports forward traversal of containers. We can use the deference to access the element it points to, but cannot modify it, since the deference returns a `const` reference to the element.

```cpp
int main() {
    vector<int> v;
    for (int i = 0; i < 10; i++) {
        v.push_back(i);
    }
    vector<int>::const_iterator it;
    for (it = v.begin(); it != v.end(); ++it) {
        *it += 1;	// ERROR
        cout << *it << " ";
    }
    return 0;
}
```

### *reverse_iterator* 

*reverse_iterator* supports backward traversal of containers. We can use the deference to access the element it points to, and modify it as well.

Instead of *begin()* and *end()* in normal iterators, we use *rbegin()* and *rend()* in reverse iterators. *rbegin()* returns a *reverse_iterator* to the last element in the container, while *rend()* returns a *reverse_iterator* to the one before the first element in the container.

```cpp
int main() {
    vector<int> v;
    for (int i = 0; i < 10; i++) {
        v.push_back(i);
    }
    vector<int>::reverse_iterator it;
    for (it = v.rbegin(); it != v.rend(); ++it) {
        *it += 1;
        cout << *it << " ";	// 10 9 8 7 6 5 4 3 2 1
    }
    return 0;
}
```

### *const_reverse_iterator* 

*reverse_iterator* supports backward traversal of containers. We can use the deference to access the element it points to, but cannot modify it, since the deference returns a `const` reference to the element.

```cpp
int main() {
    vector<int> v;
    for (int i = 0; i < 10; i++) {
        v.push_back(i);
    }
    vector<int>::const_reverse_iterator it;
    for (it = v.rbegin(); it != v.rend(); ++it) {
        *it += 1;	// ERROR
        cout << *it << " ";
    }
    return 0;
}
```

