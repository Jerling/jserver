#ifndef __CONNECT_H_
#define __CONNECT_H_

#include "jbase/log/logging.h"
#include "jbase/utils/utils.h"

namespace jnet {
namespace conn {
using NoCopyAble = utils::NonCopyAble;
static const JS_UINT32 MaxLine = 8192;
class Connect : NoCopyAble {
 public:
  Connect(JS_INT32 Cfd = 0)
      : _Cfd(Cfd), _KeepAlive(JS_TRUE), _Deleted(JS_TRUE){};

  JS_UINT32 Read(JS_STL_STRING& Str);
  JS_UINT32 Write(const JS_STL_STRING& Str);
  JS_VOID InvertKeepAlive() { _KeepAlive = ~_KeepAlive; }

 private:
  JS_INT32 _Cfd;
  JS_BOOL _KeepAlive;
  JS_BOOL _Deleted;
  JS_CHAR _Buffer[MaxLine];

  static JS_STL_LIST<void*> _NeedDel;
  static JS_MUTEX DelListMutex;
};
}  // namespace conn
}  // namespace jnet

#endif  // __CONNECT_H_
