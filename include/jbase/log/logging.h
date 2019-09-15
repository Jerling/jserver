#ifndef __LOGGING_H_
#define __LOGGING_H_

#include <assert.h>
#include <glog/logging.h>
#include "jbase/conf/conf.h"
#include "jbase/config.h"

#ifdef USE_GLOG

#define JS_LOG(level) LOG(level)
#define JS_INF() LOG(INFO)
#define JS_WAR() LOG(WARNING)
#define JS_ERR() LOG(ERROR)
#define JS_FAT() LOG(FATAL)

// condition log
#define JS_LOG_IF(level, cond) LOG_IF(level, cond)
#define JS_INF_IF(cond) LOG_IF(INFO, cond)
#define JS_WAR_IF(cond) LOG_IF(WARNING, cond)
#define JS_ERR_IF(cond) LOG_IF(ERROR, cond)
#define JS_FAT_IF(cond) LOG_IF(FATAL, cond)

// times
#define JS_LOG_EVERY_N(level, times) LOG_EVERY_N(level, times)
#define JS_INF_EVERY_N(times) LOG_EVERY_N(INFO, times)
#define JS_WAR_EVERY_N(times) LOG_EVERY_N(WARNING, times)
#define JS_ERR_EVERY_N(times) LOG_EVERY_N(ERROR, times)
#define JS_FAT_EVERY_N(times) LOG_EVERY_N(FATAL, times)

// conditon times
#define JS_LOG_IF_EVERY_N(level, times) LOG_IF_EVERY_N(level, cond, times)
#define JS_INF_IF_EVERY_N(times) LOG_IF_EVERY_N(INFO, cond, times)
#define JS_WAR_IF_EVERY_N(times) LOG_IF_EVERY_N(WARNING, cond, times)
#define JS_ERR_IF_EVERY_N(times) LOG_IF_EVERY_N(ERROR, cond, times)
#define JS_FAT_IF_EVERY_N(times) LOG_IF_EVERY_N(FATAL, cond, times)

// fist log
#define JS_LOG_FIRST_N(level, N) LOG_FIRST_N(level, N)
#define JS_INF_FIRST_N(N) LOG_FIRST_N(INFO, N)
#define JS_WAR_FIRST_N(N) LOG_FIRST_N(WARNING, N)
#define JS_ERR_FIRST_N(N) LOG_FIRST_N(ERROR, N)
#define JS_FAT_FIRST_N(N) LOG_FIRST_N(FATAL, N)

// check
#define JS_CHECK(expr) CHECK(expr)
#define JS_CHECK_NOTNULL(expr) CHECK_NOTNULL(expr)
#define JS_CHECK_NE(v1, v2) CHECK_NE(v1, v2)
#define JS_CHECK_EQ(v1, v2) CHECK_EQ(v1, v2)

// Perror
#define JS_PLOG(level) PLOG(level)
#define JS_PINF() PLOG(INFO)
#define JS_PWAR() PLOG(WARNING)
#define JS_PERR() PLOG(ERROR)
#define JS_PFAT() PLOG(FATAL)
#define JS_PLOG_IF(level, cond) PLOG_IF(level, cond)
#define JS_PINF_IF(cond) PLOG_IF(INFO, cond)
#define JS_PWAR_IF(cond) PLOG_IF(WARNING, cond)
#define JS_PERR_IF(cond) PLOG_IF(ERROR, cond)
#define JS_PFAT_IF(cond) PLOG_IF(FATAL, cond)
#define JS_PLOG_EVERY_N(level, times) PLOG_EVERY_N(level, times)
#define JS_PINF_EVERY_N(times) PLOG_EVERY_N(INFO, times)
#define JS_PWAR_EVERY_N(times) PLOG_EVERY_N(WARNING, times)
#define JS_PERR_EVERY_N(times) PLOG_EVERY_N(ERROR, times)
#define JS_PFAT_EVERY_N(times) PLOG_EVERY_N(FATAL, times)
#define JS_PLOG_IF_EVERY_N(level, times) PLOG_IF_EVERY_N(level, cond, times)
#define JS_PINF_IF_EVERY_N(times) PLOG_IF_EVERY_N(INFO, cond, times)
#define JS_PWAR_IF_EVERY_N(times) PLOG_IF_EVERY_N(WARNING, cond, times)
#define JS_PERR_IF_EVERY_N(times) PLOG_IF_EVERY_N(ERROR, cond, times)
#define JS_PFAT_IF_EVERY_N(times) PLOG_IF_EVERY_N(FATAL, cond, times)
#define JS_PLOG_FIRST_N(level, N) PLOG_FIRST_N(level, N)
#define JS_PINF_FIRST_N(N) PLOG_FIRST_N(INFO, N)
#define JS_PWAR_FIRST_N(N) PLOG_FIRST_N(WARNING, N)
#define JS_PERR_FIRST_N(N) PLOG_FIRST_N(ERROR, N)
#define JS_PFAT_FIRST_N(N) PLOG_FIRST_N(FATAL, N)
#define JS_PCHECK(expr) PCHECK(expr)
#define JS_PCHECK_NOTNULL(expr) PCHCK_NE(expr, nullptr)
#define JS_PCHECK_NE(v1, v2) PCHECK_NE(v1, v2)
#define JS_PCHECK_EQ(v1, v2) PCHECK_EQ(v1, v2)

