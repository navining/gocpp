# More about `new` and `delete`

`new` and `delete` are a couple of keywords in C++ for memory arrangement. Meanwhile, they are operators that can be overloaded as well. When `new` is used, the compiler will first calls function *operator new()* to allocate memory on heap, and then calls the corresponding constructor of the object. When `delete` is used, the compiler first calls the destructor, and then calls function *operator delete()* to deallocate the memory. Those are same for `new[]` and `delete[]`, which is used for array elements.

The underlying implementations of operators `new` and `delete` are standard C functions *malloc()* and *free()*, which shows as follow. The former takes size of the object as parameter, and the latter takes the pointer of the object to be deleted as parameter.

```cpp
void *operator new(size_t size) {
    void *p = malloc(size);
    if (p == nullptr)
        throw bad_alloc();
    return p;
}

void operator delete(void *p) {
    free(p);
}
```

Knowing this, we can overload them using our own-defined memory management functions. With overloading, we may track the allocated memory, for more precise and detailed memory management. It is widely used in a memory pool, or in checking memory leaks. 

We already know that `delete` is used to free a single object, and `delete[]` is used to free an array object. But can these two be mixed used? Well, it depends.

In the following example, it is okay to use either of them. *int* is a built-in type instead of an object, so there's no constructor to be called. In this case, `delete` and `delete[]` are the same since their  underlying implementations are the same.

```cpp
int main() {
    int *p = new int;
    delete[] p;
    int *q = new int[10];
    delete q;
    return 0;
}
```

However, in the next example, incorrect use of these two will make the program crash:

```cpp
class Test {
public:
	Test() {...}
    ~Test() {...}
private:
	int a;    
};

int main() {
    Test *t1 = new Test();
    delete[] t1;	// ERROR
    Test *t2 = new Test[5];
    delete t2;	// ERROR
    return 0;
}
```

It is because that objects need to be destroyed before deallocation. When `new[]` is used to create array objects, not only the memory space for these objects is allocated, an extra 4-byte space for recording the counts of objects is allocated as well. When `delete[]` is used, it first reads the counts *n* from it, then divides the memory space into *n* portions. In this way, the destructor of each array object can be called correctly. Unlike `delete[]`, `delete` simply treats the whole memory space as a single object and frees it. 

Therefore, if `delete[]` is used for a single object, it cannot find the count information. On the other hand, if `delete` is used for an array object, the freed memory has a 4-byte offset, and the destructors are not called properly as well.