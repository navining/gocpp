# Mutual Exclusion

Using what we have learnt about multithreading, we write a simple program which has three windows selling bus tickets. The total number of tickets is 100 and it takes 100 milliseconds for each window to sell a ticket.

```cpp
int numOfTickets = 100;

void sellTicket(int index) {
    while (numOfTickets > 0) {
        printf("Window %d sells ticket No. %d\n", index, numOfTickets);
        numOfTickets--;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main() {
    list<thread> tlist;
    for (int i = 0; i < 3; i++) {
        tlist.push_back(thread(sellTicket, i));
    }
    for (thread &t : tlist) {
        t.join();
    }
    return 0;
}
```

Now if we look at the output we may find a problem: some tickets are sold more than once in different windows! It is apparently incorrect.

```
...
Window 0 sells ticket No. 10
Window 1 sells ticket No. 10
Window 2 sells ticket No. 10
Window 1 sells ticket No. 7
Window 0 sells ticket No. 7
Window 2 sells ticket No. 5
Window 1 sells ticket No. 4
Window 2 sells ticket No. 4
Window 0 sells ticket No. 3
Window 0 sells ticket No. 1
Window 1 sells ticket No. 1
Window 2 sells ticket No. 1
```

This is a thread safety issue of multithreaded programs, which is also called a **race condition**. A race condition is where the program's substantive behavior is dependent on the sequence or timing of other uncontrollable events. In our previous example, `numOfTickets--` is not a thread safe operation, since its assembly code can be written as follow:

```assembly
mov eax, numOfTickets
sub eax, 1
mov numOfTickets, eax
```

No suppose thread 1 move the value of *numOfTickets* into the register, and minus it by 1. But before it writes from the register back to *numOfTickets*, thread 2 access *numOfTickets*. For thread 2, *numOfTickets* is still its original value and has not be substracted yet. Hence *numOfTickets* is not substracted correctly.

In order to fix it, we should use **mutual exclusion**. A mutual exclusion (mutex) is a program object that prevents simultaneous access to a shared resource. Inside the critical section which is protected by mutex, the piece of code can only be accessed by one thread at the same time. To use mutual exclusion, we should include the mutex library:

```cpp
#include <mutex>
```

Outside the function, we define a global mutex *_mutex*. Then in *sellTicket()*, we use mutex to protect the piece of code where race condition may happen. In specific, we lock the mutex with *_mutex.lock()* before the subtraction operation, and unlock the mutex with *_mutex.unlock()* after *numOfTickets* is substracted by 1. Notice that the sleep operation do not need to be put inside the critical section for it is independent for each thread.

```cpp
mutex _mutex;

void sellTicket(int index) {
    while (numOfTickets > 0) {
        _mutex.lock();
        printf("Window %d sells ticket No. %d\n", index, numOfTickets);
      	numOfTickets--;
		_mutex.unlock();        this_thread::sleep_for(chrono::milliseconds(100));
    }
}
```

But there is still a bug here. We may find that Window 2 and Window 1 still sell the tickets even if there is no more ticket. This may happen when *numOfTickets* is still larger than 0 when thread 1 and thread 2 enter the while loop, but is subtracted into 0 by thread 0 inside the critical section. After thread 1 and thread 2 enter the critical section, they still substract it though they should not.

```
...
Window 2 sells ticket No. 10
Window 0 sells ticket No. 9
Window 1 sells ticket No. 8
Window 0 sells ticket No. 7
Window 2 sells ticket No. 6
Window 1 sells ticket No. 5
Window 1 sells ticket No. 4
Window 2 sells ticket No. 3
Window 0 sells ticket No. 2
Window 0 sells ticket No. 1
Window 2 sells ticket No. 0
Window 1 sells ticket No. -1
```

After analyzing the cause, we can simply fix it by adding another if condition inside the mutex:

```cpp
mutex _mutex;

void sellTicket(int index) {
    while (numOfTickets > 0) {
        _mutex.lock();
        if (numOfTickets > 0) {
        	printf("Window %d sells ticket No. %d\n", index, numOfTickets);
        	numOfTickets--;
        }
		_mutex.unlock();        this_thread::sleep_for(chrono::milliseconds(100));
    }
}
```

This time we get a correct result:

```
...
Window 0 sells ticket No. 10
Window 1 sells ticket No. 9
Window 2 sells ticket No. 8
Window 2 sells ticket No. 7
Window 0 sells ticket No. 6
Window 1 sells ticket No. 5
Window 1 sells ticket No. 4
Window 0 sells ticket No. 3
Window 2 sells ticket No. 2
Window 0 sells ticket No. 1
```

Though it is correct in this example, there is still a potential problem: in some cases, if the function returns inside the critical section, the mutex will not be unlocked properly. This means that other thread can not acquire the mutex, and wait there forever. This problem is called a **dead lock**.

From other perspectives, a mutex lock is also a resource similar to the memory resource on the heap which should always be released when it is not used. If the memory is not deallocated properly, there will be a memory leak. Remember that we use smart pointers to deal with memory release automatically. For mutex lock, we also have corresponding management tools ***lock_guard*** and ***unique_lock***.

*lock_guard* is a class that encapsulates a lock. The object will be automatically destroyed when it is out of scope, and the lock is unlocked as well. We can create a *lock_guard* object which takes *_mutex* as an argument instead of use its *lock()* and *unlock()* methods explicitly. Notice that the life cycle of the object now is the while loop, but we don't want to punt the sleep operation inside the critical section. So what we do here is to add a pair of brackets `{}` where we want the scope to be.

```cpp
mutex _mutex;

void sellTicket(int index) {
  	while (numOfTickets > 0) {
    	{
      		lock_guard<mutex> lock(_mutex);
      		if (numOfTickets > 0) {
        		printf("Window %d sells ticket No. %d\n", index, numOfTickets);
        		numOfTickets--;
      		}
    	}
    	this_thread::sleep_for(chrono::milliseconds(100));
  	}
}
```

*lock_guard* is similar to *scoped_ptr*, where its copy constructor and operator `=` are disabled. Like *unique_ptr*, we also have *unique_lock* which provides copy constructor and operator `=` with Rvalue references. We can use *std::move()* to copy a *unique_lock* object explicitly. *unique_lock* is often used for thread communication, in which multiple threads may share a mutex lock.