//
// Created by alexs on 2023-02-23.
//

#ifndef DSA_FISR_H
#define DSA_FISR_H

/**
 * This algorithm uses "Fast Inverse Square Root" algorithm that is explained in this video:
 * https://www.youtube.com/watch?v=p8u_k2LIZyo
 * Restriction: can only be used with float (32 bit numbers), so maximum available precision is 7
 * @param number - number to get square root of
 * @return square root of a given number
 */
float fisr(float number);

#endif //DSA_FISR_H
