## 第十二讲：hashtable深度探索
### 为什么要使用hashtable？

![](img12_1.jpg)
如上图所示，如果空间足够，我们当然可以按照次序进行存储，但往往存储是比较有限的，我们就可以使用
hashtable的结构来存储！

### 如何处理hashtable的碰撞现象？
如果我们使用hashtable的结构，一定会存在取余之后相等的情况：例如`15%7`和`22%7`就会发生碰撞！

我们解决的办法是：**如果发生碰撞，就将它们以一个链表的形式串在一起，如下图所示。**

![](img12_2.jpg)

特点：
* 发生碰撞时使用形成链表的形式来解决碰撞。
* 链表的搜寻时间是线性增长的（ 平均时间复杂度为O(n) ），但如果list够小，搜寻的速度荏苒很快。
* 如果所有链表的总节点数超过了`bucket`（这里指模的值，图中为53，也是GNU中使用的初始值）的数量， 采用`再哈希`的方法:
    * 方式为将`bucket`的数量扩充到原来的值的2倍，然后选取离它最近的素数作为新的`bucket`值。
    * 每次扩充都需要对每个元素重新计算新的位置。
    * 在源码中已经将所有`bucket`的值全部算好了，需要扩充时，直接取就ok！

部分源码（GNU2.9）：
```c++
template <class Value, class Key, class HashFcn,
          class ExtractKey, class EqualKey,
          class Alloc> 	
class hashtable {
public: 
    typedef HashFcn hasher;
    typedef EqualKey key_equal;
    typedef size_t            size_type;

private:
    // 以下三者都是function objects。<stl_hash_fun.h> 中定義有數個
    // 標準型別（如int,c-style string 等）的hasher。
    hasher hash;	
    key_equal equals;
    ExtractKey get_key;

    typedef __hashtable_node<Value> node;
    vector<node*,Alloc> buckets;	// 以 vector 完成
    size_type num_elements;
public:
    size_type bucket_count() const {return buckets.size();}
    ...
};
```
其中`__hashtable_node`的定义如下：
```c++
template<class Value> struct __hashtable_node {
    __hashtable_node* next;
    Value val;
};
```

