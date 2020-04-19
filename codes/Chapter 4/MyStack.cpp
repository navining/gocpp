template <typename T>
class MyStack {
 public:
  MyStack(int size = 10) : _pstack(new T[size]), _top(0), _size(size) {}

  ~MyStack() {
    delete[] _pstack;
    _pstack = nullptr;
  }

  MyStack(const MyStack<T> &other) : _top(other.top), _size(other._size) {
    _pstack = new T[_size];
    for (int i = 0; i < _top; i++) {
      _pstack[i] = other._pstack[i];
    }
  }

  MyStack<T> &operator=(const MyStack<T> &other) {
    if (*this == other) return *this;
    delete[] _pstack;
    _top = other.top;
    _size = other._size;
    _pstack = new T[_size];
    for (int i = 0; i < _top; i++) {
      _pstack[i] = other._pstack[i];
    }
    return *this;
  }

  void push(const T &val) {
    if (full()) resize();
    _pstack[_top++] = val;
  }

  void pop() {
    if (!empty()) --_top;
  }

  T top() const { return _pstack[_top - 1]; }

  bool full() const { return _top == _size; }

  bool empty() const { return _top == 0; }

 private:
  T *_pstack;
  int _top;
  int _size;

  void resize() {
    T *tmp = new T[_size * 2];
    for (int i = 0; i < _top; i++) {
      tmp[i] = _pstack[i];
    }
    delete[] _pstack;
    _pstack = tmp;
    _size *= 2;
  }
};