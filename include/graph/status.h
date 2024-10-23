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