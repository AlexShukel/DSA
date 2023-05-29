//
// Created by alexs on 2023-05-29.
//

#ifndef DSA_ORIENTEDGRAPH_H
#define DSA_ORIENTEDGRAPH_H

#include <vector>
#include "config.h"
#include "ReadableGraph.h"

template<class TWeight>
class OrientedGraph : public ReadableGraph<TWeight> {
private:
    class Implementation;

    Implementation *implementation;
public:
    OrientedGraph(TWeight **matrix, size_t size);

    OrientedGraph(const OrientedGraph<TWeight> &other);

    ~OrientedGraph();

    Vertex addVertex();

    void removeVertex(Vertex vertex);

    void addEdge(Vertex from, Vertex to);

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

#endif //DSA_ORIENTEDGRAPH_H
