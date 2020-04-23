# Issues of Iterator Invalidation

When using iterators, we need to pay attention to the validation of them. In some cases, the iterator may turns invalid, which is not easy to notice.

For example, in the following case, we use an iterator to delete all the even numbers in the vector.

```cpp
int main() {
    vector<int> v;
    for (int i = 0; i < 20; ++i) {
        vec.push_back(rand() % 100 + 1);
    }
    for (auto it = v.begin(); it != v.end(); ++it) {
        if (*it % 2 == 0) {
            v.erase(it);	// ERROR
        }
    }
    return 0;
}
```

But the program exits abnormally. In fact, after the first element is erased from the vector, the elements after it need to be moved forward. Therefore, all iterators behind the current one is no longer valid any more.

The second example is to add *n - 1* before every even number n:

```cpp
int main() {
    vector<int> v;
    for (int i = 0; i < 20; ++i) {
        vec.push_back(rand() % 100 + 1);
    }
    for (auto it = v.begin(); it != v.end(); ++it) {
        if (*it % 2 == 0) {
           v.insert(it, *it-1);	// ERROR
        }
    }
    return 0;
}
```

Similarly, an error occurs after the first element is added. When an element is added, all elements after it need to be moved backward, so their iterators are invalid. Moreover, the vector is likely to be double-expanded, in which all iterators of the container are invalid now.

If an iterator is invalid, we can no longer do iterator operations, for example increment and dereference. To fix this, we need to update the iterator at the erase point or insert point. The designers of STL containers have taken this into account, so function *erase()* and *insert()* return a new iterator pointing to the current element after called.

After an element is erased from the container, the elements after it will move forward,  and the returned iterator points to the one after the erase point, so increment is not needed when an element is erased. 

```cpp
int main() {
    vector<int> v;
    for (int i = 0; i < 20; ++i) {
        vec.push_back(rand() % 100 + 1);
    }
    for (auto it = v.begin(); it != v.end();) {
        if (*it % 2 == 0) {
            it = v.erase(it);
        } else {
            ++it;
        }
    }
    return 0;
}
```

After an element is erased from the container, the elements after it will move backward,  and the returned iterator points to the one being added, so another increment is needed in this case.

```cpp
int main() {
    vector<int> v;
    for (int i = 0; i < 20; ++i) {
        vec.push_back(rand() % 100 + 1);
    }
    for (auto it = v.begin(); it != v.end();) {
        if (*it % 2 == 0) {
           v.insert(it, *it-1);
           ++it;
        }
    }
    return 0;
}
```

How does the iterator invalidation works at the bottom? In STL containers, a linked list is used to maintain the status of current iterators. Every time a container operation is performed, the validation of current iterator is verified using the linked list. We will not elaborate here, but we modify our *MyVector* class to implement this feature.

