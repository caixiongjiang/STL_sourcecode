//
// Created by Jarson's mac on 2022/4/7.
//
#include <set>
#include <string>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "test.h"
#include <algorithm>
using namespace std;

/**
 *
 * 底层结构为红黑树
 *
 */
namespace jj13
{
    void test_set(long& value)
    {
        cout << "\ntest_set().........\n";
        set<string> c;
        char buf[10];

        clock_t timeStart = clock();
        for(long i = 0; i < value; ++i)
        {
            //try-catch用于抓取异常（如果数据太多可能会要不到内存）
            try {
                snprintf(buf, 10, "%d", rand());
                c.insert(string(buf));
            }
            catch(exception& p) {
                cout << "i =" << i << " " << p.what() << endl;
                abort();
            }
        }
        cout << "milli-seconds:" << (clock() - timeStart) << endl; //set插入1000000个随机数据所使用的时间:3922ms
        cout << "set.size() = " << c.size() << endl;//32768(因为重复的不能加入)
        cout << "set.max_size() = " << c.max_size() << endl;//214748364


        string target = get_a_target_string();//target:23456

        //使用::find()
        {
            timeStart = clock();
            auto pItem = ::find(c.begin(), c.end(), target);//比c.find()慢很多
            cout << "::find(), milli-seconds:" << (clock() - timeStart) << endl;//使用全局find算法找target的时间：0ms

            if (pItem != c.end())
                cout << "found, " << *pItem << endl;//found，23456
            else
                cout << "not found! " << endl;
        }

        //使用c.find()
        {
            timeStart = clock();
            auto pItem = c.find(target);//比::find()快很多
            cout << "c.find(), milli-seconds:" << (clock() - timeStart) << endl;//使用c.find算法找target的时间：0ms
            if (pItem != c.end())
                cout << "found, " << *pItem << endl;//found，23456
            else
                cout << "not found! " << endl;
        }
    }
}
