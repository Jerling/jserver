#include "jnet/listener/listener.h"

int main(int argc, char *argv[]) {
  JS_INF() << "Starting ...";
  jnet::listen::Listener ln = jnet::listen::Listener();
  JS_EVENT evs[1025];
  int n = 0, nums;
  int events = evs[0].events;
  JS_STL_STRING Str;

  char Res[] = "Server";
  while (true) {
    if ((n = ln.Wait(evs) > 0)) {
      for (int i = 0; i < n; i++) {
        auto ev = evs[i].events;
        auto fd = evs[i].data.fd;
        auto Ptr = (jnet::conn::Connect *)evs[i].data.ptr;
        if (ev & (EPOLLIN | EPOLLERR)) {
          if (ln.GetLfd() == fd) {
            ln.Accept();
          } else {
            char Buf[1024];
            nums = Ptr->GetReadBufData(Buf, 1024);
            JS_WAR() << "Recv " << nums << " : " << Buf << " end";
            nums = Ptr->SetWriteBuf(Res, sizeof(Res));
            JS_WAR() << "Send " << nums << " Bytes";
          }
        } else if (ev & EPOLLOUT) {
          Ptr->FromWriteBufToCfd();
        }
      }
    }
  }
  return 0;
}
