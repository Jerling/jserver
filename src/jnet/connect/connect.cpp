#include "jbase/buffer/ibuffer.h"
#include "jbase/buffer/obuffer.h"
#include "jbase/log/logging.h"
#include "jnet/connect/connect.h"

namespace jnet {
namespace conn {
using IBuffer = buffer::IBuffer;
using OBuffer = buffer::OBuffer;

JS_STL_LIST<Connect *> Connect::_NeedDel;
JS_STL_UMAP<JS_INT32, Connect *> Connect::_Conns;
JS_MUTEX Connect::_DelListMutex;
Poller *Connect::_Poller = JS_NULL;

Connect::Connect(Poller *Poller, JS_INT32 Cfd)
    : _Cfd(Cfd), _KeepAlive(JS_TRUE), _State(NonDelete) {
  if (!_Poller) {
    _Poller = Poller;
  }
  _ReadBuf = JS_NEW IBuffer(_Cfd);
  _WriteBuf = JS_NEW OBuffer(_Cfd);
  _Conns[_Cfd] = this;
};

Connect::~Connect(){};

JS_UINT32 Connect::DoRead(JS_CHAR *Ptr, JS_UINT32 Len) {
  return _ReadBuf->Read(Ptr, Len);
}

JS_UINT32 Connect::DoWrite(const JS_CHAR *Ptr, JS_UINT32 Len) {
  char P[10];
  _WriteBuf->Read(P, Len);
  return _WriteBuf->Write(Ptr, Len);
}

JS_VOID Connect::DoDelete() {
  std::unique_lock<JS_MUTEX> UniqueLock(_DelListMutex);
  for (auto It : _NeedDel) {
    Connect *Ptr = (Connect *)It;
    delete Ptr;
    Ptr = JS_NULL;
  }
  _NeedDel.clear();
}

JS_INT32 Connect::Unregister() {
  _State = NeedDelete;
  _Conns[_Cfd] = JS_NULL;
  auto Ret = _Poller->Del(_Cfd, JS_NULL);
  close(_Cfd);
  _Cfd = -1;
  return Ret;
}

JS_INT32 Connect::_HandleRST() {
  {
    std::unique_lock<JS_MUTEX> UniqueLock(_DelListMutex);
    _NeedDel.push_back(this);
  }
  return Unregister();
}

}  // namespace conn
}  // namespace jnet
