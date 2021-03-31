#include "SimpleHeader.h"
#include <iostream>
#include <bitset>
#include <fstream>
#include <iterator>
#include <algorithm>

int main()
{
    std::ifstream input( "myText.txt", std::ios::binary );
    std::ofstream output( "output.txt", std::ios::binary );

    std::copy(
        std::istreambuf_iterator<char>(input),
        std::istreambuf_iterator<char>( ),
        std::ostreambuf_iterator<char>(output));
}
