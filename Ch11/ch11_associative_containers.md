# 关联容器
关联容器有八种，是三种不同特性的二选一组合：map、set，有序、无序，不可重复、可重复：
map，set，multimap，multiset，unordered_map，unordered_set，unordered_map，unordered_map，
## 11.1 使用关联容器
## 11.2 关联容器概述
关联容器的操作：普通的容器操作，不支持顺序容器中基于未知的操作如push_front等
关联容器的特有操作：操作关键字的操作，类型别名，无序容器提供调整哈希性能的操作
关联容器的迭代器都是双向的
### 11.2.1 定义关联容器
```
map<string, size_t> word_count;
set<string> exclude = {"the", "but", "and", "or", "an", "a", "The", "But", "And", "Or", "An", "A"};
map<string, string> autors = {{"Zhang", "San"}, {"Li", "Si"}, {"Wang", "Wu"}};
```
- 初始化multimap或multiset

`multiset<int> miset(ivec.begin(), ivec.end())`
### 11.2.2 关键字类型的要求
有序容器的关键字必须定义元素比较的方法
- 有序容器的关键字类型
必须有严格意义的小于，具体包含下面三个规则：
1. 两个关键字不能同时小于对方
2. 传递性：k1小于k2，k2小于k3，k1小于k3
3. 如果两个关键字同时不小于对方，则两个关键字等价，等价也有传递性
- 使用关键字类型的比较函数
`multiset<Sales_data, decltype(compareIsbn) *>`
### 11.2.3 pair类型
在<utility>中
map的元素是pair类型
`make_pair(v1, v2)`
  
## 11.3 关联容器操作
key_type 关键词类型
value_type 对于set与key_type相同，对于map为pair<const key_type, mapped_type>
mapped_type 只适用于map，为关键字所关联到的类型，即pair.second的类型
### 11.3.1 关联容器迭代器
- set的迭代器是const的，map的key是const的
- 遍历关联容器
```
auto map_it = word_count.cbegin();
while (map_it != word_count.cend())
{
  ++map_it;
}
```
- 关联容器和算法
我们一般不对关联容器使用泛型算法。有写操作的的泛型算法无法用于关联容器，因为set的元素是const，而map的元素中pair.first为const。
### 11.3.2 添加元素
insert操作，由于set和map没有重复元素，向其中添加已存在的元素是没有效果的
- 向map添加元素
要插入一个pair对象
```
word_count.insert({word, 1});
word_count.insert(make_pair(word, 1));
```
- 检测insert的返回值

insert返回值为一个pair，其中first是一个迭代器，second是bool，表明是否成功，如果插入的元素已经存在，则插入失败，不进行插入操作，返回false
- 展开递增语句
- 向multiset或multimap添加元素

对map来说如果一个key对应多个元素可以用multimap
## 11.4 无序容器
