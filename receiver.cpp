#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include "header.h"
#include <iostream>
#define PORT 8080

int main(int argc, char const *argv[]) {

  if (argc < 3 || argc > 4) {
        std::cerr << "[ERROR] incorrect arguments.";
        std::cerr << "usage: receiver -f <file> <port>\n";
        exit(1);
    }

  

 return 0;
}
