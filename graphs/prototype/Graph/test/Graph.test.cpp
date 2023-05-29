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

    matrix[0][1] = 1;
    matrix[1][0] = 1;

    matrix[1][2] = 1;
    matrix[2][1] = 1;

    matrix[2][3] = 1;
    matrix[3][2] = 1;

    matrix[3][0] = 1;
    matrix[0][3] = 1;

    Graph<int> graph(matrix, n);
    EXPECT_EQ(graph.getEdgeCount(), 4);
    EXPECT_EQ(graph.degree(0), 3);

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
