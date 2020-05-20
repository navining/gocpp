# Custom Deleters

Smart pointers ensure the automatic release of resources on the heap. In the previous example, our custom *SmartPtr* release the resources by calling `delete` on the pointer. However, `delete` is not always the correct way to release resources. For example, array objects need to be destroyed with `delete[]`, and files need to be closed with *fclose()*. Therefore, under some circumstances we need to customize the deleter.

*unique_ptr* 和 *shared_ptr* both support custom deleters. Inside their destructors a function object of the deleter is called. The default deleter simply uses `delete`:

```cpp
template <typename T>
class Deleter {
public:
    void operator() (T *ptr) {
        delete ptr;
    }
};
```

Now if we use a *unique_ptr* to point to an array, we can defined our own deleter which uses `delete[]` to free the memory. Then we need to use *MyDeleter* as a template parameter.

```cpp
template <typename T>
class MyDeleter {
public:
    void operator() (T *ptr) const {
        delete[] ptr;
    }
};

int main() {
    unique_ptr<int, MyDeleter<int>> p = new int[100];
    return 0;
}
```

Similarly, we can also customize a deleter to release a file resource with *fclose()*:

```cpp
template <typename T>
class MyDeleter {
public:
    void operator() (T *ptr) const {
        fclose(ptr);
    }
};

int main() {
    unique_ptr<FILE, MyDeleter<FILE>> p = fopen("data.txt", "w");
    return 0;
}
```

In modern C++, a more convenient way to use custom deleters is to use the lambda expressions. The above examples can also be written as follows, without additional definitions of function objects.

```cpp
#include <functional>
int main() {
    unique_ptr<int, function<void (int *)>> p1(new int[100], 
    	[](int *p) -> void {
        	delete[] p;
    	}
    );
    unique_ptr<FILE, function<void (FILE *)>> p2(fopen("data.txt", "w"), 
    	[](FILE *p) -> void {
        	fclose(p);
    	}
    );
}
```

