#ifndef __SIMPLEHEADER_H
#define __SIMPLEHEADER_H

#include <cstdint>
#include <bitset>
#include <fstream>
#include <iterator>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <iostream>

#define DATA_SZ 512

struct simplepacket {
  std::bitset<2> type;
  std::bitset<1> tr;
  std::bitset<5> window;
  std::bitset<8> seqnum;
  std::bitset<16> length;
  std::time_t timestamp;
  std::bitset<32> crc1;
  std::bitset<32> crc2;
  char data[DATA_SZ];
    // payload
};

// class to be tested. Implements a simple packet structure consisting of a 16 bit integer + data
class SimpleHeader {
private:
  struct simplepacket packet;

  unsigned char* serializeChar(unsigned char* b);
  unsigned char* serializeString(unsigned char* b, std::string s, int i);

public:
  // default constructor initializes the header to zero.
  SimpleHeader();

  // returns the header as 128 bit bitset object
  std::bitset<128> getHeader();

  void buildHeader(unsigned int length, unsigned int sequence,
    unsigned int type, unsigned int window);

  void serializePacket(unsigned char* b);

  void deserializePacket(unsigned char* b);
  template <size_t bitsetSize>
  void deserializeBitset(int &i, int j, unsigned char* b, std::bitset<bitsetSize> &p);
  void deserializeString(int &i, int j, unsigned char* b);
  //getters to return values as int for each header field
  unsigned int getType();
  unsigned int getTR();
  unsigned int getWindow();
  unsigned int getSeqNum();
  unsigned int getLength();
  unsigned int getTimestamp();
  unsigned int getCRC1();
  unsigned int getCRC2();

  //setters to return values as int for each header field
  void setType(unsigned int t);
  void setTR(unsigned int t);
  void setWindow(unsigned int w);
  void setSeqNum(unsigned int seqNum);
  void setLength(unsigned int l);
  void setTimestamp();
  void setCRC1(unsigned int num);
  void setCRC2(unsigned int num);


  // returns the size of the packet, including headers and data
  // to be used with recvfrom() or sendto()
  int packetSize() const {
    return sizeof(simplepacket);
  }

  // returns the size of the payload. Use with reading / writing to/from files
  int payloadSize() const {
    return DATA_SZ;
  }

  // returns pointer to the structure holding the thePacket, including the headers
  // To be used with recvfrom or sendto
  simplepacket thePacket() {
    return packet;
  }

  std::string setPaylod(std::string msg) {
  int i;
  for (int j = 0; j < DATA_SZ; ++j) {
    packet.data[j] = 0;
  }

    for (i = 0; i < msg.length() && i < DATA_SZ; ++i) {
      packet.data[i] = msg[i];
    }
    msg.erase(0, i);
    setLength(i);

    return msg;
  }

  std::string thePayload() {
    return packet.data;
  }
};

#endif
