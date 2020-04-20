# Memory Allocators

Now using what we've learnt in template programming, we write a class *MyVector* which is a vector container similar to *std::vector*. The code is shown below.

```cpp
template <typename T>
class MyVector {
 public:
  MyVector(int size = 10) {
    _first = new T[size];
    _last = _first;
    _end = _first + size;
  }

  ~MyVector() {
    delete[] _first;
    _first = _last = _end = nullptr;
  }

  MyVector(const MyVector<T> &other) {
    int size = other._end - other._first;
    _first = new T[size];
    int len = other._last - other._first;
    for (int i = 0; i < len; i++) {
      _first[i] = other._first[i];
    }
    _last = _first + len;
    _end = _first + size;
  }

  MyVector<T> &operator=(const MyVector<T> &other) {
    if (*this == other) return *this;
    delete[] _first;
    int size = other._end - other._first;
    _first = new T[size];
    int len = other._last - other._first;
    for (int i = 0; i < len; i++) {
      _first[i] = other._first[i];
    }
    _last = _first + len;
    _end = _first + size;
    return *this;
  }

  void push_back(T &val) {
    if (full()) expand();
    *_last++ = val;
  }

  void pop_back() {
    if (!empty()) --_last;
  }

  T &back() const { return *(_last - 1); }

  bool full() const { return _last == _end; }

  bool empty() const { return _last == _first; }

  int size() const { return _last - _first; }

 private:
  T *_first;  // Start point
  T *_last;   // One step after the last valid element
  T *_end;    // One step after the last element in the space

  void expand() {
    int size = _last - _first;
    T *tmp = new T[2 * size];
    for (int i = 0; i < size; i++) {
      tmp[i] = _first[i];
    }
    delete[] _first;
    _first = tmp;
    _last = _first + size;
    _end = _first + size * 2;
  }
};
```

In the above class, we use three pointers pointing to the start point of the vector, one step after the last valid element, and one step after the last element in the space respectively. This container works fine when we put integers or float numbers inside, but there's something wrong with object elements. Let's look at the following case.

```cpp
class Test {
public:
    Test(){
        cout << "Test()" << endl;
    }
    ~Test() {
        cout << "~Test()" << endl;
    }
    Test(const Test &) {
        cout << "Test(const Test &)" << endl;
    }
};

int main() {
    Test t1, t2, t3;
    cout << "------------------" << endl;
    MyVector<Test> v;
   	v.push_back(t1);
    v.push_back(t2);
    v.push_back(t3);
    cout << "------------------" << endl;
    v.pop_back();
    cout << "------------------" << endl;
    return 0;
}
```

The code above has the output as follow:

```
Test()
Test()
Test()
------------------
Test()
Test()
Test()
Test()
Test()
Test()
Test()
Test()
Test()
Test()
------------------
------------------
~Test()
~Test()
~Test()
~Test()
~Test()
~Test()
~Test()
~Test()
~Test()
~Test()
~Test()
~Test()
~Test()
```

Here we only put three objects inside *MyVector*, but why 10 objects are constructed and destroyed? That is because every time we construct *MyVector*, we use `new` to create an array of size 10. Notice that `new` not only allocates memory on the heap, but also call the constructor of objects as well. In this case, we only need to allocate memory without constructing objects. In general, three things should be done for our previous code.

1. In vector constructor, memory allocation and object construction should be separated.
2. In vector destructor, only existing elements in the container should be destroyed and deallocated.

3. *pop* operation can't just move the pointer. Corresponding element should be destroyed as well.

To achieve this, we need the **memory allocator**. The memory allocator is one of the most important component of a container class. It does four things: memory allocation, memory deallocation, object construction and object destruction. Using a memory allocator, we can separate memory operations and object operations, which `new` and `delete` can not achieve. 

```cpp
template <typename T>
class Allocator {
  T *allocate(size_t size) { return (T *)malloc(sizeof(T) * size); }

  void deallocate(void *p) { free(p); }

  void construct(T *p, const T &val) { new (p) T(val); }

  void destroy(T *p) { p->~T(); }
};
```

Then we can improve *MyVector* with memory allocator. All the places involved memory management should be implemented with it.

```cpp
template <typename T, typename Alloc = Allocator<T>>
class MyVector {
 public:
  MyVector(int size = 10) {
    //_first = new T[size];
    _first = _allocator.allocate(size);
    _last = _first;
    _end = _first + size;
  }

  ~MyVector() {
    // delete[] _first;
    for (T *p = _first; p != _last; p++) {
      _allocator.destroy(p);
    }
    _allocator.deallocate(_first);
    _first = _last = _end = nullptr;
  }

  MyVector(const MyVector<T> &other) {
    int size = other._end - other._first;
    //_first = new T[size];
    _first = _allocator.allocate(size);
    int len = other._last - other._first;
    for (int i = 0; i < len; i++) {
      //_first[i] = other._first[i];
      _allocator.construct(_first + i, other._first[i]);
    }
    _last = _first + len;
    _end = _first + size;
  }

  MyVector<T> &operator=(const MyVector<T> &other) {
    if (*this == other) return *this;
    // delete[] _first;
    for (T *p = _first; p != _last; p++) {
      _allocator.destroy(p);
    }
    //_first = new T[size];
    _first = _allocator.allocate(size);
    int len = other._last - other._first;
    for (int i = 0; i < len; i++) {
      //_first[i] = other._first[i];
      _allocator.construct(_first + i, other._first[i]);
    }
    _last = _first + len;
    _end = _first + size;
    return *this;
  }

  void push_back(T &val) {
    if (full()) expand();
    //*_last++ = val;
    _allocator.construct(_last, val);
    _last++;
  }

  void pop_back() {
    if (!empty()) {
      //--_last;
      _last--;
      _allocator.destroy(_last);
    }
  }

  T &back() const { return *(_last - 1); }

  bool full() const { return _last == _end; }

  bool empty() const { return _last == _first; }

  int size() const { return _last - _first; }

 private:
  T *_first;  // Start point
  T *_last;   // One step after the last valid element
  T *_end;    // One step after the last element in the space
  Alloc _allocator;

  void expand() {
    int size = _last - _first;
    // T *tmp = T[2 * size];
    T *tmp = _allocator.allocate(2 * size);
    for (int i = 0; i < size; i++) {
      // tmp[i] = _first[i];
      _allocator.construct(tmp + i, _first[i]);
    }
    // delete[] _first;
    for (T *p = _first; p != _last; p++) {
      _allocator.destroy(p);
    }
    _allocator.deallocate(_first);
    _first = tmp;
    _last = _first + size;
    _end = _first + size * 2;
  }
};
```

After then, we get the correct output. An object is only constructed after being pushed, and destroyed after being popped.

```
Test()
Test()
Test()
------------------
Test(const Test &)
Test(const Test &)
Test(const Test &)
------------------
~Test()
------------------
~Test()
~Test()
~Test()
~Test()
~Test()
```

> Memory allocators are heavily used in STL containers, further details will be discussed in later chapters.