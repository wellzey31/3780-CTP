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
  std::string host, port, file;
  short unsigned int p;
  char msgin[1024] = {0};

  char *msg = "hello";

  s = socket(AF_INET, SOCK_STREAM, 0);

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
    p = std::stoi(port);
    std::cout << "host: " << host << " port: " << port << " file: " << file << std::endl;
  }

  sa.sin_family = AF_INET;
	sa.sin_port = htons(p);


  if (inet_pton(AF_INET, host.c_str(), &(sa.sin_addr)) <=0 )
  {
    std::cerr << "[ERROR] Invalid address" << std::endl;
    exit(1);
  }

  if (connect(s, (struct sockaddr *)&sa, sizeof(sa)) < 0)
  {
    std::cerr << "[ERROR] Connection failled";
    exit(1);
  }

  send(s, msg, strlen(msg), 0);
  std::cout << "Message sent." << std::endl;
  sread = read(s, msgin, 1024);
  std::cout << msgin << std::endl;

  return 0;
}
