# 重载运算与类型转换
## 14.1 基本概念
重载运算符是具有特殊名字的函数，由关键字operator和后面的符号构成。
如果运算符函数是成员函数，则其第一个操作数与this指针隐式绑定。
运算符函数必须与特定类型相关联。
重载运算符的优先级和结合律与原运算符相同。
- 直接调用一个重载的运算符函数
非成员函数
```
data1+data2;
operator+(data1, data2);
```
成员函数
```
data1 += data2;
data1.operator+(data2);
```
- 某些运算符不应该被重载
通常不应重载, & && ||运算符

- 使用与内置类型一致的含义
重载运算符很大程度上让类的理解和使用更加方便直观。
如果定义了==一般也需要定义!=
如果定义了<一般也需要定义其他关系运算符

- 赋值和复合赋值运算符
重载赋值运算符应返回其左侧运算对象的一个引用，复制之后，左侧对象应该与右侧对象值相等
如果有算术运算符则最到定义对应的复合赋值运算符+=,\*=等
- 选择作为成员或者非成员
在重载运算符时，首先要确定是作为成员还是非成员。
1. 赋值、下标、调用和成员访问（->）必须是成员
2. 复合赋值运算符一般来说应为成员，但非必须
3. 改变对象状态的运算符一般应为成员
4. 具有对称性的运算符通常应该是非成员函数
## 14.2 输入和输出运算符
### 14.2.1 重载输出运算符<<
输出运算符有两个参数，第一个参数是一个非常量的ostream对象的引用，非常量是因为向流写入数据会改变它的状态，引用是因为我们无法复制ostream对象；第二个参数是一个想要输出对象的常量引用，常量是因为我们不会改变他的值，引用是为了避免复制数据；返回值是它的ostream形参，这是为了与内置的输出运算符保持一致。
- Sales_data的输出运算符
```C++
ostream &operator(ostream &os, const Sales_data &item)
{
  os << item.isbn() << " " << item.units_sold << " "
     << item.revenue << " " << item.avg_price();
  return os;
}
```
- 输出运算符尽量减少格式化操作
为了保留用户使用输出运算符输出内容格式的自由度，尽量不要在输出运算符内进行格式化操作，比如加换行符或者对齐等。
- 输入输出运算符必须是非成员函数
如果写成成员函数，则运算符的第一个参数为this指针，无法进行输入输出，因此输入输出运算符不能被声明为成员函数。为了能够访问类内私有成员，一般将其声明为友元函数。
### 14.2.2 重载输入运算符>>
输入运算符有两个参数，第一个为非常量的istream的引用，第二个为非常量的输入类型的对象的引用，非常量是因为我们要将数据写入到这个对象中。
- Sales_data的输入运算符
```C++
istream &operator(istream &is, Sale_data &item)
{
  is >> item.bookNo >> item.units_sold >> price;
  if (is)
    item.revenue = item.units_sold*price;
  else
    item = Sales_data();
  return is;
}
```
- 输入时的错误
常见的错误有两种：
1. 读取的内容跟存储的对象不符
2. 读取到达文件末尾或者遇到留的其他错误
我们必须保证，在发生错误时，产生的结果仍然是合法的并且最好不产生误导，因此，如果读取失败，我们将item置为Sales_data默认初始化的值。
- 标示错误
最好的方式是有IO标准库来标识这些错误。
## 14.3 算术和关系运算符
我们通常把算术和关系运算符定义为非成员函数，因为这样更方便对左侧或右侧的运算对象进行转换。参数一般为常量，因为不需要改变左右操作数的值。返回值一般都是一个新的对象，在函数体中建立局部对象，最后返回对这个对象的拷贝。
由于定义算术运算符时，一般也需要定义对应的复合赋值运算符，因此算数运算符的实现一般直接使用复合赋值运算符。
```C++
Sales_data
operator+(const Sales_data &lhs, const Sales_data &rhs)
{
  Sales_data sum = lhs;
  sum += rhs;
  return sum;
}
```
### 14.3.1 相等运算符
相等运算符应该比较每个数据成员，当他们都相等时，才认为两个对象相等。
```C++
bool operator==(const Sales_data &lhs, const Sales_data &rhs)
{
  return lhs.isbn() == rhs.isbn() &&
         lhs.units_sold == rhs.units_sold &&
         lhs.revenue == rhs.revenue;
}
bools operator!=(cosnt Sales_data &lhs, cosnt Sales_data &rhs)
{
  return !(lhs == rhs);
}
```
设计准则：
1. 如果类需要比较是否相等的操作，则应该将它定义为==运算符
2. 如果定义了==，则应该能用它判断一组给定对象中是否有重复数据
3. ==应该有传递性
4. 定义==则也应该定义!=
5. ==与!=应该将其中一个的工作委托给另外一个
### 14.3.2 关系运算符
关系运算符通常应该：
1. 定义顺序关系，令其与关联容器中对关键字的要求一致
2. 如果同时有==运算符，则关系运算符应该与==保持匹配：如果两个对象是!=的则一个应<另一个
## 14.4 赋值运算符
拷贝赋值运算符与移动赋值运算符将类的一个对象复制给另一个对象。我们也可以定义别的运算符，将其他类的对象赋值给本类。

