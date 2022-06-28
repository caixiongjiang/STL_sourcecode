## 第十三讲：heap深入探索
### heap概述
heap不是STL容器组件，它是扮演`priority queue`的助手。`priority queue`允许用户以任何次序将任何元素推入容器中，
但取出时一定是从优先权最高的元素开始取。`binary max heap`正具有这样的特性，适合作为`priority queue`的底层机制。

`priority queue`选用`binary heap`来实现，它是一种`完全二叉树`，也就是说除了最底层的叶子节点之外，是填满的，且
最底层的叶节点由左至右不能右空隙。因为整棵树没有任何节点漏洞，我们可以使用array来存储所有的节点。
> binary heap是一颗完全二叉树，那么它就具备完全二叉树的特点：当某个节点位于array的i处，其左子节点必位于array的
2i处，其右子节点一定位于array的2i+1处，其父节点必定位于"i/2"处。

`binary heap`使用一个array（保存数据）和一组heap算法（用来插入元素、删除元素、取极值）。这种使用array表述
tree的方式，被称为`隐式表达`。

![](img13_1.png)

当然heap要能动态的改变大小，所以用vector存储数据会更好。
> heap可以分为max-heap以及min-heap，前者每个节点的键值都大于或等于其子节点键值，后者的每个节点键值都小于或
等于其子节点键值。可以推出，max-heap的最大键值在根节点，min-heap的最小键值在根节点。

### heap算法
#### push_heap算法
在很多书籍当中，通常通过一个上浮的操作来完成push_heap。其基本原理可见下图（假设新加入的元素是50）：

![](img13_2.png)

1.将50插入到数组的末尾。

2.将其于父元素相比较，发现24小于50，交换这两个元素。上浮一次

3.继续上述操作直到找到一个合适的位置，也即其父元素大于50的位置，则上浮结束。

一个简易的c++实现：
```c++
template<typename T>
void push_heap(std::vector<T> &vec, T value)
{
	vec.push_back(value);
	int i = vec.size()-1;
	while (i > 1 && vec[i] > vec[i / 2]) {
		std::swap(vec[i], vec[i / 2]);
		i = i / 2;
	}
}
```
#### pop_heap算法
pop操作是类似的：

![](img13_3.png)

1.将最后一个元素与第一个元素（根元素）交换。

2.删除最后一个元素。

3.将第一个元素/根元素下沉到一个合适的位置。**注意下沉的时候是与子节点较大的那个元素交换**。

一个简单的c++实现：
```c++
template<typename T>
T pop_heap(std::vector<T> &vec)
{
	int i = 1;
	//将最后元素与第一个元素(根元素)交换, 然后删除最后一个元素
	std::swap(vec[1], vec[vec.size() - 1]);
	T v = vec[vec.size() - 1];
	vec.pop_back();

	//将现在的第一个元素/根元素下沉到一个合适的位置
	while (2 * i < vec.size()) {
		int j = 2 * i;	//左子节点
		if (j < vec.size() - 1 && vec[j] < vec[j + 1]) j++;
		if (vec[j] < vec[i]) break;
		std::swap(vec[i], vec[j]);
		i = j;
	}
	return v;
}
```
#### sort_heap算法
既然每次`pop_heap`可获得`heap`中键值最大的元素，如果持续对整个`heap`做`pop_heap`操作，
每次将操作范围从后向前缩减一个元素（因为`pop_heap`会把键值最大的元素放在底部容器的最尾端），
当整个程序执行完毕时，我们便有了一个递增序列。下图所示的是`sort_heap`的实际操演情况。

![](img13_4.png)
![](img13_5.png)
![](img13_6.png)

> 可以看到不断对heap进行pop操作，便可达到排序效果

一个简单的c++实现：
```c++
template<typename T>
void sort_heap(std::vector<T> &vec)
{
	std::vector<T> temvec;
	int size = vec.size()-1;
	while (size != 0) {
		temvec.push_back(pop_heap(vec));
		size--;
	}
	for (T value : temvec) {
		vec.push_back(value);
	}
}
```
#### make_heap算法
这个算法是将一段现有的数据转化为一个heap，主要依据就是前面所说的`隐式表达`。

#### heap没有迭代器
因为heap的结构是一个完全二叉树，类似于红黑树，我们都不能对它进行遍历，这样会造成heap结构的破坏，因此它也就没有迭代器。