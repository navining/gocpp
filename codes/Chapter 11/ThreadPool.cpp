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
