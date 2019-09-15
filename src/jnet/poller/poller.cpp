#include <signal.h>
#include "jbase/log/logging.h"
#include "jnet/poller/poller.h"

namespace jnet {

namespace poller {
static const JS_UINT32 MAX_EVENTS = 1024;

EPoller::EPoller() {
  _Efd = epoll_create(1);
  JS_PCHECK(_Efd > 0) << "Create epoll failed";
  _SetSigHandle();
}
JS_INT32 EPoller::Add(JS_INT32 Fd, JS_EVENT *Event) {
  auto Ret = SUCCESS;
  JS_PCHECK(epoll_ctl(_Efd, EPOLL_CTL_ADD, Fd, Event) == 0)
      << "Add" << Fd << " Failed";
  return Ret;
}
JS_INT32 EPoller::Mod(JS_INT32 Fd, JS_EVENT *Event) {
  auto Ret = SUCCESS;
  JS_PCHECK(epoll_ctl(_Efd, EPOLL_CTL_MOD, Fd, Event) == 0)
      << "Mod" << Fd << " Failed";
  return Ret;
}
JS_INT32 EPoller::Del(JS_INT32 Fd, JS_EVENT *Event) {
  auto Ret = SUCCESS;
  JS_PCHECK(epoll_ctl(_Efd, EPOLL_CTL_DEL, Fd, Event) == 0)
      << "Del " << Fd << " Failed";
  return Ret;
}
JS_INT32 EPoller::Wait(JS_EVENT *Event, JS_UINT32 Timeout) {
  int Ret = epoll_wait(_Efd, Event, MAX_EVENTS, Timeout);
  JS_PCHECK(Ret >= 0) << "Epoll wait Failed";
  return Ret;
}

JS_INT32 EPoller::_SetSigHandle() {
  struct sigaction SA;
  SA.sa_handler = SIG_IGN;
  sigemptyset(&SA.sa_mask);
  SA.sa_flags = 0;
  return sigaction(SIGPIPE, &SA, JS_NULL);
}

}  // namespace poller

}  // namespace jnet
