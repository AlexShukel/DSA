#include <iostream>
#include "AVL/Avl.hpp"

int main() {
    Avl<int> tree;
    tree.insertFromVector({8, 30, 62, 61, 70, 3, 40, 92, 11, 7, 5, 6, 91});

    return 0;
}
