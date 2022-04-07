//
// Created by Jarson's mac on 2022/4/4.
//
#include <deque>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <algorithm>
#include "test.h"
using namespace std;

/**
 *
 *
 */
namespace jj05
{
    void test_deque(long& value)
    {
        cout << "\ntest_deque().........\n";
        deque<string> c;
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
        cout << "milli-seconds:" << (clock() - timeStart) << endl; //deque插入1000000个随机数据所使用的时间:2704ms
        cout << "deque.size() = " << c.size() << endl;//1000000
        cout << "deque.front() = " << c.front() << endl;//5249
        cout << "deque.back() = " << c.back() << endl;//1098
        cout << "deque.max_size() = " << c.max_size() << endl;//表示最大可以放1073741823


        string target = get_a_target_string();//target:23456
        //使用find
        timeStart = clock();
        auto pItem = ::find(c.begin(), c.end(), target);//返回值是一个对应的迭代器
        cout << "::find(), milli-seconds:" << (clock() - timeStart) << endl;//使用find算法找target的时间：15ms

        if (pItem != c.end())
            cout << "found, " << *pItem << endl;//found，23456
        else
            cout << "not found! " << endl;

        //使用sort()
        timeStart = clock();
        sort(c.begin(), c.end());//全局sort()
        cout << "::sort(), milli-seconds:" << (clock() - timeStart) << endl;//使用sort()算法的时间：3110ms
    }
}

