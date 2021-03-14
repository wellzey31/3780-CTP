#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include "header.h"
#include <iostream>
#define PORT 8080

int main(int argc, char const *argv[]) {

  std::string host, port, file;

  if (argc < 3 || argc > 5) {
        std::cerr << "[ERROR] incorrect arguments.";
        std::cerr << "usage: sender -f <file> <ip> <port>\n";
        exit(1);
    }

    std::cout << argv[1] << std::endl;

  if (argc == 5) { //&& argv[1] == "-f") {
    host = argv[3];
    file = argv[2];
    port = argv[4];
    std::cout << "host: " << host << " port: " << port << " file: " << file << std::endl;
  }

  std::cout << "argc: " << argc << std::endl;

  for (int i = 0; i < argc; i++) {
    std::cout << argv[i] << std::endl;
  }

  return 0;
}
