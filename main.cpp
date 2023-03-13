#include <iostream>
#include "AVl/AVL.h"

int main() {
    AVL<int> tree;
    tree.insertFromVector({8, 30, 62, 61, 70, 3, 40, 92, 11, 7, 5, 6, 91});

    return 0;
}
