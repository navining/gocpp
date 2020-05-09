# Various Member Functions

We already know the properties of member functions. Member functions belong to the object of a class, and can only be called by that object.

Now back to our *Goods* class, we want to count the total amount of goods in a grocery. How can we do that? We need a variable which belongs to the class instead of its objects. This kind of variable is called a **static member variable**.

```cpp
class Goods {
	...
private:
      char _name[20];
      double _price;
      int _amount;
      Date _date;
      static int _count;
}

int Goods::_count = 0;

Goods::Goods(const char *name, double price, int amount, int y, int m, int d)
    : _date(y, m, d), _price(price), _amount(amount) {
  strcpy(_name, name);
  _count++;
}
```

A static member variable is declared inside the class with keyword `static`, and has to be defined outside the scope of the class, which is similar to a static variable. A static member variable doesn't belong to any objects. Instead, it belongs to the class. Since the variable is private, we need another public method to access it. Also, we want this function to be managed by the class itself instead of any instances. This kind of function is a **static member function**.

## Static Member Function

We can define our static member function *showCounts()* like this.

```cpp
static void Goods::showCounts() {
  cout << "Counts: " << _count << endl;
}
```

Then we can call this function directly inside our main function, without instantiating any objects. We need to add a scope qualifier before it.

```cpp
int main() {
    ...
	Goods::showCounts();
    return 0;
}
```

The main difference between a normal member function and a static one is that the normal method has a pointer **this* as the parameter (which is added by the compiler), and a static method doesn't. Therefore, we can not access any normal member variables because there's no actual object. We can only access static variables.

## Constant Member Function

Now look at this case. We create a constant object of class *Goods*, and call its *show()* method. But this raises an error.

```cpp
int main() {
    const Goods goods(...);
    goods.show()	// ERROR
}
```

It is because **this* pointer of *goods* has type *const Goods \**, but the parameters in *show()* has type *Goods \**, so it is invalid to convert a `const` pointer to a normal one.

To fix this, we can have a **constant member function** with keyword `const` after the function name.

```cpp
void Goods::show() const {
  cout << "name: " << _name << endl;
  cout << "price: " << _price << endl;
  cout << "amount: " << _amount << endl;
  _date.show();
};
```

Notice that *Goods::show()* calls *Date::show()*, sow *Date::show()* has to be modified with `const` as well.

```cpp
void show() const { 
    cout << _year << "/" << _month << "/" << _day << endl; 
}
```

Generally speaking, as long as the member function is read-only, we need to add the `const` qualifier, so that it can be called by both normal objects and constant objects.

## At Last

Now we understand three types of member functions.

**Member Function**

- Within the scope of class
- Called by an object

**Static Member Function**

- Within the scope of class
- Called with scope qualifier
- Can only access static member variables

**Constant Member Function**

- Within the scope of class
- Called by an object
- Read-only

Remember that the essential difference between them is the type of **this* pointer.