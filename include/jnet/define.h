#ifndef __DEFINE_H_
#define __DEFINE_H_
#include <bits/stdc++.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <memory>
#include <thread>

#define JS_STL_STRING std::string
#define JS_STL_VECTOR std::vector
#define JS_STL_LIST std::list
#define JS_STL_UMAP std::unordered_map
#define JS_STL_USET std::unordered_set
#define JS_STL_PRIORITY std::priority_queue
#define JS_FILE_IFSTREAM std::ifstream
#define JS_SHARED_PTR std::shared_ptr
#define JS_UNIQUE_PTR std::unique_ptr
#define JS_MUTEX std::mutex

#define JS_VOID void
#define JS_BOOL bool
#define JS_TRUE true
#define JS_FALSE false
#define JS_INT8 int8_t
#define JS_INT16 int16_t
#define JS_INT32 int32_t
#define JS_INT64 int64_t

#define JS_UINT8 u_int8_t
#define JS_UINT16 u_int16_t
#define JS_UINT32 u_int32_t
#define JS_UINT64 u_int64_t

#define JS_CHAR char
#define JS_UCHAR u_char

#define JS_SIZE_T size_t

#define JS_NULL nullptr
#define JS_EVENT epoll_event
#define JS_SA sockaddr_in

namespace jnet {
const JS_UINT32 BACKLOG = 1024;
const JS_UINT16 JS_MAXLINE = 4096;

enum JS_SHUTDOWN_MODE {
  IMMDEDIATELY_MODE = 0,
  GRACEFULLY_MODE,
  SHUTDOWN_MODE_BIT
};

enum JS_CODE { FAILURE = -1, SUCCESS = 0, JS_CODE_BIT };
}  // namespace jnet

#endif  // __DEFINE_H_
