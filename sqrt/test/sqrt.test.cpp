//
// Created by alexs on 2023-02-23.
//

#include <gtest/gtest.h>
#include "sqrt.h"

TEST(SquareRoot, HandlesZero) {
    EXPECT_EQ(0, mySqrt(0));
}
