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

    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);

    EXPECT_EQ(g.verticesSize(), 4);
    EXPECT_EQ(g.edgesSize(), 3);
    EXPECT_EQ(g.getVertexNeighboursCount(0), 3);
    EXPECT_EQ(g.getNeighbours(0).size(), 3);
    EXPECT_EQ(g.getNeighbour(0, 1), 2);
    EXPECT_EQ(g.hasEdge(0, 1), true);
    EXPECT_EQ(g.hasEdge(1, 0), false);

    g.removeVertex(0);

    EXPECT_EQ(g.verticesSize(), 3);
    EXPECT_EQ(g.edgesSize(), 0);
}
