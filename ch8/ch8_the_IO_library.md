# IO库
## 8.1 IO类
IO类有三类，定义在三个不同的头文件中：iostream读写流，fstream读写文件，sstream从内存string对象中读写
- IO类型间的关系
ifstream与istringstream都继承自istream，ofstream与ostringstream都继承自ostream
### 8.1.1 IO对象无拷贝或赋值
