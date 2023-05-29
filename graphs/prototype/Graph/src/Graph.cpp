//
// Created by alexs on 2023-05-29.
//

#include "Graph.h"

template<class TWeight>
Graph<TWeight>::Graph(TWeight **matrix, size_t size): orientedGraph(OrientedGraph<TWeight>(matrix, size)) {}

template<class TWeight>
Graph<TWeight>::Graph::Graph(const Graph<TWeight> &other): orientedGraph(other.orientedGraph) {}

template<class TWeight>
Vertex Graph<TWeight>::Graph::addVertex() {
    return orientedGraph.addVertex();
}

template<class TWeight>
void Graph<TWeight>::removeVertex(Vertex vertex) {
    orientedGraph.removeVertex(vertex);
}

template<class TWeight>
void Graph<TWeight>::addEdge(Vertex from, Vertex to) {
    orientedGraph.addEdge(from, to);
    orientedGraph.addEdge(to, from);
}

template<class TWeight>
void Graph<TWeight>::addEdge(Vertex from, Vertex to, TWeight weight) {
    orientedGraph.addEdge(from, to, weight);
    orientedGraph.addEdge(to, from, weight);
}

template<class TWeight>
void Graph<TWeight>::removeEdge(Vertex from, Vertex to) {
    orientedGraph.removeEdge(from, to);
    orientedGraph.removeEdge(to, from);
}

template<class TWeight>
TWeight Graph<TWeight>::getEdgeWeight(Vertex from, Vertex to) const {
    return orientedGraph.getEdgeWeight(from, to);
}

template<class TWeight>
bool Graph<TWeight>::hasEdge(Vertex from, Vertex to) const {
    return orientedGraph.hasEdge(from, to);
}

template<class TWeight>
size_t Graph<TWeight>::getNeighborCount(Vertex vertex) const {
    return orientedGraph.getNeighborCount(vertex);
}

template<class TWeight>
void Graph<TWeight>::getNeighbors(std::vector<Vertex> &neighbors, Vertex vertex) const {
    orientedGraph.getNeighbors(neighbors, vertex);
}

template<class TWeight>
size_t Graph<TWeight>::getVertexCount() const {
    return orientedGraph.getVertexCount();
}

template<class TWeight>
size_t Graph<TWeight>::getEdgeCount() const {
    return orientedGraph.getEdgeCount() / 2;
}

template<class TWeight>
size_t Graph<TWeight>::degree(Vertex vertex) const {
    return orientedGraph.inDeg(vertex);
}

template
class Graph<int>;
