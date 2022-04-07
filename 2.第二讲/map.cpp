//
// Created by Jarson's mac on 2022/4/7.
//
#include <map>
#include <string>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "test.h"
using namespace std;

/**
 *
 * 底层结构为红黑树
 *
 */
namespace jj09
{
    void test_map(long& value)
    {
        cout << "\ntest_map().........\n";
        map<long, string> c;
        char buf[10];

        clock_t timeStart = clock();
        for(long i = 0; i < value; ++i)
        {
            //try-catch用于抓取异常（如果数据太多可能会要不到内存）
            try {
                snprintf(buf, 10, "%d", rand());
                //使用[]来访问内存
                c[i] = string(buf);
            }
            catch(exception& p) {
                cout << "i =" << i << " " << p.what() << endl;
                abort();
            }
        }
        cout << "milli-seconds:" << (clock() - timeStart) << endl; //map插入1000000个随机数据所使用的时间:4890ms
        cout << "map.size() = " << c.size() << endl;//因为key值不同时，可以放入；key值相同时不能放入；//1000000
        cout << "map.max_size() = " << c.max_size() << endl;//178956970


        long target = get_a_target_long();//target:23456

        //使用c.find()
        timeStart = clock();
        auto pItem = c.find(target);
        cout << "c.find(), milli-seconds:" << (clock() - timeStart) << endl;//使用c.find算法找target的时间：0ms
        if (pItem != c.end())
            cout << "found, key = " << (*pItem).first << "value = " << (*pItem).second << endl;//found，key = 23456 value = 19128
        else
            cout << "not found! " << endl;
    }
}
