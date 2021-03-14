#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <iostream>
#define PORT 8080

/* struct sockaddr {
  unsigned short sa_family;    // address family, AF_xxx
  char sa_data[14];            // 14 bytes of protocol address
}; */

struct addrinfo {
  int ai_flags;                 //AI_PASSIVe, AI_CANONNAME, etc
  int ai_family;                //AF_INET,
  int ai_socktype;              //SOCK_STREAM, SOCK_DGRAM
  int ai_protocol = 0;          //0 for "any"
  size_t ai_addrlen;            //size of ai_addr in bytes
  struct sockaddr *ai_addr;     //struct sockaddr_in
  char *ai_canonname;           //full canonical hostname

  struct addrinfo *ai_next;     //linked list
};

// Internet address
struct in_addr {
  uint32_t s_addr;             //32-bit int
};

struct sockaddr_in {
  short int sin_family;         //Address family, AF_INET
  unsigned short int sin_port;  //Port number
  struct in_addr sin_addr;      //Internet address
  unsigned char sin_zero[8];    //Same size as struct sockadd
};

int main(int argc, char const *argv[]) {

  if (argc < 3 || argc > 4) {
        std::cerr << "[ERROR] incorrect arguments.";
        std::cerr << "usage: receiver -f <file> <port>\n";
        exit(1);
    }

  std::cout << "argc: " << argc << std::endl;

  for (int i = 0; i < argc; i++) {
    std::cout << argv[i] << std::endl;
  }

 return 0;
}
