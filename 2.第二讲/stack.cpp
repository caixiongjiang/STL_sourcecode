//
// Created by Jarson's mac on 2022/4/4.
//
#include <stack>
#include <string>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "test.h"
using namespace std;

/**
 *
 *栈采用后进后出：后入栈的先出栈（都从栈顶出）
 */
namespace jj17
{
    void test_stack(long& value)
    {
        cout << "\ntest_stack().........\n";
        stack<string> c;
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
        cout << "milli-seconds:" << (clock() - timeStart) << endl; //stack插入300000个随机数据所使用的时间:812ms
        cout << "stack.size() = " << c.size() << endl;//300000
        cout << "stack.top() = " << c.top() << endl;//23929
        c.pop();//出栈
        cout << "stack.size() = " << c.size() << endl;//299999
        cout << "stack.top() = " << c.top() << endl;//12911 代表确实将栈顶元素出栈了
    }
}


