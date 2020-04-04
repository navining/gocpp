# Inline Function

Let's look at the following program

```cpp
int sum(int x, int y) {
    return x + y;
}

int main() {
    int a = 10;
    int b = 20;
    int ret = sum(a, b);
    return 0;
}
```

When main() calls sum(), it needs to push all parameters into stack frame, create a new stack frame for sum(), and return the stack frame back to system after it quits. But what if we call sum() thousands of times? Notice that sum() function only involves three operations (*mov*, *add*, and *mov*), then it is a huge amount of overhead in calling the function comparing to the calculation itself. Under this circumstances, we had better mark function sum() as **inline**.

An function with inline simply does one work: it expand all the commands inside the function, and insert them into where the function is called, during the compiling process. In this way, the function calling process is eliminated.

``` cpp
inline int sum(int x, int y) {
    return x + y;
}

int main() {
    int a = 10;
    int b = 20;
    int ret = sum(a, b);	// Convert into: int ret = a + b;
    return 0;
}
```

Since there's no function call, there's no need to generate function symbols inside the symbol table. To verify this, we can compile this code with O2 compiler optimization as ```g++ -c main.cpp -O2``` and dump the object file with ```objdump -t main.o```.

```bash
main.o:     file format elf64-x86-64

SYMBOL TABLE:
0000000000000000 l    df *ABS*  0000000000000000 main.cpp
0000000000000000 l    d  .text  0000000000000000 .text
0000000000000000 l    d  .data  0000000000000000 .data
0000000000000000 l    d  .bss   0000000000000000 .bss
0000000000000000 l    d  .text.startup  0000000000000000 .text.startup
0000000000000000 l    d  .note.GNU-stack        0000000000000000 .note.GNU-stack
0000000000000000 l    d  .eh_frame      0000000000000000 .eh_frame
0000000000000000 l    d  .comment       0000000000000000 .comment
0000000000000000 g     F .text.startup  0000000000000003 main
```

However, not every function marked with *inline* will be converted into inline function. A recursive function, for example, which calls itself constantly, can not be inlined because the times it is called is only known at runtime. Moreover, if the function has too many lines, it may also not be inlined.

Therefore, the keyword *inline* is just a suggestion for the compiler to make it inlined. It is up to the compiler to decide whether make it inlined or not.

In VS Code, *inline* only works in the release version. The debug version makes it unavailable in order to facilitate the debugging of the program.

