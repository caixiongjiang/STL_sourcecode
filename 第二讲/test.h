//
// Created by Jarson's mac on 2022/4/4.
//

#include <iostream>

using std::cin;
using std::cout;
using std::string;

long get_a_target_long()
{
    long target = 0;
    cout << "target (0~" << RAND_MAX << "):";
    return target;
}

string get_a_target_string()
{
    long target = 0;
    char buf[10];
    cout << "target (0~" << RAND_MAX << "):";
    cin >> target;
    //snprintf功能为格式化成字符串
    // 1-- 目标字符串 2 -- 拷贝字节数 3 -- 格式化成字符串。4 -- 可变参数。
    snprintf(buf, 10, "%d", target);
    return string(buf);
}
//比较两个long数据是否相等
int compareLongs(const void* a, const void* b)
{
    return (*(long*)a - *(long*)b);
}
//比较两个string数据是否相等
int compareStrings(const void* a, const void* b)
{
    if(*(string*)a > *(string*)b)
    return 1;
    else if(*(string*)a < *(string*)b)
        return -1;
    else
        return 0;
}
