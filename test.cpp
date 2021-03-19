#include "SimpleHeader.h"
#include <iostream>
#include <bitset>

using namespace std;

int main() {
  SimpleHeader s;

  s.setHeader(16);

  s.buildHeader(512, 256, 3, 31);

  cout<< endl;

  //cout << s.getHeader() << endl;


  return 0;
}
