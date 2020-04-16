#include <iostream>
using namespace std;

class MyQueue {
 public:
  MyQueue(int size = 20) {
    _pqueue = new int[size];
    _front = _rear = 0;
    _size = size;
  }

  ~MyQueue() {
    delete[] _pqueue;
    _pqueue = nullptr;
  }

  MyQueue(const MyQueue &other) {
    _size = other._size;
    _front = other._front;
    _rear = other._rear;
    _pqueue = new int[_size];
    for (int i = _front; i != _rear; i = (i + 1) % _size) {
      _pqueue[i] = other._pqueue[i];
    }
  }

  MyQueue &operator=(const MyQueue &other) {
    if (this == &other) return *this;

    delete[] _pqueue;

    _size = other._size;
    _front = other._front;
    _rear = other._rear;
    _pqueue = new int[_size];
    for (int i = _front; i != _rear; i = (i + 1) % _size) {
      _pqueue[i] = other._pqueue[i];
    }

    return *this;
  }

  void push(int val) {
    if (full()) resize();
    _pqueue[_rear] = val;
    _rear = (_rear + 1) % _size;
  }

  void pop() {
    if (empty()) return;
    _front = (_front + 1) % _size;
  }

  int top() { return _pqueue[_front]; }

  bool full() { return (_rear + 1) % _size == _front; }

  bool empty() { return _front == _rear; }

 private:
  int *_pqueue;
  int _front;
  int _rear;
  int _size;

  void resize() {
    int *ptmp = new int[2 * _size];
    int index = 0;
    for (int i = _front; i != _rear; i = (i + 1) % _size) {
      ptmp[index++] = _pqueue[i];
    }
    delete[] _pqueue;
    _pqueue = ptmp;
    _front = 0;
    _rear = index;
    _size *= 2;
  }
};