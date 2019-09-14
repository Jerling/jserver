#include "jbase/conf/conf.h"

namespace jnet {
namespace conf {

JS_INT32 Conf::_ParseConfFile(fs::FileWrapper &FW) {
  auto Ret = SUCCESS;
  auto Ctx = FW.GetCtx();
  for (auto &s : Ctx) {
    auto End = std::remove(s.begin(), s.end(), ' ');
    if (s.empty() || s[0] == '#') {
      continue;
    }
    _Str2Map(s.begin(), End);
  }
  return Ret;
}

JS_INT32 Conf::_Str2Map(JS_STL_STRING::const_iterator begin,
                        JS_STL_STRING::const_iterator end, JS_CHAR Delim) {
  auto Ret = SUCCESS;
  auto DelimPos = std::find(begin, end, Delim);
  auto Key = JS_STL_STRING(begin, DelimPos);
  auto Value = JS_STL_STRING(DelimPos + 1, end);
  if (StrSet.find(Key) == StrSet.end()) {
    auto ValueL = std::strtol(Value.c_str(), JS_NULL, 10);
    _Str2Long.at(Key) = ValueL;
  } else {
    _Str2Str.at(Key) = Value;
  }
  return Ret;
}

JS_STL_STRING Conf::GetStr(const JS_STL_STRING &Str) const {
  if (StrSet.find(Str) == StrSet.end()) {
    std::cerr << Str << " is not a Str2Str map !!!" << std::endl;
    return "";
  }
  auto It = _Str2Str.find(Str);
  if (It == _Str2Str.end()) {
    return ".";
  }
  return It->second;
}

JS_INT64 Conf::GetValue(const JS_STL_STRING &Str) const {
  if (StrSet.find(Str) != StrSet.end()) {
    std::cerr << Str << " is not a Str2Value map !!!" << std::endl;
    return -1;
  }
  auto It = _Str2Long.find(Str);
  if (It == _Str2Long.end()) {
    return 1;
  }
  return It->second;
}

};  // namespace conf
}  // namespace jnet
