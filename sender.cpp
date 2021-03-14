#include <stdio.h>
//#include <sys/socket.h>
#include <string.h>
#include <iostream>
#define PORT 8080

int main(int argc, char const *argv[]) {

  for (int i = 0; i < argc; i++) {
    std::cout << argv[i] << std::endl;
  }

  return 0;
}
