//
// Created by alexs on 2023-05-26.
//

#ifndef DSA_GRAPH_H
#define DSA_GRAPH_H

#include <map>
#include <vector>
#include <stdexcept>

template<class TVertex>
class Graph {
private:
    std::map<TVertex, std::vector<TVertex>> adj;
    size_t _edgesSize;

    bool hasVertex(TVertex vertex) const;

public:
    Graph();

    size_t verticesSize() const;

    size_t edgesSize() const;

    void addVertex(TVertex vertex);

    void addEdge(TVertex from, TVertex to);

    void removeVertex(TVertex vertex);

    void removeEdge(TVertex from, TVertex to);
};

template<class TVertex>
Graph<TVertex>::Graph(): _edgesSize(0) {}

template<class TVertex>
bool Graph<TVertex>::hasVertex(TVertex vertex) const {
    return adj.find(vertex) != adj.end();
}

template<class TVertex>
size_t Graph<TVertex>::verticesSize() const {
    return adj.size();
}

template<class TVertex>
size_t Graph<TVertex>::edgesSize() const {
    return _edgesSize;
}

template<class TVertex>
void Graph<TVertex>::addVertex(TVertex vertex) {
    if (hasVertex(vertex)) {
        throw std::logic_error("Cannot add existing vertex!");
    }

    adj[vertex] = std::vector<TVertex>();
}

template<class TVertex>
void Graph<TVertex>::addEdge(TVertex from, TVertex to) {
    if (!hasVertex(from) || !hasVertex(to)) {
        throw std::logic_error("Cannot create an edge with non-existing vertices!");
    }

    ++_edgesSize;
    adj[from].push_back(to);
}

template<class TVertex>
void Graph<TVertex>::removeVertex(TVertex vertex) {
    if (!hasVertex(vertex)) {
        throw std::logic_error("Cannot remove non-existing vertex!");
    }

    _edgesSize -= adj[vertex].size();
    adj[vertex].clear();
    adj.erase(vertex);

    for (auto &entry: adj) {
        auto &list = entry.second;
        auto prevSize = list.size();
        list.erase(std::remove(list.begin(), list.end(), vertex), list.end());
        _edgesSize -= prevSize - list.size();
    }
}

template<class TVertex>
void Graph<TVertex>::removeEdge(TVertex from, TVertex to) {
    if (!hasVertex(from) || !hasVertex(to)) {
        throw std::logic_error("Cannot remove an edge between non-existing vertices!");
    }

    auto it = adj[from].find(to);

    if (it == adj[from].end()) {
        throw std::logic_error("Cannot remove non-existing edge!");
    }

    --_edgesSize;
    adj[from].erase(it, it + 1);
}

#endif //DSA_GRAPH_H
