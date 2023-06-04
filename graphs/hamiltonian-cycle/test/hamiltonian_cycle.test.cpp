//
// Created by alexs on 2023-05-30.
//

#include "gtest/gtest.h"
#include "Graph.h"
#include "hamiltonian_cycle.h"
#include <algorithm>

template<class T>
void expectVectorsEquality(const std::vector<T> &a, const std::vector<T> &b) {
    ASSERT_EQ(a.size(), b.size());

    for (int i = 0; i < a.size(); ++i) {
        EXPECT_EQ(a[i], b[i]);
    }
}

class SortedNeighborsGraph : public Graph<int> {
public:
    SortedNeighborsGraph(int **matrix, size_t size) : Graph<int>(matrix, size) {};

    void getNeighbors(std::vector<Vertex> &neighbors, Vertex vertex) const override {
        Graph<int>::getNeighbors(neighbors, vertex);
        std::sort(neighbors.begin(), neighbors.end(), std::greater<Vertex>());
    };
};

TEST(np_complete, hamiltonian_cycle_path_exists) {
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

    SortedNeighborsGraph graph(matrix, n);
    graph.addEdge(0, 1);
    graph.addEdge(0, 3);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 4);
    graph.addEdge(3, 4);

    std::vector<Vertex> path;
    EXPECT_EQ(hamiltonian_cycle(path, &graph, 0), true);
    expectVectorsEquality(path, {0, 3, 4, 2, 1});

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

TEST(np_complete, hamiltonian_cycle_path_not_exists) {
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

    SortedNeighborsGraph graph(matrix, n);
    graph.addEdge(0, 1);
    graph.addEdge(0, 3);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 4);

    std::vector<Vertex> path;
    EXPECT_EQ(hamiltonian_cycle(path, &graph, 0), false);
    expectVectorsEquality(path, {});

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

TEST(np_complete, hamiltonian_cycle_empty_graph) {
    const int n = 0;
    SortedNeighborsGraph graph(nullptr, n);

    std::vector<Vertex> path;
    EXPECT_EQ(hamiltonian_cycle(path, &graph, 0), false);
    expectVectorsEquality(path, {});
}

TEST(np_complete, hamiltonian_cycle_graph_as_star) {
    const int n = 5;
    int **matrix = new int *[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
        std::fill(matrix[i], matrix[i] + n, 0);
    }

    SortedNeighborsGraph graph(matrix, n);
    graph.addEdge(1, 0);
    graph.addEdge(2, 0);
    graph.addEdge(3, 0);
    graph.addEdge(4, 0);

    std::vector<Vertex> path;
    EXPECT_EQ(hamiltonian_cycle(path, &graph, 0), false);
    expectVectorsEquality(path, {});

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

TEST(np_complete, hamiltonian_cycle_not_connected_graph) {
    const int n = 1;
    int **matrix = new int *[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
        std::fill(matrix[i], matrix[i] + n, 0);
    }

    SortedNeighborsGraph graph(matrix, n);

    std::vector<Vertex> path;
    EXPECT_EQ(hamiltonian_cycle(path, &graph, 0), false);
    expectVectorsEquality(path, {});

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
