#include "graph/graph_impl.h"

namespace tdb {
//const std::string& path, const std::string& name
DBImpl::DBImpl(const std::string& path, const std::string &name): path_(path), name_(name);
}

namespace tdb_api {
DBImpl::~DBImpl() {}


private:
    tdb::AccessControlledDB *db_;
}