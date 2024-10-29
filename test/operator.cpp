#include "graph.h"



int main() {
    tdb::DB* db;
    tdb::OOptions options;
    tdb::Status status = tdb::DB::Open(options, "/tmp/testdb", &db);
    assert(status.ok());
}