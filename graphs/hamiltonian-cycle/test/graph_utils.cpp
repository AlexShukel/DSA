//
// Created by alexs on 2023-06-18.
//

#include "graph_utils.h"

void generateFullyConnectedGraph(int **matrix, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                matrix[i][j] = 1;
            }
        }
    }
}
