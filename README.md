# Go C++（现代 C++ 学习笔记）

在线阅读：https://navining.gitbook.io/gocpp/

本仓库整理了现代 C++ 的核心语法、面向对象、模板与 STL、并发编程以及常见设计模式等内容，并配有可运行的示例代码与插图，适合：
- 有 C 基础，想系统学习/巩固 C++ 的同学
- 已掌握基础，想深入理解底层机制与实践技巧的开发者
- 准备面试、需要梳理高频知识点的人

如果内容对你有帮助，欢迎 Star 支持：https://github.com/navining/gocpp

## 仓库结构

- Chapter 1 ~ 13：按主题分类的笔记（Markdown）
- codes：配套示例代码（可直接编译运行）
- assets：插图与示意图

## 快速开始

- 按章节阅读对应的 Markdown 文档
- 编译并运行示例代码（需要 g++ 或 clang++，建议 C++11 及以上）：

```bash
# 智能指针示例
g++ -std=c++11 "codes/Chapter 10/SmartPtr.cpp" -o SmartPtr
./SmartPtr

# 生产者-消费者示例（需要 pthread）
g++ -std=c++11 "codes/Chapter 12/Producer-Consumer.cpp" -pthread -o ProducerConsumer
./ProducerConsumer
```

## 目录索引

### Chapter 1：基础必备
- [进程虚拟地址空间：内存分区与布局](Chapter%201/Virtual-Address-Space-of-Process-Memory-Partition-and-Layout.md)
- [函数调用：栈帧](Chapter%201/Function-Call-Stack-Frame.md)
- [程序的编译与链接](Chapter%201/Program-Compiling-and-Linking.md)

### Chapter 2：语法进阶
- [缺省参数](Chapter%202/Default-Parameters.md)
- [内联函数](Chapter%202/Inline-Function.md)
- [函数重载](Chapter%202/Function-Overloading.md)
- [`new` 与 `delete`](Chapter%202/New-and-Delete.md)
- [`const` 与指针](Chapter%202/Const-and-Pointers.md)
- [深入引用](Chapter%202/References-in-Detail.md)

### Chapter 3：面向对象
- [类与对象](Chapter%203/Class-and-Object.md)
- [构造与析构](Chapter%203/Constructor-and-Destructor.md)
- [浅拷贝与深拷贝](Chapter%203/Shallow-Copy-and-Deep-Copy.md)
- [初始化列表](Chapter%203/Initializer-List.md)
- [各类成员函数](Chapter%203/Various-Member-Functions.md)
- [指向成员的指针](Chapter%203/Pointer-to-Class-Members.md)

### Chapter 4：模板与泛型
- [函数模板](Chapter%204/Function-Templates.md)
- [类模板](Chapter%204/Class-Templates.md)
- [内存分配器](Chapter%204/Memory-Allocators.md)

### Chapter 5：运算符与迭代器
- [运算符重载](Chapter%205/Operator-Overloading.md)
- [迭代器入门](Chapter%205/Introduction-to-Iterators.md)
- [迭代器失效问题](Chapter%205/Issues-of-Iterator-Invalidation.md)
- [更多 `new/delete`](Chapter%205/More-about-new-and-delete.md)
- [`new/delete` 重载：对象池](Chapter%205/Overloading-of-new-and-delete-Object-Pool.md)

### Chapter 6：继承与多态
- [走进继承](Chapter%206/Look-inside-Inheritance.md)
- [更多继承细节](Chapter%206/More-about-Inheritance.md)
- [虚函数、静态绑定与动态绑定](Chapter%206/Virtual-Functions-Static-Binding-and-Dynamic-Binding.md)
- [更多虚函数](Chapter%206/More-about-Virtual-Functions.md)
- [理解多态](Chapter%206/Understanding-Polymorphism.md)
- [抽象类](Chapter%206/Abstract-Classes.md)
- [多态常见面试题](Chapter%206/Frequently-Asked-Interview-Questions-Polymorphism.md)

