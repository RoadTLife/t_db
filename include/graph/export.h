#ifndef STORAGE_TDB_INCLUDE_EXPORT_H_
#define STORAGE_TDB_INCLUDE_EXPORT_H_

/**
 * 用于控制：宏用来控制库函数的导出或导入
 */

#if !defined(TDB_EXPORT)

#if defined(TDB_SHARED_LIBRARY)
#if defined(_WIN32)

#if defined(TDB_COMPILE_LIBRARY)
#define TDB_EXPORT __declspec(dllexport)
#else
#define TDB_EXPORT __declspec(dllimport)
#endif  // defined(TDB_COMPILE_LIBRARY)

#else  // defined(_WIN32)
#if defined(TDB_COMPILE_LIBRARY)
#define TDB_EXPORT __attribute__((visibility("default")))
#else
#define TDB_EXPORT
#endif
#endif  // defined(_WIN32)

#else  // defined(TDB_SHARED_LIBRARY)
#define TDB_EXPORT
#endif

#endif  // !defined(TDB_EXPORT)

#endif  // STORAGE_TDB_INCLUDE_EXPORT_H_
