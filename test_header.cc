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
  std::bitset<2> b1(3);
  ASSERT_TRUE(h_->thePacket().type == b1);

  //test window
  h_->setWindow(3); //set to 3
  ASSERT_TRUE(h_->getWindow() == 3);
  std::bitset<5> b2(3);
  ASSERT_TRUE(h_->thePacket().window == b2);

  //test TR
  h_->setTR(1); //set to 1
  ASSERT_TRUE(h_->getTR() == 1);
  std::bitset<1> b3(1);
  ASSERT_TRUE(h_->thePacket().tr == b3);
  h_->setTR(10); //should produce error msg
  ASSERT_TRUE(h_->getTR() == 1); //should remain unchanged
  ASSERT_TRUE(h_->thePacket().tr == b3);

  //test seqnum
  h_->setSeqNum(3); //set to 3
  ASSERT_TRUE(h_->getSeqNum() == 3);
  std::bitset<8> b4(3);
  ASSERT_TRUE(h_->thePacket().seqnum == b4);

  //test length
  h_->setLength(3); //set to 3
  ASSERT_TRUE(h_->getLength() == 3);
  std::bitset<16> b5(3);
  ASSERT_TRUE(h_->thePacket().length == b5);

  //test timestamp
  h_->setTimestamp(3); //set to 3
  ASSERT_TRUE(h_->getTimestamp() == 3);
  std::bitset<32> b6(3);
  ASSERT_TRUE(h_->thePacket().timestamp == b6);

  //test crc1
  h_->setCRC1(3); //set to 3
  ASSERT_TRUE(h_->getCRC1() == 3);
  ASSERT_TRUE(h_->thePacket().crc1 == b6);

  //test crc2
  h_->setCRC2(3); //set to 3
  ASSERT_TRUE(h_->getCRC2() == 3);
  ASSERT_TRUE(h_->thePacket().crc2 == b6);

  //00000000000000000000000000000010000000000000000000000000000000100000000000000000000000000000001000000000000000100000001000010110
  //getHeader long long should == 158456325065422163343097070102
  unsigned long long myll = 158456325065422163343097070102;
  EXPECT_NO_THROW(std::cerr << h_->getHeader() << std::endl);
  EXPECT_EQUAL(h_->getHeader() == myll);
}
