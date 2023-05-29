//
// Created by alexs on 2023-05-29.
//

#ifndef DSA_GRAPH_H
#define DSA_GRAPH_H

#include "OrientedGraph.h"

template<class TWeight>
class Graph {
private:
    OrientedGraph<TWeight> orientedGraph;

public:
    Graph(TWeight **matrix, size_t size);

    Graph(const Graph<TWeight> &other);

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

    size_t degree(Vertex vertex) const;
};

#endif //DSA_GRAPH_H
