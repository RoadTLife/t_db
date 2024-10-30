cmake_minimum_required(VERSION 3.10)
project(t_graph_db)

set(ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})  # 定义ROOT_DIR变量
set(GRAPH_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

# 添加头文件
include_directories(${GRAPH_INCLUDE_DIR})

 # This project is tested using GoogleTest.
# add_subdirectory(third_party/googletest)

set(DIR_SRCS 
    src/server/entry_point.cpp  # 假设主源文件是main.cpp，位于src目录下
    # 其他源文件...
)

add_executable(server ${DIR_SRCS})

# 测试相关设置（如果想要包含测试）
option(WITH_TESTS "Build tests" ON)  # 定义一个选项来开启或关闭测试构建
if (WITH_TESTS)
    #add_subdirectory(test)  # 假设测试代码在test目录下，并在此处添加子目录以构建测试目标
endif (WITH_TESTS)