#ifndef STORAGE_TDB_INCLUDE_SERVER_H_
#define STORAGE_TDB_INCLUDE_SERVER_H_

#include <memory>

#include "config.h"

namespace tdb
{


class TGraphServer {

 public:  // NOLINT
    // 设置只能显示调用
    explicit TGraphServer(std::shared_ptr<tdb::GlobalConfig> config);
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