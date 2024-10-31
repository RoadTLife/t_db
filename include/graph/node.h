/**
 * @file node.h
 * @author tampopo
 * @brief 
 * 点类型的头文件，用于定义点类型的方法
 * 
 * @version 0.1
 * @date 2024-10-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once
#include <limits>
#include <cstdint>

namespace graph_api {

/**
 * @brief 点类型
 * TODO: 用户输入
 * 
 */
enum NodeType {
    Type_A,
    Type_B
};

class Node {

public:
    Node(int64_t id, NodeType type);

    int64_t getId() const;

};

}