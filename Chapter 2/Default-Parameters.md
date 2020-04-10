
# Default Parameters

When passing arguments to a funtion, we can do this in a naive way:

```cpp
int sum(int a, int b) {
    return a + b;
}

int main() {
    int a = 10;
    int b = 20;
    int ret = sum(a, b);
    cout << "return: " << ret << endl;
    return 0;
}
```

Alternatively, we can assign values to parameters inside the funtion brackets. These parameters with initialize values are called **default parameters**. Then in our main() function, we can pass inside a single parameter *a*. Then the second argument is automatically assigned to 20 since we do not pass it inside.

```cpp
int sum(int a, int b = 20) {
    return a + b;
}

int main() {
    int a = 10;
   	int ret = sum(a);
    cout << "return: " << ret << endl;
    return 0;
}
```

It is worth noting that the defualt parameters have to be assigned from right to left. For example, the following code is illegal. Recall that the function parameters are pushed into stack frame from right to left, and it will cause ambiguity if we don't follow this pattern. (In the following case, how does the compiler know variable *b* inside main() is passing to argument *a* or *b* ?)

```cpp
int sum(int a = 10, int b) {
    return a + b;
}

int main() {
    int b = 20;
    int ret = sum(b);	// ERROR
    cout << "return: " << ret << endl;
    return 0;
}
```

Moreover, we can also give default parameters in declaration besides definition:

```cpp
int sum(int a = 10, int b = 20);

int main() {
    int ret = sum();
    cout << "return: " << ret << endl;
    return 0;
}

int sum(int a, int b) {
    return a + b;
}
```

But we must pay attention that the same default argument can only occurs once,  no matter in declaration or definition. For example, the following program is invaild, because *a* and *b* are assigned twice in declaration and definition.

```cpp
int sum(int a = 10, int b = 20);

int main() {
    int ret = sum();
    cout << "return: " << ret << endl;
    return 0;
}

int sum(int a = 10, int b = 20) {	// ERROR
    return a + b;
}
```

Then let's look at the following code. Although the default parameters shows up from left to right in line 2, this program is actually valid. When the compiler parsing the code, it first reaches line 1, and record the value of *b*. When it reaches line 2, the compiler already knows that *b* equals 20, so it only needs the value of *a*.

```cpp
int sum(int a, int b = 20);
int sum(int a = 10, int b);	// Valid

int main() {
    int ret = sum();
    cout << "return: " << ret << endl;
    return 0;
}

int sum(int a, int b) {
    return a + b;
}
```

Sometimes function with default parameters can enhance the performance. In the naive approach we pass two variables inside the function, and the assembly code of pushing parameters into stack looks like:

```assembly
mov eax, dword ptr[ebp-8]
push eax
mov ecx, dword ptr[ebp-4]
push ecx
```

Then if only one variable is passed, there is no need for moving the value of variable into register *eax*. We can directly push the constant into the stack, thus eliminating one *mov* command. Of course, if we manually pass constants inside the function like ```int ret = sum(10, 20)```, there's no such improvement since we also push the constant into stack directly.

