# ```const``` and Pointers

`const` is a keyword widely used in C and C++. Variable modified by`const` cannot be a Lvalue of operator `=`, which means it can not be modified after it is initialized.

```cpp
int main() {
    int a = 10;
    a = 20;
    const int b = 20;
    b = 30;	// ERROR
    return 0;
}
```

## `const` in C and C++

In C, the variable modified by `const` is called a constant variable, which means it is still a variable, not a constant. For example, it is invalid to declared array size with a `const int` variable.

```c
void main() {
    const int a = 20;
    int array[a] = {};	// ERROR
}
```

Therefore, the only difference with a `const` is that it can not be appended to an assignment expression. However, its memory can be modified.

```c
void main() {
    const int a = 20;
    int *p = (int*)&a;
    *p = 30;
    printf("%d %d %d", a, *p, *(&a));	// 30 30 30
}
```

In C++, the variable modified by `const` is regarded as a real constant, and has the same nature with a constant, for example can be used to initialize an array. Actually, all occurrences of `const` variables are replaced by the initial value of it in the compiling process. So the same code has different result in C++.

```cpp
int main() {
    const int a = 20;
    int *p = (int*)&a;
    *p = 30;
    printf("%d %d %d", a, *p, *(&a));	// 20 30 20
}
```

Notice that **p* does change the memory of *a* at runtime in this case, but *a* has been replaced at compile time, so this change has no effect.

If we initialize a `const` variable with a normal variable instead of ab immediate value, then the `const` variable acts as a constant variable, and no longer has the nature of constants.

```cpp
int b = 20;
const int a = b;
int array[a] = {};	// ERROR
```

## `const` and Pointers

`const` keyword ensures two things. The first one, which we have already known, is that a `const` variable cannot be a Lvalue, which means it cannot be modified directly. Besides, `const` also makes sure that the constant can not be modified indirectly, which means the memory address of a constant can not be exposed to a normal pointer nor reference.

```cpp
int main() {
    const int a = 10;
    int *p = &a;	// ERROR
    return 0;
}
```

In order to fix this, we should also modified the pointer with `const`, telling the compiler that what the pointer points to can not be modified indirectly with dereference as well. But there are various ways in adding `const` to a pointer:

```cpp
const int *p = &a;	// 1
int const* p = &a;	// 2
int *const p = &a;	// 3
const int *const p = &a;	// 4
```

Are there any differences? C++ syntax clarifies that `const` modifies the nearest type. In the first case, `const` works on *int*, which means that **p*, what *p* points to, can not be changed with dereference. But *p* itself doesn't have any regulations, and it can be changed. In the second case, `const` also modifies *int*, so it has the same effect as the first one. In the third case, `const` modifies *int \**, which means *p* can not be changed, but what *p* points to can be changed by dereference. The last case has both `const` on *int* and *int \**, which means both *p* and what *p* points to can not be changes.

```cpp
const int *p = &a;	// Can't modify a with dereference, but p can point to another object
int const* p = &a;	// Same as above
int *const p = &a;	// Can modify a with dereference, but p can't point to another object
const int *const p = &a;	// Can't modify a with dereference, and p can't point to another object
```

The most common error in using `const` is the mismatch in type conversion. Now suppose we have the following code, which of those statements will raise an error?

```cpp
int a = 10;
const int *p1 = &a;	// 1
int *const p2 = &a;	// 2
int *p3 = p2;	// 3
int *p4 = p1;	// 4
```

In the first case, *p1* has a type of *const int \**, and *&a* has a type of *int \**, this conversion is valid. We now knows that **p1*, which is the content that p1 points to can not be modified, but there's nothing to do with *a*, because *a* is not a constant, there is no constraint in changing *a*'s value. Now look at the second case, what is the type of *p2*, is it *int \*const* ? Notice that if there is no *\** after `const`, then `const` should not be included into the type.

```cpp
int *q1 = nullptr;
int *const q2 = nullptr;
cout << typeid(q1).name() << endl;	// int *
cout << typeid(q2).name() << endl;	// int *
```

In the above code, *q1* and *q2* both have the type *int \**. So in the second case, *p2* has the type of *int \**, and *&a* has the type of *int \** as well, so it is a valid conversion. In the third case, *p3* and *p2* both have a type of *int \**, so this conversion is correct as well. In the last case, *p4* has a type of *int \**, and *p1* has a type of *const int \**, this is invalid! Remember that `const` makes sure that the constant can not be modified indirectly, so *p4* has to be `const` as well.

```cpp
int a = 10;
const int *p1 = &a;	// Correct
int *const p2 = &a;	// Correct
int *p3 = p2;	// Correct
int *q = p1;	// Wrong
```

In all, we have the following formula in type conversion of pointer:

```cpp
(int*) a = (const int *) b	// Wrong
(const int*) a = (int*) b	// Correct
```

## `const` and Double Pointers

Double pointer with `const` works in a similar way. Remember that `const` always works on the nearest type.

```cpp
const int **q;	// **q can not be modified directly
int *const *q;	// *q can not be modified directly
int **const q;	// q can not be modified directly
```

Now let's look at the following code. *q* has the the type of *const int \*\**, and *&p* has the type of *int \*\**, it seems work according to our previous inference, since *a* is not a constant and doesn't have constraint, but why there's an error?

```cpp
int main() {
    int a = 10;
    int *p = &a;
    const int **q = &p;	// ERROR
   	return 0;
}
```

It might seems confusing, but we can think about it in this way. Assume that the above code is correct, then **q* has the type of *const int \**. If we have the following code, then it is a valid operation because *&b* also has the type of *const int \**.

```cpp
const int b = 20;
*q = &b;
```

But wait! What *q* points to is another pointer *p*, so the statement above is the same as  `p = &b`. Since *p* is a not a `const` pointer, now we expose the memory of a constant *b* to a normal pointer *p*! This violate the rule of `const` that there is no directly modification of a constant. So our code above is not correct. We can fix this in two ways, either mark *p* as `const` or add another `const` on `q`.

```cpp
int main() {
    int a = 10;
    const int *p = &a;
    const int **q = &p;
   	return 0;
}
```

```cpp
int main() {
    int a = 10;
    int *p = &a;
    const int *const*q = &p;
   	return 0;
}
```

In all, we have the following formula in type conversion of double pointer:

```cpp
(*int **) a = (const int **) b	// Wrong
(const int**) a = (int **) b	// Wrong
(int**) a = (int *const *) b	// Wrong
(int *const *) a = (int**) b	// Correct
```

