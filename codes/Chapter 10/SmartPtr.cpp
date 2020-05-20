template <typename T>
class RefCount {
 public:
  RefCount(T *ptr = nullptr) : _ptr(ptr) {
    if (_ptr != nullptr) _count = 1;
  }
  void addRef() { _count++; }
  int delRef() { return --_count; }

 private:
  T *_ptr;
  int _count;
};

template <typename T>
class SmartPtr {
 public:
  SmartPtr(T *ptr = nullptr) : _ptr(ptr) { _refCount = new RefCount<T>(ptr); }
  ~SmartPtr() {
    if (0 == _refCount->delRef()) {
      delete _ptr;
      _ptr = nullptr;
    }
  }
  T &operator*() { return *_ptr; }
  T *operator->() { return _ptr; }
  SmartPtr(const SmartPtr<T> &other) {
    _ptr = other._ptr;
    _refCount = other._refCount;
    if (_ptr != nullptr) _refCount->addRef();
  }
  SmartPtr<T> &operator=(const SmartPtr<T> &other) {
    if (this == &other) return *this;
    if (0 == _refCount->delRef()) {
      delete _ptr;
    }
    _ptr = other._ptr;
    _refCount = other._refCount;
    _refCount->addRef();
    return *this;
  }

 private:
  T *_ptr;
  RefCount<T> *_refCount;
};