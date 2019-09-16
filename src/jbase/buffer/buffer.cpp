#include "jbase/buffer/buffer.h"

namespace jnet {
namespace buffer {
Buffer::Buffer(JS_INT32 Fd, JS_UINT32 SZ)
    : _Fd(Fd), _Size(SZ), _LowWater(0), _HightWater(0) {
  _Data = (JS_CHAR *)JS_MALLOC(sizeof(JS_CHAR) * _Size);
  memset(_Data, 0, _Size);
}

JS_VOID Buffer::StateInfo() {
  JS_CHAR msg[MaxLine + 32];
  sprintf(msg, "%p %s %d %d %d", _Data, _Data, _LowWater, _HightWater, _Size);
  JS_WAR() << msg;
}

JS_BOOL Buffer::IsFull() const {
  return (_HightWater + 1) % _Size == _LowWater;
}
JS_BOOL Buffer::IsEmpty() const {
  return _Data == JS_NULL || _HightWater == _LowWater;
}
JS_UINT32 Buffer::Length() const {
  return _HightWater < _LowWater ? _Size - _LowWater : _HightWater - _LowWater;
}
JS_UINT32 Buffer::Remain() const {
  return _HightWater >= _LowWater ? _Size - _HightWater
                                  : _LowWater - _HightWater;
}
JS_VOID Buffer::Append(const JS_CHAR *Ptr, JS_UINT32 Len) {
  if (IsFull()) {
    JS_WAR() << "Buffer Is Full";
    return;
  }
  auto SZ = std::min(Len, Remain());
  memmove(End(), Ptr, SZ);
  _HightWater = (_HightWater + SZ) % _Size;
}

JS_VOID Buffer::_ReadFromFd() {
  JS_CHAR Ch;
  while (!IsFull() && (read(_Fd, &Ch, 1) > 0)) {
    *End() = Ch;
    ++_HightWater;
  }
}

JS_UINT32 Buffer::Read(JS_CHAR *Ptr, JS_UINT32 Len) {
  if (Length() < Len) {
    _ReadFromFd();
  }
  if (0 == Len) {
    return 0;
  }
  if (IsEmpty()) {
    memset(Ptr, 0, Len);
    return 0;
  }
  auto SZ = std::min(Len, Length());
  memmove(Ptr, Start(), SZ);
  _LowWater = (_LowWater + SZ) % _Size;
  return SZ;
}

JS_UINT32 Buffer::_WriteToFd() {
  JS_UINT32 Ret, OldLow = _LowWater;
  while (!IsEmpty() && (Ret = write(_Fd, Start(), Length() > 0))) {
    _LowWater += Ret;
  }
  return _LowWater - OldLow;
}

JS_UINT32 Buffer::Write(const JS_CHAR *Ptr, JS_UINT32 Len) {
  if (JS_NULL == Ptr) {
    return _WriteToFd();
  } else {
    Append(Ptr, Len);
  }
  JS_UINT32 Ret, OldLow = _LowWater;
  auto SZ = std::min(Len, Length());
  if (0 == SZ) {
    return 0;
  }
  while (!IsEmpty() && (Ret = write(_Fd, Start(), SZ > 0))) {
    _LowWater += Ret;
    SZ -= Ret;
  }
  return _LowWater - OldLow;
}

}  // namespace buffer
}  // namespace jnet
