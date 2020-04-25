#include <cstddef>

template <typename T>
class MyQueue {
 public:
  MyQueue() { _front = _rear = new QueueItem(); }

  ~MyQueue() {
    QueueItem *cur = _front;
    while (cur != nullptr) {
      _front = _front->_next;
      delete cur;
      cur = _front;
    }
  }

  void push(const T &val) {
    QueueItem *item = new QueueItem(val);
    _rear->_next = item;
    _rear = item;
  }

  void pop() {
    if (empty()) return;
    QueueItem *first = _front->_next;
    _front->_next = first->_next;
    if (_front->_next == nullptr) {
      _rear = _front;
    }
    delete first;
  }

  T front() const { return _front->_next->_data; }

  bool empty() const { return _front == _rear; }

 private:
  struct QueueItem {
    QueueItem(T data = T()) : _data(data), _next(nullptr) {}

    void *operator new(size_t size) {
      if (_pool == nullptr) {
        _pool = (QueueItem *)new char[POOL_ITEM_SIZE * sizeof(QueueItem)];
        QueueItem *p = _pool;
        for (; p < _pool + POOL_ITEM_SIZE; ++p) {
          p->_next = p + 1;
        }
        p->_next = nullptr;
      }
      QueueItem *p = _pool;
      _pool = _pool->_next;
      return p;
    }

    void operator delete(void *ptr) {
      QueueItem *p = (QueueItem *)ptr;
      p->_next = _pool;
      _pool = p;
    }

    T _data;
    QueueItem *_next;
    static const int POOL_ITEM_SIZE = 10000;
    static QueueItem *_pool;
  };

  QueueItem *_front;
  QueueItem *_rear;
};

template <typename T>
typename MyQueue<T>::QueueItem *MyQueue<T>::QueueItem::_pool = nullptr;