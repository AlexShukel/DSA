//
// Created by alexs on 2023-05-29.
//

#include "gtest/gtest.h"
#include "dijkstra.h"
#include "Graph.h"

TEST(dijkstra, basic) {
    const int n = 4;
    int **matrix = new int *[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
        std::fill(matrix[i], matrix[i] + n, 0);
    }

    Graph<int> graph(matrix, n);
    graph.addEdge(0, 1, 5);
    graph.addEdge(0, 2, 3);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 2);
    graph.addEdge(2, 3, 4);

    Dijkstra<int> dijkstra(&graph);
    dijkstra.run(0);

    EXPECT_EQ(dijkstra.getDistance(0, 0), 0);
    EXPECT_EQ(dijkstra.getDistance(0, 1), 4);
    EXPECT_EQ(dijkstra.getDistance(0, 2), 3);
    EXPECT_EQ(dijkstra.getDistance(0, 3), 6);

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
