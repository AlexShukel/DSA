#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Data {
public:
    Data() {
        cout << "Create data\n";
    }

    Data(const Data &other) {
        cout << "Copy data\n";
    }

    Data &operator=(const Data &other) {
        cout << "Assignment operator call\n";
        return *this;
    }

    bool operator<(const Data &other) const {
        return false;
    }
};

struct Node {
    const Data &field;

    explicit Node(const Data &data) : field(data) {}
};

int main() {
    vector<int> v = {1, 2, 3, 4};
    auto it = std::find(v.begin(), v.begin() + 1, 2);
    if (it == v.end()) {
        std::cout << "hello";
    }
    return 0;
}
