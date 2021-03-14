#include <stdio.h>
//#include <sys/socket.h>
#include <string.h>
#include <iostream>
#define PORT 8080

int main(int argc, char const *argv[]) {

  if (argc < 3 || argc > 4) {
        std::cerr << "usage: receiver -f <file> <port>\n";
        exit(1);
    }

  std::cout << "argc: " << argc << std::endl;

  for (int i = 0; i < argc; i++) {
    std::cout << argv[i] << std::endl;
  }

 return 0;
}
