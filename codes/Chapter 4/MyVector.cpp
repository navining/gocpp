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