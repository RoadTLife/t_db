
#pragma once


/**
 * @brief 支持以缓存模式写入数据到文件/socket
 * @details 缓存使用ring buffer实现，当缓存满时会自动刷新缓存。
 * 看起来直接使用fdopen也可以实现缓存写，不过fdopen会在close时直接关闭fd。
 * @note 在执行close时，描述符fd并不会被关闭
 */
class BufferedWriter
{
public:
  BufferedWriter(int fd);
  BufferedWriter(int fd, int32_t size);
  ~BufferedWriter();

  /**
   * @brief 关闭缓存
   */
  bool close();

  /**
   * @brief 写数据到文件/socket
   * @details 缓存满会自动刷新缓存
   * @param data 要写入的数据
   * @param size 要写入的数据大小
   * @param write_size 实际写入的数据大小
   */
  bool write(const char *data, int32_t size, int32_t &write_size);

  /**
   * @brief 写数据到文件/socket，全部写入成功返回成功
   * @details 与write的区别就是会尝试一直写直到写成成功或者有不可恢复的错误
   * @param data 要写入的数据
   * @param size 要写入的数据大小
   */
  bool writen(const char *data, int32_t size);

  /**
   * @brief 刷新缓存
   * @details 将缓存中的数据全部写入文件/socket
   */
  bool flush();

private:
  /**
   * @brief 刷新缓存
   * @details 期望缓存可以刷新size大小的数据，实际刷新的数据量可能小于size也可能大于size。
   * 通常是在缓存满的时候，希望刷新掉一部分数据，然后继续写入。
   * @param size 期望刷新的数据大小
   */
  bool flush_internal(int32_t size);

private:
  int        fd_ = -1;
};