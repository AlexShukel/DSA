//
// Created by alexs on 2023-05-29.
//

#ifndef DSA_READABLEGRAPH_H
#define DSA_READABLEGRAPH_H

#include "config.h"
#include <vector>

template<class TWeight>
class ReadableGraph {
public:
    virtual TWeight getEdgeWeight(Vertex from, Vertex to) const = 0;

    virtual bool hasEdge(Vertex from, Vertex to) const = 0;

    virtual size_t getNeighborCount(Vertex vertex) const = 0;

    virtual void getNeighbors(std::vector<Vertex> &neighbors, Vertex vertex) const = 0;

    virtual size_t getVertexCount() const = 0;

    virtual size_t getEdgeCount() const = 0;

    virtual ~ReadableGraph() = default;
};

#endif //DSA_READABLEGRAPH_H
