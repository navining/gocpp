# Container Adaptors

Container adaptors provide a different interface for sequential containers. They do not have their own data structures. Instead, all their methods are implemented by the dependent containers. An example of a *stack* with *deque* as the default structure shows as follow:

```cpp
template<typename T, typename Container=deque<T>>
class Stack {
public:
    void push(const T &val) {
      con.push_back(val);
    }
    
    void pop() {
        con.pop_back();
    }
    
    T top() const {
        return con.back();
    }
private:
    Container con;
};
```

In addition, container adaptors do not have their own iterators as well.

## *stack*

```cpp
#include <stack>
```

*stack* is a FILO (First-In-Last-Out) data structure which adapts a *deque* by default.

`s.push(20)` Insert element at the top. Time complexity is *O(1)*.

`s.pop()` Remove the top element. Time complexity is *O(1)*.

`s.top()` Return the top element. Time complexity is *O(1)*.

`s.empty()` Check whether the container is empty.

`s.size()`  Return the number of elements in the container.

## *queue*

```cpp
#include <queue>
```

*queue* is a FIFO (First-In-First-Out) data structure which adapts a *deque* by default.

`q.push(20)` Insert element at the end. Time complexity is *O(1)*.

`q.pop()` Remove the first element. Time complexity is *O(1)*.

`q.front()` Return the first element. Time complexity is *O(1)*.

`q.back()` Return the last element. Time complexity is *O(1)*.

`q.empty()` Check whether the container is empty.

`q.size()`  Return the number of elements in the container.

## *priority_queue*

```cpp
#include <priority_queue>
```

*priority_queue* is a container that can access queue elements by their priority (larger by default). It adapts a *vector* by default.

`pq.push(20)` Insert element sorts the container. Time complexity is *O(nlog(n))*.

`pq.pop()` Remove the top element. Time complexity is *O(1)*.

`pq.top()` Return the top element. Time complexity is *O(1)*.

`pq.empty()` Check whether the container is empty.

`pq.size()`  Return the number of elements in the container.

## More about Underlying Containers

**Q:** *stack* and *queue* use *deque* as their default underlying containers. Why don't they use a *vector*?

**A:** We can answer from the differences between these two data structures.

1. The initial memory usage efficiency of *vector* is worse than *deque*, since *deque* allocates more memory when initialized and reduces overhead for expansion.

2. *queue* requires insert from the end. These operations are *O(1)* in *deque*, but *O(n)* in *vector*.

3. When there are a large amount of elements, *vector* requires large continuous memory, while *deque* only requires segmented memory, thus providing a better memory utilization.

**Q:** Why does *priority_queue* use a *vector*？

**A:** The underlying data structure of *priority_queue* is a heap. In a heap structure, we access child nodes with the node index (For example, if a heap starts with 0 and a node has index *i*, then its child nodes are *2i +1* and *2i + 2*). Therefore, heap indexes should be stored in an array of continuous memory. A *vector* makes sure that random access of heap indexes is *O(1)*.