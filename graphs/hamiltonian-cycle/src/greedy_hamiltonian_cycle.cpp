//
// Created by alexs on 2023-06-04.
//

#include "greedy_hamiltonian_cycle.h"
#include <algorithm>

bool greedy_hamiltonian_cycle(std::vector<Vertex> &path, AbstractGraph<int> *graph, Vertex start) {
    size_t size = graph->getVertexCount();

    if (size < 3) {
        return false;
    }

    std::vector<bool> visited(size, false);

    visited[start] = true;
    path.push_back(start);

    while (true) {
        std::vector<Vertex> neighbors;
        graph->getNeighbors(neighbors, path.back());

        // Avoid going on bridge
        auto candidate = std::find_if(neighbors.begin(), neighbors.end(), [graph, visited](const Vertex &vertex) {
            return !visited[vertex] && graph->getNeighborCount(vertex) > 1;
        });

        if (candidate == neighbors.end()) {
            break;
        }

        path.push_back(*candidate);
        visited[*candidate] = true;
    }

    if (graph->hasEdge(path.back(), start)) {
        // Hamiltonian cycle found
        return true;
    }

    for (auto it = path.rbegin(); it != path.rend(); ++it) {
        if (graph->hasEdge(*it, start)) {
            path.erase(it.base(), path.end());

            if (path.size() < 3) {
                // No cycle found
                path.clear();
            }

            // Some cycle found
            return false;
        }
    }

    // No cycle found
    path.clear();
    return false;
}
