# Observer Pattern

The observer pattern belongs to the behavior pattern, which focuses on the communication between objects. The observer pattern applies to a one-to-many relationship of objects, where multiple objects rely on a single object. When the state of the object changes, other objects can receive corresponding notifications.

A common observer pattern is the publish-subscribe model, where the observers subscribe to a subject, and the subject publishes notification to the observers when its status changes.

Here we have an abstract class *Observer*, and three classes that inherit from it. These classes override the *handle()* method which handles messages according to their IDs. *Observer1* handles message 1 and 2, while *Observer2* handles message 2 and 3, and *Observer3* handles message *1* and *3*.

```cpp
class Observer {
public:
    virtual void handle(int id) = 0;
};

class Observer1 : public Observer {
public:
    void handle(int id) {
        switch (id) {
            case 1:
                cout << "Message 1" << endl;
                break;
            case 2:
                cout << "Message 2" << endl;
            	break;
            default:
                cout << "Unknown message" << endl;
                break;
        }
    }
};

class Observer2 : public Observer {
public:
    void handle(int id) {
        switch (id) {
            case 2:
                cout << "Message 2" << endl;
                break;
            case 3:
                cout << "Message 3" << endl;
            	break;
            default:
                cout << "Unknown message" << endl;
                break;
        }
    }
};

class Observer3 : public Observer {
public:
    void handle(int id) {
        switch (id) {
            case 1:
                cout << "Message 1" << endl;
                break;
            case 3:
                cout << "Message 3" << endl;
            	break;
            default:
                cout << "Unknown message" << endl;
                break;
        }
    }
};
```

Then we have the *Subject* class which keeps an unordered map. The map keys are message IDs, and the values are lists of observers. The class has two methods *subscribe()* and *publish()*. The former takes an *Observer* and the message ID to be subscribed, and add the observer to the map with message ID as the key. *publish()* takes the message ID to be published, takes out the observers from the map who have subscribed to this message, and call their *handle()* method one by one.

```cpp
class Subject {
public:
    void subscribe(Observer *observer, int id) {
        _map[id].push_back(observer);
    }
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
```

Now in the *main()* function, we subscribes the observers to the messages they would like to handle. When the status of the subject changes, it notify the observers by publishing the corresponding messages.

```cpp
int main() {
  Subject subject;
  Observer *p1 = new Observer1();
  Observer *p2 = new Observer2();
  Observer *p3 = new Observer3();

  subject.subscribe(p1, 1);
  subject.subscribe(p1, 2);
  subject.subscribe(p2, 2);
  subject.subscribe(p2, 3);
  subject.subscribe(p3, 1);
  subject.subscribe(p3, 3);

  subject.publish(1);
  cout << "--------------------" << endl;
  subject.publish(2);
  cout << "--------------------" << endl;
  subject.publish(3);
  cout << "--------------------" << endl;
  subject.publish(4);
  delete p1, p2, p3;
}
```

The above code has the following outputs:

```
Observer1: Message 1
Observer3: Message 1
--------------------
Observer1: Message 2
Observer2: Message 2
--------------------
Observer2: Message 3
Observer3: Message 3
--------------------
```

