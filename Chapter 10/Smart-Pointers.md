# Smart Pointers

Pointers are the most powerful tools in C++, but programmers have to be responsible for the management of memory allocated on the heap. Any objects created with `new` has to be destroyed with `delete`, otherwise a memory leak will happen. Is there a way that the pointer can be automatically deleted when the memory is no longer used? The answer is yes. We can use object-oriented programming to implement a simplest smart pointer.

Here we defined a template class *SmartPtr* which keeps a normal pointer as its member variable. The constructor simply initializes the pointer, while the destructor deletes it.

```cpp
template <typename T>
class SmartPtr {
public:
    SmartPtr(T *ptr = nullptr) : _ptr(ptr) {}
    ~SmartPtr() {delete _ptr;}
private:
    T *_ptr;
}
```

Now our smart pointer can be automatically deleted, taking use of the feature that objects on the function stack are automatically destroyed when they get out of the scope.

```cpp
int main() {
    SmartPtr<int> p(new int);
    return 0;
}
```

To achieve full functionality of a pointer, we need to provide the dereference and the arrow as well.

```cpp
template <typename T>
class SmartPtr {
    ...
	T& operator*() {return *_ptr;}
    T* operator->() {return _ptr;}
}
```

So far, out smart pointer works perfectly, but a problem occurs with the copy constructor:

```cpp
int main() {
    SmartPtr<int> p1(new int);
    SmartPtr<int> p2(p1);
    return 0;	// ERROR
}
```

The program goes wrong when it returns. Here our copy constructor is a shallow copy, which only copies the pointer. When *p1* and *p2* is destroyed, the memory is deallocated repeatedly. Of course, we can rewrite the copy constructor to implement a deep copy, but in most circumstances we only want *p1* and *p2* pointing to a same object.

There are two ways to solve the shallow copy problem, with or without the reference counting. In next articles, we will introduce different kinds of smart pointers in C++ utilities library.