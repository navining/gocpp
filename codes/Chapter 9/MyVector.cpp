#include <stdlib.h>

#include <utility>

template <typename T>
class Allocator {
 public:
  T *allocate(size_t size) { return (T *)malloc(sizeof(T) * size); }

  void deallocate(void *p) { free(p); }

  template <typename Ty>
  void construct(T *p, Ty &&val) {
    new (p) T(std::forward<Ty>(val));
  }

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

  template <typename Ty>
  void push_back(Ty &&val) {
    if (full()) expand();
    _allocator.construct(_last, std::forward<Ty>(val));
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

int main() {}