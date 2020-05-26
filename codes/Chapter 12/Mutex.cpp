#include <stdio.h>

#include <list>
#include <mutex>
#include <thread>
using namespace std;

int numOfTickets = 100;
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