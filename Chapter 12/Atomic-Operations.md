# Atomic Operations

In previous chapter, we wrote a multithreaded program that sells bus tickets. We used mutual exclusion for thread synchronization. Inside the critical section, only one thread can execute at the same time. Though mutex is the most common tool for synchronization, it is somehow heavy since it block other threads to keep waiting. For some simple operations, for example adding and subtracting, we can keep thread safety without using any locks. These operations are known as **atomic operations**.

The word "atomic" means uncuttable. A task performed by a computer can't be broken into smaller steps if it is atomic. In other words, there is no way for a thread to slip through an atomic operation concurrently performed by another one. Remember in traditional `++` operation, it takes three steps to add a variable by 1: load the value of the variable into a register, add the register by 1, and store the value back to the variable. With atomic operations, the load and store operations of the variable are uncuttable, therefore there's no possibility of race condition.

```assembly
mov eax, a
add eax, 1
mov a, eax
```

Atomic operations are low-level, which need the support of hardware. The most common strategy to achieve atomicity is called **compare-and-swap (CAS)**.  It compares the contents of a memory location with a given value and, only if they are the same, modifies the contents of that memory location to a new given value.

C++ 11 provides an atomic library which supports atomic operations:

```cpp
#include <atomic>
```

Here we use a simple example to illustrate it. We defined two variables, *isReady* and *myCount* which is of type *atomic_bool* and *atomic_int* respectively. They are just aliases for *atomic\<bool>* and *atomic\<int>*. Then we create 10 threads, and each of them call `myCount++` for a hundred times. *this_thread::yield()* is called to skip the current CPU time slice and wait for the next scheduling, if the thread creation has not finished yet. If we are not using atomic operations here, there would be races between threads, and the final result is uncertain. But with atomic operations, we can get a correct result of 1000.

```cpp
atomic_bool isReady;
atomic_int myCount;

void task() {
    while (!isReady) {
        this_thread::yield();
    }
    for (int i = 0; i < 100; i++) {
        myCount++;
    }
}

int main() {
    list<thread> tlist;
    for (int i = 0; i < 10; i++) {
        tlist.push_back(thread(task));
    }
    isReady = true;
    for (thread &t : tlist) {
        t.join();
    }
    cout << myCount << endl;	// 1000
    return 0;
}
```

However, the above program still has potential problems. We will discuss more in the next article.