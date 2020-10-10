# 面向对象程序设计
## 15.1 OOP：概述
面向对象的基础是数据抽象、继承和动态绑定。通过数据抽象，我们将类的接口与实现分离；通过继承，可以定义相似的类型并对其相似关系建模；使用动态绑定，可以在一定程度上忽略相似类型的区别，而以统一的方式使用他们的对象
- 继承
基类与派生类
我们将定义两个类，Quote与派生类Bulk_quote
``` C++
class Quote {
  public:
    std::string isbn() const;
    virtual double net_price(std::size_t n) const;
};

class Bulk_quote : public Quote {
  public:
    double net_price(std::size_t) const override;
};
```
对于基类允许派生类重新定义的函数，我们声明为虚函数，即在前面加上virtual。在派生类中重新定义虚函数时可以在最后加上override来注明他使用这个成员函数来改写基类的虚函数。
- 动态绑定
``` C++
double print_total(ostream &os, const Quote &item, size_t n)
{
  double ret = item.net_price(n);
  os << "ISBN: " << item.isbn()
     << " # sold: " << n << " total due: " << ret << endl;
  return ret;
}
```
调用这个函数，当传入基类对象时，调用的是基类的net_price，传入派生类对象，则调用派生类的对应函数
当我们使用基类的引用或指针调用一个虚函数时发生动态绑定
## 15.2 定义基类和派生类
### 15.2.1 定义基类
``` C++
class Quote {
public:
  Quote() = default;
  Quote(const std::string &book, double sales_price):
    bookNo(book), price(sales_price) {}
  std::string isbn() const {return bookNo;}
  virtual double net_price(std::size_t n) const {return n * price;}
  virtual ~Quote() = default;
private:
  std::string bookNo;
protected:
  double price = 0.0;
};
```
基类通常应该定义一个虚析构函数
- 成员函数与继承
派生类override覆盖基类的成员定义来实现自己区别于基类的操作
基类的成员函数有两类：希望派生类进行覆盖的函数和不希望的。前者通常定义为虚函数。当我们使用指针或引用调用虚函数时，该调用将被动态绑定。
任何构造函数之外的费静态函数都可以是虚函数。如果基类把一个函数声明为虚函数，则该函数在派生类中隐式地为虚函数。
成员函数若为声明为虚函数，则其解析过程发生在编译时。
- 访问控制与继承
派生类可以访问基类中的公有成员，不能访问私有成员。基类中受保护的成员派生类可以访问但其他用户不能访问
### 15.2.2 定义派生类
类派生列表
``` C++
class Bulk_quote : public Quote {
public:
  Bulk_quote() = default;
  Bulk_quote(const std::string &, double, std::size_t, double);
  double net_price(std::szie_t) const override;
private:
  std::size_t min_qty = 0;
  double discount = 0.0;
};
```
类派生列表中访问说明符的作用是控制从基类继承来的成员对派生类的用户是否可见
public继承则基类的公有成员也是派生类的公有成员
- 派生类中的虚函数
派生类可以不覆盖虚函数
可以在函数声明后面加上override关键字来显式说明此函数覆盖了基类的虚函数
- 派生类对象及派生类向基类的类型转换
一个派生类对象包含多个组成部分：一个含有派生类自己定义的非静态成员的子对象，一个与该派生类继承的基类对应的子对象，如果有多个基类，这样的对象也有多个
基类的指针或引用可以绑定到派生类的基类对应的子对象上，这就是派生类到基类的转换
- 派生类构造函数
派生类必须调用基类的构造函数来初始化基类部分
``` C++
Bulk_quote(const std::string &book, double p, std::size_t qty, double disc):
  Quote(book, p), min_qty(qty), discount(disc) {}
```
- 派生类使用基类的成员
派生类可访问基类的公有成员和protected成员
``` C++
double Bulk_quote::net_price(size_t cnt) const
{
  if (cnt >= min_qty)
    return cnt * (1 - discount) * price;
  else 
    return cnt * price;
}
```
- 继承与静态成员
如果基类定义了一个静态成员，则在整个继承体系内只存在该成员的唯一定义。
静态成员遵循通用的访问限制规则
- 派生类的声明
派生类的声明不能包含他的派生列表
- 被用作基类的类
如果我们想将某个类作为基类，这个类必须已经定义而非仅仅声明。原因是派生类可以使用基类的成员，因此不仅需要知道它存在，而且必须知道它是什么。
这也导致了另外一个结果，类不能继承自己
- 防止继承
在类名后加final
``` C++
class Noderived final {};
```

