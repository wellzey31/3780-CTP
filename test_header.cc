#include "SimpleHeader.h"
#include "gtest/gtest.h"  // google test framework
#include <bitset>

class HeaderTest : public testing::Test {
protected:
  SimpleHeader * h_;

  void SetUp() override {
    h_ = new SimpleHeader;  // create a new class before each test to start fresh
  }

  void TearDown() override {
    delete h_;
  }
};

TEST_F(HeaderTest, setHeader) {

  //test type
  h_->setType(3); //set to 3
  h_->setType(0); //should ignore 0 and remain 3
  ASSERT_TRUE(h_->getType() == 3);
  ASSERT_TRUE(h_->packet.type == std::bitset<2> b1(3));

  //test window
  h_->setWindow(3); //set to 3
  ASSERT_TRUE(h_->getWindow() == 3);
  ASSERT_TRUE(h_->packet.window == std::bitset<5> b2(3));

  //test TR
  h_->setTR(1); //set to 1
  ASSERT_TRUE(h_->getTR() == 1);
  ASSERT_TRUE(h_->packet.tr == std::bitset<1> b3(1));
  h_->setTR(10); //should produce error msg
  ASSERT_TRUE(h_->getTR() == 1); //should remain unchanged
  ASSERT_TRUE(h_->packet.tr == b3;

  //test seqnum
  h_->setSeqNum(3); //set to 3
  ASSERT_TRUE(h_->getSeqNum() == 3);
  ASSERT_TRUE(h_->packet.seqnum == std::bitset<8> b4(3));

  //test length
  h_->setLength(3); //set to 3
  ASSERT_TRUE(h_->getLength() == 3);
  ASSERT_TRUE(h_->packet.length == std::bitset<16> b5(3));

  //test timestamp
  h_->setTimestamp(3); //set to 3
  ASSERT_TRUE(h_->getTimestamp() == 3);
  ASSERT_TRUE(h_->packet.timestamp == std::bitset<32> b6(3));

  //test crc1
  h_->setCRC1(3); //set to 3
  ASSERT_TRUE(h_->getCRC1() == 3);
  ASSERT_TRUE(h_->packet.crc1 == std::bitset<32> b7(3));

  //test crc2
  h_->setCRC2(3); //set to 3
  ASSERT_TRUE(h_->getCRC2() == 3);
  ASSERT_TRUE(h_->packet.crc2 == std::bitset<32> b7(3));

  //00000000000000000000000000000010000000000000000000000000000000100000000000000000000000000000001000000000000000100000001000010110
  //getHeader long long should == 158456325065422163343097070102
  unsigned long long myll = 158456325065422163343097070102;
  ASSERT_TRUE(h_->getHeader() == myll);
}
