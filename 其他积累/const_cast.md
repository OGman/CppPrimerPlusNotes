const_cast的作用是去掉const指针或const引用的const属性。
使用场景一般有两种：
1. 一个不修改对象的函数将参数定义为非const，想要传入const引用或指针时，可以用const_cast去掉const属性
2. 一个可修改的对象，却只有一个const的指针或引用可使用，这时需要在可变场景下使用这个对象时，可以用const_cast去掉const属性
``` C++
int a = 10;
const int *p = &a;
int *p1 = const_cast<int *>(p);
*p1 = 12;
```
总结：
const_cast不能修改底层对象的const属性，只能在保证底层对象使用合法的情况下，修改指针或引用的const属性。
