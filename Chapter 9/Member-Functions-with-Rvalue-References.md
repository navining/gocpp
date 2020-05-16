# Member Functions with Rvalue References

In Chapter 5, we have implemented a class *MyString* that represents a string, in which its copy constructor and operator `=` is defined as

```cpp
MyString::MyString(const MyString &other) {
  _pstr = new char[strlen(other._pstr) + 1];
  strcpy(_pstr, other._pstr);
}

MyString::MyString &operator=(const MyString &other) {
  if (this == &other) return *this;
  delete[] _pstr;
  _pstr = new char[strlen(other._pstr) + 1];
  strcpy(_pstr, other._pstr);
  return *this;
}
```

The former allocates memory for the new string, and copies the data from the old one. The latter first deletes the old string, and then does the copy.

Now suppose we have an interface *getString()* which takes a *MyString* object, does some modification and returns a new object. And in the main function, we pass *s1* inside, and use *s2* to receive the return object. 

```cpp
MyString getString(MyString &str) {
    const char* pstr = str.c_str();
    myString tmp(pstr);
    // Do something 
    return tmp;
}

int main() {
    MyString s1 = "aaa";
    MyString s2 = "bbb";
    s2 = getString(s1);
    return 0;
}
```

From the last chapter we've already known that three principles of optimizing objects should be applied. However in some circumstances, we cannot either returns a temporary object or receive the returned object by initialization, for example here. In this case, a temporary object has to be constructed on the heap of *main()* and be assigned to *s2*. What our copy constructor and operator `=` do here is to allocate new memory space, and copy the data from the temporary object. But since temporary object is destroyed immediately after then, it is an unnecessary overhead of memory. Why don't we just modify the pointer of the new object, and let it point to the temporary object's data? Fortunately, C++ 11 introduced **Rvalue references** to deal with these circumstances.

First let's review what is a Rvalue. We already know that a Lvalue has a specific name or a memory address, for example variables and objects. Rvalues are those without a name or memory address, for example, constants and temporary objects. We can only use a constant reference or a Rvalue reference to refer to a Rvalue:

```cpp
int main() {
    const int &a = 20;
    int &&b = 20;
    int &&c = MyString("aaa");
}
```

Knowing this, we can add a new copy constructor which takes a Rvalue reference as the parameter. Inside the copy constructor, we only need to let the new pointer point to the data of the temporary object. After then, we set its pointer to NULL, so that the destructor does nothing.

```cpp
MyString(MyString &&other) {
	_pstr = other._ptr;
	other._pstr = nullptr;
}
```

operator `=` with Rvalue reference can be added in a similar way:

```cpp
MyString &operator=(MyString &&other) {
	if (this == &other) return *this;
	delete[] mptr;
	_pstr = other._pstr;
	other._pstr = null;
	return *this;
}
```

Now when the copy constructor or operator `=` is called on a temporary object, only the pointers are changed. No extra memory allocation or deallocation is needed, which increases memory efficiency. Member functions with Rvalue references are widely used in STL containers to improve performance.
