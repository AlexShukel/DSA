//
// Created by alexs on 2023-05-26.
//

#ifndef DSA_WEIGHTEDORIENTEDGRAPH_HPP
#define DSA_WEIGHTEDORIENTEDGRAPH_HPP

#include "../oriented-graph/OrientedGraph.hpp"

template<class TVertex>
class WeightedOrientedGraph : public OrientedGraph<TVertex> {
private:
    std::map<std::pair<TVertex, TVertex>, size_t> weights;

public:
    void addEdge(TVertex from, TVertex to, size_t weight);

    // Function that set the weight to 1 by default
    void addEdge(TVertex from, TVertex to) override;

    void removeEdge(TVertex from, TVertex to) override;

    void removeVertex(TVertex vertex) override;

    size_t getEdgeWeight(TVertex from, TVertex to) const;
};

template<class TVertex>
void WeightedOrientedGraph<TVertex>::addEdge(TVertex from, TVertex to, size_t weight) {
    OrientedGraph<TVertex>::addEdge(from, to);
    weights[std::pair<TVertex, TVertex>(from, to)] = weight;
}

template<class TVertex>
void WeightedOrientedGraph<TVertex>::addEdge(TVertex from, TVertex to) {
    addEdge(from, to, 1);
}

template<class TVertex>
void WeightedOrientedGraph<TVertex>::removeEdge(TVertex from, TVertex to) {
    OrientedGraph<TVertex>::removeEdge(from, to);
    weights.erase(std::pair<TVertex, TVertex>(from, to));
}

template<class TVertex>
void WeightedOrientedGraph<TVertex>::removeVertex(TVertex vertex) {
    OrientedGraph<TVertex>::removeVertex(vertex);

    for (auto it = weights.begin(); it != weights.end();) {
        auto &key = it->first;
        if (key.first == vertex || key.second == vertex) {
            it = weights.erase(it);
        } else {
            ++it;
        }
    }
}

template<class TVertex>
size_t WeightedOrientedGraph<TVertex>::getEdgeWeight(TVertex from, TVertex to) const {
    auto it = weights.find(std::pair<TVertex, TVertex>(from, to));

    if (it == weights.end()) {
        throw std::logic_error("Cannot get weight of non-existing edge!");
    }

    return it->second;
}

#endif //DSA_WEIGHTEDORIENTEDGRAPH_HPP
