#include "jbase/buffer/buffer.h"

namespace jnet {
namespace buffer {
Buffer::Buffer(JS_UINT32 SZ, JS_CHAR *Ptr)
    : Data(Ptr), Size(SZ), LowWater(0), HightWater(0) {
  if (Size == 0 || !Ptr) {
    return;
  }
}

JS_VOID Buffer::StateInfo() {
  JS_CHAR msg[MaxLine + 32];
  sprintf(msg, "%p %s %d %d %d", Data, Data, LowWater, HightWater, Size);
  JS_WAR() << msg;
}

JS_UINT32 Buffer::Product(JS_CHAR *Ptr, JS_UINT32 Len) {
  if (IsFull()) {
    JS_WAR() << "Buffer Is Full";
    return 0;
  }
  auto SZ = std::min(Len, Remain());
  memmove(End(), Ptr, SZ);
  HightWater = (HightWater + SZ) % Size;
  return SZ;
}

IBuffer::IBuffer(JS_UINT32 SZ) : Buffer(SZ) {
  Data = (JS_CHAR *)malloc(sizeof(JS_CHAR) * Size);
  JS_PCHECK(JS_NULL != Data) << "Malloc Buffer Failed";
  memset(Data, 0, Size);
}

IBuffer::IBuffer(const IBuffer &Buf) {
  Size = Buf.Size;
  LowWater = Buf.LowWater;
  HightWater = Buf.HightWater;
  Data = (JS_CHAR *)JS_MALLOC(sizeof(JS_CHAR) * Size);
  memmove(Data, Buf.Data, Size);
}

IBuffer IBuffer::operator=(const IBuffer &Buf) {
  if (!Data) {
    free(Data);
  }
  Size = Buf.Size;
  LowWater = Buf.LowWater;
  HightWater = Buf.HightWater;
  Data = (JS_CHAR *)JS_MALLOC(sizeof(JS_CHAR) * Size);
  memmove(Data, Buf.Data, Size);
  return *this;
}

IBuffer::~IBuffer() { free(Data); }

JS_UINT32 IBuffer::Consume(JS_CHAR *Ptr, JS_UINT32 Len) {
  if (0 == Len) {
    return 0;
  }
  if (IsEmpty()) {
    memset(Ptr, 0, Len);
    return 0;
  }
  auto SZ = std::min(Len, Length());
  memmove(Ptr, Start(), SZ);
  LowWater = (LowWater + SZ) % Size;
  return SZ;
}

OBuffer::OBuffer(JS_CHAR *Ptr, JS_UINT32 SZ) : Buffer(SZ, Ptr) {
  HightWater = SZ;
  ;
}

OBuffer::OBuffer(const OBuffer &Buf) {
  Size = Buf.Size;
  LowWater = Buf.LowWater;
  HightWater = Buf.HightWater;
  Data = (JS_CHAR *)JS_MALLOC(sizeof(JS_CHAR) * Size);
  memmove(Data, Buf.Data, Size);
}

OBuffer OBuffer::operator=(const OBuffer &Buf) {
  Size = Buf.Size;
  LowWater = Buf.LowWater;
  HightWater = Buf.HightWater;
  Data = (JS_CHAR *)JS_MALLOC(sizeof(JS_CHAR) * Size);
  memmove(Data, Buf.Data, Size);
  return *this;
}

JS_UINT32 OBuffer::Consume(JS_CHAR *, JS_UINT32 Fd) {
  JS_UINT32 Ret, OldLow = LowWater;
  while (!IsEmpty() && (Ret = write(Fd, Start(), Length()) > 0)) {
    LowWater += Ret;
  }
  Ret = LowWater - OldLow;
  if (EAGAIN == errno || EWOULDBLOCK == errno) {
    return Ret;
  }
  JS_PCHECK(Ret >= 0) << "Write at " << Fd << " Error";
  return Ret;
}

JS_UINT32 OBuffer::Consume(JS_INT32 Fd) { return Consume(JS_NULL, Fd); }

}  // namespace buffer
}  // namespace jnet
