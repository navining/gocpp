# Understanding Polymorphism

We already know that polymorphism is a key feature of Object-Oriented Programming, but what exactly is polymorphism? Why polymorphism is important?

There are two kinds of polymorphism: **static polymorphism** and **dynamic polymorphism**. We have already learned function overloading and templates, which are two kinds of static polymorphism, for their status is determined under compilations. 

On the other hand, dynamic polymorphism refers to the polymorphism under runtime. It happens when we use a base class pointer to point to a derived class object, and call the member functions through the pointer. In this case, to which derived class object the pointer points to will its corresponding overridden method be called. The bottom layer of dynamic polymorphism is realized through dynamic binding.

To illustrate the necessity of polymorphism, let's look at the following example. Here we defined a base class *Animal*, which has a member variable *_name* and a member function *bark()*. Then we defined three derived classes *Cat*, *Dog* and *Bear* which inherit from *Animal*.

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

Now in the the main function, we defined three objects of *Cat*, *Dog* and *Bear* respectively. What's more, we want to provide an interface *bark()* to call the member function *bark()* of these animals. In this case, we have to defined three different functions which accept different types of objects as parameters. Apparently, this approach is redundant, and is not conductive to code modification and maintenance, for every time we defined a new class, we need to add a corresponding interface.

```cpp
void bark(Cat &cat) {
    cat.bark();
}

void bark(Dog &dog) {
    dog.bark();
}

void bark(Bear &bear) {
    bear.bark();
}

int main() {
    Cat cat("Kitty");
    Dog dog("Puppy");
    Bear bear("Winnie");
    bark(cat);
    bark(dog);
    bark(bear);
    return 0;
}
```

In OOP, a good software development principle is the **open-closed principle**, which states that *software entities (classes, modules, functions, etc.) should be open for extension, but closed for modification*. In polymorphism, open-closed principle refer to the use of abstracted interfaces, where the implementations can be changed and multiple implementations could be created and polymorphically substituted for each other. Therefore, we can rewrite our interface as:

```cpp
void bark(Animal *p) {
    p->bark();
}

int main() {
    Cat cat("Kitty");
    Dog dog("Puppy");
    Bear bear("Winnie");
    bark(&cat);
    bark(&dog);
    bark(&bear);
    return 0;
}
```

Now we can just pass the addresses of objects inside. With polymorphism, we simply use a *Animal* pointer to call the corresponding method of derived objects.