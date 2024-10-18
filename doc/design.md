# T_DB Architecture

## 存储(Store)
* 存储设计方案：
  * 原生存储
    * 优点：查询性能O(1)复杂度 快于lsm-tree的O(log n)，存储采用免索引链接的方式。
    * 缺点：相对采用第三方其实现复杂度高，工程化量较大

  * 采用lsm-tree存储
    * 优点：目前主流的存储方案，各大图数据库基础存储引擎基本采用这个方案，利于增删大的业务场景，并且方便与raft的日志复制机制结合
    * 缺点：性能相对较差

## 索引(Index) 

## 查询(Query)

## 事务(Tx)

## 单元测试
* 采用google test 测试框架进行单元测试
  官方地址： https://github.com/google/googletest
