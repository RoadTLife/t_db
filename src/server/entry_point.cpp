#include "tdb_server.h"
#include "service.h"
#include "config.h"

namespace tdb
{
class TDBService : public Service {
    TGraphServer server_;
public:
    explicit TDBService(const std::shared_ptr<tdb::GlobalConfig> config) : Service("graph", "./graph.pid"), server_(config) {}

    int Run() override {
        auto ret = server_.Start();
        if (ret) {
            return ret;
        }
        return server_.WaitTillKilled();
    }

};

} // namespace name

int main() {
    std::cout << "Starting TDB service..."  << std::endl;
    std::string cmd = "run";

    // TODO: load config file
    std::string config_file = "config.json";
    std::string json;
    {

    }

    std::shared_ptr<tdb::GlobalConfig> config = std::make_shared<tdb::GlobalConfig>();

    tdb::TDBService service(config);
    if (cmd == "run") {
        return service.Run();
    } else if (cmd == "start") {
        return service.Start();
    } else if (cmd == "restart") {
        return service.Restart();
    } else if (cmd == "stop") {
        return service.Stop();
    }
    return 0;
}