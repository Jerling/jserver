#ifndef __BUFFER_H_
#define __BUFFER_H_

#include "jbase/log/logging.h"

namespace jnet {
namespace buffer {
static const JS_UINT32 MaxLine = 8192;

class Buffer {
 public:
  Buffer(JS_UINT32 SZ = MaxLine, JS_CHAR* Ptr = JS_NULL);
  Buffer(const Buffer& Buf) = delete;
  virtual ~Buffer(){};
  JS_VOID StateInfo();
  JS_BOOL IsFull() const { return (HightWater + 1) % Size == LowWater; }
  JS_BOOL IsEmpty() const { return Data == JS_NULL || HightWater == LowWater; }
  JS_UINT32 Length() const {
    return HightWater < LowWater ? Size - LowWater : HightWater - LowWater;
  }
  JS_UINT32 Remain() const {
    return HightWater >= LowWater ? Size - HightWater : LowWater - HightWater;
  }
  JS_UINT32 Capacity() const { return Size; }
  JS_UINT32 Product(JS_CHAR*, JS_UINT32);

  virtual JS_UINT32 Consume(JS_CHAR*, JS_UINT32) = 0;
  virtual JS_UINT32 Consume(JS_INT32) = 0;

 protected:
  JS_CHAR* Start() { return Data + LowWater; }
  JS_CHAR* End() { return Data + HightWater; }

 protected:
  JS_CHAR* Data;
  JS_UINT32 Size;
  JS_UINT32 LowWater;
  JS_UINT32 HightWater;
};

class IBuffer : public Buffer {
  using Buffer::Buffer;

 public:
  ~IBuffer();
  IBuffer(JS_UINT32 SZ = MaxLine);
  IBuffer(const IBuffer&);
  IBuffer operator=(const IBuffer& Buf);
  JS_UINT32 Consume(JS_CHAR* Ptr, JS_UINT32 Len);

 private:
  JS_UINT32 Consume(JS_INT32) { return 0; };
};

class OBuffer : public Buffer {
  using Buffer::Buffer;

 public:
  ~OBuffer(){};
  explicit OBuffer(JS_CHAR* Ptr, JS_UINT32 SZ);
  OBuffer(const OBuffer&);
  OBuffer operator=(const OBuffer& Buf);
  JS_UINT32 Consume(JS_INT32);

 private:
  JS_UINT32 Consume(JS_CHAR*, JS_UINT32 Fd);
};

}  // namespace buffer
}  // namespace jnet

#endif  // __BUFFER_H_
