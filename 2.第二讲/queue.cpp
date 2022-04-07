//
// Created by Jarson's mac on 2022/4/4.
//
#include <queue>
#include <string>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "test.h"
using namespace std;

/**
 *
 *队列采用先进先出：队尾入队，队头出队
 */
namespace jj18
{
    void test_queue(long& value)
    {
        cout << "\ntest_queue().........\n";
        queue<string> c;
        char buf[10];

        clock_t timeStart = clock();
        for(long i = 0; i < value; ++i)
        {
            //try-catch用于抓取异常（如果数据太多可能会要不到内存）
            try {
                snprintf(buf, 10, "%d", rand());
                c.push(string(buf));
            }
            catch(exception& p) {
                cout << "i =" << i << " " << p.what() << endl;
                abort();
            }
        }
        cout << "milli-seconds:" << (clock() - timeStart) << endl; //queue插入300000个随机数据所使用的时间:890ms
        cout << "queue.size() = " << c.size() << endl;//300000
        cout << "queue.front() = " << c.front() << endl;//12074
        cout << "queue.back() = " << c.back() << endl;//14585
        c.pop();//出队
        cout << "queue.size() = " << c.size() << endl;//299999
        cout << "queue.front() = " << c.front() << endl;//6888 改变了，代表从队头出队
        cout << "queue.back() = " << c.back() << endl;//14585 没有变，代表从队头出队
    }
}



