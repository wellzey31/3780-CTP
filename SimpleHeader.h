#ifndef __SIMPLEHEADER_H
#define __SIMPLEHEADER_H

#include <cstdint>
#include <bitset>
#define DATA_SZ 256

struct simplepacket {
  std::bitset<2> type;
  std::bitset<1> tr;
  std::bitset<5> window;
  std::bitset<8> seqnum;
  std::bitset<16> length;
  std::bitset<32> timestamp;
  std::bitset<32> crc1;
  std::bitset<32> crc2;
  char data[DATA_SZ];  // payload
};

// class to be tested. Implements a simple packet structure consisting of a 16 bit integer + data
class SimpleHeader {
private:
  struct simplepacket packet;

public:
  // default constructor initializes the header to zero.
  SimpleHeader();

  // returns the header value
  unsigned long long getHeader() const;

  void buildHeader(unsigned int length, unsigned int sequence,
    unsigned int type, unsigned int window);

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
  void setTimestamp(unsigned int num);
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
  simplepacket * thePacket() {
    return packet;
  }

  void * thePayload() {
    return packet.data;
  }
};

#endif
