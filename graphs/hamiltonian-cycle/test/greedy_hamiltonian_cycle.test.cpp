//
// Created by alexs on 2023-06-04.
//

#include "gtest/gtest.h"
#include "greedy_hamiltonian_cycle.h"
#include "Graph.h"
#include "utils.h"

TEST(np_complete, greedy_hamiltonian_cycle_path_exists) {
//    (0)--(1)--(2)
//    |   / \   |
//    |  /   \  |
//    | /     \ |
//    (3)-------(4)
    const int n = 5;
    int **matrix = new int *[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
        std::fill(matrix[i], matrix[i] + n, 0);
    }

    Graph<int> graph(matrix, n);
    graph.addEdge(0, 1);
    graph.addEdge(0, 3);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 4);
    graph.addEdge(3, 4);

    std::vector<Vertex> path;
    EXPECT_EQ(greedy_hamiltonian_cycle(path, &graph, 0), true);
    expectVectorsEquality(path, {0, 1, 2, 4, 3});

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

TEST(np_complete, greedy_hamiltonian_cycle_path_not_exists) {
//    (0)--(1)--(2)
//    |   / \   |
//    |  /   \  |
//    | /     \ |
//    (3)      (4)
    const int n = 5;
    int **matrix = new int *[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
        std::fill(matrix[i], matrix[i] + n, 0);
    }

    Graph<int> graph(matrix, n);
    graph.addEdge(0, 1);
    graph.addEdge(0, 3);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 4);

    std::vector<Vertex> path;
    EXPECT_EQ(greedy_hamiltonian_cycle(path, &graph, 0), false);
    expectVectorsEquality(path, {});

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

TEST(np_complete, greedy_hamiltonian_cycle_empty_graph) {
    const int n = 0;
    Graph<int> graph(nullptr, n);

    std::vector<Vertex> path;
    EXPECT_EQ(greedy_hamiltonian_cycle(path, &graph, 0), false);
    expectVectorsEquality(path, {});
}

TEST(np_complete, greedy_hamiltonian_cycle_graph_as_star) {
    const int n = 5;
    int **matrix = new int *[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
        std::fill(matrix[i], matrix[i] + n, 0);
    }

    Graph<int> graph(matrix, n);
    graph.addEdge(1, 0);
    graph.addEdge(2, 0);
    graph.addEdge(3, 0);
    graph.addEdge(4, 0);

    std::vector<Vertex> path;
    EXPECT_EQ(greedy_hamiltonian_cycle(path, &graph, 0), false);
    expectVectorsEquality(path, {});

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

TEST(np_complete, greedy_hamiltonian_cycle_not_connected_graph) {
    const int n = 5;
    int **matrix = new int *[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
        std::fill(matrix[i], matrix[i] + n, 0);
    }

    Graph<int> graph(matrix, n);

    std::vector<Vertex> path;
    EXPECT_EQ(greedy_hamiltonian_cycle(path, &graph, 0), false);
    expectVectorsEquality(path, {});

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
