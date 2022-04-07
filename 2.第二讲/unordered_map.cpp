//
// Created by Jarson's mac on 2022/4/7.
//
#include <unordered_map>
#include <string>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "test.h"
using namespace std;

/**
 *
 * 底层结构为hashtable
 * if(元素的个数 >= 篮子的个数)  { 篮子就要重新扩充成大约原来的两倍的数量 }
 */
namespace jj09
{
    void test_unordered_map(long& value)
    {
        cout << "\ntest_unordered_map().........\n";
        unordered_map<long, string> c;
        char buf[10];

        clock_t timeStart = clock();
        for(long i = 0; i < value; ++i)
        {
            //try-catch用于抓取异常（如果数据太多可能会要不到内存）
            try {
                snprintf(buf, 10, "%d", rand());
                //multimap不可使用[]做insertion(map可以这么使用)
                c.insert(pair<long, string>(i, buf));
            }
            catch(exception& p) {
                cout << "i =" << i << " " << p.what() << endl;
                abort();
            }
        }
        cout << "milli-seconds:" << (clock() - timeStart) << endl; //unordered_map插入1000000个随机数据所使用的时间:4313ms
        cout << "unordered_map.size() = " << c.size() << endl;//1000000
        cout << "unordered_map.max_size() = " << c.max_size() << endl;//357913941


        long target = get_a_target_long();//target:23456

        //使用c.find()
        timeStart = clock();
        auto pItem = c.find(target);
        cout << "c.find(), milli-seconds:" << (clock() - timeStart) << endl;//使用c.find算法找target的时间：0ms
        if (pItem != c.end())
            cout << "found, key = " << (*pItem).first << "value = " << (*pItem).second << endl;//found，key = 23456 value = 15962
        else
            cout << "not found! " << endl;
    }
}



