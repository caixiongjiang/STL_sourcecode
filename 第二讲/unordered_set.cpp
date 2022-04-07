//
// Created by Jarson's mac on 2022/4/7.
//
#include <unordered_set>
#include <string>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "test.h"
#include <algorithm>
using namespace std;

/**
 *
 * 底层结构为hashtable
 * if(元素的个数 >= 篮子的个数)  { 篮子就要重新扩充成大约原来的两倍的数量 }
 */
namespace jj08
{
    void test_unordered_set(long& value)
    {
        cout << "\ntest_unordered_set().........\n";
        unordered_set<string> c;
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
        cout << "milli-seconds:" << (clock() - timeStart) << endl; //unordered_set插入1000000个随机数据所使用的时间:4406ms
        cout << "unordered_set.size() = " << c.size() << endl;//1000000
        cout << "unordered_set.max_size() = " << c.max_size() << endl;//357913941
        cout << "unordered_set.bucket_count() = " << c.bucket_count() << endl;//篮子的个数（其实就是每个链表前面的格子，一定比元素多）：1056323
        cout << "unordered_set.load_factor() = " << c.load_factor() << endl;//载重因子：0.94668
        cout << "unordered_set.max_load_factor() = " << c.max_load_factor() << endl;//最大的载重因子恒定为1
        cout << "unordered_set.max_bucket_count() = " << c.max_bucket_count() << endl;//最大篮子数量：357913941

        //输出前20个篮子，每个篮子后面跟着多少个元素
        for(unsigned i = 0; i < 20; ++i) {
            cout << "bucket #" << i << "has" << c.bucket_size(i) << "elements.\n";
        }

        string target = get_a_target_string();//target:23456
        //使用::find()
        {
            timeStart = clock();
            auto pItem = ::find(c.begin(), c.end(), target);//比c.find()慢很多
            cout << "::find(), milli-seconds:" << (clock() - timeStart) << endl;//使用全局find算法找target的时间：109ms

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


