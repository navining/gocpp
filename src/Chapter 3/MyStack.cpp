class MyStack {
 public:
  MyStack(int size = 10) {
    _pstack = new int[size];
    _top = -1;
    _size = size;
  }

  ~MyStack() {
    delete[] _pstack;
    _pstack = nullptr;
  }

  MyStack(const MyStack &other) {
    _pstack = new int[other._size];
    for (int i = 0; i < _size; i++) {
      _pstack[i] = other._pstack[i];
    }
    _top = other._top;
    _size = other._size;
  }

  MyStack &operator=(const MyStack &other) {
    if (this == &other) return *this;
    // 1. Release current memory
    delete[] _pstack;
    // 2. Allocate new memory
    _pstack = new int[other._size];
    for (int i = 0; i < _size; i++) {
      _pstack[i] = other._pstack[i];
    }
    _top = other._top;
    _size = other._size;

    return *this;
  }

  void push(int val) {
    if (full()) resize();
    _pstack[++_top] = val;
  }

  void pop() {
    if (empty()) return;
    --_top;
  }

  int top() { return _pstack[_top]; }

  bool empty() { return _top == -1; }

  bool full() { return _top == _size - 1; }

 private:
  int *_pstack;
  int _top;
  int _size;

  void resize() {
    int *ptmp = new int[_size * 2];
    for (int i = 0; i < _size; ++i) {
      ptmp[i] = _pstack[i];
    }
    delete[] _pstack;
    _pstack = ptmp;
    _size *= 2;
  }
};