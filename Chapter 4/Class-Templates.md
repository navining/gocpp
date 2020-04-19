# Class Templates

Templates are also widely used for classes. For example, the Standard Template Library (STL) is a set of *C++* template classes to provide common programming data structures and functions.

The syntax of template classes is similar to template functions, with keyword `template` and the template parameters before the class name. Since that the class name of a template class is composed of the template name and the template parameter, wherever a template class appears should the parameters be added as well. For convenience, constructors and destructors can omit template parameters. 

A template version of our *MyStack* class is shown as follow:

```cpp
template<typename T>
class MyStack {
public:
    MyStack(int size = 10);
    ~MyStack();
    MyStack(const MyStack<T> &other);
    MyStack<T>& operator=(const MyStack<T> &other);
    void push(const T &val);
    void pop();
    T top() const;
    bool full() const;
    bool empty() const;
private:
    T *_pstack;
    int _top;
    int _size;
    void resize();
};
```

The keyword `template` only play a role within the scope of the class. So if we want to implement member functions outside the class, keyword `template` should be reused again.

```cpp
template<typename T>
void MyStack<T>::push(const T &val) {
    if (full()) resize();
    _pstack[_top++] = val;
  }
```

Then we can use our self-defined fancy stack in the main function. When the template class is used, the compiler instantiate a copy of it with the type we choose. But unlike template functions, this instantiation is selective, which means only those methods being called are instantiated. This approach decreases the amount of the code text.

```cpp
int main() {
    MyStack<int> s;
    s.push(20);
    s.push(30);
    s.push(40);
    s.pop();
    cout << s.top() << endl;	// 30
    return 0;
}
```

Templates can also have default parameters as well. In the following case, if we don't specify the type when using *MyStack*, the type name is *int* by default.

```cpp
template<typename T = int>
class MyStack {
	...
};

int main() {
    MyStack<> s;
    return 0;
}
```

The complete code of *MyStack* is as follows.

```cpp
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
```

