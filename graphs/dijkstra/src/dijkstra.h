//
// Created by alexs on 2023-05-29.
//

#ifndef DSA_DIJKSTRA_H
#define DSA_DIJKSTRA_H

#include "config.h"
#include "ReadableGraph.h"

template<class TWeight>
class Dijkstra {
private:
    ReadableGraph<TWeight> *graph;
    std::vector<std::vector<size_t>> distances;

public:
    explicit Dijkstra(ReadableGraph<TWeight> *graph);

    void run(Vertex vertex);

    size_t getDistance(Vertex from, Vertex to) const;
};

#endif //DSA_DIJKSTRA_H
