#include "SimpleHeader.h"
#include <bitset>
#include <iostream>

SimpleHeader::SimpleHeader() {}

unsigned int SimpleHeader::getHeader() const {
  return 1;
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

    unsigned long longhead = header.to_ulong();
    unsigned int headint = (int) longhead;
<<<<<<< HEAD
=======
  }

  void setType(unsigned int type) {
    packet.type.reset();

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

  void setWindow(unsigned int w) {
    packet.window.reset();

    std::bitset<5> bitWindow(w);
    for (int i = 0; i < 5; i++) {
      if (bitWindow[i] == 1) {
        packet.window.set(i);
      }
    }
  }

  void setSeqNum(unsigned int seqNum) {
    packet.seqnum.reset();

    std::bitset<8> bitSequence(seqNum);
    for (int i = 0; i < 8; i++) {
      if (bitSequence[i] == 1) {
        packet.seqnum.set(i);
      }
    }
  }

  void setLength(unsigned int l) {

  }

  void setTimestamp() {

  }

  void setCRC1() {

  }

  void setCRC2() {

>>>>>>> 49034efc4be7319bdc83fd3aab112d85e52e1dc4
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
