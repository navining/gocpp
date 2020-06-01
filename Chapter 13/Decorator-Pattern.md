# Decorator Pattern

The decorator pattern enables us to add new functionality to an existing class, without changing its structure. Similar to proxy pattern, the decorator pattern is also a structural pattern, where the decorator class acts as a wrapper for the existing class.

Generally, inheritance is also used to extend the functionality of a class. But as the extended functionality increases, the number of derived classes will expand as well. Therefore, the decorator pattern is more flexible.

Let's look at the following example, where we have an abstract class *Car* and three brands of cars that implement it and override *show()* method.

```cpp
class Car {
public:
    virtual void show() = 0;
};

class Bmw : public Car {
public:
    void show() {
        cout << "This is a BMW" << endl;
    }
};

class Audi : public Car {
public:
    void show() {
        cout << "This is an Audi" << endl;
    }
};

class Benz : public Car {
public:
    void show() {
        cout << "This is a Benz" << endl;
    }
};
```

Now suppose we want to add new features to these cars. Instead of using inheritance, we can define a decorator class instead. Here we have a class *CarDecorator1* which inherits *Car*. The class has a *Car* object as its member. The class overrides *show()*, and besides calling the *show()* method of the *Car* object, it implements its own functionality here. This pattern is similar to the proxy pattern, but it actively takes a *Car* object as a parameter in its constructor. We can also write *CarDecorator2* and *CarDecorator3* which implements other features in a similar way.

```cpp
class CarDecorator1 : public Car {
public:
    CarDecorator1(Car *p) : pCar(p) {}
    ~CarDecorator1() {
        delete pCar;
    }
    void show() {
        pCar->show();
        cout << "Feature 1" << endl;
    }
private:
    Car *pCar;
};
```

To use the decorator, we create a decorator object, and pass in the *Car* object to be decorated. In this way, different brand of cars can have different features without modifying the original class.

```cpp
int main() {
    Car *p1 = new CarDecorator1(new Bmw());
    Car *p2 = new CarDecorator2(new Audi());
    Car *p3 = new CarDecorator3(new Benz());
    p1->show();
    p2->show();
    p3->show();
    delete p1;
    delete p2;
    delete p3;
    return 0;
}
```

The above code has the following output:

```
This is a Bwm
Feature 1
This is an Audi
Feature 2
This is a Benz
Feature 3
```

Moreover, a single object can also have multiple features: just use the decorator in a nested way by keep passing the same pointer inside:

```cpp
int main() {
    Car *p1 = new CarDecorator1(new Bmw());
    p1 = new CarDecorator2(p1);
    p1 = new CarDecorator3(p1);
    p1->show();
    delete p1;
    return 0;
}
```

The above code has the following output:

```cpp
This is a Bwm
Feature 1
Feature 2
Feature 3
```

