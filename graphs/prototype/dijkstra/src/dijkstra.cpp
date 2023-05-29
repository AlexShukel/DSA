//
// Created by alexs on 2023-05-29.
//

#include "dijkstra.h"
#include <queue>
#include <limits>

#define INF std::numeric_limits<size_t>::max()

template<class TWeight>
Dijkstra<TWeight>::Dijkstra(ReadableGraph<TWeight> *graph): graph(graph) {
    size_t size = graph->getVertexCount();
    distances.resize(size);
    for (size_t i = 0; i < size; ++i) {
        distances[i].resize(size);
    }
}

template<class TWeight>
void Dijkstra<TWeight>::run(Vertex vertex) {
    auto &dists = distances[vertex];
    std::fill(dists.begin(), dists.end(), INF);
    dists[vertex] = 0;

    std::priority_queue<Vertex, std::vector<Vertex>, std::greater<>> queue;
    queue.push(vertex);

    while (!queue.empty()) {
        auto current = queue.top();
        queue.pop();

        std::vector<Vertex> neighbors;
        graph->getNeighbors(neighbors, current);

        for (auto &neighbor: neighbors) {
            TWeight weight = graph->getEdgeWeight(current, neighbor);
            if (dists[current] + weight < dists[neighbor]) {
                dists[neighbor] = dists[current] + weight;
                queue.push(neighbor);
            }
        }
    }
}

template<class TWeight>
size_t Dijkstra<TWeight>::getDistance(Vertex from, Vertex to) const {
    return distances[from][to];
}

template
class Dijkstra<int>;
