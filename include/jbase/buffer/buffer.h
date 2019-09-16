#ifndef __BUFFER_H_
#define __BUFFER_H_

#include "jbase/log/logging.h"

namespace jnet {
namespace buffer {
static const JS_UINT32 MaxLine = 8192;

class Buffer {
 public:
  Buffer(JS_INT32 Fd, JS_UINT32 SZ = MaxLine);
  Buffer(const Buffer& Buf) = delete;
  virtual ~Buffer(){};
  JS_VOID StateInfo();
  JS_BOOL IsFull() const;
  JS_BOOL IsEmpty() const;
  JS_UINT32 Length() const;
  JS_UINT32 Remain() const;
  JS_UINT32 Capacity() const { return _Size; }

  virtual JS_UINT32 Read(JS_CHAR* Ptr, JS_UINT32 Len);
  virtual JS_UINT32 Write(const JS_CHAR* Ptr, JS_UINT32 Len);

 private:
  JS_CHAR* Start() { return _Data + _LowWater; }
  JS_CHAR* End() { return _Data + _HightWater; }
  JS_VOID Append(const JS_CHAR*, JS_UINT32);
  JS_VOID _ReadFromFd();
  JS_UINT32 _WriteToFd();

 private:
  JS_INT32 _Fd;
  JS_CHAR* _Data;
  JS_UINT32 _Size;
  JS_UINT32 _LowWater;
  JS_UINT32 _HightWater;
};

}  // namespace buffer
}  // namespace jnet

#endif  // __BUFFER_H_
