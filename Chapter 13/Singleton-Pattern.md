# Singleton Pattern

Singleton pattern is a design pattern that restricts the instantiation of a class to one single instance. No matter how many times the objects of a singleton class are created, only one instance of the class can be acquired.

Singleton pattern is often used in modules that can only exists once in the program, for example log modules and database modules. There are two types of singleton patterns, lazy and eager, which are suitable for different scenarios.

## Eager Singleton Pattern

We need three steps to define a singleton class:

1. Make the constructor private.
2. Define a unique private instance inside the class

3. Provide an public interface to acquire the only instance of the class

```cpp
class Singleton {
public:
    static Singleton* getInstance() {
        return &instance;
    }
private:
    static Singleton instance;
    Singleton() {}
};
Singleton Singleton::instance;
```

In the example, we declared the interface *getInstance()* as a static method. Therefore, we can access the method without instantiating any object:

```cpp
int main() {
    Singleton *p1 = Singleton::getInstance();
    Singleton *p2 = Singleton::getInstance();
    Singleton *p3 = Singleton::getInstance();
    return 0;
}
```

But there remains a problem. Though we make the constructor private, we can still create instances through the copy constructor, for example `Singleton *p4 = p3`. Therefore, we should disable the copy constructor and operator `=` as well:

```cpp
class Singleton {
public:
    static Singleton* getInstance() {
        return &instance;
    }
private:
    static Singleton instance;
    Singleton() {}
    Singleton(const Singleton &) = delete;
    Singleton& operator=(const Singleton &) = delete;
};
Singleton Singleton::instance;
```

Since the private instance is static and is defined outside the class, the object is always initialized before the main function. It is called a **eager initialization**, in which the instance is initialized before it is acquired. This pattern is straightforward, but might be a waste of resource, because a singleton class object needs to be initialized even if it is not used at all. Moreover, since all those eager singleton classes are initialized before the program begins to execute, it will slows down the launch speed.

## Lazy Singleton Pattern

To improve those drawbacks, we have the **lazy initialization**. The instance of a lazy singleton class is not created until the first acquisition with *getInstance()*. To achieve this, we change the private instance into a pointer, and initialize it with NULL. The first time *getInstance()* is called, we create a new object. When it is called later, we simply return the pointer.

```cpp
class Singleton {
public:
    static Singleton* getInstance() {
        if (instance == nullptr)
            instance = new Singleton();
        return instance;
    }
private:
    static Singleton *instance;
    Singleton() {}
    Singleton(const Singleton &) = delete;
    Singleton& operator=(const Singleton &) = delete;
};
Singleton Singleton::instance = nullptr;
```

However, this example has a thread safety problem. Remember that the keyword `new` does three things: allocates the memory, constructs the object, and assigns its address to the pointer. Now if a thread has created the object, but another thread enters the `if` branch before the pointer has been assigned the address of the object. In this case, the object will be created repeatedly.

Therefore, to ensure thread safety, we should use the mutual exclusion. Here we use a *lock_guard* to manage the mutex, and use dual judgment to ensure the correctness. Moreover, since the instance pointer is a shared variable, it should be declared with `volatile` as well.

```cpp
mutex _mutex;
class Singleton {
public:
    static Singleton* getInstance() {
        if (instance == nullptr) {
            lock_guard<mutex> lock(_mutex);
            if (instance == nullptr)
            	instance = new Singleton();
        }
        return instance;
    }
private:
    static Singleton *volatile instance;
    Singleton() {}
    Singleton(const Singleton &) = delete;
    Singleton& operator=(const Singleton &) = delete;
};
Singleton* volatile Singleton::instance = nullptr;
```

Furthermore, we can write a thread-safe lazy singleton class in a simpler way using the features of static variables. Instead of declaring the instance as a member variable, we defined the instance in the *getInstance()* method. Remember that a static variable is initialized when the program first executes that line.

```cpp
class Singleton {
public:
    static Singleton* getInstance() {
        static Singleton instance;
        return &instance;
    }
private:
    Singleton() {}
    Singleton(const Singleton &) = delete;
    Singleton& operator=(const Singleton &) = delete;
};
```

Then what about the thread safety of defining the instance? If we look at the assembly code of the previous example, we may find that mutex instructions have already be added when the variable is defined. In fact, when initializing a static local variable inside a function, the compiler will automatically add mutex at the assembly level when compiling.