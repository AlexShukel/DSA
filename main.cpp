#include <iostream>
#include "AVL/Avl.hpp"

int main() {
    std::vector<int> list = {1, 2, 3, 5, 2, 5, 2};
    list.erase(std::remove(list.begin(), list.end(), 2), list.end());
    for (auto x: list) {
        std::cout << x << " ";
    }

    return 0;
}
