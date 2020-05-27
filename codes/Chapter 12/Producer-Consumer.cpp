#include <stdio.h>

#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
using namespace std;

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

int main() {
  Queue q;
  thread t1(producer, &q);
  thread t2(consumer, &q);
  t1.join();
  t2.join();
  return 0;
}