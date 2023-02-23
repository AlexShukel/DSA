//
// Created by alexs on 2023-02-23.
//

#include "fisr.h"
#include <cinttypes>

float fisr(float number) {
    int32_t i;
    float x2, y;
    const float threehalfs = 1.5f;

    x2 = number * 0.5f;
    y = number;
    i = *(int32_t *) &y;
    i = 0x5f3759df - (i >> 1);
    y = *(float *) &i;

    for (int j = 0; j < 4; ++j) {
        y = y * (threehalfs - (x2 * y * y)); // Newton's method iteration
    }

    return 1 / y;
}
