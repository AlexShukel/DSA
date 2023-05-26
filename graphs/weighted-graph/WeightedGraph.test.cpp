//
// Created by alexs on 2023-05-26.
//

#include "gtest/gtest.h"
#include "WeightedGraph.hpp"

TEST(weighted_graph, test) {
    WeightedGraph<int> g;

    g.addVertex(0);
    g.addVertex(1);
    g.addEdge(0, 1, 5);

    EXPECT_EQ(g.getEdgeWeight(0, 1), 5);
    EXPECT_EQ(g.getEdgeWeight(1, 0), 5);

    g.removeEdge(0, 1);
    EXPECT_THROW(g.getEdgeWeight(0, 1), std::logic_error);

    // Should set weight to 1 by default
    g.addEdge(0, 1);
    EXPECT_EQ(g.getEdgeWeight(0, 1), 1);

    g.removeVertex(0);
    g.addVertex(0);

    EXPECT_THROW(g.getEdgeWeight(0, 1), std::logic_error);
}
