#ifndef STORAGE_TDB_INCLUDE_DB_H_
#define STORAGE_TDB_INCLUDE_DB_H_

#include "graph/export.h"
#include "graph/status.h"

// 定义命名数据库命名空间为tdb
namespace tdb {

struct Options;


class TDB_EXPORT DB {
public:
    static Status Open(const Options &options, const std::string &dbname,
                      DB **dbptr);
                       DB() = default;

  DB(const DB&) = delete;
  DB& operator=(const DB&) = delete;

  virtual ~DB();
  
  /**
   * Close the graph. 
   */
  Status close();

  /**
   * Flushes buffered data to disk.
   */
  bool flush();

  /**
   * Get graphDb name
   */
  std::string GetGraphName();

  Status DestroyDB(); 

};

}

#endif