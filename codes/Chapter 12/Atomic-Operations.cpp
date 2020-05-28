#include <atomic>
#include <iostream>
#include <list>
#include <thread>
using namespace std;

volatile atomic_bool isReady;
volatile atomic_int myCount;

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
  cout << myCount << endl;
  return 0;
}