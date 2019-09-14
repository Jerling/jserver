#include "jnet/listener/listener.h"

int main(int argc, char *argv[]) {
  JS_INF() << "Starting ...";
  jnet::listen::Listener ln = jnet::listen::Listener();
  JS_EVENT evs[1025];
  int n = 0;
  int events = evs[0].events;
  JS_STL_STRING Str;

  while (true) {
    if ((n = ln.Wait(evs) > 0)) {
      for (int i = 0; i < n; i++) {
        auto ev = evs[i].events;
        auto fd = evs[i].data.fd;
        auto Ptr = (jnet::conn::Connect *)evs[i].data.ptr;
        if (ev & (EPOLLIN | EPOLLERR)) {
          if (ln.GetLfd() == fd) {
            JS_INF_IF(ln.Accept() == 0) << "Connected";
          } else {
            JS_INF_IF(Ptr->Read(Str) > 0)
                << "Recv " << Str.size() << " bytes : " << Str;
          }
        }
        if (ev & EPOLLOUT) {
          Ptr->Write("Server");
        }
      }
    }
  }
  return 0;
}
