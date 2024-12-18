#include "graph/export.h"

struct TDB_EXPORT Options {
    // Create an Options object with default values for all fields.
  Options();

    // If true, the database will be created if it is missing.
  bool create_if_missing = false;

  // If true, an error is raised if the database already exists.
  bool error_if_exists = false;

    // Use the specified object to interact with the environment,
  // e.g. to read/write files, schedule background work, etc.
  // Default: Env::Default()
  // Env* env;

    // Any internal progress/error information generated by the db will
  // be written to info_log if it is non-null, or to a file stored
  // in the same directory as the DB contents if info_log is null.
  Logger* info_log = nullptr;

};