### Chapter 7：多重继承
- [虚继承与虚基类](Chapter%207/Virtual-Inheritance-and-Virtual-Base-Classes.md)
- [菱形继承问题](Chapter%207/Diamond-Problem.md)
- [四种类型转换](Chapter%207/Four-Kinds-of-Type-Conversions.md)

### Chapter 8：STL 基础
- [顺序容器](Chapter%208/Sequence-Containers.md)
- [容器适配器](Chapter%208/Container-Adaptors.md)
- [关联式容器](Chapter%208/Associative-Containers.md)
- [更多迭代器](Chapter%208/More-about-Iterators.md)
- [函数对象](Chapter%208/Function-Objects.md)
- [泛型算法、绑定器与 Lambda](Chapter%208/Generic-Algorithms-Binders-and-Lambda-Expressions.md)

### Chapter 9：对象优化
- [对象背后的实现](Chapter%209/Behind-the-Object.md)
- [函数中的对象优化](Chapter%209/Optimizing-Objects-in-Functions.md)
- [右值引用成员函数](Chapter%209/Member-Functions-with-Rvalue-References.md)
- [移动语义与完美转发](Chapter%209/Move-Semantics-and-Perfect-Forwarding.md)

### Chapter 10：智能指针
- [智能指针综述](Chapter%2010/Smart-Pointers.md)
- [无引用计数的智能指针](Chapter%2010/Smart-Pointers-without-Reference-Counting.md)
- [带引用计数的智能指针](Chapter%2010/Smart-Pointers-with-Reference-Counting.md)
- [自定义删除器](Chapter%2010/Custom-Deleters.md)

### Chapter 11：函数对象与绑定
- [更多绑定器](Chapter%2011/More-about-Binders.md)
- [std::function 入门](Chapter%2011/Introduction-to-std-function.md)
- [模板特化与参数推导](Chapter%2011/Template-Specialization-and-Argument-Deduction.md)
- [std::function 进阶](Chapter%2011/More-about-std-function.md)
- [std::bind：简易线程池](Chapter%2011/std-bind()-A-Simple-Thread-Pool.md)
- [更多 Lambda](Chapter%2011/More-about-Lambda-Expressions.md)

### Chapter 12：并发编程
- [C++11 重要特性](Chapter%2012/Important-Features-in-C++11.md)
- [std::thread 多线程编程](Chapter%2012/Multithreaded-Programming-with-std-thread.md)
- [互斥](Chapter%2012/Mutual-Exclusion.md)
- [生产者-消费者问题](Chapter%2012/Producer-Consumer-Problem.md)
- [原子操作](Chapter%2012/Atomic-Operations.md)
- [线程可见性与 volatile](Chapter%2012/Thread-Visibility-and-volatile.md)

### Chapter 13：设计模式
- [单例模式](Chapter%2013/Singleton-Pattern.md)
- [工厂模式](Chapter%2013/Factory-Pattern.md)
- [代理模式](Chapter%2013/Proxy-Pattern.md)
- [装饰器模式](Chapter%2013/Decorator-Pattern.md)
- [适配器模式](Chapter%2013/Adapter-Pattern.md)
- [观察者模式](Chapter%2013/Observer-Pattern.md)

## 代码示例速览

示例代码位于 `codes/` 目录，建议以单文件方式快速验证概念。更多示例：

```bash
# 线程池（示例文件名以实际为准）
g++ -std=c++11 "codes/Chapter 11/ThreadPool.cpp" -pthread -o ThreadPool

# 原子与互斥
g++ -std=c++11 "codes/Chapter 12/Atomic-Operations.cpp" -pthread -o AtomicOps
g++ -std=c++11 "codes/Chapter 12/Mutex.cpp" -pthread -o MutexDemo
```

## 贡献

- 欢迎提交勘误、补充示例或新增主题
- 提交前请确保能在本地正确编译运行示例
