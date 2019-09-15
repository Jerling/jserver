#ifndef __CONNECT_H_
#define __CONNECT_H_

#include "jbase/buffer/buffer.h"
#include "jbase/utils/utils.h"
#include "jnet/poller/poller.h"

namespace jnet {
namespace conn {
using NoCopyAble = utils::NonCopyAble;
using Poller = poller::Poller;
using Buffer = buffer::Buffer;
using IBuffer = buffer::IBuffer;
using OBuffer = buffer::OBuffer;

enum STATE { NonDelete = 0, NeedDelete };

class Connect : NoCopyAble {
 public:
  Connect(Poller* Poller, JS_INT32 Cfd);
  ~Connect();

  STATE GetState() const { return _State; }
  JS_INT32 Unregister();

  JS_UINT32 GetReadBufData(JS_CHAR* Buf, JS_UINT32 Len);
  JS_UINT32 GetReadBufCapacity() const;
  JS_UINT32 FromCfdToReadBuf();

  JS_UINT32 SetWriteBuf(JS_CHAR* Buf, JS_UINT32 Len);
  JS_UINT32 FromWriteBufToCfd();
  JS_BOOL IsWriteDone() const;

  static JS_VOID DoDelete();
  static JS_STL_LIST<Connect*>& GetNeedDel() { return _NeedDel; }
  static JS_MUTEX& GetDelListMutex() { return _DelListMutex; }
  static const JS_STL_UMAP<JS_INT32, Connect*>& GetConns() { return _Conns; }

 private:
  JS_INT32 _HandleRST();

 private:
  JS_INT32 _Cfd;
  JS_BOOL _KeepAlive;
  STATE _State;

  Buffer* _ReadBuf;
  Buffer* _WriteBuf;

  static JS_STL_LIST<Connect*> _NeedDel;
  static JS_STL_UMAP<JS_INT32, Connect*> _Conns;
  static JS_MUTEX _DelListMutex;
  static Poller* _Poller;
};
}  // namespace conn
}  // namespace jnet

#endif  // __CONNECT_H_
