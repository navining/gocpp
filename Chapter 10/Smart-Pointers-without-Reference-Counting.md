# Smart Pointers without Reference Counting

```cpp
#include <memory>
```

C++ utilities library provides us three kinds of smart pointers without reference counting: *auto_ptr*, *scoped_ptr* and *unique_ptr*. These pointers have a common feature, that at the same time there can only be one pointer that manages the object. In other words, every time a new copy of a pointer transfer the ownership of objects from the previous one.

## *auto_ptr* 

*auto_ptr* rewrites the copy constructor so that every time a new copy of the pointer is created, it takes handle of its object, and the original pointer is set to NULL. In this way, there can only be one pointer pointing to the object. In this way, the destructor only need to deal with the only pointer pointing to the object. Therefore, we can not use the original pointer any more if its ownership has been transferred:

```cpp
int main() {
    auto_ptr<int> p1(new int);
    auto_ptr<int> p2(p1);
    *p2 = 20;
    cout << *p1 << endl;	// ERROR
    return 0;
}
```

*auto_ptr* has to be used carefully, for programmers sometimes may not realize the transfer of ownership and invalidate the pointer unintentionally,.

## *scoped_ptr*

*scoped_ptr* strictly regulates that there is always one pointer pointing to an object. It achieves this by disabling the copy constructor of operator`=`:

```cpp
scoped_ptr(const scoped_ptr<T> &) = delete;
scpoed_ptr<T> &operator=(const scoped_ptr<T> &) = delete;
```

In this case, any copy of a *scoped_ptr* is not allowed:

```cpp
int main() {
    scoped_ptr<int> p1(new int);
    scoped_ptr<int> p2(p1);	// ERROR
    return 0;
}
```

Since *scoped_ptr* is to strict towards the ownership, it is not widely used.使用的比较少

## *unique_ptr*

*unique_ptr* disables the copy constructor and operator`=` as well. But instead, it provides a copy constructor and operator`=` with Rvalue references:

```cpp
unique_ptr(const unique_ptr<T> &) = delete;
unique_ptr<T> &operator=(const unique_ptr<T> &) = delete;
unique_ptr(unique_ptr<T> &&);
unique_ptr<T> &operator=(unique_ptr<T> &&);
```

In this case, we still cannot copy a pointer directly, but we can use the move semantics here:

```cpp
int main() {
    unique_ptr<int> p1(new int);
    unique_ptr<int> p2(std::move(p1));
    return 0;
}
```

Now *p1* transfer the ownership of the object to *p2*, and then be set to NULL. Again, the destructor only needs to deal with *p2*.

*unique_ptr* has almost the same functionality as *auto_ptr*, but is more recommended because its semantic is clearer. Under normal circumstances, copying a *unique_ptr* is not allowed, and we must explicitly use *std::move*. Hence, it will not happen that the programmer unintentionally transfer the ownership of a pointer, which is much safer.