//
// Created by alexs on 2023-05-28.
//

#include <iostream>
#include <queue>
#include <limits>
#include <set>
#include "ford_fulkerson.h"

#define INF std::numeric_limits<int>::max()

int **alloc_2d_array(int n) {
    int **arr = new int *[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = new int[n];
    }
    return arr;
}

void free_2d_array(int **arr, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}

void print_graph(int *graph[], int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << graph[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool bfs(AbstractGraph<int> *residual_graph, int s, int t, int path[], int n) {
    // Initialize queue of vertices
    std::queue<int> q;
    q.push(s);

    // Initialize array of visited vertices
    bool *visited = new bool[n];
    std::fill(visited, visited + n, false);
    visited[s] = true;

    path[s] = -1;
    bool path_exists = false;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int i = 0; i < n; ++i) {
            // There is an edge in residual graph
            if (!visited[i] && residual_graph->hasEdge(current, i)) {
                // Add current vertex in path
                path[i] = current;

                if (i == t) {
                    path_exists = true;
                    break;
                }

                q.push(i);
                visited[i] = true;
            }
        }

        if (path_exists) {
            break;
        }
    }

    delete[] visited;
    return path_exists;
}

int ford_fulkerson(AbstractGraph<int> *residual_graph, AbstractGraph<int> *graph, int s, int t, int n) {
    int *path = new int[n];
    int max_flow = 0;

    while (bfs(residual_graph, s, t, path, n)) {
        int current = t;
        int min_residual_capacity = INF;

        // Find the minimum residual capacity along augmenting path
        while (current != s) {
            min_residual_capacity = std::min(min_residual_capacity,
                                             residual_graph->getEdgeWeight(path[current], current));
            current = path[current];
        }

        current = t;
        while (current != s) {
            // Update weights
            residual_graph->addEdge(path[current], current,
                                    residual_graph->getEdgeWeight(path[current], current) - min_residual_capacity);
            residual_graph->addEdge(current, path[current],
                                    residual_graph->getEdgeWeight(current, path[current]) + min_residual_capacity);

            current = path[current];
        }

        max_flow += min_residual_capacity;
    }

    delete[] path;
    return max_flow;
}

void get_final_flows(int *final_flows[], AbstractGraph<int> *residual_graph, AbstractGraph<int> *graph, int n) {
    for (int i = 0; i < n; ++i) {
        std::fill(final_flows[i], final_flows[i] + n, 0);

        for (int j = 0; j < n; ++j) {
            if (graph->hasEdge(i, j)) {
                final_flows[i][j] = graph->getEdgeWeight(i, j) - residual_graph->getEdgeWeight(i, j);
            }
        }
    }
}

void dfs(int src, bool *visited, AbstractGraph<int> *graph, int n, std::set<int> &source_side) {
    source_side.insert(src);
    visited[src] = true;

    for (int i = 0; i < n; ++i) {
        if (graph->hasEdge(src, i) && !visited[i]) {
            dfs(i, visited, graph, n, source_side);
        }
    }
}

void
get_min_cut(std::vector<std::pair<int, int>> &min_cut, AbstractGraph<int> *residual_graph, AbstractGraph<int> *graph,
            int s, int n) {
    std::set<int> source_side;

    bool *visited = new bool[n];
    dfs(s, visited, residual_graph, n, source_side);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (graph->hasEdge(i, j) && source_side.find(i) != source_side.end() &&
                source_side.find(j) == source_side.end()) {
                min_cut.emplace_back(i, j);
            }
        }
    }

    delete[] visited;
}
