#include <iostream>
#include <map>
#include "AVL/Avl.hpp"

int main() {
    unsigned char a = 1;
    unsigned char b = 254;

    std::cout << static_cast<int>(static_cast<unsigned char>(a - b));

    return 0;
}
