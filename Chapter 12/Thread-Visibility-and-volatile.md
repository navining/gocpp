# Thread Visibility and `volatile`

In the previous chapter we see an example of atomic operations. However, the program has a potential problem which is common in multithreaded programming which is called **thread visibility**. In multithreaded programming, shared variables are often used  to notify other threads that a certain state has changed, and these threads are supposed to sense the change in time. In the previous example, we use a global atomic variable *isReady* to tell the threads whether they are ready to work or not. 

In a symmetric multiprocessor architecture (SMP), multiple processors and cores share a same global memory through the bus, but each processor has its own cache as well. During thread executions, the data is usually loaded into caches or registers instead of reading from the global memory directly to improve access efficiency. However, this optimization may bring problems in multithreaded programs. When a thread makes a modification to a shared variable, it may just modify the temporary value in the register or cache, and may not update the global memory immediately. Even if the memory is updated in time, other threads on other processors may not read from it immediately, and can not perceive the changes of the shared data.

To fix this problem, we can use keyword `volatile` to force each thread to always access the original data in the global memory:

```cpp
volatile atomic_bool isReady;
volatile atomic_int myCount;
```

The word "volatile" means liable to change rapidly and unpredictably. It is a type modifier which tells the compiler that the variable may be changed by some factors unknown to the compiler, for example operating system, hardware or multi-threads. When encountering variables declared by `volatile`, the compiler will no longer optimize the code, and provides stable access to the original memory address. This non-optimizable feature is reflected in two places:

First, do not make any optimization involving memory access. When accessing a memory object multiple times, the compiler tends to put the data in the cache or in the register, and access the object from them. With `volatile`, the data is always read from the memory, even if its previous instruction just read the data. Similarly, the data is written into the global memory immediately after being modified.

Secondly, keeps the order of instructions unchanged. For multiple read and write operations on variables with `volatile`, the compiler cannot eliminate some of the read and write operations based on its prediction. Moreover, it ensures that the previous read and write operations must be completed before the subsequent read and write operations.

A good approach in multithreaded programming is to always declare shared variables as `volatile`. Notice that `volatile` only ensures that the compiler won't do any optimization on the variable, but there is not any guarantee on thread safety. Please don't confuse this concept with atomicity, as some people may do.