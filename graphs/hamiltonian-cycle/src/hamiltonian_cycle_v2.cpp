//
// Created by alexs on 2023-06-18.
//

#include "hamiltonian_cycle_v2.h"
#include <algorithm>
#include <cassert>

void getNextVertex(int **graph, int size, std::vector<int> &path, size_t position) {
    while (true) {
        path[position] = (path[position] + 1) % size;

        if (path[position] == 0) {
            return;
        }

        auto endIt = path.begin() + static_cast<int>(position);
        // Edge exists
        if (graph[path[position]][path[position - 1]] != 0 &&
            // Vertex is new in cycle
            std::find(path.begin(), endIt, path[position]) == endIt &&
            // There is an edge from start to current if it is the last vertex
            (position < size - 1 || (position == size - 1 && graph[0][path[position]] != 0))) {
            return;
        }
    }
}

void
hamiltonian_recursion(std::vector<std::vector<int>> &cycles, int **graph, int size, std::vector<int> &path,
                      size_t position) {
    if (position == size) {
        return;
    }

    while (true) {
        getNextVertex(graph, size, path, position);

        if (path[position] == 0) {
            return;
        }

        if (position == size - 1) {
            cycles.push_back(path);
        } else {
            hamiltonian_recursion(cycles, graph, size, path, position + 1);
        }
    }
}

bool cmp(const std::vector<int> &a, const std::vector<int> &b) {
    assert(a.size() == b.size());

    for (int i = 0; i < a.size(); ++i) {
        if (a[i] < b[i]) {
            return false;
        } else if (a[i] > b[i]) {
            return true;
        }
    }

    return false;
}

bool hamiltonian_cycle_v2(std::vector<int> &path, int **graph, int size, int start) {
    if (size < 3) {
        return false;
    }

    path.resize(size, 0);
    path[0] = start;

    std::vector<std::vector<int>> cycles;
    hamiltonian_recursion(cycles, graph, size, path, 1);

    bool hasCycle = !cycles.empty();

    if (hasCycle) {
        std::sort(cycles.begin(), cycles.end(), cmp);

        std::copy(cycles[0].begin(), cycles[0].end(), path.begin());
    } else {
        path.clear();
    }

    return hasCycle;
}
