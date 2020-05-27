# Producer-Consumer Problem

In multithreaded programs, the execution order of threads is uncertain. In many situations, the execution of one thread relies on the execution of other threads. **Producer-Consumer** pattern is a type of synchronization between threads. Where some of the threads serve as producers which produce resources, and the others are consumers which consumes theses resources.

Here we have two threads. One is the producer and the other is the consumer. In addition, we have a queue which stores the resources. The producer puts resources inside the queue, and the consumer gets resources from the queue.

```cpp
int main() {
    Queue q;
    thread t1(producer, &q);
    thread t2(consumer, &q);
    t1.join();
    t2.join();
    return 0;
}
```

The queue here is shared by both thread, but *std::queue* in STL is not thread-safe, so we need to encapsulate it with mutual exclusion:

```cpp
mutex _mutex;

class Queue {
public:
    void put(int val) {
        lock_guard<mutex> lock(_mutex);
        q.push(val);
        printf("Producer produces %d\n", val);
    }
    
    int get() {
        lock_guard<mutex> lock(_mutex);
        int val = q.front();
        q.pop();
        printf("Consumer consumes %d\n", val);
        return val;
    }
private:
    queue<int> q;
};
```

Here is our function *producer()* and *consumer()*. The former puts elements into the queue, and the latter gets elements from the queue. Each operation takes 100 milliseconds.

```cpp
void producer(Queue *q) {
    for (int i = 1; i <= 10; i++) {
    	q->put(i);
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void consumer(Queue *q) {
    for (int i = 1; i <= 10; i++) {
    	q->get();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}
```

Now taking a look at the output. Some of the output seem correct, but sometimes the consumer consumes a wrong element. It happens when the consumer takes an element from an empty queue before the producer put any inside it.

```
Producer produces 1
Consumer consumes 1
Consumer consumes 15663296
Producer produces 2
Producer produces 3
Consumer consumes 3
Consumer consumes 1867799607
Producer produces 4
Producer produces 5
Consumer consumes 5
Producer produces 6
Consumer consumes 6
Consumer consumes 1598374991
Producer produces 7
Producer produces 8
Consumer consumes 8
Producer produces 9
Consumer consumes 9
Producer produces 10
Consumer consumes 10
```

To fix it, we want to ensure that consumers can only consume after producers have produced. More specifically, every time the producer produces one element, it informs the consumer to consume it. After the consumer consumes the element, it informs the producer to go on.

To achieve this, we can modify our code in such way. Every time *put()* is called by a producer, it first check if the queue is empty. If there are still remaining elements in the queue, it informs the consumer to consume. But now the producer still owns the mutex, so it should hands over the mutex, and wait for the consumer. Similarly, every time *get()* is called by a consumer, it first check if the queue is empty. If there is no element in the queue, it informs the producer to produce one. Moreover, the consumer should hand over the mutex and wait for the producer as well.

```cpp
class Queue {
public:
    void put(int val) {
        lock_guard<mutex> lock(_mutex);
        if (!q.empty()) {
        	// Inform consumers to consume
        	// Release mutex and wait for signal
    	}
        q.push(val);
        printf("Producer produces %d\n", val);
    }
    
    int get() {
        lock_guard<mutex> lock(_mutex);
        if (q.empty()) {
            // Inform producers to produce
            // Release mutex and wait for signal
        }
        int val = q.front();
        q.pop();
        printf("Consumer consumes %d\n", val);
        return val;
    }
private:
    queue<int> q;
};
```

There are some options to achieve thread communication, but the most convenient way here is to use **condition variables**. Condition variables are synchronization primitives that enable threads to wait until a particular condition occurs. We can include the condition_variable library to use them.

```cpp
#include <condition_variable>
```

Here we defined a global condition variable *cv*. When a producer checks the queue and finds it not empty, we call the *wait()* method to release the mutex and begin to wait. *wait()* needs the current mutex as its parameter. Remember that *lock_guard* can not be copied, so we change it into a *unique_lock* here so it can be passed into a function. Moreover, to make sure the thread keeps waiting, we should change `if` into `while`. After the producer produces an element, it needs to tell the consumer to consume it. The *notify_all()* method is used here to send signals to all waiting threads and wake them up. Then those threads compete for the ownership of mutex, and continue to execute after they own the mutex. The *get()* method for consumers have a similar design.

```cpp
mutex _mutex;
condition_variable cv;

class Queue {
public:
    void put(int val) {
        unique_lock<mutex> lock(_mutex);
        while (!q.empty()) {
            cv.wait(lock);
    	}
        q.push(val);
        cv.notify_all();
        printf("Producer produces %d\n", val);
    }
    
    int get() {
        unique_lock<mutex> lock(_mutex);
        while (q.empty()) {
            cv.wait(lock);
    	}
        int val = q.front();
        q.pop();
        cv.notify_all();
        printf("Consumer consumes %d\n", val);
        return val;
    }
private:
    queue<int> q;
};
```

Now we get a correct output. The producer produces elements and the consumer produces elements, one by one.

```
Producer produces 1
Consumer consumes 1
Producer produces 2
Consumer consumes 2
Producer produces 3
Consumer consumes 3
Producer produces 4
Consumer consumes 4
Producer produces 5
Consumer consumes 5
Producer produces 6
Consumer consumes 6
Producer produces 7
Consumer consumes 7
Producer produces 8
Consumer consumes 8
Producer produces 9
Consumer consumes 9
Producer produces 10
Consumer consumes 10
```

You may feel confused why we should use `while` instead of `if` here, since *wait()* always blocks the current thread. Indeed, `if` works correctly if there are only one producer and one consumer. But problems may happen if there are multiple producers and consumers. Assume we have two consumers instead of one. Consumer 1 first gets the mutex, and finds the queue empty. Therefore, it hands over the mutex and keeps waiting. Then consumer 2 gets the mutex. Same as before, there is no element in the queue, so consumer 2 hands over the mutex and keeps waiting. Then the producer gets the mutex, produces one element, wakes up all the consumers and hands over the mutex. Consumer 1 gets the mutex, consumes one element and hands it over. Then consumer 2 gets the mutex. If we are using `if` here, consumer 2 will jump out of the judgement and gets one element from the queue. However, since the only element has been taken away by consumer 1, the queue is empty now! Therefore, `while` should be used here instead. After consumer 2 gets the mutex, it still finds the queue empty and will go on waiting.

Multithreading programs are hard to debug, since most thread problems appear randomly and even difficult to reproduce. Therefore, good programming habits should be developed. The previous example shows that thread waiting should always be called inside a loop.