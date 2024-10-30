#ifndef STORAGE_TDB_INCLUDE_SERVICE_H_
#define STORAGE_TDB_INCLUDE_SERVICE_H_
#include <string>
#include <filesystem>

namespace tdb {
class Service {
    std::string service_name_;
    std::string pid_path_;

    int GetServicePid() const {
        if (fs.FileExists(pid_path_)) {
            std::ifstream pid_file(pid_path_);

             // 文件状态有问题
            if (!pid_file.good()){
                return -2;
            }

            // 从文件中读取
            std::string line;
            std::getline(pid_file, line);

            return pid;
        } else {
            return -1;
        }
    }

    int setServicePid(int pid) {
        std::ofstream pid_file(pid_path_);
        if(!pid_file.good()) {
            return -2;
        }

        pid_file << pid;
    }

    int RemoveServicePidFile() const {
        //TODO del file
        return 0;
    }

 public:
    Service(const std::string &service_name, const std::string &pid_path):service_name_(service_name), pid_path_(pid_path) {}

    int Start() {
#ifdef _WIN32
        return Run();
#else
        std::cout << "Starting " << service_name_ << "...";

        int oldpid = GetServicePid();

#endif
}

    int Stop() {
#ifdef _WIN32
        return Kill();
#else

#endif
    }

    int Restart() {
        int r = Stop();
        if (r != 0 && r != -1) {
            std::cout << "Failed to stop existing service." << std::endl;
            return r;
        }
        return Start();
    }

    // 类似抽象方法，由派生类（derived class）中被重写（override），从而实现多态
    virtual int Run() = 0;
};
}

#endif