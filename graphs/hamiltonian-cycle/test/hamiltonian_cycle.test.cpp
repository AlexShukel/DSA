//
// Created by alexs on 2023-05-30.
//

#include "gtest/gtest.h"
#include "Graph.h"
#include "hamiltonian_cycle.h"
#include <algorithm>

class SortedNeighborsGraph : public Graph<int> {
public:
    SortedNeighborsGraph(int **matrix, size_t size) : Graph<int>(matrix, size) {};

    void getNeighbors(std::vector<Vertex> &neighbors, Vertex vertex) const override {
        Graph<int>::getNeighbors(neighbors, vertex);
        std::sort(neighbors.begin(), neighbors.end(), std::greater<Vertex>());
    };
};

TEST(np_complete, hamiltonian_cycle) {
//    (0)--(1)--(2)
//    |   / \   |
//    |  /   \  |
//    | /     \ |
//    (3)-------(4)
    const int n = 5;
    int **matrix = new int *[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
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

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
