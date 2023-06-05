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
    Data d;

    set<Data> set;
    set.insert(d);

//    a = 3;
//    auto it = set.find(5);
//    cout << *it;
    return 0;
}
