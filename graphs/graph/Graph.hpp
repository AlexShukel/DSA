//
// Created by alexs on 2023-05-26.
//

#ifndef DSA_GRAPH_H
#define DSA_GRAPH_H

#include "../oriented-graph/OrientedGraph.hpp"

template<class TVertex>
class Graph : public OrientedGraph<TVertex> {

public:
    using OrientedGraph<TVertex>::edgesSize;

    void addEdge(TVertex first, TVertex second) override;

    void removeEdge(TVertex first, TVertex second) override;

    void removeVertex(TVertex vertex) override;

    bool hasEdge(TVertex first, TVertex second) const override;
};

template<class TVertex>
void Graph<TVertex>::addEdge(TVertex first, TVertex second) {
    OrientedGraph<TVertex>::addEdge(first, second);
    OrientedGraph<TVertex>::addEdge(second, first);
    OrientedGraph<TVertex>::setEdgesSize(OrientedGraph<TVertex>::edgesSize() - 1);
}

template<class TVertex>
void Graph<TVertex>::removeEdge(TVertex first, TVertex second) {
    OrientedGraph<TVertex>::removeEdge(first, second);
    OrientedGraph<TVertex>::removeEdge(second, first);

    OrientedGraph<TVertex>::setEdgesSize(OrientedGraph<TVertex>::edgesSize() + 1);
}

template<class TVertex>
void Graph<TVertex>::removeVertex(TVertex vertex) {
    size_t oldEdgesSize = edgesSize();
    OrientedGraph<TVertex>::removeVertex(vertex);
    size_t newEdgesSize = edgesSize();

    OrientedGraph<TVertex>::setEdgesSize(newEdgesSize + (oldEdgesSize - newEdgesSize) / 2);
}

template<class TVertex>
bool Graph<TVertex>::hasEdge(TVertex first, TVertex second) const {
    return OrientedGraph<TVertex>::hasEdge(first, second) || OrientedGraph<TVertex>::hasEdge(second, first);
}

#endif //DSA_GRAPH_H
