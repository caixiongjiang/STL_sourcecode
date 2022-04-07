//
// Created by Jarson's mac on 2022/4/4.
//
#include <list>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <algorithm>
#include "test.h"

using namespace std;

/**
 *如果容器里自己提供了sort函数，那一定会比使用全局的sort()函数（包含在算法头文件里）来的快
 *
 */

namespace jj03
{
    void test_list(long& value)
    {
        cout << "\ntest_list().........\n";

        list<string> c;
        char buf[10];

        clock_t timeStart = clock();
        for(long i = 0; i < value; ++i)
        {
            //try-catch用于抓取异常（如果数据太多可能会要不到内存）
            try {
                snprintf(buf, 10, "%d", rand());
                c.push_back(string(buf));
            }
            catch(exception& p) {
                cout << "i =" << i << " " << p.what() << endl;
                abort();
            }
        }
        cout << "milli-seconds:" << (clock() - timeStart) << endl; //list插入1000000个随机数据所使用的时间:3265ms
        cout << "list.size() = " << c.size() << endl;//1000000
        cout << "list.max_size() = " << c.max_size() << endl;//最多可以放多少个数：357913941
        cout << "list.front() = " << c.front() << endl;//4710
        cout << "list.back() = " << c.back() << endl;//16410


        string target = get_a_target_string();//target:23456
        //使用find()找target
        timeStart = clock();
        auto pItem = ::find(c.begin(), c.end(), target);//返回值是一个对应的迭代器
        cout << "::find(), milli-seconds:" << (clock() - timeStart) << endl;//使用find算法找target的时间：16ms

        if (pItem != c.end())
            cout << "found, " << *pItem << endl;//found，23456
        else
            cout << "not found! " << endl;

        //使用sort()
        timeStart = clock();
        c.sort();//调用容器里的自己的sort()算法
        cout << "c.sort(),  milli-seconds:" << (clock() - timeStart) << endl;//使用sort()时间：2312ms

    }
}
