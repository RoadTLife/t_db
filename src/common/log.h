#pragma once

#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <string>

#include "../lang/iostream.h"
#include "../lang/fstream.h"

namespace common
{

  // 静态常量
  const int LOG_STATUS_OK = 0;
  const int LOG_STATUS_ERR = 1;

  // 日志级别
  typedef enum
  {
    LOG_LEVEL_DEBUG = 0,
    LOG_LEVEL_INFO = 1,
    LOG_LEVEL_WARN = 2,
    LOG_LEVEL_ERROR = 3,
  } LOG_LEVEL;

  class Log
  {
  public:
    Log(const string &log_name, const LOG_LEVEL log_level = LOG_LEVEL_INFO,
        const LOG_LEVEL console_level = LOG_LEVEL_WARN);
    ~Log(void);

    static int init(const string &log_file);

    template <class T>
    Log &operator<<(T message);

    template <class T>
    int error(T message);

    template <class T>
    int warnning(T message);

    template <class T>
    int info(T message);

    template <class T>
    int debug(T message);

    // 设置控制台level
    int set_console_level(const LOG_LEVEL console_level);

    LOG_LEVEL get_console_level();

    // 设置log 的level
    int set_log_level(const LOG_LEVEL log_level);

    LOG_LEVEL get_log_level();

    int output(const LOG_LEVEL level, const char *module, const char *prefix, const char *f, ...);

    bool check_output(const LOG_LEVEL log_level, const char *module);

    intptr_t context_id();

  private:
    pthread_mutex_t lock_;
    ofstream ofs_;
    string log_name_;
    LOG_LEVEL log_level_;
    LOG_LEVEL console_level_;
  };

  // 只是声明 不定义
  extern Log *g_log;

// log header的长度
#define LOG_HEAD_SIZE 128

#define LOG_HEAD(prefix, level)                                              \
  if (common::g_log)                                                         \
  {                                                                          \
    struct timeval tv;                                                       \
    gettimeofday(&tv, NULL);                                                 \
    struct tm curr_time;                                                     \
    struct tm *p = localtime_r(&tv.tv_sec, &curr_time);                      \
                                                                             \
    char sz_head[LOG_HEAD_SIZE] = {0};                                       \
    if (p)                                                                   \
    {                                                                        \
      int usec = (int)tv.tv_usec;                                            \
      snprintf(sz_head,                                                      \
               LOG_HEAD_SIZE,                                                \
               "%04d-%02d-%02d %02d:%02d:%02u.%06d pid:%u tid:%llx ctx:%lx", \
               p->tm_year + 1900,                                            \
               p->tm_mon + 1,                                                \
               p->tm_mday,                                                   \
               p->tm_hour,                                                   \
               p->tm_min,                                                    \
               p->tm_sec,                                                    \
               usec,                                                         \
               (int32_t)getpid(),                                            \
               gettid(),                                                     \
               common::g_log->context_id());                                 \
      common::g_log->rotate(p->tm_year + 1900, p->tm_mon + 1, p->tm_mday);   \
    }                                                                        \
    snprintf(prefix,                                                         \
             sizeof(prefix),                                                 \
             "[%s %s %s@%s:%u] >> ",                                         \
             sz_head,                                                        \
             (common::g_log)->prefix_msg(level),                             \
             __FUNCTION__,                                                   \
             __FILE_NAME__,                                                  \
             (int32_t)__LINE__);                                             \
  }

// 定义了宏方法
#define LOG_OUTPUT(level, fmt, ...)                                    \
  do                                                                   \
  {                                                                    \
    using namespace common;                                            \
    if (g_log && g_log->check_output(level, __FILE_NAME__))            \
    {                                                                  \
      char prefix[ONE_KILO] = {0};                                     \
      LOG_HEAD(prefix, level);                                         \
      g_log->output(level, __FILE_NAME__, prefix, fmt, ##__VA_ARGS__); \
    }                                                                  \
  } while (0)

// fmt 是传递给宏的字符串  ##__VA_ARGS__是一个特殊的预处理操作符，用于处理可变参数宏中的参数。
// LOG_OUTPUT是另外一个宏 __VA_ARGS__代表所有传递给LOG_DEBUG宏的额外参数（除了fmt之外）
#define LOG_DEFAULT(fmt, ...) LOG_OUTPUT(common::g_log->get_log_level(), fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) LOG_OUTPUT(common::LOG_LEVEL_ERROR, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) LOG_OUTPUT(common::LOG_LEVEL_WARN, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) LOG_OUTPUT(common::LOG_LEVEL_INFO, fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...) LOG_OUTPUT(common::LOG_LEVEL_DEBUG, fmt, ##__VA_ARGS__)

  // 定义模板实现
  template <class T>
  Log &Log::operator(T message)
  {
    // at this time, the input level is the default log level
    out(console_level_, log_level_, message);
    return *this;
  }

  // 定义模板实现
  template <class T>
  Log &Log::error(T message)
  {
    // at this time, the input level is the default log level
    out(LOG_LEVEL_ERROR, LOG_LEVEL_ERROR, message);
    return *this;
  }

  template <class T>
  int Log::warnning(T message)
  {
    return out(LOG_LEVEL_WARN, LOG_LEVEL_WARN, message);
  }

  template <class T>
  int Log::info(T message)
  {
    return out(LOG_LEVEL_INFO, LOG_LEVEL_INFO, message);
  }

  template <class T>
  int Log::debug(T message)
  {
    return out(LOG_LEVEL_DEBUG, LOG_LEVEL_DEBUG, message);
  }

  // 模板函数 最终out的实现
  template <class T>
  int Log::out(const LOG_LEVEL console_level, const LOG_LEVEL log_level, T &message)
  {
    bool locked = false;
    if (console_level > console_level_)
    {
      return LOG_STATUS_OK;
    }

    try
    {
      char prefix[ONE_KILO] = {0};
      LOG_HEAD(prefix, log_level);
      if (LOG_LEVEL_PANIC <= console_level && console_level <= console_level_)
      {
        cout << prefix_map_[console_level] << message;
      }

      if (LOG_LEVEL_PANIC <= log_level && log_level <= log_level_)
      {
        pthread_mutex_lock(&lock_);
        locked = true;
        ofs_ << prefix;
        ofs_ << message;
        ofs_.flush();
        log_line_++;
        pthread_mutex_unlock(&lock_);
        locked = false;
      }
    }
    catch (exception &e)
    {
      if (locked)
      {
        pthread_mutex_unlock(&lock_);
      }
      cerr << e.what() << endl;
      return LOG_STATUS_ERR;
    }

    return LOG_STATUS_OK;
  }

} // namespace name
