//
// Created by Jarson's mac on 2022/4/4.
//

#include <array>  //c++11之后将array封装成了一个类
#include <iostream>
#include <ctime>
#include <cstdio>
#include <stdlib.h>
#include "test.h"

#define ASIZE 500000
using namespace std;

namespace jj01
{
    void test_array()
    {
        cout << "\ntest_array()..........\n";

        array<long, ASIZE> c;
        clock_t timeStart = clock();//当前时间
        for(long i = 0; i < ASIZE; ++i) {
            c[i] = rand();
        }
        cout << "milli-seconds:" << (clock() - timeStart) << endl; //放500000个随机数所使用的时间:47ms
        cout << "array.size() = " << c.size() << endl;//500000
        cout << "array.front() = " << c.front() << endl;//3557
        cout << "array.back() = " << c.back() << endl;//23084
        cout << "array.data() = " << c.data() << endl;//表示数组在内存中起点的地址：0x47a20

        long target = get_a_target_long(); //输入200000, 找这个数

        timeStart = clock();
        //qsort(快速排序)：1--数组的起点地址 2--元素个数 3--每个元素的大小 4--比大小的规则
        qsort(c.data(), ASIZE, sizeof(long), compareLongs);
        //bsearch（二分查找）：1--目标数 2--起始地址 3--元素个数 4--每个元素的大小 5--比较的规则
        long* pItem = (long*) bsearch(&target, (c.data()), ASIZE, sizeof(long), compareLongs);
        cout << "qsort() + bsearch(), milli-seconds :" << (clock() - timeStart) << endl;//表示排序 + 搜索所使用的时间：187ms
        if(pItem != NULL)
            cout << "found, " << *pItem << endl;//found ，20000
        else
            cout << "not found !" << endl;
    }
}
