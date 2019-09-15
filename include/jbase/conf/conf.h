#ifndef __CONF_H_
#define __CONF_H_

#include "jbase/fs/file_wrapper.h"

namespace jnet {
namespace conf {

class Conf {
 public:
  Conf(const JS_STL_STRING &ConfFilePath = "./conf/jnet.conf")
      : _Str2Str({{"root", "./"}, {"log_dir", "./log"}}),
        _Str2Long({{"port", 8000},
                   {"shutdown", 1},
                   {"logtostderr", 0},
                   {"alsologtostderr", 1},
                   {"stderrthreshold", 2},
                   {"log_prefix", 1},
                   {"colorlogtostderr", 1},
                   {"logbufsecs", 0},
                   {"max_log_size", 10},
                   {"stop_logging_if_full_disk", 1}}) {
    fs::FileWrapper FW(ConfFilePath);
    _ParseConfFile(FW);
  };
  JS_STL_STRING GetStr(const JS_STL_STRING &Str) const;
  JS_INT64 GetValue(const JS_STL_STRING &Str) const;

 private:
  JS_INT32 _ParseConfFile(fs::FileWrapper &FW);
  JS_INT32 _Str2Map(JS_STL_STRING::const_iterator begin,
                    JS_STL_STRING::const_iterator end, JS_CHAR delim = '=');

 private:
  const JS_STL_USET<JS_STL_STRING> StrSet = {"root", "log_dir"};
  JS_STL_UMAP<JS_STL_STRING, JS_STL_STRING> _Str2Str;
  JS_STL_UMAP<JS_STL_STRING, JS_INT64> _Str2Long;
};
}  // namespace conf

}  // namespace jnet

#endif  // __CONF_H_
