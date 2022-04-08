## 第四讲：深入理解分配器

### operator new() & malloc()
operator() new会调用malloc(), malloc()作用是分配内存。

看图：

![malloc()分配的内存视图](img1.jpg)
size部分为我们所需要的内存，可以看出malloc()分配的内存比所需要的内存多。**多分配的内存空间如果称为开销的话，也就是说我们的单个内存越大，开销所占比例就越小！**

### 分配器最重要的两个函数：allocate & deallocate

VC++下和BC++下：
```
申请内存：allocator-->operator new()-->malloc()
释放内存：deallocator-->operator delete()-->free()
```

分配512个int整数：
```c++
int *p = allocator<int>().allocate(512, (int*)0);
allocator<int>().deallocate(p, 512);
```
注：*一个type +（）形成了一个临时对象，才能调用其中的成员函数。举例：`queue<int>()`*

#### alloc的优点

GNU2.9下：
```
申请内存：allocator-->allocate()-->operator new()-->malloc()
释放内存：deallocator-->deallocate()->operator delete()-->free()
```
注：*虽然GNU标准allocator被设计出来，但它的容器基本都不用标准的allocator，而是使用alloc*

![容器的分配器](img2.jpg)

![运行过程](img3.jpg)

* **使用malloc()和free()会带来很大的额外开销，如果区块小，开销比例会很大。**
* **额外开销中的cookie记录内存的大小，但因为容器元素的大小是一样的，所以alloc使用一个长链表（i = 0～15），第i个对应cookie大小为8(i + 1)Bytes的内存大小，容器的内存大小会被调整为8的倍数，这样就只需要用少量cookie来记录内存大小！**
* 所以使用alloc存放1000000个元素，可以省掉cookie开销大约8000000个Bytes

GNU4.9下：
* 容器使用的分配器又变为了allocator，继承于new_allocator，使用operator new() 和 operator delete()
* 2.9下的alloc被更名为__pool_alloc，属于__gnu_cxx::__pool_alloc