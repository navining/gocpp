# Move Semantics and Perfect Forwarding

In the previous article, we learned member functions with Rvalue references as parameters. Member functions with Rvalue references are widely used in STL containers to improve performance. For example

```cpp
int main() {
    vector<MyString> v;
    MyString s = "aaa"
    v.push_back(s);
    v.push_back(MyString("bbb"));
    return 0;
}
```

The first *push_back()* takes a *MyString* object, whose normal copy constructor will be called in the container. The latter one takes a temporary object, whose copy constructor with Rvalue reference will be called.

We have written a *MyVector* in previous chapters. Now let's modify it to add member functions with Rvalue references. We've already have a normal version of *push_back* as

```cpp
void push_back(const T &val) {
    if (full()) expand();
    _allocator.construct(_last, val);
    _last++;
}
```

which calls the *construct()* method of the allocator. The Rvalue reference version of *push_back()* can be written as

```cpp
void push_back(T &&val) {
    if (full()) expand();
    _allocator.construct(_last, val);
    _last++;
}
```

Inside *push_back()* we called *constrct()*, so its Rvalue reference version should be implemented as well.

```cpp
void construct(T *p, T &&val) { new (p) T(val); }
```

But the Rvalue reference *val* is a Lvalue itself, which means that *constrct(_last, val)* will always call the Lvalue reference version. To fix this, we can use *std::move()* here, which is called the **move semantics**.

```cpp
#include <utility>
```

*std::move()* is used to indicate that an object may be "moved from". In specific, it is exactly equivalent to a `static_cast` to an Rvalue reference type. We can use *std::move()* to cast *val* into its Rvalue reference:

```cpp
void push_back(T &&val) {
    if (full()) expand();
    _allocator.construct(_last, std::move(val));
    _last++;
}
```

Similarly, *std::move()* should be used in *construct()* as well:

```cpp
void construct(T *p, T &&val) { new (p) T(std::move(val)); }
```

Now we have the corresponding Lvalue reference and Rvalue reference member functions. But should we defined two functions every time? It seems not a good way of reusing code. A better approach is to use the type deduction of function templates:

```cpp
template <typename Ty>
void push_back(Ty &&val) {
    if (full()) expand();
    _allocator.construct(_last, std::forward<Ty>(val));
    _last++;
}
```

In the above code, we defined a template function *push_back()* which takes a parameter of type *Ty &&*. When a Lvalue is passed in, *val* will also be a Lvalue because of the type deduction. Instead, if a Rvalue is passed in, *val* will be a Rvalue. But how could the corresponding version of *construct()* be called properly, since *val* is always treated as a Lvalue? Here we need to use *std::forward()*, which is known as **perfect forwarding**.

*std::forward()* forwards Lvalues as either Lvalues or as Rvalues, depending on the type. Then the corresponding version of *construct()* can be called.

Similarly, *construct()* can also be rewritten into template function as

```cpp
  template <typename Ty>
  void construct(T *p, Ty &&val) {
    new (p) T(std::forward<Ty>(val));
  }
```

*std::forward()* is also used here to call the corresponding copy constructor of type *T*.