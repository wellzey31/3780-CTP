#include "SimpleHeader.h"
#include <iostream>

using namespace std;

int main() {
  SimpleHeader s;

  s.setHeader(300);

  cout << s.getHeader() << endl;


  return 0;
}
