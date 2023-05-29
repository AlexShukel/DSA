//
// Created by alexs on 2023-05-29.
//

#ifndef DSA_ORIENTEDGRAPHIMPLEMENTATION_H
#define DSA_ORIENTEDGRAPHIMPLEMENTATION_H

#include <vector>
#include "config.h"

template<class TWeight>
class OrientedGraphImplementation {
private:
    // Matrix of weights that represents graph structure
    std::vector<std::vector<TWeight>> matrix;
    size_t edgeCount;

public:
    explicit OrientedGraphImplementation(const std::vector<std::vector<TWeight>> &matrix);

    Vertex addVertex();

    void removeVertex(Vertex vertex);

    void addEdge(Vertex from, Vertex to, TWeight weight);

    void removeEdge(Vertex from, Vertex to);

    TWeight getEdgeWeight(Vertex from, Vertex to) const;

    bool hasEdge(Vertex from, Vertex to) const;

    size_t getNeighborCount(Vertex vertex) const;

    void getNeighbors(std::vector<Vertex> &neighbors, Vertex vertex) const;

    size_t getVertexCount() const;

    size_t getEdgeCount() const;

    size_t inDeg(Vertex vertex) const;

    size_t outDeg(Vertex vertex) const;
};

#endif //DSA_ORIENTEDGRAPHIMPLEMENTATION_H
