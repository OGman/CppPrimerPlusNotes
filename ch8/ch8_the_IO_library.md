# IO库
## 8.1 IO类
IO类有三类，定义在三个不同的头文件中：iostream读写流，fstream读写文件，sstream从内存string对象中读写
- IO类型间的关系

ifstream与istringstream都继承自istream，ofstream与ostringstream都继承自ostream
### 8.1.1 IO对象无拷贝或赋值
### 8.1.2 条件状态
IO操作有一个与生俱来的问题是容易发生错误，IO类定义了一系列函数和状态让我们能够获取和修改io流的状态。
定义了iostate类型，定义了四个iostate类型的constexpr值：eofbit,failbit,badbit,goodbit。
对应的函数可以查询这些状态：eof(),fail(),bad(),good()
一些改变这些状态的函数：clear(),clear(flags),setstate(),rdstate()
### 8.1.3管理输出缓冲
每个输出流都有一个缓冲区，
