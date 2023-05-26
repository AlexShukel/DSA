//
// Created by alexs on 2023-05-26.
//

#include "gtest/gtest.h"
#include "WeightedOrientedGraph.hpp"

TEST(weighted_oriented_graph, test) {
    WeightedOrientedGraph<int> g;

    g.addVertex(0);
    g.addVertex(1);

    g.addEdge(0, 1);

    EXPECT_EQ(g.getEdgeWeight(0, 1), 1);
    EXPECT_THROW(g.getEdgeWeight(1, 0), std::logic_error);

    g.removeVertex(0);
    g.addVertex(0);

    EXPECT_THROW(g.getEdgeWeight(0, 1), std::logic_error);

    g.addEdge(0, 1);
    g.removeEdge(0, 1);

    EXPECT_THROW(g.getEdgeWeight(0, 1), std::logic_error);
}

