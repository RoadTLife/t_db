#ifndef STORAGE_TDB_INCLUDE_STATUS_H_
#define STORAGE_TDB_INCLUDE_STATUS_H_

#include <string>

#include "graph/export.h"

namespace tdb
{

    class TDB_EXPORT Status
    {
    private:
        enum Code
        {
            kOk = 0,
            kNotFound = 1,
            kCorruption = 2,
            kNotSupported = 3,
            kInvalidArgument = 4,
            kIOError = 5
        };

    public:
        Status();
    };

}

#endif  // STORAGE_TDB_INCLUDE_STATUS_H_