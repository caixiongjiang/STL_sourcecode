## 第一讲:容器之分类及各种测试

### 容器结构及分类

![容器的分类](img1.jpg)

![容器的分类](img2.jpg)

* 序列式容器
    * 数组（Array）：定长数组，无法扩充
    * vector：可扩充的数组（分配器做内存扩充）
    * Deque：双端队列
    * List：双向链表
    * Forward-List：单向链表
* 关联式容器（key->value）
    * Set/Multiset（Multiset中的值可以重复）：内部为红黑数
    * Map/Multimap（Multimap中的value值可以重复）：内部为红黑树
* 无序容器（unordered,大类上属于关联式容器）

*介绍一个常用的结构hashtable：根据公式进行分类， 但会产生碰撞，
产生碰撞的元素全部放在一个链表中。但如果链表太长如何做呢？后面会继续介绍。*

先写用于测试的几个辅助函数:
```c++
using std::cin;
using std::cout;
using std::string;

long get_a_target_long()
{
    long target = 0;
    cout << "target (0~" << RAND_MAX << "):";
    return target;
}

string get_a_target_string()
{
    long target = 0;
    char buf[10];
    cout << "target (0~" << RAND_MAX << "):";
    cin >> target;
    //snprintf功能为格式化成字符串
    // 1-- 目标字符串 2 -- 拷贝字节数 3 -- 格式化成字符串。4 -- 可变参数。
    snprintf(buf, 10, "%d", target);
    return string(buf);
}
//比较两个long数据是否相等
int compareLongs(const void* a, const void* b)
{
    return (*(long*)a - *(long*)b);
}
//比较两个string数据是否相等
int compareStrings(const void* a, const void* b)
{
    if(*(string*)a > *(string*)b)
        return 1;
    else if(*(string*)a < *(string*)b)
        return -1;
    else
        return 0;
}
```

### 顺序容器使用及测试
* 使用容器array：[array.cpp](https://github.com/caixiongjiang/STL_sourcecode/blob/master/%E7%AC%AC%E4%BA%8C%E8%AE%B2/array.cpp)
* 使用容器vector：[vector.cpp](https://github.com/caixiongjiang/STL_sourcecode/blob/master/%E7%AC%AC%E4%BA%8C%E8%AE%B2/vector.cpp)
* 使用容器list：[list.cpp](https://github.com/caixiongjiang/STL_sourcecode/blob/master/%E7%AC%AC%E4%BA%8C%E8%AE%B2/list.cpp)
* 使用容器forward_list：[forward_list.cpp](https://github.com/caixiongjiang/STL_sourcecode/blob/master/%E7%AC%AC%E4%BA%8C%E8%AE%B2/forward_list.cpp)
* 使用容器slist：[slist.cpp](https://github.com/caixiongjiang/STL_sourcecode/blob/master/%E7%AC%AC%E4%BA%8C%E8%AE%B2/slist.cpp)
* 使用容器deque：[deque.cpp](https://github.com/caixiongjiang/STL_sourcecode/blob/master/%E7%AC%AC%E4%BA%8C%E8%AE%B2/deque.cpp)
  * deque容器的结构：
  
  ![deque容器的结构](img3.jpg)
  
  deque容器由一个个具有一定长度的buffer组成，在每一个buffer上是连续的，
但是buffer与buffer之间不是连续的。（也就是所谓的**分段连续**的特点）
  
  deque内存扩充的机制是向两边扩充：哪边不够用了就扩充一下，每次都扩充一个buffer。
### 关联式容器使用及测试
**注意一点，只要是关联式的容器它的查找效率都是非常高的！**
* 使用容器stack：[stack.cpp](https://github.com/caixiongjiang/STL_sourcecode/blob/master/%E7%AC%AC%E4%BA%8C%E8%AE%B2/stack.cpp)
  
  deque其实已经涵盖了stack的功能：
  
  ![deque和stack的结构对比](img4.jpg)
* 使用容器queue：[queue.cpp](https://github.com/caixiongjiang/STL_sourcecode/blob/master/%E7%AC%AC%E4%BA%8C%E8%AE%B2/queue.cpp)
  
  deque其实已经涵盖了queue的功能：

  ![deque和queue的结构对比](img5.jpg)