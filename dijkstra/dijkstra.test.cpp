//
// Created by alexs on 2023-05-27.
//

#include "gtest/gtest.h"
#include "dijkstra.hpp"

void addBothDirectionEdge(WeightedOrientedGraph<int> &graph, int from, int to, size_t weight) {
    graph.addEdge(from, to, weight);
    graph.addEdge(to, from, weight);
}

void initGraph(WeightedOrientedGraph<int> &graph) {
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addVertex(4);
    graph.addVertex(5);

    addBothDirectionEdge(graph, 1, 2, 1);
    addBothDirectionEdge(graph, 1, 4, 2);
    addBothDirectionEdge(graph, 1, 3, 4);
    addBothDirectionEdge(graph, 2, 3, 2);
    addBothDirectionEdge(graph, 3, 4, 3);
    addBothDirectionEdge(graph, 4, 5, 1);
    addBothDirectionEdge(graph, 3, 5, 5);
}

TEST(path_finding, dijkstra) {
    WeightedOrientedGraph<int> graph;
    initGraph(graph);
    Dijkstra<int> dijkstra(graph);
    dijkstra.run(1);

    EXPECT_EQ(dijkstra.getDistance(1, 2), 1);
    EXPECT_EQ(dijkstra.getDistance(1, 3), 3);
    EXPECT_EQ(dijkstra.getDistance(1, 4), 2);
    EXPECT_EQ(dijkstra.getDistance(1, 5), 3);

    EXPECT_THROW(dijkstra.getDistance(2, 3), std::logic_error);
}
