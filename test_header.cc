#include "SimpleHeader.h"
#include "gtest/gtest.h"  // google test framework

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

/*TEST_F(HeaderTest, setHeader) {
  h_->setHeader(0x1234);
  struct simplepacket * ptr = static_cast<struct simplepacket*> (h_->thePacket());
  ASSERT_TRUE(ptr->msb == 0x12);
  ASSERT_TRUE(ptr->lsb == 0x34);

  //test buildHeader


}

TEST_F(HeaderTest, getHeader) {
  struct simplepacket * ptr = static_cast<struct simplepacket*> (h_->thePacket());
  ptr->msb = 0x56;
  ptr->lsb = 0xa2;
  ASSERT_TRUE(h_->getHeader() == 0x56a2);
}*/
