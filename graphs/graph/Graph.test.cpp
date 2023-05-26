//
// Created by alexs on 2023-05-26.
//

#include "gtest/gtest.h"
#include "Graph.hpp"

TEST(graph, test) {
    Graph<int> g;

    g.addVertex(0);
    g.addVertex(1);

    g.addEdge(0, 1);

    EXPECT_EQ(g.edgesSize(), 1);

    g.removeEdge(1, 0);

    EXPECT_EQ(g.edgesSize(), 0);

    g.addVertex(2);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.removeVertex(0);

    EXPECT_EQ(g.edgesSize(), 0);

    g.addVertex(0);
    g.addVertex(3);
    g.addVertex(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(0, 4);
    g.removeVertex(0);

    EXPECT_EQ(g.edgesSize(), 0);

    g.addEdge(1, 2);
    EXPECT_THROW(g.addEdge(2, 1), std::logic_error);
}
