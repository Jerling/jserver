#ifndef __OBUFFER_H_
#define __OBUFFER_H_

#include "buffer.h"

#include "buffer.h"
namespace jnet {
namespace buffer {
class OBuffer : public Buffer {
 public:
  OBuffer(JS_INT32 Fd, JS_UINT32 Size = MaxLine) : Buffer(Fd, Size) {}
  JS_UINT32 Read(JS_CHAR* Ptr, JS_UINT32 Len) override {
    JS_WAR() << "OBuffer can't Read";
    return 0;
  };
};
}  // namespace buffer
}  // namespace jnet

#endif  // __OBUFFER_H_