void SetGlogFlag(const JS_STL_STRING &ProcName, const jnet::conf::Conf &Conf);

class GlogHelper {
 public:
  GlogHelper();
  ~GlogHelper() { google::ShutdownGoogleLogging(); }
};
#else
#define JS_LOG(level) std::cout
#define JS_INF() std::cout
#define JS_WAR() std::cout
#define JS_ERR() std::cout
#define JS_FAT() std::cout

// condition log
#define JS_LOG_IF(level, cond) std::cout
#define JS_INF_IF(cond) std::cout
#define JS_WAR_IF(cond) std::cout
#define JS_ERR_IF(cond) std::cout
#define JS_FAT_IF(cond) std::cout

// times
#define JS_LOG_EVERY_N(level, times) std::cout
#define JS_INF_EVERY_N(times) std::cout
#define JS_WAR_EVERY_N(times) std::cout
#define JS_ERR_EVERY_N(times) std::cout
#define JS_FAT_EVERY_N(times) std::cout

// conditon times
#define JS_LOG_IF_EVERY_N(level, times) std::cout
#define JS_INF_IF_EVERY_N(times) std::cout
#define JS_WAR_IF_EVERY_N(times) std::cout
#define JS_ERR_IF_EVERY_N(times) std::cout
#define JS_FAT_IF_EVERY_N(times) std::cout

// fist log
#define JS_LOG_FIRST_N(level, N) std::cout
#define JS_INF_FIRST_N(N) std::cout
#define JS_WAR_FIRST_N(N) std::cout
#define JS_ERR_FIRST_N(N) std::cout
#define JS_FAT_FIRST_N(N) std::cout

// check
#define JS_CHECK(expr) assert(expr)
#define JS_CHECK_NOTNULL(expr) assert(ptr != NULL)
#define JS_CHECK_NE(v1, v2) assert(v1 != v2)
#define JS_CHECK_EQ(v1, v2) assert(v1 == v2)

// Perror
#define JS_PLOG(level) std::clog
#define JS_PINF() std::clog
#define JS_PWAR() std::cerr
#define JS_PERR() std::cerr
#define JS_PFAT() std::cerr
#define JS_PLOG_IF(level, cond) std::clog
#define JS_PINF_IF(cond) std::clog
#define JS_PWAR_IF(cond) std::cerr
#define JS_PERR_IF(cond) std::cerr
#define JS_PFAT_IF(cond) std::cerr
#define JS_PLOG_EVERY_N(level, times) std::clog
#define JS_PINF_EVERY_N(times) std::clog
#define JS_PWAR_EVERY_N(times) std::cerr
#define JS_PERR_EVERY_N(times) std::cerr
#define JS_PFAT_EVERY_N(times) std::cerr
#define JS_PLOG_IF_EVERY_N(level, times) std::clog
#define JS_PINF_IF_EVERY_N(times) std::clog
#define JS_PWAR_IF_EVERY_N(times) std::cerr
#define JS_PERR_IF_EVERY_N(times) std::cerr
#define JS_PFAT_IF_EVERY_N(times) std::cerr
#define JS_PLOG_FIRST_N(level, N) std::clog
#define JS_PINF_FIRST_N(N) std::clog
#define JS_PWAR_FIRST_N(N) std::cerr
#define JS_PERR_FIRST_N(N) std::cerr
#define JS_PFAT_FIRST_N(N) std::cerr
#define JS_PCHECK(expr) std::cerr
#define JS_PCHECK_NOTNULL(expr) std::cerr
#define JS_PCHECK_NE(v1, v2) std::cerr
#define JS_PCHECK_EQ(v1, v2) std::cerr
#endif
#endif  // __LOGGING_H_
