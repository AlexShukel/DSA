//
// Created by alexs on 2023-03-06.
//

#ifndef DSA_TESTUTILS_H
#define DSA_TESTUTILS_H

#include <vector>

template<class T>
void expectVectorsEquality(const std::vector<T> &a, const std::vector<T> &b) {
    ASSERT_EQ(a.size(), b.size());

    for (int i = 0; i < a.size(); ++i) {
        EXPECT_EQ(a[i], b[i]);
    }
}

#endif //DSA_TESTUTILS_H
