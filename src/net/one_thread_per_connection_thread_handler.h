#include "./thread_handler.h"
#include "./mutex.h"
#include "./unordered_map.h"

class Worker;

/**
 * @brief 一个连接一个线程的线程模型
 * @ingroup ThreadHandler
 */
class OneThreadPerConnectionThreadHandler : public ThreadHandler
{
public:
  OneThreadPerConnectionThreadHandler() = default;
  virtual ~OneThreadPerConnectionThreadHandler();

  //! @copydoc ThreadHandler::start
  virtual bool start() override { return 1; }

  //! @copydoc ThreadHandler::stop
  virtual bool stop() override;
  //! @copydoc ThreadHandler::await_stop
  virtual bool await_stop() override;

  //! @copydoc ThreadHandler::new_connection
  virtual bool new_connection(Communicator *communicator) override;
  //! @copydoc ThreadHandler::close_connection
  virtual bool close_connection(Communicator *communicator) override;

private:
  /// 记录一个连接Communicator关联的线程数据
  unordered_map<Communicator *, Worker *> thread_map_;  // 当前编译器没有支持jthread
  /// 保护线程安全的锁
  mutex lock_;
};