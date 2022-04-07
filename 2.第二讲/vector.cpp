//
// Created by Jarson's mac on 2022/4/4.
//
#include <vector>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <algorithm>
#include "test.h"
using namespace std;

/**
 *vector的内存空间是两倍增长的 （每次都✖2）
 * 注意空间的成长不是在原来的地方进行扩容，而是另外找一个2倍大的地方将蒜素一个一个搬过去！！
 */
namespace jj02
{
    void test_vector(long& value)
    {
        cout << "\ntest_vector().........\n";

        vector<string> c;
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
        cout << "milli-seconds:" << (clock() - timeStart) << endl; //vector插入1000000个随机数据所使用的时间:3063ms
        cout << "vector.size() = " << c.size() << endl;//1000000
        cout << "vector.front() = " << c.front() << endl;//4047
        cout << "vector.back() = " << c.back() << endl;//2877
        cout << "vector.data() = " << c.data() << endl;//表示数组（vector）在内存中起点的地址：0x2880020
        cout << "vector.capacity() = " << c.capacity() << endl;//表示数组在内存中开辟的空间：1048576

        string target = get_a_target_string();//target:23456
        //使用find
        {
            timeStart = clock();
            auto pItem = ::find(c.begin(), c.end(), target);//返回值是一个对应的迭代器
            cout << "::find(), milli-seconds:" << (clock() - timeStart) << endl;//使用find算法找target的时间：0ms

            if (pItem != c.end())
                cout << "found, " << *pItem << endl;//found，23456
            else
                cout << "not found! " << endl;
        }

        //使用sort() + bsearch()
        {
            timeStart = clock();
            sort(c.begin(), c.end());//sort()将花掉大量的时间
            string *pItem = (string*) bsearch(&target, (c.data()), c.size(), sizeof(string), compareStrings);//返回值是一个string类型的指针
            cout << "sort() + bsearch(),  milli-seconds:" << (clock() - timeStart) << endl;//使用sort() + bsearch()算法找target的时间：2765ms

            if (pItem != NULL)
                cout << "found, " << *pItem << endl;
            else
                cout << "not found! " << endl;
        }
    }
}
