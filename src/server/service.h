#ifndef STORAGE_TDB_INCLUDE_SERVICE_H_
#define STORAGE_TDB_INCLUDE_SERVICE_H_
#include <string>


namespace tdb {
class Service {
    std::string service_name_;
    std::string pid_path_;



 public:
    Service(const std::string &service_name, const std::string &pid_path):service_name_(service_name), pid_path_(pid_path) {}

    int Start() {
#ifdef _WIN32
        return Run();
#else

#endif
}

};
}

#endif