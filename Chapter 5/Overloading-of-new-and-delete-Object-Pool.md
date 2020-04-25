# Overloading of `new` and `delete`: Object Pool

We have already written an own-defined queue data structure *MyQueue* before, which maintains a dynamic array as its private member. This time, we are going to rewrite *MyQueue*, using linked list as its underlying implementation.

```cpp
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
    T _data;
    QueueItem *_next;
  };

  QueueItem *_front;
  QueueItem *_rear;
};
```

Here we use a nested struct *QueueItem* as the list node, and keep tracking the front and rear of our linked list. Now suppose we are using our new queue in this way:

```cpp
int main() {
  MyQueue<int> q;
  for (int i = 0; i < 10000; i++) {
    q.push(i);
    q.pop();
  }
  return 0;
}
```

Here we keep pushing and poping items from the queue for ten thousand times. In our current implementation, each time an element is pushed or popped, a new memory space for *QueueItem* is allocated and deallocated on the heap. When these operations are very frequent, the memory allocation and deallocation is consuming. To improve this, we can reuse the list nodes we'v already created.

An **object pool** is a good approach in cases that a large number of objecs are constructed and destroyed in a short time. There are other kinds of pools like thread pool or connection pool, which share the same idea of resource reuse. 

The main idea of object pool is to create a pool of objects at once. When an object is created, we get an empty object from the pool. When an object is destroyed, we return it back to the pool. Here we use a static linked list of 10000 *QueueItem*s whose memory space is continuous. A pointer *_pool* points to the first empty element in the pool. Then we can overload the member function *operator new()* and *operator delete()* of *QueueItem*. 

When a new *QueueItem* is created, we simply return *_pool* to it, and move *_pool* to the next empty element. When a *QueueItem* is deleted, we do not deallocate the memory. Instead, we change its next element into *_pool*, and move *_pool* onto it. In this way, the object is returned back to the pool. If the pool is full, another pool is opened up.

```cpp
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

template <typename T>
typename MyQueue<T>::QueueItem *MyQueue<T>::QueueItem::_pool = nullptr;
```

Here we haven't implemented the memory deallocation of the object pool, since it's not straightforward here. Using smart pointers is a clever way to do so, which we will introduce in the future.