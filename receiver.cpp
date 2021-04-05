#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <cstring>
#include <fstream>

#include "SimpleHeader.h"

int main(int argc, char const *argv[]) {
  int s, new_socket, valread;

  struct sockaddr_in sa;
  int opt = 1;
  int addrlen = sizeof(sa);
  unsigned char buffer[1024] = {0};
  std::string port, file, argv1;
  char *message = "Hola este es el servidor";

  argv1 = argv[1];

  if (argc < 2 || argc > 4) {
        std::cerr << "[ERROR] incorrect arguments.";
        std::cerr << "usage: receiver -f <file> <port>\n";
        exit(1);
    } else if (argc == 2) {
        port = argv[1];
        std::cout << " port: " << port << std::endl;
    }  else if (argc == 4 && argv1.compare("-f") == 0) {
        file = argv[2];
        port = argv[3];
        std::cout << " port: " << port << " file: " << file << std::endl;
    }

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == 0 ) {
      std::cerr << "Socket failed" << std::endl;
      exit(EXIT_FAILURE);
    }

    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
      std::cerr << "setsockopt" << std::endl;
      exit(EXIT_FAILURE);
    }

    unsigned short portnum = (unsigned short) std::strtoul(port.c_str(), NULL, 0);

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = INADDR_ANY;
    sa.sin_port = htons( portnum );

    // Forcefully attaching socket to the port 8080
    if (bind(s, (struct sockaddr *)&sa,
                                 sizeof(sa))<0)
    {
        std::cerr << "bind failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (listen(s, 3) < 0)
    {
        std::cerr << "listen" << std::endl;
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(s, (struct sockaddr *)&sa,
                       (socklen_t*)&addrlen))<0)
    {
        std::cerr << "accept" << std::endl;
        exit(EXIT_FAILURE);
    }
  std::string eop = "end of packet.\n";
  std::string msg = "";
  while (true) {
    valread = read(new_socket, buffer, 640);

    SimpleHeader* read = new SimpleHeader();
    read -> deserializePacket(buffer);
    if (read -> getType() == 3) {
      break;
    }

    msg = msg + read -> thePacket().data;
    msg = msg + eop;
  }

  if (argv1.compare("-f") == 0) {
    std::ofstream input(file, std::ios::binary);
    input << msg;
    input.close();
  } else {
    printf("%s\n", msg);
  }

    send(new_socket , message , strlen(message) , 0 );
    printf("Mensaje de servidor enviado\n");

 return 0;
}
