#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <cstring>

int main(int argc, char const *argv[]) {
  int s, sread;

  struct sockaddr_in sa;
  struct addrinfo hints, *res;
  std::string host, port, file, msg;
  char msgin[1024] = {0};

  memset(&hints, 0, sizeof hints); //makes sure the struct is empty
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  s = socket(res -> ai_family, res -> ai_socktype, res -> ai_protocol);

  if(s == -1) {
    std::cerr << "[ERROR] socket = -1.\n";
    exit(1);
  }

  if (argc < 3 || argc > 5) {
        std::cerr << "[ERROR] incorrect arguments." << std::endl;
        std::cerr << "usage: sender -f <file> <ip> <port>\n";
        exit(1);
  }
  else if (argc == 5) { //&& argv[1] == "-f") {
    host = argv[3];
    file = argv[2];
    port = argv[4];
    std::cout << "host: " << host << " port: " << port << " file: " << file << std::endl;
  }

  getaddrinfo(host.c_str(), port.c_str(), &hints, &res);

  if(inet_pton(AF_INET, host.c_str(), &(sa.sin_addr)) <=0 )
  {
    std::cerr << "[ERROR] Invalid address" << std::endl;
    exit(1);
  }

  if(connect(s, (struct sockaddr *)&sa, sizeof(sa)) < 0)
  {
    std::cerr << "[ERROR] Connection failled";
    exit(1);
  }

  std::cout << "What message would you like to send? ";
  std::cin >> msg;

  send(s, msg.c_str(), strlen(msg.c_str()), 0);
  sread = read(s, msgin, 1024);
  std::cout << msgin << std::endl;

  return 0;
}
