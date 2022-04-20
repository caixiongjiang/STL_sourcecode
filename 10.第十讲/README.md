## 第十讲：rb_tree深度探索

### 红黑树的结构
* 红黑树是平衡二分搜索树中常常使用的一种，平衡二分搜索树的特性：排列规则有利search和insert，并保持适度平衡。
* 红黑树提供遍历的功能及iterators。按正常规则（++ite）遍历，便能获得排序状态。
* 红黑树的结构样例：
    
    ![](img10_1.jpg)
    排序的状态为红黑树的中序遍历，begin()在左下，end()是在右下
* 红黑树的规则：
    * 1.每个节点不是红色就是黑色
    * 2.根节点为黑色
    * 3.如果节点为红，其子节点必须是黑
    * 4.任一节点至NULL(树尾端)的任何路径，所含黑色节点数必须相同

    ![](img10_2.jpg)
    *根据规则4，新增节点必须为红；根据规则3，新增节点之父节点必须为黑，当新节点根据二叉搜索树的规则到达其插入点，
但未能符合上述要求，就必须调整颜色并旋转树形*

* 我们不应该用红黑树的iterators改变元素值（因为元素有其严谨的排序规则）。但是编程层面并未阻止此事，rb_tree将会为set和map服务，而map允许元素的data被改变，
只有元素的key才是不能被改变的。
* rb_tree提供两种insertion操作（红黑树本身对重复与否没有限制，而取决于insert的方式）：insert_unique()和insert_equal()。前者表示节点的key一定在整个树中独一无二，
否则安插失败；后者表示节点的key可以重复。

部分源码（在这里将key和data合起来的节点合成value）：
```c++
//这里的Value是key和data的组合，如果value只传一个值说明没有value（set）
template <class Key, class Value, class KeyOfValue, class Compare,
          class Alloc = alloc>
class rb_tree {
protected:
    typedef __rb_tree_node<Value> rb_tree_node;//红黑树的结构
    ···
public:
     // 注意，没有定义iterator（喔，不，定义在后面）
    typedef rb_tree_node* link_type;//指向红黑树节点的指针
    ···
protected:
    //rb_tree只以三个资料表现它自己
    size_type node_count;//rb_tree的大小（节点数量）
    link_type header;
    Compare key_compare;//key的大小比较准则；应会是个function object
    ···
}
```

测试rb_tree（GNU2.9）:
```c++
rb_tree<int, int, identity<int>, less<int>> itree;
cout << itree.empty() << endl;//1
cout << itree.size() << endl;//0

itree.insert_unique(3);
itree.insert_unique(8);
itree.insert_unique(5);
itree.insert_unique(9);
itree.insert_unique(13);
itree.insert_unique(5);//无效，因为使用了insert_unique()函数
cout << itree.empty() << endl;//0
cout << itree.size() << endl;//5
cout << itree.count(5) << endl;//1

itree.insert_equal(5);
itree.insert_equal(5);
cout << itree.size() << endl;//7，因为使用了insert_equal()函数
cout << itree.count(5) << endl;//3
```
在GNU4.9下只是改变了名称：
```c++
_Rb_tree<int, int, identity<int>, less<int>> itree;
cout << itree.empty() << endl;//1
cout << itree.size() << endl;//0

itree._M_insert_unique(3);
itree._M_insert_unique(8);
itree._M_insert_unique(5);
itree._M_insert_unique(9);
itree._M_insert_unique(13);
itree._M_insert_unique(5);//无效，因为使用了_M_insert_unique()函数
cout << itree.empty() << endl;//0
cout << itree.size() << endl;//5
cout << itree.count(5) << endl;//1

itree._M_insert_equal(5);
itree._M_insert_equal(5);
cout << itree.size() << endl;//7，因为使用了_M_insert_equal()函数
cout << itree.count(5) << endl;//3
```
