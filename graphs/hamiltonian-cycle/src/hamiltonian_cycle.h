//
// Created by alexs on 2023-05-30.
//

#ifndef DSA_HAMILTONIAN_CYCLE_H
#define DSA_HAMILTONIAN_CYCLE_H

#include "AbstractGraph.h"
#include "config.h"
#include <vector>

/**
 * Function to find a hamiltonian cycle in a given graph
 * @param path - an output path of hamiltonian cycle if it exists
 * @param graph - an input graph
 * @param start - starting vertex of hamiltonian cycle
 * @return boolean indicating whether hamiltonian cycle exists
 */
bool hamiltonian_cycle(std::vector<Vertex> &path, AbstractGraph<int> *graph, Vertex start);

#endif //DSA_HAMILTONIAN_CYCLE_H
