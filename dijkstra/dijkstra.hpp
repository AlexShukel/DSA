//
// Created by alexs on 2023-05-27.
//

#ifndef DSA_DIJKSTRA_H
#define DSA_DIJKSTRA_H

#include <queue>
#include <unordered_map>
#include <map>
#include <vector>
#include <stdexcept>
#include <limits>
#include "../graphs/weighted-oriented-graph/WeightedOrientedGraph.hpp"

#define INF std::numeric_limits<size_t>::max()

template<class TVertex>
class Dijkstra {
private:
    // Graph on which dijkstra algorithm is performed
    WeightedOrientedGraph<TVertex> graph;
    // Matrix of all shortest distances between all vertices
    std::vector<std::vector<size_t>> distances;
    // Map each vertex to specific index
    std::unordered_map<TVertex, size_t> vertexToIndex;

public:
    explicit Dijkstra(WeightedOrientedGraph<TVertex> &graph);

    void run(TVertex vertex);

    size_t getDistance(TVertex from, TVertex to) const;
};

template<class TVertex>
Dijkstra<TVertex>::Dijkstra(WeightedOrientedGraph<TVertex> &graph): graph(graph) {
    auto vertices = graph.getVertices();

    size_t i = 0;
    for (auto &vertex: vertices) {
        vertexToIndex[vertex] = i;
        ++i;
    }

    distances.resize(i);
    for (auto &d: distances) {
        d.resize(i, 0);
    }
}

template<class TVertex>
void Dijkstra<TVertex>::run(TVertex vertex) {
    std::priority_queue<TVertex, std::vector<TVertex>, std::greater<TVertex>> queue;
    auto vertexIndex = vertexToIndex[vertex];
    auto &dists = distances[vertexIndex];
    std::fill(dists.begin(), dists.end(), INF);

    queue.push(vertex);
    dists[vertexIndex] = 0;
    while (!queue.empty()) {
        auto current = queue.top();
        auto currentIndex = vertexToIndex[current];
        queue.pop();

        auto neighbours = graph.getNeighbours(current);
        for (auto &neighbour: neighbours) {
            auto neighbourIndex = vertexToIndex[neighbour];
            auto w = graph.getEdgeWeight(current, neighbour);

            if (dists[currentIndex] + w < dists[neighbourIndex]) {
                dists[neighbourIndex] = dists[currentIndex] + w;
                queue.push(neighbour);
            }
        }
    }
}

template<class TVertex>
size_t Dijkstra<TVertex>::getDistance(TVertex from, TVertex to) const {
    if (from == to) {
        return 0;
    }

    size_t fromIndex = vertexToIndex.find(from)->second;
    size_t toIndex = vertexToIndex.find(to)->second;

    auto d = distances[fromIndex][toIndex];

    if (d == 0) {
        throw std::logic_error("Requested path was not calculated!");
    }

    return d;
}

#endif //DSA_DIJKSTRA_H
