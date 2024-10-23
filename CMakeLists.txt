cmake_minimum_required(VERSION 3.13)
project(t_graph_db)

set(GRAPH_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

# 添加头文件
include_directories(${GRAPH_INCLUDE_DIR})


aux_source_directory(${ROOT_DIR}/src DIR_SRCS)

add_executable(server ${DIR_SRCS})

# unit_test
# if (WITH_TESTS)
#     add_subdirectory(test)
# endif (WITH_TESTS)
