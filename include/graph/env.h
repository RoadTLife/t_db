#ifndef STORAGE_TDB_INCLUDE_ENV_H_
#define STORAGE_TDB_INCLUDE_ENV_H_

#include <vector>
#include <string>
#include <cstdarg>

#include "graph/export.h"

namespace tdb {
class TDB_EXPORT Env {
 public:
  virtual ~Env() {}

 };

class TDB_EXPORT Logger {  
 public:
  Logger() = default;

  //删除了复制构造函数
  Logger(const Logger&) = delete;
  //代码删除了赋值操作符
  Logger& operator=(const Logger&) = delete;

  virtual ~Logger() {}

  virtual void Logv(const char* format, std::va_list ap) = 0;
};


}


#endif  // STORAGE_TDB_INCLUDE_ENV_H_