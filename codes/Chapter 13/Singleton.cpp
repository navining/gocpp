#include <mutex>
using namespace std;

class Singleton1 {
 public:
  static Singleton1* getInstance() { return &instance; }

 private:
  static Singleton1 instance;
  Singleton1() {}
  Singleton1(const Singleton1&) = delete;
  Singleton1& operator=(const Singleton1&) = delete;
};
Singleton1 Singleton1::instance;

mutex _mutex;
class Singleton2 {
 public:
  static Singleton2* getInstance() {
    if (instance == nullptr) {
      lock_guard<mutex> lock(_mutex);
      if (instance == nullptr) instance = new Singleton2();
    }
    return instance;
  }

 private:
  static Singleton2* volatile instance;
  Singleton2() {}
  Singleton2(const Singleton2&) = delete;
  Singleton2& operator=(const Singleton2&) = delete;
};
Singleton2* volatile Singleton2::instance = nullptr;

class Singleton3 {
 public:
  static Singleton3* getInstance() {
    static Singleton3 instance;
    return &instance;
  }

 private:
  Singleton3() {}
  Singleton3(const Singleton3&) = delete;
  Singleton3& operator=(const Singleton3&) = delete;
};