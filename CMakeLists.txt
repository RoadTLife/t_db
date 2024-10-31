cmake_minimum_required(VERSION 3.10)
project(t_graph_db)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})  # 定义ROOT_DIR变量
set(GRAPH_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

option(TDB_BUILD_TESTS "Build TDB's unit tests" ON)

# 添加头文件
include_directories(
    ${GRAPH_INCLUDE_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/src/server # 添加 server 目录
)
 # This project is tested using GoogleTest.
# add_subdirectory(third_party/googletest)

set(DIR_SRCS 
    src/server/entry_point.cpp  # 假设主源文件是main.cpp，位于src目录下
    src/server/tdb_server.cpp
    # 其他源文件...
)

add_executable(server ${DIR_SRCS})

# 测试相关设置（如果想要包含测试）
if (TDB_BUILD_TESTS)
    #add_subdirectory("third_party/googletest")  # 假设测试代码在test目录下，并在此处添加子目录以构建测试目标
endif (TDB_BUILD_TESTS)