#ifndef STORAGE_TDB_INCLUDE_SERVER_H_
#define STORAGE_TDB_INCLUDE_SERVER_H_

#include <thread>
#include <memory>
#include "service.h"
#include "string"
#include "config.h"

namespace tdb
{


// class Signal {
//     bool signal;
//     std::mutex lock;
//     std::condition_variable cv;

//  public:
//     Signal() : signal(false) {}

//     bool Wait(double timeout_s = 0) {
//         std::unique_lock<std::mutex> l(lock);
//         if (timeout_s <= 0) {
//             cv.wait(l, [this]() { return signal; });
//             return true;
//         } else {
//             cv.wait_for(l, std::chrono::milliseconds((size_t)(timeout_s * 1000)),
//                         [this]() { return signal; });
//             return signal;
//         }
//     }

//     void Notify() {
//         std::lock_guard<std::mutex> l(lock);
//         signal = true;
//         cv.notify_all();
//     }
// };

class TGraphServer {
    protected:  // NOLINT
    // Signal server_exit_;
    std::string config_;
    // std::unique_ptr<lgraph::RestServer> rest_server_;
    std::thread heartbeat_detect;

 public:  // NOLINT
    explicit TGraphServer(std::string config);
    ~TGraphServer();

    // just start services
    int Start();

    // wait till service terminated
    int WaitTillKilled();

    // stop all services
    int Stop(bool force_exit = false);
};
    
} // namespace name



#endif