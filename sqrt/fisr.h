//
// Created by alexs on 2023-02-23.
//

#ifndef DSA_FISR_H
#define DSA_FISR_H

/**
 * This algorithm uses "Fast Inverse Square Root" algorithm that is explained in this video:
 * https://www.youtube.com/watch?v=p8u_k2LIZyo
 * @param number - number to get square root of
 * @return square root of a given number
 */
float fisr(float number);

// Some experiments with this algorithm
// Gi - got result with i Newton's method iterations
// R - real value

// sqrt(2)
// G1   1.414567112922668
// G2   1.414213776588440
// G3   1.414213418960571
// G4   1.414213538169861 - 4 iterations is enough to get maximum precision (7)
// G100 1.414213538169861
// R    1.41421356237309504880168872420969807856967187537694

// 1 / sqrt(2)
// G1   0.7069300413
// G2   0.7071066499
// G3   0.7071068287
// G4   0.7071067691 - 4 iterations is enough to get maximum precision (7)
// G100 0.7071067690
// R    0.7071067812

#endif //DSA_FISR_H
