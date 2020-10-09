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
如果我们想将某个类作为基类，这个类必须已经定义而非仅仅声明

### 15.2.3 类型转换与继承
## 15.3 虚函数
## 15.4 抽象基类
纯虚函数
## 15.5 访问控制和继承
- 受保护的成员
- 公有、私有和保护继承
- 派生类向基类转换的可访问性
- 友元和继承
- 改变个别成员的可访问性
- 默认的继承保护级别
## 15.6 继承中的类作用域
- 在编译时进行名字查找
- 名字冲突与继承
- 通过作用域运算符类使用隐藏的成员
- 一如往常，名字查找先于类型检查
- 虚函数与作用域
- 通过基类调用隐藏的虚函数
- 覆盖重载的函数
## 15.7 构造函数和拷贝控制
### 15.7.1 虚析构函数
### 15.7.2 合成拷贝控制与继承
### 15.7.3 派生类的拷贝控制成员
### 15.7.4 继承的构造函数
## 15.8 容器与继承
## 15.9 再探文本查询
