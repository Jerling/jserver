#include <unistd.h>
#include "jbase/fs/file_wrapper.h"

namespace jnet {
namespace fs {
FileWrapper::FileWrapper(const JS_STL_STRING &FileName) {
  _Open(FileName);
  _Read2Ctx();
}
JS_INT32 FileWrapper::_Open(const JS_STL_STRING &FileName) {
  auto Ret = SUCCESS;
  if (_FileWrapperStream.is_open() || !access(FileName.c_str(), F_OK)) {
    return Ret;
  }
  _FileWrapperStream.open(FileName);
  return Ret;
}

JS_INT32 FileWrapper::_Read2Ctx() {
  auto Ret = SUCCESS;
  JS_CHAR C_Str[JS_MAXLINE] = {'\0'};
  JS_UINT16 i = 0;
  while (_FileWrapperStream.getline(C_Str, JS_MAXLINE)) {
    _Ctx.emplace_back(C_Str);
    _Size += _Ctx[i++].size();
  }
  return Ret;
}

JS_INT32 FileWrapper::_Close() {
  auto Ret = SUCCESS;
  _FileWrapperStream.close();
  return Ret;
}

FileWrapper::~FileWrapper() {
  if (_IsOpen()) {
    _Close();
  }
  _Ctx.clear();
}

};  // namespace fs
}  // namespace jnet
