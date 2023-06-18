//
// Created by alexs on 2023-06-18.
//

#ifndef DSA_HAMILTONIAN_CYCLE_V2_H
#define DSA_HAMILTONIAN_CYCLE_V2_H

#include <vector>

/**
 * Function to find a hamiltonian cycle in a given graph
 * @param path - an output path of hamiltonian cycle if it exists
 * @param graph - an input graph
 * @param start - starting vertex of hamiltonian cycle
 * @return boolean indicating whether hamiltonian cycle exists
 */
bool hamiltonian_cycle_v2(std::vector<int> &path, int **graph, int size, int start);

#endif //DSA_HAMILTONIAN_CYCLE_V2_H
