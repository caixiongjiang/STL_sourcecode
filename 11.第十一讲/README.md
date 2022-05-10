## 第十一讲：set/multiset & map/multimap深度探索

### set和multiset特性
* set/multiset以红黑树为底层结构，因此有自动排序的特性，排序的依据是key，而set和multiset的value和key
是合二为一的：value就是key（key和data合成value）
* set和multiset提供遍历的操作以及iterator，按照正常的规则遍历就能获得排序状态。
* 无法使用iterator来改变元素值（**底层为将iterator设为const**），因为key有其严谨的排序规则。
* set的key必须独一无二，因此其insert()用的是rb_tree的insert_unique()
* multiset元素的key可以重复，因此其insert()用的是rb_tree的insert_equal()

### set容器

模版定义：（GNU2.9）
```c++
//set默认采用key值降序排列
template <class Key, class Compare = less<Key>, class Alloc = alloc>
class set {
public:
    // typedefs:
    typedef Key key_type;
    typedef Key value_type;
    // 注意，以下 key_compare 和 value_compare 使用相同的比較函式
    typedef Compare key_compare;
    typedef Compare value_compare;
private:
    typedef rb_tree<key_type, value_type, 
                     identity<value_type>, key_compare, Alloc> rep_type;
    rep_type t;  // 采用紅黑树（RB-tree）來表現 set
public:
    typedef typename rep_type::const_iterator iterator;//这里的迭代器不能改变
    //set的所有操作都转而呼叫底层（红黑树）的操作
    ...
```

### multiset容器
除了multiset之外和set基本没有区别

### map和multimap特性
* rb_tree为底层结构，因此有元素自动排序功能,排序的依据依然为key
* 提供iterator，正常遍历便能获得排序状态的结果
* 无法使用iterators来改变元素的key，但可以用来改变元素的data。（**底层为将key值设为const类型**）
* map的key必须独一无二，因此其insert()用的是rb_tree的insert_unique()
* multimap元素的key可以重复，因此其insert()用的是rb_tree的insert_equal()

### map容器

模版定义：（GNU2.9）
```c++
template <class Key, class T, class Compare = less<Key>, class Alloc = alloc>
class map {
public:
    // typedefs:

    typedef Key key_type;	// 鍵值型別
    typedef T data_type;		// 資料（真值）型別
    typedef T mapped_type;	
    typedef pair<const Key, T> value_type;	// 元素型別（鍵值/真值）注意key值为const
    typedef Compare key_compare;	// 鍵值比較函式
private:
    // 以下定義表述型別（representation type）。以map元素型別（一個pair）
    // 的第一型別，做為RB-tree節點的鍵值型別。
    typedef rb_tree<key_type, value_type, 
                  select1st<value_type>, key_compare, Alloc> rep_type;
    rep_type t;  // 以紅黑樹（RB-tree）表現 map
public:
    typedef typename rep_type::iterator iterator;
    ...
```

**调用map发生的事情**：
```markdown
map<int, string> imap;  
==>  map<int, string, less<int>, alloc> imap;
==>  template<int; pair<const int, string>select1st<pair<const int, string>>, less<int>, alloc> imap;
```
**select1st<value_type>代表的是拿出value类型中第一个类型，也就是key的类型**

#### map独特的operator[]
* operator[]的作用为返回对应key的data值，**如果这个key不存在，标准库将会自动创建该key值放入map中**
* 源码层：使用lower_bound来寻找元素的key值，如果找到则返回迭代器进行操作；如果没有找到则呼叫insert()
* lower_bound是二分查找的一种版本，试图在已经排序的范围[first, last)中寻找一个元素值，如果找得到就返回
一个iterator指向其中的第一个符合条件的元素值；如果没有找到则返回last的iterator（最适合安插这个值的位置）
* **operator[]创建新的key比直接使用insert插入效率低**，因为前面还多了一步lower_bound的过程
### multimap
multimap使用和map类似