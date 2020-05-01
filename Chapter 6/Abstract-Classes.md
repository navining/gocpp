# Abstract Classes

Let's take another look at what we wrote earlier:

```cpp
class Animal {
public:
    Animal(string name) : _name(name) {}
    virtual void bark() {}
protected:
    string _name;
};

class Cat : public Animal {
public:
    Cat(string name) : Animal(name) {}
    void bark() {
        cout << _name << "Meow!" << endl;
    }
};

class Dog : public Animal {
public:
    Dog(string name) : Animal(name) {}
    void bark() {
        cout << _name << "Woof!" << endl;
    }
};

class Bear : public Animal {
public:
    Bear(string name) : Animal(name) {}
    void bark() {
        cout << _name << "Rua!" << endl;
    }
};
```

Remember that the original intention of defining class *Animal* is not to make *Animal* an abstract of some entities, but to:

1. Let all derived classes inherit the member variables of *Animal* to reuse its properties.
2. Keep a unified interface for all derived classes to override it to achieve polymorphism.

Hence, we can defined *Animal* as an **abstract class**:

```cpp
class Animal {
public:
    Animal(string name) : _name(name) {}
    virtual void bark() = 0;
protected:
    string _name;
};
```

Here we declared a virtual function *bark()*, but assign its address to 0. In this case, *bark()* is a **pure virtual function**. A class with pure virtual functions is called an abstract class. An abstract class can not be instantiated, but can have pointers and references:

``` cpp
int main() {
    Animal a;	// No
    Animal *pa;	// Yes
    return 0;
}
```

Let's look at another example. Here we defined an abstract class *Car*, and has a method which returns remaining miles under the current fuel level.

```cpp
class Car {
public:
    Car(string name, double oil) : _name(name), _oil(oil) {}
    double getLeftMiles(double oil) {
        return oil * getMilesPerGallon();
    }
protected:
    string _name;
    double _oil;
    virtual double getMilesPerGallon() = 0;
};
```

Then we defined three cars of different brands, with different mileages per gallon.

```cpp
class Benz : public Car {
public:
    Benz(string name, double oil) : Car(name, oil) {}
    double getMilesPerGallon() {return 20.0;}
};

class Audi : public Car {
public:
    Audi(string name, double oil) : Car(name, oil) {}
    double getMilesPerGallon() {return 18.0;}
};

class BMW : public Car {
public:
    BMW(string name, double oil) : Car(name, oil) {}
    double getMilesPerGallon() {return 19.0;}
};
```

Moreover, we provide an interface to get the remaining miles of the car, and passes in different objects:

```cpp
double showCarLeftMiles(Car &car) {
    cout << car.getName() << " " << car.getLeftMiles() << endl;
}

int main() {
    Benz a("Benz", 20.0);
    Audi b("Audi", 20.0);
    BMW c("BWM", 20.0);
    showCarLeftMiles(a);	// Benz 400
    showCarLeftMiles(b);	// Audi 360
    showCarLeftMiles(c);	// BMW 380
    return 0;
}
```

Now in *showCarLeftMiles()*, the parameter is a *Car* object instead of a pointer, isn't it a static binding? How can we achieve polymorphism? Of course it is a static binding here, but notice that in *Car::getLeftMiles()*, the virtual function *getMilesPerGallon()* is called with *this->getMilesPerGallon()*. Since **this* is a *Car* pointer, it is still a dynamic binding, so the corresponding method of different objects is called.

