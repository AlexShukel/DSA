//
// Created by alexs on 2023-05-29.
//

#include "gtest/gtest.h"
#include "aStar.h"
#include "OrientedGraph.h"
#include "unordered_map"
#include <cmath>

std::unordered_map<Vertex, std::pair<int, int>> coords;

size_t heuristicEuclidean(Vertex from, Vertex to) {
    int dx = coords[from].first - coords[to].second;
    int dy = coords[from].second - coords[to].second;
    return static_cast<size_t>(std::sqrt(dx * dx + dy * dy));
}

TEST(a_star, shortest_path_exists) {
    const int n = 5;
    int **matrix = new int *[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
        std::fill(matrix[i], matrix[i] + n, 0);
    }

    OrientedGraph<int> graph(matrix, n);

    coords[0] = {0, 0};
    coords[1] = {2, 2};
    coords[2] = {4, 0};
    coords[3] = {6, 2};
    coords[4] = {8, 0};

    graph.addEdge(0, 1, 3);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 3, 1);
    graph.addEdge(2, 4, 6);
    graph.addEdge(3, 4, 2);

    std::vector<Vertex> path;

    EXPECT_EQ(aStar(path, &graph, heuristicEuclidean, 0, 4), 6);

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
