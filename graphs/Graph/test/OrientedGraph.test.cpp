//
// Created by alexs on 2023-05-29.
//

#include "gtest/gtest.h"
#include "OrientedGraph.h"

TEST(graph, oriented_graph_public) {
    const int n = 4;
    int **input = new int *[n];
    for (int i = 0; i < n; ++i) {
        input[i] = new int[n];
        std::fill(input[i], input[i] + n, 0);
    }

    input[0][1] = 1;
    input[1][2] = 1;
    input[2][3] = 1;
    input[3][0] = 1;

    OrientedGraph<int> graph(input, n);
    EXPECT_EQ(graph.getVertexCount(), n);
    EXPECT_EQ(graph.getEdgeCount(), 4);
    EXPECT_EQ(graph.getNeighborCount(0), 1);

    std::vector<Vertex> neighbors;
    graph.getNeighbors(neighbors, 0);
    EXPECT_EQ(neighbors.size(), 1);
    EXPECT_EQ(neighbors[0], 1);

    EXPECT_EQ(graph.addVertex(), 4);
    graph.addEdge(4, 0);
    EXPECT_EQ(graph.inDeg(0), 2);
    EXPECT_EQ(graph.outDeg(0), 1);

    EXPECT_EQ(graph.getEdgeCount(), 5);
    graph.removeVertex(0);
    EXPECT_EQ(graph.getEdgeCount(), 2);

    for (int i = 0; i < n; ++i) {
        delete[] input[i];
    }
    delete[] input;
}
