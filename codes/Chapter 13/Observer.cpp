#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

class Observer {
 public:
  virtual void handle(int id) = 0;
};

class Observer1 : public Observer {
 public:
  void handle(int id) {
    switch (id) {
      case 1:
        cout << "Observer1: Message 1" << endl;
        break;
      case 2:
        cout << "Observer1: Message 2" << endl;
        break;
      default:
        cout << "Observer1: Unknown message" << endl;
        break;
    }
  }
};

class Observer2 : public Observer {
 public:
  void handle(int id) {
    switch (id) {
      case 2:
        cout << "Observer2: Message 2" << endl;
        break;
      case 3:
        cout << "Observer2: Message 3" << endl;
        break;
      default:
        cout << "Observer2: Unknown message" << endl;
        break;
    }
  }
};

class Observer3 : public Observer {
 public:
  void handle(int id) {
    switch (id) {
      case 1:
        cout << "Observer3: Message 1" << endl;
        break;
      case 3:
        cout << "Observer3: Message 3" << endl;
        break;
      default:
        cout << "Observer3: Unknown message" << endl;
        break;
    }
  }
};

class Subject {
 public:
  void subscribe(Observer *observer, int id) { _map[id].push_back(observer); }
  void publish(int id) {
    auto it = _map.find(id);
    if (it != _map.end()) {
      for (Observer *p : it->second) {
        p->handle(id);
      }
    }
  }

 private:
  unordered_map<int, list<Observer *>> _map;
};