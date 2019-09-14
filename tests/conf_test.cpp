#include <gtest/gtest.h>
#include "jnet/conf/conf.h"

TEST(ConfTest, Conf) {
  jnet::conf::Conf Conf(
      "/home/linjie/data/Code/Cpp/jnet/conf/jnet.conf");
  ASSERT_EQ(Conf.GetStr("root"), "/home/linjie/data/Code/Cpp/jnet");
  ASSERT_EQ(Conf.GetStr("log_dir"), "/home/linjie/data/Code/Cpp/jnet/log");

  ASSERT_EQ(Conf.GetValue("shutdown"), 1);
  ASSERT_EQ(Conf.GetValue("logtostderr"), 0);
  ASSERT_EQ(Conf.GetValue("alsologtostderr"), 1);
  ASSERT_EQ(Conf.GetValue("stderrthreshold"), 2);
  ASSERT_EQ(Conf.GetValue("colorlogtostderr"), 1);
  ASSERT_EQ(Conf.GetValue("log_prefix"), 1);
  ASSERT_EQ(Conf.GetValue("logbufsecs"), 0);
  ASSERT_EQ(Conf.GetValue("max_log_size"), 10);
  ASSERT_EQ(Conf.GetValue("port"), 8000);
  ASSERT_EQ(Conf.GetValue("stop_logging_if_full_disk"), 1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
