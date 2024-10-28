#ifndef STORAGE_TDB_DB_DB_IMPL_H_
#define STORAGE_TDB_DB_DB_IMPL_H_

#include "graph/graph.h"
#include "graph/env.h"

namespace tdb
{
// 定义对象 Vertex 和 Edge 两个集合


class DBImpl : public DB {
 public:
  DBImpl(const std::string& path, const std::string& name);

  DBImpl(const DBImpl& db) = delete;
  DBImpl& operator=(const DBImpl& db) = delete;

  ~DBImpl() override;

  void DropAllNode();

  void DropAllEdge();
  
  bool AddVertexLabel(const std::string &label);


private:
  Env env_;
  std::string path_;
  std::string name_;


};
    
} // namespace tdb


#endif