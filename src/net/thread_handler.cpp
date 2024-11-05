#include <string.h>

#include "thread_handler.h"
#include "../common/log.h"
#include "../lang/string.h"


ThreadHandler * ThreadHandler::create(const char *name)
{

  // 线程池
  const char *default_name = "one-thread-per-connection";
  if (nullptr == name || common::is_blank(name)) {
    name = default_name;
  }

  // 忽略大小写比较
  if (0 == strcasecmp(name, default_name)) {
    return new OneThreadPerConnectionThreadHandler();
  } else if (0 == strcasecmp(name, "java-thread-pool")) {
    //return new JavaThreadPoolThreadHandler();
    // TODO: 未实现
    return nullptr;
  } else {
    LOG_ERROR("unknown thread handler: %s", name);
    return nullptr;
  }
}