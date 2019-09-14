#include "jnet/connect/connect.h"

namespace jnet {
namespace conn {

JS_UINT32 Connect::Read(std::string &Str) {
  int Ret = read(_Cfd, _Buffer, MaxLine);
  JS_PCHECK(Ret >= 0) << "Read at " << _Cfd << " Error";
  Str = _Buffer;
  return Ret;
}

JS_UINT32 Connect::Write(const std::string &Str) {
  int Ret = write(_Cfd, Str.c_str(), Str.size());
  JS_PCHECK(Ret >= 0) << "Write at " << _Cfd << " Error";
  JS_PWAR() << "Write " << Ret << " bytes";
  return Ret;
}

}  // namespace conn
}  // namespace jnet
