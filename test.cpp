#include "SimpleHeader.h"
#include <iostream>

using namespace std;

int main() {
  SimpleHeader s;

  s.setHeader(16);

  s.buildHeader(512, 256, 3, 31);

  cout << s.getHeader() << endl;


  return 0;
}
