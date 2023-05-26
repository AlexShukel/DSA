//
// Created by alexs on 2023-05-26.
//

#include "gtest/gtest.h"
#include "Graph.hpp"

TEST(graph, init) {
    Graph<int> g;
    g.addVertex(0);
    g.addVertex(1);
    g.addEdge(0, 1);

    EXPECT_EQ(g.verticesSize(), 2);
    EXPECT_EQ(g.edgesSize(), 1);

    g.removeVertex(1);

    EXPECT_EQ(g.verticesSize(), 1);
    EXPECT_EQ(g.edgesSize(), 0);
}
