#include <iostream>
#include <map>
#include <utility>
#include "AVL/Avl.hpp"

class A {
private:
    std::vector<int> v;

public:
    explicit A(std::vector<int> v) : v(std::move(v)) {}

    void mutate() {
        v.push_back(42);
    }
};

int main() {
    std::cout << sizeof(long double);

    return 0;
}
