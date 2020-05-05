# Sequence Containers

Sequence containers implement data structures which can be accessed sequentially. There are three common sequence containers in STL: *vector*, *deque* and *list*.

## *vector*

```cpp
#include <vector>
```

*vector* is a dynamic contiguous array. It's underlying data structure is an array whose space is opened up dynamically. Every time the array is full, its original space is expanded by twice.

**Adding:**

```vec.push_back(20);``` Add elements at the end of *vector*. The Time complexity is *O(1)*. May need to be expanded.

`vec.insert(it, 20);` Add elements at where the iterator points to. The Time complexity is *O(n)*. May need to be expanded.

**Deleting:**

`vec.pop_back(20);` Delete elements at the end of *vector*. The Time complexity is *O(1)*.

`vec.erase(it);` Delete elements at where the iterator points to. The Time complexity is *O(n)*.

**Inquiry：**

`operator[]` Random access with the index. The Time complexity is *O(1)*.

`vector::iterator` Iterators of *vector*.

**Common methods：**

`vec.size()` Number of elements in the *vector*.

`vec.empty()` Whether the *vector* is empty.

`vec.reserve(20)` Reserve space for the *vector*. It only opens up memory space and no new elements will be added. It can be used if the amount of elements is already known, in order to avoid the overhead of expansion.

`vec.resize(20)` Expand space for the *vector*. It not only opens up memory space but also adds new elements with default constructors.

`vec.swap(vec2)` Swap the elements in two *vector*s.

## *deque*

```cpp
#include <deque>
```

*deque* is an double-ended queue which allows fast insertion and deletion at both its beginning and its end. Its underlying data structure is a two-dimensional array whose space is opened up dynamically. Elements are stored in the second dimension, and the first dimension stores pointers to the second dimension. Every time the array is full, the first dimension is expanded by twice.

**Adding:**

`deq.push_back(20);` Add elements at the end of *deque*. The Time complexity is *O(1)*. May need to be expanded.

`deq.push_front(20);` Add elements at the front of *deque*. The Time complexity is *O(1)*. May need to be expanded.

`deq.insert(it, 20);` Add elements at where the iterator points to. The Time complexity is *O(n)*. May need to be expanded.

**Deleting:**

`deq.pop_back();` Delete elements at the end of *deque*. The Time complexity is *O(1)*.

`deq.pop_front();` Delete elements at the front of *deque*. The Time complexity is *O(1)*.

`deq.erase(it);` Delete elements at where the iterator points to. The Time complexity is *O(n)*.

**Inquiry：**

`deque::iterator` Iterators of *deque*.

**Common methods：**

Similar to *vector*.

## *list*

```cpp
#include <list>
```

*list* is a doubly-linked list that supports constant time insertion and removal of elements from anywhere in the container. It's underlying data structure is a double circular list, in which each element has pointers pointing to its previous and next, and the head and tail are linked together as well.

Most of its methods are the same as *deque*.

**Adding:**

`li.push_back(20);` Add elements at the end of *list*. The Time complexity is *O(1)*.

`li.push_front(20);` Add elements at the front of *list*. The Time complexity is *O(1)*. 

`li.insert(it, 20);` Add elements at where the iterator points to. The Time complexity is *O(1)*.

**Deleting:**

`li.pop_back();` Delete elements at the end of *list*. The Time complexity is *O(1)*.

`li.pop_front();` Delete elements at the front of *list*. The Time complexity is *O(1)*.

`li.erase(it);` Delete elements at where the iterator points to. The Time complexity is *O(1)*.

**Inquiry：**

`list::iterator` Iterators of *list*.

**Common methods：**

Similar to *vector*.

## Differences between *vector*, *deque* and *list*

*vector*, *deque*, *list* and their differences is a frequently asked question during the interview. When answering this kinds of questions, we can focus on their underlying data structures and the time complexity of operations.

### Data Structures

1. *vector*: Dynamic array with continuous memory. Double expansion is implemented when the array is full.

2. *deque*: Dynamic 2-dimensional array. The second dimension is a fixed-length array with continuous memory, and the first dimension stores pointers to second dimensions (partially continuous). Double expansion is implemented in the first dimension.

3. *list*: Double circular list. Each element has pointers pointing to its previous and next, and the head and tail are linked together as well. The memory space is not continuous.

### Differences between *vector* and *deque*

1. Differences in data structures.
2. Time complexity of adding and deleting elements: all *O(1)* at the end and *O(n)* in the middle. *O(1)* at the front for *deque*, and *O(n)* at the front for *vector*.
3. Efficiency of *insert()* and *erase()*: Time complexity is both *O(n)*，but elements movement is faster in *vector* since its memory is continuous.
4. Memory efficiency: *vector* requires continuous memory space, while *deque* can store elements in chunks and does not require large continuous spaces.

### Differences between *vector* and *list*

1. Differences in data structures.
2. Time complexity of adding and deleting elements: all *O(1)* at the end. *O(1)* in the middle and the front for *list*, and *O(n)* in the middle and the front for *vector*.
3. Time complexity of inquiring elements: *O(1)* for *vector* and *O(n)* for *list*.

All in all, *vector* is preferred in most circumstances because it allows *O(1)* random access. If we want to add items from both the front and the end, *deque* is a good choice. *list* has better performance if we have lots of insert and delete operations since they are all *O(1)* compared to *O(n)* in *vector* and *deque*.