#include "jbase/log/logging.h"
#include "jnet/connect/connect.h"

namespace jnet {
namespace conn {
JS_STL_LIST<Connect *> Connect::_NeedDel;
JS_STL_UMAP<JS_INT32, Connect *> Connect::_Conns;
JS_MUTEX Connect::_DelListMutex;
Poller *Connect::_Poller = JS_NULL;

Connect::Connect(Poller *Poller, JS_INT32 Cfd)
    : _Cfd(Cfd), _KeepAlive(JS_TRUE), _State(NonDelete) {
  if (!_Poller) {
    _Poller = Poller;
  }
  _ReadBuf = JS_NEW IBuffer();
  _WriteBuf = JS_NEW OBuffer();
  _Conns[_Cfd] = this;
};

Connect::~Connect(){};

JS_UINT32 Connect::FromCfdToReadBuf() {
  JS_CHAR Ch;
  while (!_ReadBuf->IsFull() && (read(_Cfd, &Ch, 1) > 0)) {
    _ReadBuf->Product(&Ch, 1);
  }
  if (ECONNRESET == errno) {
    _HandleRST();
    return _ReadBuf->Length();
  }
  if (EAGAIN == errno | EWOULDBLOCK == errno) {
    return _ReadBuf->Length();
  }
  return _ReadBuf->Length();
}

JS_UINT32 Connect::GetReadBufData(JS_CHAR *Ptr, JS_UINT32 Len) {
  FromCfdToReadBuf();
  return _ReadBuf->Consume(Ptr, Len);
}

JS_UINT32 Connect::GetReadBufCapacity() const { return _ReadBuf->Capacity(); }

JS_UINT32 Connect::SetWriteBuf(JS_CHAR *Buf, JS_UINT32 Len) {
  *_WriteBuf = OBuffer(Buf, Len + 1);
  return FromWriteBufToCfd();
}

JS_UINT32 Connect::FromWriteBufToCfd() {
  if (_State != NonDelete && _WriteBuf->IsEmpty()) {
    return 0;
  }
  return _WriteBuf->Consume(_Cfd);
}

JS_BOOL Connect::IsWriteDone() const { return _WriteBuf->IsEmpty(); }

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
