#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>

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
    int n = 10;
    int *arr = (int *) malloc(n * sizeof(int));

    for (int i = 0; i < n; ++i) {
        arr[i] = i;
    }

    arr = (int *) realloc(arr, 6 * sizeof(int));

    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }

    return 0;
}
