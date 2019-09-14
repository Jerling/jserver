#include "jbase/log/logging.h"

// auto init and deinit glog
static GlogHelper GH;

JS_VOID SetGlogFlag(const JS_STL_STRING &ProcName,
                    const jnet::conf::Conf &Conf) {
  FLAGS_log_dir = Conf.GetStr("log_dir");
  FLAGS_logtostderr = static_cast<JS_BOOL>(Conf.GetValue("logtostderr"));
  FLAGS_alsologtostderr =
      static_cast<JS_BOOL>(Conf.GetValue("alsologtostderr"));
  FLAGS_stderrthreshold =
      static_cast<JS_INT32>(Conf.GetValue("stderrthreshold"));
  FLAGS_log_prefix = static_cast<JS_BOOL>(Conf.GetValue("log_prefix"));
  FLAGS_colorlogtostderr =
      static_cast<JS_BOOL>(Conf.GetValue("colorlogtostderr"));
  FLAGS_logbufsecs = static_cast<JS_INT32>(Conf.GetValue("logbufsecs"));
  FLAGS_max_log_size = static_cast<JS_INT32>(Conf.GetValue("max_log_size"));
  FLAGS_stop_logging_if_full_disk =
      static_cast<JS_BOOL>(Conf.GetValue("stop_logging_if_full_disk"));
}

GlogHelper::GlogHelper() {
  google::InitGoogleLogging("jnet");
  FLAGS_logtostderr = JS_TRUE;
}
