//
// Created by alexs on 2023-06-18.
//

#include "gtest/gtest.h"
#include "hamiltonian_cycle_v2.h"
#include "utils.h"
#include "graph_utils.h"
#include <algorithm>

void addEdge(int **matrix, int from, int to) {
    matrix[from][to] = 1;
    matrix[to][from] = 1;
}

TEST(np_complete, hamiltonian_cycle_v2_path_exists) {
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

    addEdge(matrix, 0, 1);
    addEdge(matrix, 0, 3);
    addEdge(matrix, 1, 2);
    addEdge(matrix, 1, 3);
    addEdge(matrix, 1, 4);
    addEdge(matrix, 2, 4);
    addEdge(matrix, 3, 4);

    std::vector<int> path;
    EXPECT_EQ(hamiltonian_cycle_v2(path, matrix, n, 0), true);
    expectVectorsEquality(path, {0, 3, 4, 2, 1});

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

TEST(np_complete, hamiltonian_cycle_v2_path_not_exists) {
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

    addEdge(matrix, 0, 1);
    addEdge(matrix, 0, 3);
    addEdge(matrix, 1, 2);
    addEdge(matrix, 1, 3);
    addEdge(matrix, 1, 4);
    addEdge(matrix, 2, 4);

    std::vector<int> path;
    EXPECT_EQ(hamiltonian_cycle_v2(path, matrix, n, 0), false);
    expectVectorsEquality(path, {});

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

TEST(np_complete, hamiltonian_cycle_v2_empty_graph) {
    std::vector<int> path;
    EXPECT_EQ(hamiltonian_cycle_v2(path, nullptr, 0, 0), false);
    expectVectorsEquality(path, {});
}

TEST(np_complete, hamiltonian_cycle_v2_graph_as_star) {
    const int n = 5;
    int **matrix = new int *[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
        std::fill(matrix[i], matrix[i] + n, 0);
    }

    addEdge(matrix, 1, 0);
    addEdge(matrix, 2, 0);
    addEdge(matrix, 3, 0);
    addEdge(matrix, 4, 0);

    std::vector<int> path;
    EXPECT_EQ(hamiltonian_cycle_v2(path, matrix, n, 0), false);
    expectVectorsEquality(path, {});

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

TEST(np_complete, hamiltonian_cycle_v2_not_connected_graph) {
    const int n = 5;
    int **matrix = new int *[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
        std::fill(matrix[i], matrix[i] + n, 0);
    }

    std::vector<int> path;
    EXPECT_EQ(hamiltonian_cycle_v2(path, matrix, n, 0), false);
    expectVectorsEquality(path, {});

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

TEST(np_complete, hamiltonian_cycle_v2_fully_connected_graph) {
    std::vector<int> sizes = {5};

    for (auto n: sizes) {
        int **matrix = new int *[n];
        for (int i = 0; i < n; ++i) {
            matrix[i] = new int[n];
            std::fill(matrix[i], matrix[i] + n, 0);
        }

        generateFullyConnectedGraph(matrix, n);

        std::vector<int> path;
        EXPECT_EQ(hamiltonian_cycle_v2(path, matrix, n, 0), true);

        for (int i = 0; i < n; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}

TEST(np_complete, hamiltonian_cycle_v2_cyclic_graph_with_one_extra_vertex) {
    const int n = 5;
    int **matrix = new int *[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
        std::fill(matrix[i], matrix[i] + n, 0);
    }

    addEdge(matrix, 0, 1);
    addEdge(matrix, 1, 2);
    addEdge(matrix, 2, 3);
    addEdge(matrix, 3, 0);
    addEdge(matrix, 0, 4);
    addEdge(matrix, 4, 1);

    std::vector<int> path;
    EXPECT_EQ(hamiltonian_cycle_v2(path, matrix, n, 0), true);
    expectVectorsEquality(path, {0, 4, 1, 2, 3});

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
