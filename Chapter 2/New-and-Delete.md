# `new` and `delete`

There are two ways to create memory on heap. One original approach in C style is to use the library functions `malloc` and `free`:

```cpp
int main() {
    int *p = (int*)malloc(sizeof(int));
    if (p == nullptr) {
        return -1;
    }
    *p = 20;
    free(p);
    return 0;
}
```

Notice that `malloc` returns a type of *void \**, so we always need to cast it into the correct pointer type. What's more, we need to pass the size of allocated memory as the function argument. If the allocation fails, the function will return a NULL pointer, so we also need to check the validity of our pointer after the function call.

In C++, the memory allocation on heap can be done in a cleverer way: using operator **`new`** and **`delete`**.

```cpp
int *p = new int(20);
delete p;
```

When using `new`, we no longer need to calculate the memory size nor cast the pointer type, thus things get much easier. Notice that `new` can also initialize the memory bucket after allocating it, just like the brackets we use in the code above. If the memory allocation fails, a *bad_alloc* exception is raised, we can then handle it with a try-catch structure.

When it's up to arrays, we can also allocate memory for it in a easy way. For `new`, we need to use square brackets, just like the way we declare an array on the stack. And for `delete`, we also need to add a pair of square brackets after it. `delete[]` will then loop through the array and operate `delete` to every element in the array.

Besides the conventional way to use `new`, there is also several other ways to use `new`. We can tell the program not to throw an exception if the allocation fails by stating *(nothrow)* after `new`.

```cpp
int *p2 = new (nothrow) int;	// No exception
```

We can also assign constant memory on the heap with `const` keyword. In this way, the return pointer should be modified with `const` as well.

```cpp
const int *p3 = new const int(40);	// Constant memory
```

Now all the memory address on the heap is allocated by the system. What if we want to allocate the memory on a specific location?  We need to state the address of the destination after `new`, with brackets.

```cpp
int data = 0;
int *p4 = new (&data) int(50);	// Memory allocated on &data
cout << data << endl;	// 50
```

