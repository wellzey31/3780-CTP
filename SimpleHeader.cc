#include "SimpleHeader.h"
#include <bitset>
#include <iostream>

SimpleHeader::SimpleHeader() {
}

unsigned int SimpleHeader::getHeader() const {
  return packet.lsb | (packet.msb<<8);
}

void SimpleHeader::buildHeader(unsigned int length, unsigned int sequence,
  unsigned int type, unsigned int window)
  {
    std::bitset<32> header;
    //type should be 1,2,3 but never 0
    if (type != 0) {
      switch (type) {
        case 1:
          header.set(0); //sets rightmost bit to 1
        case 2:
          header.set(1); //sets second from right to 1
        case 3:
          header.set(0);
          header.set(1);
      }
      //not sure how we deal with the TR (truncated bit) we think this gets done for us

      //window passed in as a value from 0 to 31
      std::bitset<5> bitWindow(window);
      for (int i = 0; i < 5; i++) {
        if (bitWindow[i] == 1) {
          header.set(i+3);
        }
      }

      std::bitset<8> bitSequence(sequence);

      std::cout << "sequence: " << sequence << "\n";

      std::cout << "bitSequence: " << bitSequence << "\n";

      for (int i = 0; i < 8; i++) {
        if (bitSequence[i] == 1) {
          header.set(i+8);
        }
      }

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
    setHeader(headint);
  }

  unsigned int SimpleHeader::getType() {
    std::bitset<32>
  }
  unsigned int SimpleHeader::getTR();
  unsigned int SimpleHeader::getWindow();
  unsigned int SimpleHeader::getSeqNum();
  unsigned int SimpleHeader::getLength();
  unsigned int SimpleHeader::getTimestamp();
  unsigned int SimpleHeader::getCRC();
