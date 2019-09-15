#include "jnet/listener/listener.h"

namespace jnet {
namespace listen {
Poller Listener::_Poller;

Listener::Listener(int Events, JS_UINT16 Port, JS_UINT32 IP, JS_INT32 Backlog)
    : _Port(Port), _IP(IP), _Backlog(Backlog), _Registered(JS_FALSE) {
  _Lfd = socket(AF_INET, SOCK_STREAM, 0);
  JS_PCHECK(0 < _Lfd) << "Create Listener Faild";
  int reuse = 1;
  JS_PCHECK(0 <=
            setsockopt(_Lfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)))
      << "Reuse Failed";
  _BindAndListen();
  _Event.events = Events;
  _Event.data.fd = _Lfd;
  Register();
}

Listener::~Listener() { UnRegister(); }

JS_INT32 Listener::_BindAndListen() {
  auto Ret = 0;
  JS_SA SA;
  memset(&SA, 0, sizeof(SA));
  SA.sin_family = AF_INET;
  SA.sin_addr.s_addr = _IP;
  SA.sin_port = htons(_Port);

  Ret = bind(_Lfd, (struct sockaddr *)&SA, sizeof(SA));
  JS_PCHECK(0 == Ret) << "Bind Faied at " << _IP << " : " << _Port;
  Ret = ::listen(_Lfd, _Backlog);
  JS_PCHECK(0 == Ret) << "Listen Faied at " << _IP << " : " << _Port;
  return Ret;
}

JS_INT32 Listener::SetDataPtr(void *Ptr) {
  auto Ret = SUCCESS;
  _Event.data.ptr = Ptr;
  return Ret;
}

JS_INT32 Listener::ModEvent(JS_UINT32 event) {
  return _Poller.Mod(_Lfd, &_Event);
}

JS_INT32 Listener::Register() {
  if (_Registered) {
    return SUCCESS;
  }
  auto Ret = _Poller.Add(_Lfd, &_Event);
  _Registered = JS_TRUE;
  JS_WAR() << _Lfd << " Registered at " << _Poller.GetEfd();
  return Ret;
}
JS_INT32 Listener::UnRegister() {
  if (!_Registered) {
    return SUCCESS;
  }
  auto Ret = _Poller.Del(_Lfd, &_Event);
  _Registered = JS_FALSE;
  return Ret;
}

JS_INT32 Listener::Accept() {
  JS_INT32 Cfd = accept(_Lfd, JS_NULL, 0);
  JS_PCHECK(Cfd > 0) << "Accept Failed";
  JS_WAR() << "Connected at " << Cfd;
  utils::SetNoBlocking(Cfd);
  JS_EVENT Event;
  Event.events = Default_Event | EPOLLET;
  Event.data.ptr = (JS_VOID *)(new Connect(&_Poller, Cfd));
  JS_WAR() << "New Conn at " << Event.data.ptr;
  return _Poller.Add(Cfd, &Event);
}

}  // namespace listen
}  // namespace jnet
