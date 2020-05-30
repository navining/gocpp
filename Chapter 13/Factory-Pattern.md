# Factory Pattern

The factory pattern is a creational pattern which encapsulates the construction of objects. In factory pattern, we do not expose the construction logic to the client directly. Instead, we provide a common interface to construct the objects.

Here we have a base class *Car*, and two classes *Bwm* and *Audi* that derive from *Car*:

```cpp
class Car {
public:
    Car(string name) : _name(name) {}
    virtual void show() = 0;
protected:
    string _name;
};

class Bmw : public Car {
public:
    Bmw(string name) : Car(name) {}
    void show() {
        cout << "BMW: " << _name << endl;
    }
};

class Audi : public Car {
public:
    Audi(string name) : Car(name) {}
    void show() {
        cout << "Audi: " << _name << endl;
    }
};
```

A native way to construct objects of those classes is to use `new`  to call their constructor directly, for example:

```cpp
int main() {
    Car *p1 = new Bmw("X1");
    Car *p2 = new Audi("A6");
    delete p1;
    delete p2;
    return 0;
}
```

In this way, the programmers must know the construction methods of these classes. It becomes inconvenient if there are a large amount of classes. Moreover, if the constructor has changed, all constructions of that class must be changed as well. Hence, a good OOP design is to provide a uniform interface for construction.

## Simple Factory

The simple factory pattern provides a factory class which has a uniform interface for construction. In the following example, we defined a *SimpleFactory* class which has a method *createCar()*. The method takes a enumeration as parameter, and returns the created object according to the corresponding car brand.

```cpp
enum CarType {BMW, AUDI};

class SimpleFactory {
public:
    Car* createCar(CarType ct) {
        switch (ct) {
        case BMW:
            return new Bmw("X1");
        case AUDI:
            return new Audi("A6");
        }
        return nullptr;
    }
};
```

Now we can simply defined a single factory class, and use *createCar()* to get objects of different car brands.

```cpp
int main() {
    SimpleFactory *factory = new SimpleFactory();
    Car *p1 = factory->createCar(BMW);
    Car *p2 = factory->createCar(AUDI);
    delete factory;
    delete p1;
    delete p2;
    return 0;
}
```

The simple factory pattern use a single factory class to produce all the products. It is simple, but it doesn't meet the open-close principle. If we want to add new products to the factory, we need to always modify the interface, which is not a good software design. 

## Factory Method

In factory method pattern, a factory is responsible for one product. Here we have a base class *Factory* which has a pure virtual function *createCar()*. Then we have two derived class which have their own version of interface for constructing objects.

```cpp
class Factory {
public:
    virtual Car* createCar(string name) = 0;
};

class BMWFactory : public Factory {
public:
    Car* createCar(string name) {
        return new Bmw(name);
    }
};

class AudiFactory : public Factory {
public:
    Car* createCar(string name) {
        return new Audi(name);
    }
};
```

In this way, we can use the interface provided by different factories to create the corresponding objects:

```cpp
int main() {
    Factory *bmwfactory = new BMWFactory();
    Factory *audifactory = new AudiFactory();
    Car *p1 = bmwfactory->createCar("X6");
    Car *p2 = audifactory->createCar("A8");
    delete bwmfactory;
    delete audifactory;
    delete p1;
    delete p2;
}
```

If a new brand of car is added, we can define a new factory class which inherits from *Factory*, and provide its own *createCar()* interface.

