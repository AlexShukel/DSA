//
// Created by alexs on 2023-04-28.
//

#ifndef DSA_HUNGARIAN_H
#define DSA_HUNGARIAN_H

#include <vector>

// Binary matrix for hungarian algorithm output
typedef std::vector<std::vector<bool>> Output;

template<class T>
Output hungarian(const std::vector<std::vector<T>> &input);

#endif //DSA_HUNGARIAN_H