- 复合赋值运算符
复合赋值运算符不一定必须是类成员，但我们还是习惯于将包括复合赋值运算符在内的所有赋值运算符包含在类内。符合赋值运算符返回其左侧运算对象的引用。
```C++
Sales_data& Sales_data::operator+=(const Sales_data &rhs)
{
  units_sold += rhs.units_sold;
  revenue += rhs.revenue;
  return *this;
}
```
## 14.5 下标运算符[]
容器类需要下标运算符来访问元素。下标运算符必须是成员函数。
下标运算符的返回值一般是成员的引用，这样我们方便将其放在赋值号的左边或者右边。我们最好同时定义返回值为常量的版本和非常量的版本。这样当下标运算符作用于常量对象时，可以确保返回值不被改变。
```C++
class StrVec {
public：
  std::string& operator[](std::size_t n)
  {
    return elements[n];
  }
  const std::string& operator[](std::size_t n) const
  {
    return elements[n];
  }
private:
  std::string *elements;
};
```
如果作用的对象是一个常量的StrVec，将调用常量版本的[]，返回常量对象
## 14.6 递增和递减运算符
递增和递减运算符在迭代器类中通常会实现。由于这两种运算符直接改变对象的值，因此作为类的成员函数比较好。
内置的递增运算符和递减运算符包含前置和后置版本。我们在重载时也应实现。
- 定义前置递增/递减运算符
```C++
class StrBlobPtr {
public:
  StrBlobPtr& operator++();
  StrBlobPtr& operator--();
};

StrBlobPtr& StrBlobPtr::operator++()
{
  check(curr, "increment past end of StrBlobPtr");
  ++curr;
  return *this;
}

StrBlobPtr& StrBlobPtr::operator--()
{
  --curr;
  check(curr, "decrement past begin of StrBlobPtr");
  return *this;
}
```
- 区分前置和后置运算符
C++为了区分前置和后置的版本，在后置版本声明时加入了一个额外的int类型的形参。这个int的唯一作用就是标识这一重载版本为后置。
```C++
class StrBlobPtr{
public:
  StrBlobPtr operator++(int);
  StrBlobPtr operator--(int);
};

StrBlobPtr StrBlobPtr::operator++(int)
{
  StrBlobPtr ret = *this;
  ++*this;
  return ret;
}

StrBlobPtr StrBlobPtr::operator--(int)
{
  StrBlobPtr ret = *this;
  --*this;
  return ret;
}
```
- 显式地调用后置运算符
在显式调用后置运算符时，必须传入一个int类型的参数，编译器才知道调用的是后置版本
## 14.7 成员访问运算符
成员访问运算符包括两种：->和\*
``` C++
class StrBlobPtr {
public:
  std::string& operator*() const
  {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
  }
  std::string* operator->() const
  {
    return & this->operator*();
  }
}
```
将这两个运算符定义为const成员是因为这两个成员并不会改变对象的状态。
- 对箭头运算符返回值的限定
箭头运算符只能获取成员。其返回值必须是一个指针。对于一个重载了箭头运算符的对象point，point->mem相当于point.operator->()->mem
重载运算符必须返回类的指针或自定义了箭头运算符的某个类的对象
## 14.8 函数调用运算符()
如果重载了()，则能够像调用函数一样调用类的对象，相比于普通函数，这种对象还可以保存状态，更加灵活
函数调用运算符必须是成员函数，如果定义了调用运算符，则该类的对象被称为函数对象
- 含有状态的函数对象类
``` C++
class PrintString {
public:
  PrintString(ostream &o = cout, char c = ' '):
    os(o), sep(c) {}
  void operator() (cosnt string &s) const { os << s << sep; }
private:
  ostream &os;
  char sep;
}
```
函数对象常常用作泛型算法的实参，如```for_each(vs.begin(), vs.end(), PrintString(cerr, '\n'));```
### 14.8.1 lambda是函数对象
``` C++
stable_sort(words.begin(), words.end(), [](const string &a, const string &b) {return a.size() < b.size();});

//其中的lambda表达式类似于下面的类
class ShorterString {
public:
  bool operator() (const string &a, const string &b) const
  {
    return a.size() < b.size();
  }
};

//前面的表达式等价于下面
stable_sort(words.begin(), words.end(), ShorterString());
```
- 表示lambda及相应捕获行为的类
lambda表达式通过引用捕获变量时，由程序确保lambda执行时引用的对象确实存在。当lambda表达式通过值捕获变量时需要拷贝到lambda中，需要建立对应的数据成员。
``` C++
auto wc = find_if(words.begin(), words.end(), 
                  [sz](const string &a) {return a.size() >= b.size();});
//其中的lambda表达式类似下面的类：
class SizeComp {
public:
  SizeComp(size_t n): sz(n) {}
  bool operator() (const string &s) const
    {return s.size() >= sz;}
private:
  size_t sz;
};

//表达式等价于
auto wc = find_if(words.begin(), words.end(), SizeComp(sz));
```
### 14.8.2 标准库定义的函数对象
- 在算法中使用标准库函数对象
在泛型算法中比较方便使用
### 14.8.3 可调用对象与function
C++中的可调用对象有：函数、函数指针、lambda表达式、bind创建的对象、重载了函数调用运算符的类。
可调用对象有不同的类型，例如函数和函数指针的类型由它的返回值和实参数量及类型确定，每个lambda表达式有自己的类类型(未命名)。但不同类型的可调用对象可能共享同一种调用形式，一种调用形式对应一个函数类型：例如int(int, int)
- 不同类型可能具有相同的调用形式
相同的调用形式可以用标准库中的function类型统一起来。
function<int (int, int)>可以用所有相同调用形式的可调用对象来赋值。
``` C++
int add(int a1, int a2)
  { return a1 + a2; }
function<int (int, int)> f1 = add;
```
- 重载的函数与function
上面例子中，当函数重载时，不能使用函数名来赋值f1，这时有两种方法：函数指针或lambda表达式
## 14.9 重载、类型转换与运算符
类型转换，凭空添乱，最好不用
### 14.9.1 类型转换运算符
### 14.9.2 避免有二义性的类型转换
### 14.9.3 函数匹配与重载运算符
