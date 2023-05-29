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
    std::vector<int> v = {1, 2, 3};
    A a(v);
    a.mutate();
    for (auto x: v) {
        std::cout << x << " ";
    }

    return 0;
}
