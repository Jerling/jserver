#ifndef __LISTENER_H_
#define __LISTENER_H_
#include "jnet/connect/connect.h"
#include "jnet/poller/poller.h"
#include "jbase/utils/utils.h"

namespace jnet{
namespace listen {
using Poller = poller::EPoller;
using Connect = conn::Connect;

static const JS_INT32 Default_Event = EPOLLIN | EPOLLOUT | EPOLLERR;
static const JS_UINT32 Default_Time = 500;

class Listener : public std::enable_shared_from_this<Listener> {
 public:
  Listener(JS_INT32 Events = Default_Event, JS_UINT16 port = 8000,
           JS_UINT32 = INADDR_ANY, JS_INT32 Backlog = BACKLOG);
  JS_SHARED_PTR<Listener> GetSelf() { return shared_from_this(); }
  ~Listener();
  JS_INT32 GetLfd() const { return _Lfd; }
  const JS_EVENT &GetEvent() const { return _Event; }
  JS_INT32 ModEvent(JS_UINT32 event);
  JS_INT32 SetDataPtr(void *Ptr);
  JS_INT32 Register();
  JS_INT32 Accept();
  JS_INT32 UnRegister();
  JS_INT32 Wait(JS_EVENT *AcEvents, JS_UINT32 Timeout = Default_Time) {
    return _Poller.Wait(AcEvents, Timeout);
  }

 private:
  JS_INT32 _BindAndListen();

 private:
  JS_INT32 _Lfd;
  JS_UINT16 _Port;
  JS_UINT32 _IP;
  JS_EVENT _Event;
  JS_UINT32 _Backlog;
  static Poller _Poller;
  JS_BOOL _Registered;
};

}  // namespace listen
}  // namespace jnet

#endif  // __LISTENER_H_
