#ifndef __FILE_WRAPPER_H_
#define __FILE_WRAPPER_H_

#include <assert.h>
#include "jbase/define.h"

namespace jnet {

namespace fs {
class FileWrapper {
 public:
  FileWrapper(const JS_STL_STRING &FileName);
  ~FileWrapper();

  JS_SIZE_T Size() const { return _Size; }
  const JS_STL_VECTOR<JS_STL_STRING> &GetCtx() { return _Ctx; }

 private:
  JS_INT32 _IsOpen() const { return _FileWrapperStream.is_open(); };
  JS_INT32 _Open(const JS_STL_STRING &FileName);
  JS_INT32 _Read2Ctx();
  JS_INT32 _Close();

 private:
  JS_FILE_IFSTREAM _FileWrapperStream;
  JS_STL_VECTOR<JS_STL_STRING> _Ctx;
  JS_BOOL _Deleted;
  JS_SIZE_T _Size;
};
}  // namespace fs
}  // namespace jnet

#endif  // __JS_FileWrapper_WRAPPER_H_
