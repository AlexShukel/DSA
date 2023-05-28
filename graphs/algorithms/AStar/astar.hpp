//
// Created by alexs on 2023-05-28.
//

#ifndef DSA_ASTAR_HPP
#define DSA_ASTAR_HPP

#include <functional>
#include <unordered_map>
#include <queue>
#include <vector>
#include <limits>
#include <stdexcept>
#include "../../weighted-oriented-graph/WeightedOrientedGraph.hpp"

#define INF std::numeric_limits<size_t>::max()

// A hash function used to hash a pair of any kind
struct hash_pair {
    template<class T1, class T2>
    size_t operator()(const std::pair<T1, T2> &p) const {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);

        if (hash1 != hash2) {
            return hash1 ^ hash2;
        }

        // If hash1 == hash2, their XOR is zero.
        return hash1;
    }
};

// The result of A* algorithm
template<class TVertex>
struct ShortestPath {
    size_t distance;
    std::vector<TVertex> path;
};

template<class TVertex, class TVertexHash>
class AStar {
private:
    // Graph on which dijkstra algorithm is performed
    WeightedOrientedGraph<TVertex> graph;
    // Heuristic function that estimates the cost from n to goal
    std::function<size_t(TVertex n, TVertex goal)> heuristic;
    // For vertex n, gScore[n] is the cost of the cheapest path from start to n currently known
    std::unordered_map<TVertex, size_t, TVertexHash> gScore;
    // For vertex n, fScore[n] := gScore[n] + h(n). fScore[n] represents our current best guess as to
    // how cheap a path could be from start to finish if it goes through n.
    std::unordered_map<TVertex, size_t, TVertexHash> fScore;

    void initializeScores();

public:
    AStar(WeightedOrientedGraph<TVertex> &graph, const std::function<size_t(TVertex n, TVertex goal)> &h);

    ShortestPath<TVertex> run(TVertex start, TVertex goal);
};

template<class TVertex, class TVertexHash>
AStar<TVertex, TVertexHash>::AStar(WeightedOrientedGraph<TVertex> &graph,
                                   const std::function<size_t(TVertex n, TVertex goal)> &h)
        : graph(graph), heuristic(h) {
    initializeScores();
}

template<class TVertex, class TVertexHash>
void AStar<TVertex, TVertexHash>::initializeScores() {
    auto vertices = graph.getVertices();

    for (auto &vertex: vertices) {
        gScore[vertex] = INF;
        fScore[vertex] = INF;
    }
}

template<class TVertex, class TVertexHash>
ShortestPath<TVertex> AStar<TVertex, TVertexHash>::run(TVertex start, TVertex goal) {
    ShortestPath<TVertex> result;

    std::priority_queue<TVertex, std::vector<TVertex>, std::greater<TVertex>> queue;
    queue.push(start);

    std::unordered_map<TVertex, TVertex, TVertexHash> cameFrom;

    initializeScores();
    gScore[start] = 0;
    fScore[start] = heuristic(start, goal);

    while (!queue.empty()) {
        auto current = queue.top();
        queue.pop();

        if (current == goal) {
            result.distance = gScore[goal];

            result.path.push_back(goal);
            auto currentVertex = cameFrom.find(goal);
            while (currentVertex != cameFrom.end()) {
                result.path.push_back(currentVertex->second);
                currentVertex = cameFrom.find(currentVertex->second);
            }

            std::reverse(result.path.begin(), result.path.end());

            return result;
        }

        auto neighbours = graph.getNeighbours(current);
        for (auto &neighbour: neighbours) {
            auto w = graph.getEdgeWeight(current, neighbour);
            size_t newScore = gScore[current] + w;

            if (newScore < gScore[neighbour]) {
                cameFrom[neighbour] = current;
                gScore[neighbour] = newScore;
                fScore[neighbour] = newScore + heuristic(neighbour, goal);

                queue.push(neighbour);
            }
        }
    }

    throw std::logic_error("Queue is empty but goal was never reached.");
}

#endif //DSA_ASTAR_HPP
