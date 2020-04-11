# Class and Object

OOP (Object-Oriented Programming) is almost the most important programming paradigm nowadays. The following code is a class *Goods* which represents goods from a grocery.

```cpp
class Goods {
public:	// Methods
	// Initialize goods information
	void init(const char *name, double price, int amount);
	// Print goods information
	void show();
	// Getters
   	void setName(const char *name) {strcpy(_name, name);}
    void setPrice(double price)	{_price = price;};
    void setAmount(int amount) {_amount = amount;};
    // Setters
    const char* getName() {return _name;};
    double getPrice() {return _price;};
    int getAmount() {return _amount;};
private:	// Variables
	char _name[20];
    double _price;
    int _amount;
};
```

Class is an abstract blueprint of an entity. An entity has its attributes and behaviors, and a class is a composition of member variables and member methods. With a class as an abstract, we can instantiate objects. These objects all follows a similar pattern, with same types of attributes and behaviors. 

Object-oriented programming has four basic features: abstract, encapsulation, inherence and Polymorphism. Access qualifiers enables the encapsulation of a class. There are three types of access qualifiers: `public`, `private` and `protected`. Generally, member variables are declared a private, and public methods a provided to access them, known as Getters and Setters. These methods are usually defined inside the class, and is compiled as inline functions.

When declaring methods outside the class, we need to add scope before the function name.

```cpp
void Goods::init(const char *name, double price, int amount) {
    strcpy(_name, name);
    _price = price;
    _amount = amount;
}

void Goods::show() {
    cout << "name: " << _name << endl;
    cout << "price: " << _price << endl;
    cout << "amount: " << _amount << endl;
}
```

A number of objects can be defined with a class. Each object has their own member variables, but the member methods are shared among them. Then how does the methods know which one should be dealt with? In fact while compiling, a pointer **this* which refers to the object itself is added into the parameter list of member methods, and when the methods are called, the memory address of the object is passed as argument.

```cpp
int main() {
	Goods good;
	good.init("Bread", 10.0, 200);	// init(&good, "Bread", 10.0, 200);
	good.show();	// good.show(&good);
}
```

What is the size of our Goods class? Notice that the memory size of an object is only related to its member variables. The class above has an *char* array with length 20, a *double* and an *int*, so the size of this class is 32. 

But that's not correct! The actual size of Goods is 40. Why's that?  It is because of the memory alignment mechanism in memory allocation. The size of each variable should be aligned to the largest type size in all variables. In this case the largest type is *double*, which occupies 8 bytes. So all variables should be a multiple of 8. Then the *char* array is aligned to 24 bytes, and the *int* variable is aligned to 8 bytes.

> There are other factors that change the size of a class, we will cover those later.