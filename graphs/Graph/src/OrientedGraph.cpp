//
// Created by alexs on 2023-05-29.
//

#include "OrientedGraph.h"
#include "OrientedGraphImplementation.h"

template<class TWeight>
class OrientedGraph<TWeight>::Implementation {
public:
    OrientedGraphImplementation<TWeight> impl;

    Implementation() = default;

    explicit Implementation(const OrientedGraphImplementation<TWeight> &impl) : impl(impl) {}
};

template<class TWeight>
OrientedGraph<TWeight>::OrientedGraph(TWeight **input, size_t size) {
    std::vector<std::vector<TWeight>> matrix;
    matrix.resize(size);

    for (size_t i = 0; i < size; ++i) {
        matrix[i].resize(size);
        for (size_t j = 0; j < size; ++j) {
            matrix[i][j] = input[i][j];
        }
    }

    this->implementation = new Implementation(OrientedGraphImplementation<TWeight>(matrix));
}

template<class TWeight>
OrientedGraph<TWeight>::OrientedGraph(const OrientedGraph<TWeight> &other): implementation(
        new Implementation(*other.implementation)) {}

template<class TWeight>
OrientedGraph<TWeight>::~OrientedGraph() {
    delete implementation;
}

template<class TWeight>
Vertex OrientedGraph<TWeight>::addVertex() {
    return implementation->impl.addVertex();
}

template<class TWeight>
void OrientedGraph<TWeight>::removeVertex(Vertex vertex) {
    implementation->impl.removeVertex(vertex);
}

template<class TWeight>
void OrientedGraph<TWeight>::addEdge(Vertex from, Vertex to) {
    implementation->impl.addEdge(from, to, 1);
}

template<class TWeight>
void OrientedGraph<TWeight>::addEdge(Vertex from, Vertex to, TWeight weight) {
    implementation->impl.addEdge(from, to, weight);
}

template<class TWeight>
void OrientedGraph<TWeight>::removeEdge(Vertex from, Vertex to) {
    implementation->impl.removeEdge(from, to);
}

template<class TWeight>
TWeight OrientedGraph<TWeight>::getEdgeWeight(Vertex from, Vertex to) const {
    return implementation->impl.getEdgeWeight(from, to);
}

template<class TWeight>
bool OrientedGraph<TWeight>::hasEdge(Vertex from, Vertex to) const {
    return implementation->impl.hasEdge(from, to);
}

template<class TWeight>
size_t OrientedGraph<TWeight>::getNeighborCount(Vertex vertex) const {
    return implementation->impl.getNeighborCount(vertex);
}

template<class TWeight>
void OrientedGraph<TWeight>::getNeighbors(std::vector<Vertex> &neighbors, Vertex vertex) const {
    return implementation->impl.getNeighbors(neighbors, vertex);
}

template<class TWeight>
size_t OrientedGraph<TWeight>::getVertexCount() const {
    return implementation->impl.getVertexCount();
}

template<class TWeight>
size_t OrientedGraph<TWeight>::getEdgeCount() const {
    return implementation->impl.getEdgeCount();
}

template<class TWeight>
size_t OrientedGraph<TWeight>::inDeg(Vertex vertex) const {
    return implementation->impl.inDeg(vertex);
}

template<class TWeight>
size_t OrientedGraph<TWeight>::outDeg(Vertex vertex) const {
    return implementation->impl.outDeg(vertex);
}

template
class OrientedGraph<int>;

template
class OrientedGraph<double>;
