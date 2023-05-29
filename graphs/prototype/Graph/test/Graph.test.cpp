//
// Created by alexs on 2023-05-29.
//

#include "gtest/gtest.h"
#include "Graph.h"

TEST(graph, graph_public) {
    const int n = 4;
    int **matrix = new int *[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
        std::fill(matrix[i], matrix[i] + n, 0);
    }

    Graph<int> graph(matrix, n);

    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 0);

    EXPECT_EQ(graph.getEdgeCount(), 4);
    EXPECT_EQ(graph.degree(0), 2);

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
