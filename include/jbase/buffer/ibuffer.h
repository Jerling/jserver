#ifndef __IBUFFER_H_
#define __IBUFFER_H_

#include "buffer.h"
namespace jnet {
namespace buffer {
class IBuffer : public Buffer {
 public:
  IBuffer(JS_INT32 Fd, JS_UINT32 Size = MaxLine) : Buffer(Fd, Size) {}
  JS_UINT32 Write(const JS_CHAR* Ptr, JS_UINT32 Len) override {
    JS_WAR() << "IBuffer can't Write";
    return 0;
  };
};
}  // namespace buffer
}  // namespace jnet

#endif  // __IBUFFER_H_
