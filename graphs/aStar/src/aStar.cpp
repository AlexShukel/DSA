//
// Created by alexs on 2023-05-29.
//

#include "aStar.h"
#include <limits>
#include <queue>

#define INF std::numeric_limits<size_t>::max()
#define NULL_VERTEX std::numeric_limits<Vertex>::max()

template<class TWeight>
size_t aStar(std::vector<Vertex> &path, ReadableGraph<TWeight> *graph,
             const std::function<size_t(Vertex from, Vertex to)> &heuristic, Vertex from, Vertex to) {
    size_t size = graph->getVertexCount();

    // For vertex n, gScore[n] is the cost of the cheapest path from start to n currently known
    std::vector<size_t> gScore(size, INF);
    gScore[from] = 0;

    // For vertex n, fScore[n] := gScore[n] + h(n). fScore[n] represents our current best guess as to
    // how cheap a path could be from start to finish if it goes through n.
    std::vector<size_t> fScore(size, INF);
    fScore[from] = heuristic(from, to);

    // For vertex n, cameFrom[n] is previous vertex in the shortest path from start to n
    std::vector<Vertex> cameFrom(size, NULL_VERTEX);

    std::priority_queue<Vertex, std::vector<Vertex>, std::greater<Vertex>> queue;
    queue.push(from);

    std::vector<bool> inQueue(size, false);

    while (!queue.empty()) {
        auto current = queue.top();
        queue.pop();
        inQueue[current] = false;

        if (current == to) {
            path.push_back(to);
            Vertex currentVertex = cameFrom[to];
            while (currentVertex != NULL_VERTEX) {
                path.push_back(currentVertex);
                currentVertex = cameFrom[currentVertex];
            }

            std::reverse(path.begin(), path.end());

            return gScore[to];
        }

        std::vector<Vertex> neighbors;
        graph->getNeighbors(neighbors, current);
        for (auto &neighbour: neighbors) {
            auto weight = graph->getEdgeWeight(current, neighbour);
            size_t newScore = gScore[current] + weight;

            if (newScore < gScore[neighbour]) {
                cameFrom[neighbour] = current;
                gScore[neighbour] = newScore;
                fScore[neighbour] = newScore + heuristic(neighbour, to);

                if (!inQueue[neighbour]) {
                    queue.push(neighbour);
                    inQueue[neighbour] = true;
                }
            }
        }
    }

    return INF;
}

template size_t aStar(std::vector<Vertex> &path, ReadableGraph<int> *graph,
                      const std::function<size_t(Vertex from, Vertex to)> &heuristic, Vertex from, Vertex to);

template size_t aStar(std::vector<Vertex> &path, ReadableGraph<double> *graph,
                      const std::function<size_t(Vertex from, Vertex to)> &heuristic, Vertex from, Vertex to);