```cpp
#include <stdlib.h>

template <typename T>
class Allocator {
 public:
  T *allocate(size_t size) { return (T *)malloc(sizeof(T) * size); }

  void deallocate(void *p) { free(p); }

  void construct(T *p, const T &val) { new (p) T(val); }

  void destroy(T *p) { p->~T(); }
};

template <typename T, typename Alloc = Allocator<T>>
class MyVector {
 public:
  MyVector(int size = 10) {
    _first = _allocator.allocate(size);
    _last = _first;
    _end = _first + size;
  }

  ~MyVector() {
    for (T *p = _first; p != _last; p++) {
      _allocator.destroy(p);
    }
    _allocator.deallocate(_first);
    _first = _last = _end = nullptr;
  }

  MyVector(const MyVector<T> &other) {
    int size = other._end - other._first;
    _first = _allocator.allocate(size);
    int len = other._last - other._first;
    for (int i = 0; i < len; i++) {
      _allocator.construct(_first + i, other._first[i]);
    }
    _last = _first + len;
    _end = _first + size;
  }

  MyVector<T> &operator=(const MyVector<T> &other) {
    if (*this == other) return *this;
    for (T *p = _first; p != _last; p++) {
      _allocator.destroy(p);
    }
    _first = _allocator.allocate(size);
    int len = other._last - other._first;
    for (int i = 0; i < len; i++) {
      _allocator.construct(_first + i, other._first[i]);
    }
    _last = _first + len;
    _end = _first + size;
    return *this;
  }

  void push_back(T &val) {
    if (full()) expand();
    _allocator.construct(_last, val);
    _last++;
  }

  void pop_back() {
    if (!empty()) {
      verify(_last - 1, _last);
      _last--;
      _allocator.destroy(_last);
    }
  }

  T &back() const { return *(_last - 1); }

  bool full() const { return _last == _end; }

  bool empty() const { return _last == _first; }

  int size() const { return _last - _first; }

  T &operator[](int index) { return _first[index]; }

  // Iterators for MyVector
  class iterator {
   public:
    iterator(MyVector<T, Alloc> *pvec = nullptr, T *p = nullptr)
        : _p(p), _pVec(pvec) {
      Iterator_Base *itb = new Iterator_Base(this, _pVec->_head._next);
      _pVec->_head._next = itb;
    }

    bool operator!=(const iterator &other) {
      if (_pVec == nullptr || _pVec != other._pVec) {
        throw "iterator incompatable!";
      }
      return _p != other._p;
    }

    void operator++() {
      if (_pVec == nullptr) {
        throw "iterator invalid!";
      }
      _p++;
    }

    T &operator*() {
      if (_pVec == nullptr) {
        throw "iterator invalid!";
      }
      return *_p;
    }

    const T &operator*() const {
      if (_pVec == nullptr) {
        throw "iterator invalid!";
      }
      return *_p;
    }

   private:
    T *_p;
    MyVector<T, Alloc> *_pVec;
  };

  iterator begin() { return iterator(_first); }

  iterator end() { return iterator(_last); }

  // Insert an element into the vector
  iterator insert(iterator it, const T &val) {
    verify(it._ptr - 1, _last);
    T *p = _last;
    while (p > it._ptr) {
      _allocator.construct(p, *(p - 1));
      _allocator.destroy(p - 1);
      p--;
    }
    _allocator.construct(p, val);
    _last++;
    return iterator(this, p);
  }

  // Erase an element from the vector
  iterator erase(iterator it) {
    verify(it._ptr - 1, _last);
    T *p = it._ptr;
    while (p < _last - 1) {
      _allocator.destroy(p);
      _allocator.construct(p, *(p + 1));
      p++;
    }
    _allocator.destroy(p);
    _last--;
    return iterator(this, it._ptr);
  }

 private:
  T *_first;  // Start point
  T *_last;   // One step after the last valid element
  T *_end;    // One step after the last element in the space
  Alloc _allocator;

  // A linked list storing pointes to iterators
  struct Iterator_Base {
    Iterator_Base(iterator *c = nullptr, Iterator_Base *n = nullptr)
        : _cur(c), _next(n) {}
    iterator *_cur;
    Iterator_Base *_next;
  };
  Iterator_Base _head;

  void expand() {
    int size = _last - _first;
    T *tmp = _allocator.allocate(2 * size);
    for (int i = 0; i < size; i++) {
      _allocator.construct(tmp + i, _first[i]);
    }
    for (T *p = _first; p != _last; p++) {
      _allocator.destroy(p);
    }
    _allocator.deallocate(_first);
    _first = tmp;
    _last = _first + size;
    _end = _first + size * 2;
  }

  // Verify the validation of iterators
  void verify(T *first, T *last) {
    Iterator_Base *pre = &this->_head;
    Iterator_Base *it = this->_head._next;
    while (it != nullptr) {
      if (it->_cur->_ptr > first && it->_cur->_ptr <= last) {
        it->_cur->_pVec = nullptr;
        pre->_next = it->_next;
        delete it;
        it = pre->_next;
      } else {
        pre = it;
        it = it->_next;
      }
    }
  }
};
```



