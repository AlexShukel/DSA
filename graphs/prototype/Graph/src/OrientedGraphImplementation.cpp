//
// Created by alexs on 2023-05-29.
//

#include "OrientedGraphImplementation.h"

template<class TWeight>
OrientedGraphImplementation<TWeight>::OrientedGraphImplementation(const std::vector<std::vector<TWeight>> &matrix)
        : matrix(matrix) {
    edgeCount = 0;
    size_t size = matrix.size();

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            if (hasEdge(i, j)) {
                ++edgeCount;
            }
        }
    }
}

template<class TWeight>
Vertex OrientedGraphImplementation<TWeight>::addVertex() {
    matrix.resize(matrix.size() + 1);

    size_t size = matrix.size();

    matrix[size - 1].resize(size);
    std::fill(matrix[size - 1].begin(), matrix[size - 1].end(), 0);

    for (size_t i = 0; i < size - 1; ++i) {
        matrix[i].push_back(0);
    }

    return size - 1;
}

template<class TWeight>
void OrientedGraphImplementation<TWeight>::removeVertex(Vertex vertex) {
    edgeCount -= getNeighborCount(vertex);
    matrix.erase(matrix.begin() + vertex);

    size_t size = matrix.size();
    for (size_t i = 0; i < size; ++i) {
        if (hasEdge(i, vertex)) {
            --edgeCount;
        }
        matrix[i].erase(matrix[i].begin() + vertex);
    }
}

template<class TWeight>
void OrientedGraphImplementation<TWeight>::addEdge(Vertex from, Vertex to, TWeight weight) {
    if (!hasEdge(from, to)) {
        ++edgeCount;
    }

    matrix[from][to] = weight;
}

template<class TWeight>
void OrientedGraphImplementation<TWeight>::removeEdge(Vertex from, Vertex to) {
    if (hasEdge(from, to)) {
        --edgeCount;
    }

    matrix[from][to] = 0;
}

template<class TWeight>
TWeight OrientedGraphImplementation<TWeight>::getEdgeWeight(Vertex from, Vertex to) const {
    return matrix[from][to];
}

template<class TWeight>
bool OrientedGraphImplementation<TWeight>::hasEdge(Vertex from, Vertex to) const {
    // FIXME: this may not work with doubles
    return matrix[from][to] != 0;
}

template<class TWeight>
size_t OrientedGraphImplementation<TWeight>::getNeighborCount(Vertex vertex) const {
    size_t count = 0;

    for (size_t i = 0; i < matrix.size(); ++i) {
        if (hasEdge(vertex, i)) {
            ++count;
        }
    }

    return count;
}

template<class TWeight>
void OrientedGraphImplementation<TWeight>::getNeighbors(std::vector<Vertex> &neighbors, Vertex vertex) const {
    for (size_t i = 0; i < matrix.size(); ++i) {
        if (hasEdge(vertex, i)) {
            neighbors.push_back(i);
        }
    }
}

template<class TWeight>
size_t OrientedGraphImplementation<TWeight>::getVertexCount() const {
    return matrix.size();
}

template<class TWeight>
size_t OrientedGraphImplementation<TWeight>::getEdgeCount() const {
    return edgeCount;
}

template<class TWeight>
size_t OrientedGraphImplementation<TWeight>::inDeg(Vertex vertex) const {
    size_t degree = 0;

    for (size_t i = 0; i < matrix.size(); ++i) {
        if (hasEdge(i, vertex)) {
            ++degree;
        }
    }

    return degree;
}

template<class TWeight>
size_t OrientedGraphImplementation<TWeight>::outDeg(Vertex vertex) const {
    size_t degree = 0;

    for (size_t i = 0; i < matrix.size(); ++i) {
        if (hasEdge(vertex, i)) {
            ++degree;
        }
    }

    return degree;
}

template
class OrientedGraphImplementation<int>;
