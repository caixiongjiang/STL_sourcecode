cmake_minimum_required(VERSION 3.21)
project(STL_source_code)

set(CMAKE_CXX_STANDARD 14)


# 遍历项目根目录下所有的 .cpp 文件
file (GLOB_RECURSE files *.cpp)
foreach (file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    add_executable (${exe} ${file} 第二讲/list.cpp 第二讲/forward_list.cpp 第二讲/slist.cpp 第二讲/deque.cpp 第二讲/stack.cpp 第二讲/queue.cpp)
    message (\ \ \ \ --\ src/${exe}.cpp\ will\ be\ compiled\ to\ bin/${exe})
endforeach ()