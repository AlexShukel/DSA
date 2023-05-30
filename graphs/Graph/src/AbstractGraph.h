//
// Created by alexs on 2023-05-30.
//

#ifndef DSA_ABSTRACTGRAPH_H
#define DSA_ABSTRACTGRAPH_H

#include "config.h"
#include "ReadableGraph.h"

template<class TWeight>
class AbstractGraph : public ReadableGraph<TWeight> {
public:
    virtual Vertex addVertex() = 0;

    virtual void removeVertex(Vertex vertex) = 0;

    virtual void addEdge(Vertex from, Vertex to) = 0;

    virtual void addEdge(Vertex from, Vertex to, TWeight weight) = 0;

    virtual void removeEdge(Vertex from, Vertex to) = 0;
};

#endif //DSA_ABSTRACTGRAPH_H
