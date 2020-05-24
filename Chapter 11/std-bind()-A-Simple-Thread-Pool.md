# *std::bind()*: A Simple Thread Pool

In previous chapter, we have introduced *bind1st* and *bind2nd*. These binders are used to bind function parameters with fixed value. However, they only apply to functions with two parameters. Now let's introduce a more powerful binder in C++ 11: *std::bind()*.

*std::bind()* binds the parameters in a function, and returns a function object. *std::bind()* is implemented with function templates, so it supports type deduction of parameter types, and various number of parameters. *std::bind()* can be used to bind functions with different number of parameters, and member functions as well:

```cpp
void foo(string str) {
    cout << str << endl;
}

int sum(int a, int b) {
    return a + b;
}

class Test {
public:
    int sum(int a, int b) {
        return a + b;
    }
};

int main() {
    bind(foo, "foo")();	// foo
    cout << bind(sum, 10, 20)() << endl;	// 30
    cout << bind(&Test::sum, Test(), 20, 30)() << endl;	// 50
    return 0;
}
```

In the previous example, all parameters are bound with *std::bind()*. We can also bind a part of them with **parameter placeholders**. Parameter placeholders are within the namespace of *placeholders*, and consist of a underline and a number, which indicates the order of parameters. In the following example, we put a placeholder at the first parameter of *sum()*, and bind the other one with 10. It is the same as using *bind1st(sum, 10)*, but is much more flexible.

```cpp
using namespace placeholders
int main() {
    cout << bind(sum, _1, _2)(20, 30) << endl;	// 50
    cout << bind(sum, _1, 10)(20) << endl;	// 30
    return 0;
}
```

Since *std::bind()* returns a function object, we can use a *std::function* object with it. The next example use an object of type *function<void(string)>* to receive the returned function object, where the binder can be reused later.

```cpp
int main() {
    function<void(string)> f = bind(foo, _1);
    f("foo");	// foo
    f("bar");	// bar
    return 0;
}
```

*std::bind()* are widely used in large-scale C++ projects. We can implement a simple thread pool with the feature of *std::bind()*. More about multithreading will be introduced later. Now let's just look at this example.

```cpp
#include <functional>
#include <iostream>
#include <thread>
#include <vector>
using namespace std;

class Thread {
 public:
  Thread(function<void()> func) : _func(func) {}

  thread start() {
    thread t(_func);
    return t;
  }

 private:
  function<void()> _func;
};

class ThreadPool {
 public:
  ThreadPool() {}

  ~ThreadPool() {
    for (int i = 0; i < _pool.size(); i++) {
      delete _pool[i];
    }
  }
  void startPool(int size) {
    for (int i = 0; i < size; i++) {
      _pool.push_back(new Thread(bind(&ThreadPool::runInThread, this, i)));
    }

    for (int i = 0; i < size; i++) {
      _handler.push_back(_pool[i]->start());
    }

    for (thread &t : _handler) {
      t.join();
    }
  }

 private:
  vector<Thread *> _pool;
  vector<thread> _handler;
  void runInThread(int id) { cout << "Thread " << id << endl; }
};
```

The above example has a *Thread* class which basically takes a function object and *start()* executes that function in the thread. Then inside *ThreadPool*, we create a certain number of *Thread* objects, and call their *start()* method respectively. Here we also have a function *runInThread()* which is exactly the function we want to execute in each thread. Since this function is a member function, we can not pass it as a function pointer or else to the constructor of *Thread*. Instead, we use *std::bind()* to bind its parameter, and convert it into a function object. In this way, *Thread::start()* can call the function directly with operator `()`.

Now in the main function we create a thread pool, and start with 10 threads.

```cpp
int main() {
  ThreadPool pool;
  pool.startPool(10);
  return 0;
}
```

The program has the following output. Since each print statement is executed in each thread disorderly, the output is disordered as well.

```
Thread Thread 10

Thread 2
Thread 3
Thread 4
Thread 5
Thread 6
Thread 7
Thread 8
Thread 9
```

