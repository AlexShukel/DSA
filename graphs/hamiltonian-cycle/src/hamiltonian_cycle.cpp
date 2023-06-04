//
// Created by alexs on 2023-05-30.
//

#include "hamiltonian_cycle.h"
#include <algorithm>
#include <limits>
#include <iostream>

#define NULL_VERTEX std::numeric_limits<Vertex>::max()

bool construct_hamiltonian_cycle(std::vector<Vertex> &path, AbstractGraph<int> *graph, size_t position) {
    size_t size = graph->getVertexCount();
    Vertex last_vertex = path[position - 1];

    if (position == size) {
        return graph->hasEdge(last_vertex, path[0]);
    }

    std::vector<Vertex> neighbors;
    graph->getNeighbors(neighbors, last_vertex);

    for (Vertex &i: neighbors) {
        if (std::find(path.begin(), path.end(), i) == path.end()) {
            path[position] = i;

            if (construct_hamiltonian_cycle(path, graph, position + 1)) {
                return true;
            }

            path[position] = NULL_VERTEX;
        }
    }

    return false;
}

bool hamiltonian_cycle(std::vector<Vertex> &path, AbstractGraph<int> *graph, Vertex start) {
    size_t size = graph->getVertexCount();

    if (size == 0) {
        return false;
    }

    path.resize(size, NULL_VERTEX);
    path[0] = start;

    bool result = construct_hamiltonian_cycle(path, graph, 1);

    if (!result) {
        path.clear();
    }

    return result;
}
