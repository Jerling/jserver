#include <gtest/gtest.h>
#include "jnet/fs/file_wrapper.h"

TEST(FileWrapper, File) {
  jnet::fs::FileWrapper File(
      "/home/linjie/data/Code/Cpp/jnet/jnet.conf");
  auto Ctx = File.GetCtx();
  ASSERT_EQ(Ctx[0], "# base conf");
  ASSERT_EQ(Ctx[5], "");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
