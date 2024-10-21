#include "graph/export.h"

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
    
};

}