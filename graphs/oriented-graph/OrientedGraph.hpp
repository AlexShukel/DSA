//
// Created by alexs on 2023-05-26.
//

#ifndef DSA_ORIENTED_GRAPH_H
#define DSA_ORIENTED_GRAPH_H

#include <map>
#include <vector>
#include <stdexcept>
#include <algorithm>

template<class TVertex>
class OrientedGraph {
private:
    std::map<TVertex, std::vector<TVertex>> adj;
    size_t _edgesSize;

protected:
    bool hasVertex(TVertex vertex) const;

    void setEdgesSize(size_t newSize);

public:
    OrientedGraph();

    size_t verticesSize() const;

    size_t edgesSize() const;

    void addVertex(TVertex vertex);

    virtual void addEdge(TVertex from, TVertex to);

    virtual void removeVertex(TVertex vertex);

    virtual void removeEdge(TVertex from, TVertex to);

    size_t getVertexNeighboursCount(TVertex vertex) const;

    std::vector<TVertex> getNeighbours(TVertex vertex) const;

    TVertex getNeighbour(TVertex vertex, size_t pos) const;

    virtual bool hasEdge(TVertex from, TVertex to) const;
};

template<class TVertex>
OrientedGraph<TVertex>::OrientedGraph(): _edgesSize(0) {}

template<class TVertex>
bool OrientedGraph<TVertex>::hasVertex(TVertex vertex) const {
    return adj.find(vertex) != adj.end();
}

template<class TVertex>
size_t OrientedGraph<TVertex>::verticesSize() const {
    return adj.size();
}

template<class TVertex>
size_t OrientedGraph<TVertex>::edgesSize() const {
    return _edgesSize;
}

template<class TVertex>
void OrientedGraph<TVertex>::addVertex(TVertex vertex) {
    if (hasVertex(vertex)) {
        throw std::logic_error("Cannot add existing vertex!");
    }

    adj[vertex] = std::vector<TVertex>();
}

template<class TVertex>
void OrientedGraph<TVertex>::addEdge(TVertex from, TVertex to) {
    if (!hasVertex(from) || !hasVertex(to)) {
        throw std::logic_error("Cannot create an edge with non-existing vertices!");
    }

    auto &neighbours = adj[from];

    if (std::find(neighbours.begin(), neighbours.end(), to) != neighbours.end()) {
        throw std::logic_error("Cannot add an existing edge in non-multi graph!");
    }

    ++_edgesSize;
    neighbours.push_back(to);
}

template<class TVertex>
void OrientedGraph<TVertex>::removeVertex(TVertex vertex) {
    if (!hasVertex(vertex)) {
        throw std::logic_error("Cannot remove non-existing vertex!");
    }

    auto &neighbours = adj[vertex];

    _edgesSize -= neighbours.size();
    neighbours.clear();
    adj.erase(vertex);

    for (auto &entry: adj) {
        auto &list = entry.second;
        auto prevSize = list.size();
        list.erase(std::remove(list.begin(), list.end(), vertex), list.end());
        _edgesSize -= prevSize - list.size();
    }
}

template<class TVertex>
void OrientedGraph<TVertex>::removeEdge(TVertex from, TVertex to) {
    if (!hasVertex(from) || !hasVertex(to)) {
        throw std::logic_error("Cannot remove an edge between non-existing vertices!");
    }

    auto &list = adj[from];
    auto it = std::find(list.begin(), list.end(), to);

    if (it == adj[from].end()) {
        throw std::logic_error("Cannot remove non-existing edge!");
    }

    --_edgesSize;
    adj[from].erase(it, it + 1);
}

template<class TVertex>
size_t OrientedGraph<TVertex>::getVertexNeighboursCount(TVertex vertex) const {
    if (!hasVertex(vertex)) {
        throw std::logic_error("Cannot count the neighbours of non-existing vertex!");
    }

    return (*adj.find(vertex)).second.size();
}

template<class TVertex>
std::vector<TVertex> OrientedGraph<TVertex>::getNeighbours(TVertex vertex) const {
    if (!hasVertex(vertex)) {
        throw std::logic_error("Cannot return neighbours of non-existing vertex!");
    }

    return adj.find(vertex)->second;
}

template<class TVertex>
TVertex OrientedGraph<TVertex>::getNeighbour(TVertex vertex, size_t pos) const {
    if (!hasVertex(vertex)) {
        throw std::logic_error("Cannot return a neighbour of non-existing vertex!");
    }

    auto &list = adj.find(vertex)->second;

    if (pos >= list.size()) {
        throw std::logic_error("Position of neighbour is out of bounds!");
    }

    return list[pos];
}

template<class TVertex>
bool OrientedGraph<TVertex>::hasEdge(TVertex from, TVertex to) const {
    if (!hasVertex(from) || !hasVertex(to)) {
        throw std::logic_error("Cannot determine if there is an edge between non-existing vertices!");
    }

    auto &list = adj.find(from)->second;
    return std::find(list.begin(), list.end(), to) != list.end();
}

template<class TVertex>
void OrientedGraph<TVertex>::setEdgesSize(size_t newSize) {
    _edgesSize = newSize;
}

#endif //DSA_ORIENTED_GRAPH_H
