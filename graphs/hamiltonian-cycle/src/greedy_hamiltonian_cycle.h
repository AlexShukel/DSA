//
// Created by alexs on 2023-06-04.
//

#ifndef DSA_GREEDY_HAMILTONIAN_CYCLE_H
#define DSA_GREEDY_HAMILTONIAN_CYCLE_H

#include "AbstractGraph.h"
#include "config.h"
#include <vector>

/**
 * Heuristic function to find a hamiltonian cycle in a given graph
 * @param path - an output path of hamiltonian cycle if it exists and another long cycle if hamiltonian wasn't found
 * @param graph - an input graph
 * @param start - starting vertex of hamiltonian cycle
 * @return boolean indicating whether hamiltonian cycle was found
 */
bool greedy_hamiltonian_cycle(std::vector<Vertex> &path, AbstractGraph<int> *graph, Vertex start);

#endif //DSA_GREEDY_HAMILTONIAN_CYCLE_H
