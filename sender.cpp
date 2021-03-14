#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <iostream>
#define PORT 8080

int main(int argc, char const *argv[]) {

  for (int i = 0; i < argv.size(); i++) {
    std::cout << argv[i] << endl;
  }

  return 0;
}
