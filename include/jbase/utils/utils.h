#ifndef __UTILS_H_
#define __UTILS_H_

#include "jbase/log/logging.h"

namespace jnet {
namespace utils {
#include <fcntl.h>
class NonCopyAble {
 protected:
  NonCopyAble() = default;
  virtual ~NonCopyAble() = default;

 private:
  NonCopyAble(const NonCopyAble &) = delete;
  NonCopyAble operator=(const NonCopyAble &) = delete;
};

template <typename T>
struct Singleton {
 private:
  Singleton() = delete;
  Singleton(const Singleton<T> &) = delete;
  Singleton<T> operator=(const Singleton<T> &) = delete;
  static JS_SHARED_PTR<T> _Ins;

 public:
  static JS_SHARED_PTR<T> &Instance() { return _Ins; };
};

template <typename T>
JS_SHARED_PTR<T> Singleton<T>::_Ins(new T());

static JS_INT32 SetNoBlocking(JS_INT32 Fd) {
  JS_INT32 Flags;
  JS_PCHECK(fcntl(Fd, F_GETFL, &Flags) == 0) << "Get Flags Failed";
  auto Ret = fcntl(Fd, F_SETFL, Flags | O_NONBLOCK);
  JS_PCHECK(Ret == 0) << "Set Flags Failed";
  return Ret;
}

}  // namespace utils
}  // namespace jnet

#endif  // __UTILS_H_
