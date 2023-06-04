#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto it = v.begin() + 2;
    v.erase(it + 1, v.end());
    for (auto x: v) {
        std::cout << x << " ";
    }
    return 0;
}
