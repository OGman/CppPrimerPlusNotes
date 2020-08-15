# 泛型算法
## 10.1 概述
## 10.2 初识泛型算法
### 10.2.1 只读算法
accumulate(vec.cbegin(), vec.cend(), 0);
- 算法和元素类型
- 操作两个序列的算法
equal(roster1.cbegin(),roster1.cend(), roster2.cbegin());
### 10.2.2 写容器元素的算法
fill(vec.begin(), vec.end(), 0);
- 算法不检查写操作
- 介绍back_inserter
fill_n(back_inserter(vec), 10, 0);
- 拷贝算法
copy(vec.begin(), vec.end(), vec2.begin());
replace(vec.begin(), vec.end(), 0, 2); //replace 0 with 2
### 10.2.3 重排容器元素的算法
- 消除重复单词
sort(words.begin(), words.end());
unique(words.begin(), words.end());
- 使用unique
- 使用容器操作删除元素
## 10.3 定制操作
### 10.3.1 向算法传递函数
- 谓词(predicate)
一个返回bool类型的函数，可以是一元也可以是二元
- 排序算法
```
bool isShorter(const string &s1, const string &s2) {
  return s1.size() < s2.size();
}

sort(words.begin(), words.end(), isShorter);
stable_sor(words.begin(), words.end(), isShorter); //相等元素不改变原有顺序
```
### 10.3.2 lambda表达式
背景问题：
一个算法接受一个一元谓词，而我们需要传递两个参数进去
- 介绍lambda
### 10.3.3 lambda捕获和返回
### 10.3.4 参数绑定
- 标准库bind函数
- 绑定check_size的sz参数
- 使用placeholders名字
- bind的参数
- 用bind重排参数顺序
- 绑定引用参数

bind与lambda表达式都是产生一个可调用对象。lambda表达式用来写简短功能单一的小函数，bind用来将原有的函数进行调整
## 10.4 再探迭代器
除了普通的迭代器还有以下几种：
- 反向迭代器
- 插入迭代器
- 流迭代器
- 移动迭代器
### 10.4.1 插入迭代器
插入器三种类型：
1. back_inserter
2. front_inserter
3. inserter
分别使用容器的push_back,push_front,insert方法

