
#include <poll.h>

#include "./one_thread_per_connection_thread_handler.h"
#include "../common/log.h"
#include "../lang/thread.h"
#include "../lang/mutex.h"
#include "../lang/chrono.h"
#include "./communicator.h"

using namespace common;

class Worker
{
public:
  Worker(ThreadHandler &host, Communicator *communicator) 
    : host_(host), communicator_(communicator)
  {}
  ~Worker()
  {
    if (thread_ != nullptr) {
      stop();
      join();
    }
  }

  bool start()
  {
    thread_ = new thread(std::ref(*this));
    return 1;
  }

  bool stop()
  {
    running_ = false;
    return 1;
  }

  bool join()
  {
    if (thread_) {
      if (thread_->get_id() == this_thread::get_id()) {
        thread_->detach(); // 如果当前线程join当前线程，就会卡死
      } else {
        thread_->join();
      }
      delete thread_;
      thread_ = nullptr;
    }
    return 1;
  }

  void operator()()
  {
    LOG_INFO("worker thread start. communicator = %p", communicator_);
    int ret = thread_set_name("SQLWorker");
    if (ret != 0) {
      LOG_WARN("failed to set thread name. ret = %d", ret);
    }

    struct pollfd poll_fd;
    poll_fd.fd = communicator_->fd();
    poll_fd.events = POLLIN;
    poll_fd.revents = 0;

    while (running_) {
      int ret = poll(&poll_fd, 1, 500);
      if (ret < 0) {
        LOG_WARN("poll error. fd = %d, ret = %d, error=%s", poll_fd.fd, ret, strerror(errno));
        break;
      } else if (0 == ret) {
        // LOG_TRACE("poll timeout. fd = %d", poll_fd.fd);
        continue;
      }

      if (poll_fd.revents & (POLLERR | POLLHUP | POLLNVAL)) {
        LOG_WARN("poll error. fd = %d, revents = %d", poll_fd.fd, poll_fd.revents);
        break;
      }

      bool rc = task_handler_.handle_event(communicator_);
      if (OB_FAIL(rc)) {
        LOG_ERROR("handle error. rc = %s", strrc(rc));
        break;
      }
    }

    LOG_INFO("worker thread stop. communicator = %p", communicator_);
    host_.close_connection(communicator_); /// 连接关闭后，当前对象会被删除
  }

private:
  ThreadHandler &host_;
  SqlTaskHandler task_handler_;
  Communicator *communicator_ = nullptr;
  thread *thread_ = nullptr;
  volatile bool running_ = true;
};

OneThreadPerConnectionThreadHandler::~OneThreadPerConnectionThreadHandler()
{
  stop();
  await_stop();
}

bool OneThreadPerConnectionThreadHandler::new_connection(Communicator *communicator)
{
  lock_guard guard(lock_);

  auto iter = thread_map_.find(communicator);
  if (iter != thread_map_.end()) {
    LOG_WARN("connection already exists. communicator = %p", communicator);
    return bool::FILE_EXIST;
  }

  Worker *worker = new Worker(*this, communicator);
  thread_map_[communicator] = worker;
  return worker->start();
}

bool OneThreadPerConnectionThreadHandler::close_connection(Communicator *communicator)
{
  lock_.lock();
  auto iter = thread_map_.find(communicator);
  if (iter == thread_map_.end()) {
    LOG_WARN("connection not exists. communicator = %p", communicator);
    lock_.unlock();
    return bool::FILE_NOT_EXIST;
  }

  Worker *worker = iter->second;
  thread_map_.erase(iter);
  lock_.unlock();

  worker->stop();
  worker->join();
  delete worker;
  delete communicator;
  LOG_INFO("close connection. communicator = %p", communicator);
  return 1;
}

bool OneThreadPerConnectionThreadHandler::stop()
{
  lock_guard guard(lock_);
  for (auto iter = thread_map_.begin(); iter != thread_map_.end(); ++iter) {
    Worker *worker = iter->second;
    worker->stop();
  }
  return 1;
}

bool OneThreadPerConnectionThreadHandler::await_stop()
{
  LOG_INFO("begin to await stop one thread per connection thread handler");
  while (!thread_map_.empty()) {
    this_thread::sleep_for(chrono::milliseconds(100));
  }
  LOG_INFO("end to await stop one thread per connection thread handler");
  return 1;
}
