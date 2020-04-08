# onst``` in Depth

const修饰的变量不能作为左值，初始化完成后值不能被修改

```cpp
int main() {
    int a = 10;
    a = 20;
    const int b = 20;
    b = 30;	// ERROR
    return 0;
}
```

c和c++中const的区别

c中const修饰的可以不用初始化

不叫常量叫常变量（依然是变量），不能当作常量表达式使用

```c
void main() {
    const int a = 20;
    int array[a] = {};	// ERROR
}
```



只是不能用赋值表达式，内存可以修改

```c
void main() {
    const int a = 20;
    int *p = (int*)&a;
    *p = 30;
    printf("%d %d %d", a, *p, *(&a));	// 30 30 30
}
```

c++中const必须初始化

叫常量，可以给数组初始化

const编译方式不同，c中const当作变量编译生成指令，cpp中所有出现const常量名字的地方都被常量的初始值替换。

```cpp
int main() {
    const int a = 20;
    int *p = (int*)&a;
    *p = 30;
    printf("%d %d %d", a, *p, *(&a));	// 20 30 20
}
```

*p的确改了a的内存，但是a已经在编译阶段被替换了

```cpp
int b = 20;
const int a = b;
```

此时a是常变量，因为初始值不是立即数