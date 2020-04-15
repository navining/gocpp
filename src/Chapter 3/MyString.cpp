#include <string.h>

class MyString {
 public:
  MyString(const char *str = nullptr) {
    if (str != nullptr) {
      m_data = new char[strlen(str) + 1];
      strcpy(this->m_data, str);
    } else {
      m_data = new char[1];
      *m_data = '\0';
    }
  }

  MyString(const MyString &other) {
    m_data = new char[strlen(other.m_data) + 1];
    strcpy(m_data, other.m_data);
  }

  ~MyString() {
    delete[] m_data;
    m_data = nullptr;
  }

  MyString &operator=(const MyString &other) {
    if (this == &other) return *this;

    delete[] m_data;
    m_data = new char[strlen(other.m_data) + 1];
    strcpy(m_data, other.m_data);

    return *this;
  }

 private:
  char *m_data;
};