#include "SimpleHeader.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <mutex>
#include <thread>

bool *windowAck;
int s;

std::mutex windowInfoMutex;

std::string getFileMsg(std::string file) {
  std::ifstream input(file, std::ios::binary);

  int i = 0;
  char c;
  std::string s = "";
  while(input.get(c)){
    s = s + c;
    ++i;
  }
  return s;
}

/*void listenAck() {
  unsigned char ack[640];
  int ackSize, ackSeqNum;
  bool ackError, ackNeg;
  SimpleHeader* ackHeader = new SimpleHeader();

  while (true) {
    ackSize = read(s, ack, 640);
    ackHeader -> deserializePacket(ack);

    std::cerr << ackHeader -> getType() << std::endl;
    if (ackHeader -> getType() == 2) {
      windowAck[ackSeqNum] = true;
    }
  }
}*/

int main(int argc, char const *argv[]) {
  int seqnum = 0;

  std::cout << argc << " ";
  for (int i = 0; i < argc; i++) {
    std::cout << argv[i] << " ";
  }

  int sread;

  struct sockaddr_in sa;
  std::string host, port, file, argv1;
  short unsigned int p;
  char msgin[1024] = {0};

  std::string msg, temp;

  s = socket(AF_INET, SOCK_STREAM, 0);

  argv1 = argv[1];

  if(s == -1) {
    std::cerr << "[ERROR] socket = -1.\n";
    exit(1);
  }

  if (argc == 3) {
    host = argv[1];
    port = argv[2];
    p = std::stoi(port);
    std::cout << "host: " << host << " port: " << port << std::endl;
    std::cout << "What would you like to say. " << std::endl;
    std::getline(std::cin, msg);
  }
  else if (argc == 5 && argv1.compare("-f") == 0) {
    host = argv[3];
    file = argv[2];
    port = argv[4];
    p = std::stoi(port);
    std::cout << "host: " << host << " port: " << port << " file: " << file << std::endl;
    msg = getFileMsg(file);
  }
  else {
        std::cerr << "[ERROR] incorrect arguments." << std::endl;
        std::cerr << "usage: sender -f <file> <ip> <port>\n";
        exit(1);
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

  //std::thread recvThread(&listenAck);
  windowAck = new bool[10];
  //recvThread.detach();

  SimpleHeader* header = new SimpleHeader();
  header -> setWindow(1);

  while (msg.compare("") != 0) {
    header -> setType(1);
    header -> setSeqNum(seqnum);
    header -> setTimestamp();
    header -> setCRC1();
    header -> setCRC2(0);

    msg = header -> setPaylod(msg);
    unsigned char buffer[640] = {};
    header -> serializePacket(buffer);

    send(s, buffer, 640, 0);
    ++seqnum;
  }

  header -> setType(3);
  header -> setSeqNum(seqnum);
  header -> setTimestamp();
  header -> setCRC1();
  header -> setCRC2(0);

  msg = header -> setPaylod("");
  unsigned char buffer[640];
  header -> serializePacket(buffer);
  send(s, buffer, 640, 0);

  /*if (windowAck[0] == true) {
    std::cout << "Works" << std::endl;
  } else {
    std::cout << "Not" << std::endl;
  }*/

  sread = read(s, msgin, 1024);
  std::cout << msgin << std::endl;

  delete header;
  return 0;
}
