# Constructor and Destructor

Let's look at the following code. Here we use object-oriented programming to implement a data structure *stack*. We use a dynamic array to store elements, and use member methods to imitate stack push and pop. The stack is also able to resize if it is full.

```cpp
class MyStack {
public:
	void init() {
		_pstack = new int[size];
		_top = -1;
		_size = size;
	}   
	void push(int val) {
		if (full())
			resize();
		_pstack[++_top] = val;
	}   
	void pop() {
		if (empty())
			return;
		--_top;
	}
	int top() {
		return _pstack[_top];
	}
	bool empty() { return _top == -1; }
	bool full() { return _top == _size - 1; }
    void release()
	{
		delete[]_pstack;
		_pstack = nullptr;
	}
private:
	int *_pstack;
	int _top;
	int _size;

	void resize() {
		int *ptmp = new int[_size * 2];
		for (int i = 0; i < _size; ++i) {
			ptmp[i] = _pstack[i];
		}
		delete[]_pstack;
		_pstack = ptmp;
		_size *= 2;
	}
};
```

If we want to use our own stack, we need to initialize it with *init()* and release the memory with *release()* explicitly. If the user forget to do so, it will either fail to allocate memory or cause a memory leak.

```cpp
int main() {
    MyStack s;
    s.init(5);	// Initialize memory
    for (int i =0; i < 15; i++) {
        s.push(rand() % 100);
    }
    while(!s.empty()) {
        cout << s.top() << endl;
        s.pop();
    }
    s.release();	// Release memory
}
```

Fortunately, the class provides us a **constructor** and **destructor**. The former is called once an object is created, and the latter is called once the object is destroyed. The constructor and destructor has the same name as the class (destructor has a tilde at the front), and there's no return value. Thus, we can rewrite *init()* and *release()* as

```cpp
MyStack(int size = 10) {
    _pstack = new int[size];
	_top = -1;
	_size = size;
}
~MyStack() {
	delete[]_pstack;
	_pstack = nullptr;
}
```

Every time an object is declared, the memory is allocated first, and then the constructor is called. When to call the destructor depends on the lifecycle of the object. A global object is destructed when the program exits. The object on function stack is destructed when the function returns. It follows FILO: Objects which construct first destruct last. The object on the heap has too be released with `delete` manually. When an object is deleted, it first calls its destructor, and then free the memory with `free`.

Notice that the constructor can be overloaded. Several constructors can be defined, and the compiler will automatically calls the right one when the object is created. If no constructors are defined, the compiler will generate a empty constructor with no parameters. But destructors do not have parameters, so there is only one destructor in each object.

