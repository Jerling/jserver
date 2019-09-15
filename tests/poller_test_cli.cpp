#include "jnet/listener/listener.h"
int main(int argc, char *argv[]) {
  JS_SA sa;
  memset(&sa, 0, sizeof(sa));
  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = 0;
  sa.sin_port = htons(8000);
  auto nums = 32;
  const int conns = 1024;
  int sfd[conns] = {0};
  char str[nums];
  for (int i = 0; i < conns; i++) {
    sfd[i] = socket(AF_INET, SOCK_STREAM, 0);
    connect(sfd[i], (struct sockaddr *)&sa, sizeof(sa));
    sprintf(str, "Client %04d \n test enter", i);
    write(sfd[i], str, nums);
    std::cout << "Write Over" << std::endl;
    memset(str, 0, nums);
    int ret = read(sfd[i], str, nums);
    std::cout << "Recv " << ret << " bytes from server : " << str << std::endl;
  }
  for (int i; i < conns; i++) {
    close(sfd[i]);
  }
  return 0;
}
