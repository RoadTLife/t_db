#include <iostream>

#include "service.h"

namespace tdb
{
class TDBService : public Service {
public:
    TDBService();
    ~TDBService();
};

} // namespace name

int main() {
    std::cout << "Starting TDB service..."  << std::endl;
    // TODO: load config file
    std::string config_file = "config.json";
    std::string json;
    {

    }



    return 0;
}