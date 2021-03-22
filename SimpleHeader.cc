#include "SimpleHeader.h"
#include <bitset>
#include <iostream>

SimpleHeader::SimpleHeader() {}

unsigned long long SimpleHeader::getHeader() const {
  std::bitset<128> temp;
  int count = 0;
  //add on type bits
  for (int i = 0; i < 2; i++) {
    if (packet.type[i] == 1) {
      temp.set(count);
      count++;
    }
  }
  //add on tr bit
  if (packet.tr[0] == 1) temp.set(2);
  count++;
  //add window bits to header
  for (int i = 0; i < 5; i++) {
    if (packet.window[i] == 1) {
      temp.set(count);
      count++;
    }
  }
  //add seqnum bits to header
  for (int i = 0; i < 8; i++) {
    if (packet.seqnum[i] == 1) {
      temp.set(count);
      count++;
    }
  }
  //add length bits to header
  for (int i = 0; i < 16; i++) {
    if (packet.length[i] == 1) {
      temp.set(count);
      count++;
    }
  }
  //add timestamp bits to header
  for (int i = 0; i < 32; i++) {
    if (packet.timestamp[i] == 1) {
      temp.set(count);
      count++;
    }
  }
  //add crc1 bits to header
  for (int i = 0; i < 32; i++) {
    if (packet.crc1[i] == 1) {
      temp.set(count);
      count++;
    }
  }
  //add crc2 bits to header
  for (int i = 0; i < 32; i++) {
    if (packet.crc2[i] == 1) {
      temp.set(count);
      count++;
    }
  }
  return temp.to_ullong();
}

void SimpleHeader::buildHeader(unsigned int length, unsigned int sequence,
  unsigned int type, unsigned int window)
  {
    std::bitset<32> header;
    //type should be 1,2,3 but never 0
    setType(type);
      //not sure how we deal with the TR (truncated bit) we think this gets done for us

      //window passed in as a value from 0 to 31
      setWindow(window);

      setSeqNum(sequence);

      std::bitset<16> bitLength(length);

      std::cout << "length: " << length << "\n";

      std::cout << "bitLength: " << bitLength << "\n";

      for (int i = 0; i < 16; i++) {
        if (bitLength[i] == 1) {
          header.set(i+16);
        }
      }
  }

  void SimpleHeader::setType(unsigned int type) {
    if (type != 0 ) packet.type.reset();

    switch (type) {
      case 1:
        packet.type.set(0); //sets rightmost bit to 1
      case 2:
        packet.type.set(1); //sets second from right to 1
      case 3:
        packet.type.set(0);
        packet.type.set(1);
    }
  }

  void SimpleHeader::setTR(unsigned int tr) {
    if (tr == 0 || tr == 1) {
      packet.tr.reset();
      if (tr == 1) packet.tr.set(0);
    } else {
      std::cerr << "Error with setTR parameter" << std::endl;
    }
  }

  void SimpleHeader::setWindow(unsigned int w) {
    packet.window.reset();

    std::bitset<5> bitWindow(w);
    for (int i = 0; i < 5; i++) {
      if (bitWindow[i] == 1) {
        packet.window.set(i);
      }
    }
  }

  void SimpleHeader::setSeqNum(unsigned int seqNum) {
    packet.seqnum.reset();

    std::bitset<8> bitSequence(seqNum);
    for (int i = 0; i < 8; i++) {
      if (bitSequence[i] == 1) {
        packet.seqnum.set(i);
      }
    }
  }

  void SimpleHeader::setLength(unsigned int l) {
    std::bitset<16> temp(l);
    packet.length.reset();
    for (int i = 0; i < 32; i++) {
      if (temp[i] == 1) {
        packet.length.set(i);
      }
    }
  }

  void SimpleHeader::setTimestamp(unsigned int num) {
    std::bitset<32> temp(num);
    packet.timestamp.reset();
    for (int i = 0; i < 32; i++) {
      if (temp[i] == 1) {
        pscket.timestamp.set(i);
      }
    }
  }

  void SimpleHeader::setCRC1(unsigned int num) {
    std::bitset<32> temp(num);
    packet.crc1.reset();
    for (int i = 0; i < 32; i++) {
      if (temp[i] == 1) {
        packet.crc1.set(i);
      }
    }
  }

  void SimpleHeader::setCRC2(unsigned int num) {
    std::bitset<32> temp(num);
    packet.crc2.reset();
    for (int i = 0; i < 32; i++) {
      if (temp[i] == 1) {
        packet.crc2.set(i);
      }
    }
  }

  unsigned int SimpleHeader::getType() {
    return (unsigned int) packet.type.to_ulong();
  }
  unsigned int SimpleHeader::getTR() {
    return (unsigned int) packet.tr.to_ulong();
  }
  unsigned int SimpleHeader::getWindow() {
    return (unsigned int) packet.window.to_ulong();
  }
  unsigned int SimpleHeader::getSeqNum() {
    return (unsigned int) packet.seqnum.to_ulong();
  }
  unsigned int SimpleHeader::getLength() {
    return (unsigned int) packet.length.to_ulong();
  }
  unsigned int SimpleHeader::getTimestamp() {
    return (unsigned int) packet.timestamp.to_ulong();
  }
  unsigned int SimpleHeader::getCRC1() {
    return (unsigned int) packet.crc1.to_ulong();
  }
  unsigned int SimpleHeader::getCRC2() {
    return (unsigned int) packet.crc2.to_ulong();
  }
