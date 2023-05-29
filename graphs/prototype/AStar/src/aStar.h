//
// Created by alexs on 2023-05-29.
//

#ifndef DSA_ASTAR_H
#define DSA_ASTAR_H

#include "ReadableGraph.h"
#include <functional>

/**
 * A* algorithm
 * @tparam TWeight - type of weight in graph
 * @param path - output vector for vertices in shortest path
 * @param heuristic - heuristic function that should return approximate distance between any 2 vertices
 * @param graph - input graph
 * @param from - start vertex
 * @param to - goal vertex
 * @return the distance of shortest path
 */
template<class TWeight>
size_t aStar(std::vector<Vertex> &path, ReadableGraph<TWeight> *graph,
             const std::function<size_t(Vertex from, Vertex to)> &heuristic, Vertex from, Vertex to);

#endif //DSA_ASTAR_H
