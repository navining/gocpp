# Multithreaded Programming with *std::thread*

*std::thread* is a class that encapsulates multithreading APIs of the operating system. Different operating systems has different API functions. For example, *createThread()* is used to create a thread in Windows, while *pthread_create()* is used instead in Linux. With *std::thread*, programmers can write multithreaded programs more easily. To use *std::thread*, we should include the thread library:

```cpp
#include <thread>
```

We can start a thread by creating a *thread* object with the thread function. In the following example, we create a thread *t* which executes function *threadHander()*. The thread starts to execute after it is created.

***join()*** blocks the current thread, and wait for the child thread to terminate. The current thread continues to run only after the child thread has been terminated.

```cpp
void threadHandler() {
    cout << "Hello World!" << endl;
}

int main() {
    thread t(threadHandler);
    t.join();
    cout << "Thread Done!" << endl;
    return 0;
}
```

The above example has the following output:

```
Hello World!
Thread Done!
```

We can also pass arguments into the thread function. In the following example, we have a thread function which sleeps the thread for several seconds. We use *this_thread::sleep_for()* for sleeping and *chrono::seconds()* for the number of seconds.

```cpp
void threadHandler(int sec) {
    this_thread::sleep_for(chrono::seconds(sec));
    cout << "Hello World!" << endl;
}

int main() {
    thread t(threadHandler, 2);
    t.join();
    cout << "Thread Done!" << endl;
    return 0;
}
```

So far we use *join()* to make the main thread wait for the child thread to terminate. But what if we don't do this? When the main thread finishes its running, it will check if there are child threads which have not finished yet. If so, the process will terminate abnormally.

```cpp
int main() {
    thread t(threadHandler, 2);
    // t.join();
    cout << "Thread Done!" << endl;
    return 0;	// ERROR
}
```

If we don't want the main thread to wait for the child thread, we can use ***detach()***. *detach()* will separate the child thread with the main thread. After the process terminates, all the unfinished threads will be terminated as well.

```cpp
int main() {
    thread t(threadHandler, 2);
    t.detach();
    cout << "Thread Done!" << endl;
    return 0;
}
```

In all, *join()* ensures that the main thread can not terminate before the child thread is terminated, while *detach()* does not. We should always remember to use either *join()* or *detach()* after a thread is created.