### 15.2.3 类型转换与继承
- 静态类型与动态类型
静态类型在编译时已知，即变量声明时的类型，动态类型知道运行时才知道，如基类的指针或引用
只有指针和引用的静态类型可能与动态类型不一致，其他的表达式静态类型与动态类型一定是一致的
- 不存在从基类到派生类的隐式类型转换
派生类的对象中包含一个基类部分，因此派生类指针和引用可以向基类转换。基类的对象可以是派生类对象的一部分也可以不是，因此派生类无法向基类转换
既是一个基类指针或引用绑定在一个派生类对象上，我们也不能执行从基类向派生类的转换。除非使用dynamic_cast或static_cast进行转换
- 在对象之间不存在类型转换
当我们初始化或赋值一个类对象时，实际上是在调用构造函数与赋值运算符函数
想要从派生类对象转换到基类对象，一定会抛弃其中派生类部分的成员
## 15.3 虚函数
我们必须为每一个虚函数提供定义，而不管他是否被用到
- 对虚函数的调用可能在运行时才被解析
如果是指针或引用，在运行时才解析，如果是对象，在编译时就能解析
- 派生类中的虚函数
一旦一个函数被声明为虚函数，则它在所有的派生类中都是虚函数，不需要显式声明
派生类覆盖虚函数时，其形参类型与返回类型必须与基类中一致
返回类型一致有一个例外，当返回的是本类的指针或引用时，可以是派生类的类型
- final和override说明符
override最大的用处是让编译器帮助检查虚函数覆盖时的写错参数、写错函数名之类的错误，在覆盖虚函数定义时加override是很好的习惯
可以将一个虚函数指定为final，则之后无法再覆盖它
- 虚函数与默认实参
默认实参使用基类中定义的默认实参
- 回避虚函数的机制
如果想使用特定版本可以使用作用域运算符
``` C++
double undicounted = baseP->Quote::net_price(42);
```
如果派生类在虚函数中想调用基类版本却没写作用域运算符，将调用派生类的版本，产生无限递归

## 15.4 抽象基类
- 纯虚函数

我们不希望用户构造基类的对象，可以将其中的成员函数定义为纯虚函数
``` C++
class Disc_quote : public Quote {
public:
  Disc_quote() = default;
  Disc_quote(const std::string &book, double price, std::size_t qty, double disc):
    Quote(book, price), quantity(qty), discount(disc) {}
  double net_price(std::size_t) const = 0;
protected:
  std::size_t quantity = 0;
  double discount = 0.0;
};
```
虽然我们不想构造本类的对象，我们也必须提供构造函数。让继承本类的派生类正确初始化基类部分
可以在类外为纯虚函数提供函数体

- 含有纯虚函数的类是抽象基类

含有纯虚函数的类是抽象基类，未经覆盖直接继承纯虚函数的类也是。无法创建抽象基类的对象

- 派生类构造函数只初始化它的直接基类

``` C++
class Bulk_quote : public Disc_quote {
public:
  Bulk_quote() = default;
  Bulk_quote(const std::string &book, double price, std::size_t qty, double disc):
    Disc_quote(book, price, qty, disc) {}
  double net_price(std::size_t) const override;
};
```

## 15.5 访问控制和继承
每个类自己控制自己成员的初始化，也控制自己成员的对于派生类来说是否可访问
- 受保护的成员

protected成员有以下三点性质：
1. 与私有成员类似，protected成员对于类的用户来说是不可访问的
2. 和公有成员类似，protected成员对于类的派生类和友元来说是可以访问的
3. 派生类的成员和友元只能通过派生类的对象来访问基类的受保护成员，派生类对于一个基类对象中的受保护成员没有任何访问特权
派生类的成员和友元只能访问派生类对象中的基类部分受保护成员，不能访问普通基类对象的成员

- 公有、私有和保护继承

派生类说明符是为了控制派生类用户对基类成员的访问权限
如果继承为public则成员遵循其基类中的原有说明符
如果继承为private则所有基类成员都变成private
如果继承为protect则所有public成员变为protected

- 派生类向基类转换的可访问性
- 友元和继承

友元关系不能传递也不能继承

- 改变个别成员的可访问性

使用using声明可以改变个别对象的可访问性，派生类只能为哪些他可以访问的名字提供using声明

- 默认的继承保护级别

默认情况下，class定义的类是私有继承，struct定义的类是公有继承
class和struct仅有的差别是默认成员访问说明符即默认派生访问说明符

## 15.6 继承中的类作用域
每个类定义自己的作用域。派生类的作用域嵌套在基类作用域内
- 在编译时进行名字查找

一个对象、引用或指针的静态类型决定了该对象的哪些成员是可见的。即使静态类型与动态类型不一致，我们能使用哪些成员仍是有静态类型决定的

- 名字冲突与继承

定义在内层作用域的名字将隐藏外层作用于的名字
派生类的成员将隐藏同名的基类成员`问题：派生类可以定义与基类同名的成员？`

- 通过作用域运算符类使用隐藏的成员
- 一如往常，名字查找先于类型检查

先在派生类作用域内查找名字，如果名字被查找到，则基类中的相同名字将被隐藏。即使函数名相同而参数不同，基类中的同名函数也会被隐藏

- 虚函数与作用域
- 通过基类调用隐藏的虚函数
- 覆盖重载的函数

成员函数无论是否虚函数都能被重载
如果重载成员有很多而我们只需要覆盖其中的一部分，我们可以使用一条using语句将所有的函数重载版本添加到派生类中

## 15.7 构造函数和拷贝控制
### 15.7.1 虚析构函数
基类通常应该定义一个虚析构函数，这是为了在delete动态分配的对象的指针时，能够匹配正确的析构函数
- 虚析构函数将阻止合成移动操作
### 15.7.2 合成拷贝控制与继承


### 15.7.3 派生类的拷贝控制成员
### 15.7.4 继承的构造函数
## 15.8 容器与继承
## 15.9 再探文本查询
