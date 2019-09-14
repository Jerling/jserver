#include "jnet/log/logging.h"

int main(int argc, char *argv[]) {
  // jnet::conf::Conf Conf(
  //     "/home/linjie/data/Code/Cpp/jnet/conf/jnet.conf");
  SetGlogFlag(argv[0], jnet::conf::Conf());

  JS_LOG(INFO) << "LOG";
  JS_WAR() << "WARNING";

  JS_LOG_IF(INFO, true) << "LOG";
  JS_WAR_IF(true) << "WARNING";

  JS_LOG_EVERY_N(INFO, 1) << "LOG";
  JS_WAR_EVERY_N(1) << "WARNING";

  JS_LOG_FIRST_N(INFO, 1) << "First";
  JS_WAR_FIRST_N(1) << "First";

  JS_PLOG(INFO) << "PLOG";
  JS_PWAR() << "PCheck";

  return 0;
}
