#include <thread>

#include "tdb_server.h"
#include "config.h"

namespace tdb {
TGraphServer::TGraphServer(std::string config)
    : config_(std::move(config)) {}

TGraphServer::~TGraphServer() { Stop(false); }

int TGraphServer::Start() {
    
    return -1;
}

int TGraphServer::WaitTillKilled() {
    return Stop(true);
}

int TGraphServer::Stop(bool force_exit) {
    return 0;
}


}