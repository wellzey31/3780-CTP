#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <cstring>

int main(int argc, char const *argv[]) {
  int s;

  struct sockaddr_in sa;
  struct addrinfo hints, *res;
  std::string port, file;

  if (argc < 3 || argc > 4) {
        std::cerr << "[ERROR] incorrect arguments.";
        std::cerr << "usage: receiver -f <file> <port>\n";
        exit(1);
    }  else if (argc == 5) { //&& argv[1] == "-f") {
        file = argv[2];
        port = argv[3];
        std::cout << " port: " << port << " file: " << file << std::endl;
    }

    memset(&hints, 0, sizeof hints); //makes sure the struct is empty
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(port.c_str(), &hints, &res);

    s = socket(res -> ai_family, res -> ai_socktype, res -> ai_protocol);

    if(s == -1) {
      std::cerr << "[ERROR] socket = -1.\n";
      exit(1);
    }

    std::cout << argv[1] << std::endl;

    inet_pton(AF_INET, host.c_str(), &(sa.sin_addr));

    std::cout << "argc: " << argc << std::endl;

    for (int i = 0; i < argc; i++) {
      std::cout << argv[i] << std::endl;
    }

 return 0;
}
