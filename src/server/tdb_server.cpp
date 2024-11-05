#include <thread>

#include "tdb_server.h"
#include "config.h"
#include "../net/thread_handler.h"
#include "../common/log.h"

namespace tdb {
TGraphServer::TGraphServer(std::string config)
    : config_(std::move(config)) {}

TGraphServer::~TGraphServer() { Stop(false); }

int TGraphServer::Start() {
    // 核心把这个方法写好
    // service_name_ = config::get<std::string>("server.service_name");
    const char* service_name_ = nullptr;
    
    thread_handle_ = ThreadHandler::create(service_name_);
    if (thread_handler_ == nullptr) {
        LOG_ERROR("Failed to create thread handler: %s", server_param_.thread_handling.c_str());
        return -1;
    }

    thread_handler_->start();
    
    return -1;
}

int TGraphServer::WaitTillKilled() {
    return Stop(true);
}

int TGraphServer::Stop(bool force_exit) {
    return 0;
}


}