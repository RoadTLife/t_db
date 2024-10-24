# T_DB Architecture

整体结构可以参考neo4j的形式，但是存储引擎进行改良，将其存储的链表形式换成block的形式

## 存储(Store)
* 存储设计方案：
  * 原生存储
    * 优点：查询性能O(1)复杂度 快于lsm-tree的O(log n)，存储采用免索引链接的方式。
    * 缺点：相对采用第三方其实现复杂度高，工程化量较大

  * 采用lsm-tree存储
    * 优点：目前主流的存储方案，各大图数据库基础存储引擎基本采用这个方案，利于增删大的业务场景，并且方便与raft的日志复制机制结合
    * 缺点：性能相对较差


* 参考论文:
* https://pacman.cs.tsinghua.edu.cn/~cwg/publication/livegraph-2020/livegraph-2020.pdf  蚂蚁-陈文光教授的
  疑问点：论文中提的原生存储的方案，但是tugraph源码采用的是LSM-Tree 存储。也有可能代码也有看懂，需要好好研究。

* https://www.microsoft.com/en-us/research/publication/log-structured-merge-lsm-tree/



## 索引(Index) 

## 查询(Query)

## 事务(Tx)

## 分布式
### 共识
* raft
* paxos

## 单元测试
* 采用google test 测试框架进行单元测试
  官方地址： https://github.com/google/googletest
