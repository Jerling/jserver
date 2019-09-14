#ifndef __POLLER_IMPL_H_
#define __POLLER_IMPL_H_
#include "jbase/utils/utils.h"

namespace jnet {
namespace poller {
using NoCopyAble = utils::NonCopyAble;

class EPoller : NoCopyAble {
 public:
  EPoller();
  ~EPoller() = default;
  JS_INT32 GetEfd() const { return _Efd; }
  JS_INT32 Add(JS_INT32 Fd, JS_EVENT *Event);
  JS_INT32 Mod(JS_INT32 Fd, JS_EVENT *Event);
  JS_INT32 Del(JS_INT32 Fd, JS_EVENT *Event);
  JS_INT32 Wait(JS_EVENT *Event, JS_UINT32 Timeout);

 private:
 private:
  JS_INT32 _Efd;
};

}  // namespace poller
}  // namespace jnet

#endif  // __POLLER_IMPL_H_
