//
// Created by alexs on 2023-02-23.
//

#include <gtest/gtest.h>
#include "sqrt.h"

// Demonstrate some basic assertions.
TEST(SquareRoot, HandlesZero) {
    EXPECT_EQ(0, sqrt(0));
}
