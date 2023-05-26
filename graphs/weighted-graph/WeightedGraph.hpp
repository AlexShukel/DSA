//
// Created by alexs on 2023-05-26.
//

#ifndef DSA_WEIGHTEDGRAPH_H
#define DSA_WEIGHTEDGRAPH_H

#include <map>
#include "../graph/Graph.hpp"

template<class TVertex>
class WeightedGraph : public Graph<TVertex> {
private:
    std::map<std::pair<TVertex, TVertex>, size_t> weights;

public:
    void addEdge(TVertex first, TVertex second, size_t weight);

    // Function that set the weight to 1 by default
    void addEdge(TVertex first, TVertex second) override;

    void removeEdge(TVertex first, TVertex second) override;

    void removeVertex(TVertex vertex) override;

    size_t getEdgeWeight(TVertex first, TVertex second) const;
};

template<class TVertex>
void WeightedGraph<TVertex>::addEdge(TVertex first, TVertex second, size_t weight) {
    Graph<TVertex>::addEdge(first, second);
    weights[std::pair<TVertex, TVertex>(first, second)] = weight;
    weights[std::pair<TVertex, TVertex>(second, first)] = weight;
}

template<class TVertex>
size_t WeightedGraph<TVertex>::getEdgeWeight(TVertex first, TVertex second) const {
    auto it = weights.find(std::pair<TVertex, TVertex>(first, second));

    if (it == weights.end()) {
        throw std::logic_error("Cannot get weight of non-existing edge!");
    }

    return it->second;
}

template<class TVertex>
void WeightedGraph<TVertex>::addEdge(TVertex first, TVertex second) {
    addEdge(first, second, 1);
}

template<class TVertex>
void WeightedGraph<TVertex>::removeEdge(TVertex first, TVertex second) {
    Graph<TVertex>::removeEdge(first, second);
    weights.erase(std::pair<TVertex, TVertex>(first, second));
    weights.erase(std::pair<TVertex, TVertex>(second, first));
}

template<class TVertex>
void WeightedGraph<TVertex>::removeVertex(TVertex vertex) {
    Graph<TVertex>::removeVertex(vertex);

    for (auto it = weights.begin(); it != weights.end();) {
        auto &key = it->first;
        if (key.first == vertex || key.second == vertex) {
            it = weights.erase(it);
        } else {
            ++it;
        }
    }
}

#endif //DSA_WEIGHTEDGRAPH_H
