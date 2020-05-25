# Important Features in C++11

So far, we have already learnt most of the commonly used C++ features. Many of them are introduced in C++11 standard. Here we sum up a list of some important features in C++11.

## Keywords and Syntax

- `auto`: A type identifier that can automatically derives the type from the right side of operator `=`.

- `nullptr`: A specialized keyword that refers to a NULL pointer.

- For each: Traverse the container. The syntax is `for(element: containter)`. Underlying implementation is iterators.

- Rvalue reference `&&`: A reference to a Rvalue. It supports move semantics *std::move()* and perfect forwarding *std::forwar()*.
- `...`: Templates with variable number of paramters.

## Smart Pointers

*shared_ptr*: A pointer with reference counting. Multiple pointers can point to a same object.

*weak_ptr*: A observer pointer which will not change the reference count of the recourse, but can only examine if the object exists or not.

## Function Objects and Binders

*std::function*: A powerful class able to bind a function with a function object.

*std::bind()*: Binds the parameters in a function, and returns a function object.

Lambda expressions: Anonymous functions that can serve as a function object without being given a name.

## Containers

*unordered_set*: A associative container storing keys. Its underlying implementation is a hash map.

*unordered_map*: A associative container storing key-value pairs. Its underlying implementation is a hash map.

*array*: An array container. Unlike *vector*, the size of the array is immutable.

*forward_list*: A single linked list. *list* is a double linked list.

## Multithreading

Previous C++ standard doesn't support language-level thread library. Since different operating system has different thread API, there are troubles when writing cross-platform codes. Now C++11 has its own thread support library which is very easy to use. In this chapter we will introduce threads, locks and atomic operations in C++.