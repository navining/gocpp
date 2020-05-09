# References in Detail

## References and Pointers

A variable can be declared as reference with an *&* in the declaration. When a variable is declared as reference, it is an alias of an existing variable. Alias means that a variable and its reference can be regarded as the same thing.

```cpp
int main() {
    int a = 10;
    int *p = &a;
    int &b = a;
    cout << b << endl;	// 10
    return 0;
}
```

Declaring a pointer variable and a reference variable has the same underlying instructions. Both two approaches get the memory address of the existing variable and stores into the declared variable. Similarly, the assembly commands for modifying the value of a memory address through reference or through pointer dereference, are also the same.

```cpp
*p = 20;
cout << a << " " << *p << " " << b << endl;	// 20 20 20
b = 30;
cout << a << " " << *p << " " << b << endl;	// 30 30 30
```

Unlike pointer which can be declared without initialization or as a *nullptr*, a reference variable must be initialized with an existing variable when it is declared. In this way, a reference is safer than a pointer since it can't be NULL.

```cpp
int &q;	// ERROR
```

Besides, these is no multi-level references as pointer does.

Reference plays an important role, especially as function parameters. In the following case, we write a *swap* function which takes two arguments and swap them. We can make this in using pointers as parameters and pass addresses of arguments inside, but reference makes it in a easier way.

```cpp
int swap(int &x, int &y) {
    int temp = x;
    x = y;
    y = temp;
}

int main() {
    int a = 10;
    int b = 20;
    swap(a, b);
    cout << "a: " << a << "b: " << b << endl;
}
```

The way we declare reference to an array in kind tricky. We need to add brackets outside the reference variable, which states the priority, and then states the array size with square brackets. It is similar to declaring an array instead of declaring a pointer, since reference is the alias of another variable.

```cpp
int main() {
    int array[5] = {};
    int *p = array;
    int (&q)[5] = array; 
    
    cout << sizeof(array) << endl;	// 20
    cout << sizeof(p) << endl;	// 4
    cout << sizeof(q) << endl;	// 20
	return 0;
}
```

In the above case, the pointer has a size of 4 bytes, and reference has a size of 20 bytes, which is the same as the original array.

## Rvalue References

All the cases we've seen now is references of Lvalues. A Lvalue is a type of value that can appears at the left of operator `=`. It has a variable name and a memory address that can be modified. On the contrary, a Rvalue doesn't have a variable name nor a memory address. It can only appears at the right of operator `=`. We cannot declare a normal reference of a Rvalue.

```cpp
int main() {
    int a = 10;	// a is a Lvalue
    int &b = a;
    int &c = 20;	// ERROR: 20 a Rvalue
    return 0;
}
```

C++11 introduced many features, one of them is Rvalue references. With two *&* symbols, we can declare a reference of a constant. 

```cpp
int &&c = 20;
```

But how can we make a reference to a Rvalue since it doesn't have a memory address? The assembly commands shows the magic. When declaring a Rvalue reference, the compiler creates a temporary variable to store the value of the constant, and then assign the address of that temporary variable to the reference variable.

```assembly
mov	dword ptr [ebp-30h],14h
lea	eax,[ebp-30h]
mov dword ptr [c],eax
```

Alternatively, we can use `const` to declare a Rvalue reference as well.

```cpp
const int &c = 20;
```

Notice that a Rvalue reference is a Lvalue itself, which means that only Lvalue references can be used to refer to it.

```cpp
int &d = c;
int &&e = c;	// ERROR
```

## `const`, Pointers and References

Now let's take a look at the following code. Is this code able to be complied or not?

```cpp
int main() {
    int a = 10;
    int *p = &a;
    const int *&q = p;
    return 0;
}
```

It seems confusing, but we can convert the reference to a pointer to make it clearer. Notice that `int &a = b` has the same function as `int *p = &b`, so the code above can be converted into follows:

```cpp
int a = 10;
int *p = &a;
const int **q = &p;	// ERROR
```

Now the problem is clear since we already discuss about `const` and double pointers. The code above actually convert a type of *int \*\** into *const int \*\**, which is invalid.

> See the post "`const` and Pointers" if you forget it.







