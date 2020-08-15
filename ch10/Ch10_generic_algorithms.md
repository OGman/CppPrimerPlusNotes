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
