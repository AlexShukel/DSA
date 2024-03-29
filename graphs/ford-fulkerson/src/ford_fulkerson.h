//
// Created by alexs on 2023-05-28.
//

#ifndef DSA_FORD_FULKERSON_H
#define DSA_FORD_FULKERSON_H

#include "AbstractGraph.h"
#include <vector>

/**
 * Ford-fulkerson algorithm to find a maximum flow in a graph
 * @param residual_graph - an output residual graph. Must be initialized with initial graph
 * @param graph - an input initial graph
 * @param s - source vertex
 * @param t - sink vertex
 * @param n - number of vertices
 * @return the maximum flow
 */
int ford_fulkerson(AbstractGraph<int> *residual_graph, AbstractGraph<int> *graph, int s, int t, int n);

/**
 * Function to get final flows of edges
 * @param final_flows - an output matrix representing flows of edges
 * @param residual_graph - an input residual graph that has been constructed by ford_fulkerson
 * @param graph - an input initial graph
 * @param n - number of vertices
 */
void get_final_flows(int *final_flows[], AbstractGraph<int> *residual_graph, AbstractGraph<int> *graph, int n);

/**
 * Function to get min cut of a given graph
 * @param min_cut - an output set of edges
 * @param residual_graph - an input residual graph that has been constructed by ford_fulkerson
 * @param graph - an input initial graph
 * @param n - number of vertices
 */
void
get_min_cut(std::vector<std::pair<int, int>> &min_cut, AbstractGraph<int> *residual_graph, AbstractGraph<int> *graph,
            int s, int n);

int **alloc_2d_array(int n);

void free_2d_array(int **arr, int n);

void print_graph(int *graph[], int n);

#endif //DSA_FORD_FULKERSON_H
