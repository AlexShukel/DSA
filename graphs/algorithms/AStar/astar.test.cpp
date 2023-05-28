//
// Created by alexs on 2023-05-28.
//

#include "gtest/gtest.h"
#include "astar.hpp"
#include <cmath>

// Vertex represented as coordinates {x, y}
typedef std::pair<int, int> Vertex;

void addBothDirectionEdge(WeightedOrientedGraph<Vertex> &graph, Vertex from, Vertex to, size_t weight) {
    graph.addEdge(from, to, weight);
    graph.addEdge(to, from, weight);
}

// The example taken from https://en.wikipedia.org/wiki/A*_search_algorithm#Example
void initGraph(WeightedOrientedGraph<Vertex> &graph) {
    graph.addVertex({1, 4});
    graph.addVertex({3, 4});
    graph.addVertex({4, 2});
    graph.addVertex({4, 0});
    graph.addVertex({0, 0});
    graph.addVertex({2, 1});
    graph.addVertex({2, 3});

    addBothDirectionEdge(graph, {1, 4}, {3, 4}, 2);
    addBothDirectionEdge(graph, {3, 4}, {4, 2}, 3);
    addBothDirectionEdge(graph, {4, 2}, {4, 0}, 2);
    addBothDirectionEdge(graph, {4, 0}, {0, 0}, 4);
    addBothDirectionEdge(graph, {0, 0}, {2, 1}, 3);
    addBothDirectionEdge(graph, {2, 1}, {2, 3}, 2);
    addBothDirectionEdge(graph, {2, 3}, {1, 4}, 2);
}

// Distance between 2 points
size_t heuristic(Vertex n, Vertex goal) {
    return static_cast<size_t>(sqrt(pow(goal.second - n.second, 2) + pow(goal.first - n.first, 2)));
}

TEST(path_finding, a_star) {
    WeightedOrientedGraph<Vertex> graph;
    initGraph(graph);
    AStar<Vertex, hash_pair> astar(graph, heuristic);
    auto result = astar.run({1, 4}, {4, 0});
    EXPECT_EQ(result.distance, 7);
}
