//
// Created by alexs on 2023-05-28.
//

#include "gtest/gtest.h"
#include "ford_fulkerson.h"

TEST(max_flow, ford_fulkerson_example_1) {
    const int n = 6;
    int **graph = alloc_2d_array(n);

    // The example taken from https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/
    int static_graph[n][n]
            = {{0, 16, 13, 0,  0,  0},
               {0, 0,  10, 12, 0,  0},
               {0, 4,  0,  0,  14, 0},
               {0, 0,  9,  0,  0,  20},
               {0, 0,  0,  7,  0,  4},
               {0, 0,  0,  0,  0,  0}};

    for (int i = 0; i < n; ++i) {
        std::copy(static_graph[i], static_graph[i] + n, graph[i]);
    }

    int **flows = alloc_2d_array(n);

    EXPECT_EQ(ford_fulkerson(flows, graph, 0, 5, n), 23);

    free_2d_array(flows, n);
    free_2d_array(graph, n);
}

TEST(max_flow, ford_fulkerson_example_2) {
    const int n = 11;
    int **graph = alloc_2d_array(n);

    // The example DIRBTUVES
    int static_graph[n][n]
            = {
                    // 0   1   2   3   4   5   6   7   8   9  10
                    {00, 20, 30, 20, 00, 00, 00, 00, 00, 00, 00}, // 0
                    {00, 00, 00, 00, 20, 00, 05, 00, 00, 00, 00}, // 1
                    {00, 05, 00, 00, 00, 20, 00, 00, 00, 00, 00}, // 2
                    {00, 00, 05, 00, 00, 00, 20, 00, 00, 00, 00}, // 3
                    {00, 00, 00, 00, 00, 00, 00, 20, 00, 20, 00}, // 4
                    {00, 05, 00, 00, 05, 00, 05, 05, 20, 00, 00}, // 5
                    {00, 00, 10, 00, 00, 00, 00, 00, 20, 10, 00}, // 6
                    {00, 00, 00, 00, 00, 00, 00, 00, 05, 00, 20}, // 7
                    {00, 00, 00, 00, 00, 00, 00, 00, 00, 05, 30}, // 8
                    {00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 25}, // 9
                    {00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00}, // 10
            };

    for (int i = 0; i < n; ++i) {
        std::copy(static_graph[i], static_graph[i] + n, graph[i]);
    }

    int **residual_graph = alloc_2d_array(n);

    EXPECT_EQ(ford_fulkerson(residual_graph, graph, 0, 10, n), 65);

    int **final_flows = alloc_2d_array(n);
    get_final_flows(final_flows, residual_graph, graph, n);
    print_graph(final_flows, n);
    std::cout << std::endl;

    std::cout << "Min-cut edges are:" << std::endl;
    std::vector<std::pair<int, int>> min_cut;
    get_min_cut(min_cut, residual_graph, graph, 0, n);
    for (auto &edge: min_cut) {
        std::cout << "(" << edge.first << ", " << edge.second << ")" << std::endl;
    }
    std::cout << std::endl;

    free_2d_array(final_flows, n);
    free_2d_array(residual_graph, n);
    free_2d_array(graph, n);
}
