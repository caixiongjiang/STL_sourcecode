//
// Created by Jarson's mac on 2022/4/4.
//
#include <ext/slist>
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
 * slist与forward_list都为单向链表
 * 区别就是slist很久之前就有，不属于标准库里的内容
 * 而forward_list是c++11新增的，属于标准库里的内容
 */
namespace jj10
{
    void test_slist(long& value)
    {
        cout << "\ntest_slist().........\n";

        __gnu_cxx::slist<string> c;
        char buf[10];

        clock_t timeStart = clock();
        for(long i = 0; i < value; ++i)
        {
            //try-catch用于抓取异常（如果数据太多可能会要不到内存）
            try {
                snprintf(buf, 10, "%d", rand());
                c.push_front(string(buf));//使用前插法构建
            }
            catch(exception& p) {
                cout << "i =" << i << " " << p.what() << endl;
                abort();
            }
        }
        cout << "milli-seconds:" << (clock() - timeStart) << endl; //slist插入1000000个随机数据所使用的时间:3046ms

    }
}

