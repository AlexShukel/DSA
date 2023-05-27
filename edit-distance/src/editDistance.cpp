//
// Created by alexs on 2023-05-06.
//

#include "editDistance.h"
#include <vector>
#include <stdexcept>
#include <limits>

size_t editDistance(const std::string &s, const std::string &t, unsigned char variant) {
    const size_t sSize = s.length(), tSize = t.length();

    std::vector<std::vector<size_t>> dp;
    dp.resize(tSize + 1);
    for (auto &vec: dp) {
        vec.resize(sSize + 1);
    }

    for (size_t i = 0; i <= tSize; ++i) {
        dp[i][0] = i;
    }

    for (size_t i = 0; i <= sSize; ++i) {
        dp[0][i] = i;
    }

    for (size_t i = 1; i <= tSize; ++i) {
        for (size_t j = 1; j <= sSize; ++j) {
            size_t minValue = std::numeric_limits<size_t>::max();

            if ((variant & DELETION) == DELETION) {
                size_t v = dp[i][j - 1] + 1;
                if (v < minValue) {
                    minValue = v;
                }
            }

            if ((variant & INSERTION) == INSERTION) {
                size_t v = dp[i - 1][j] + 1;
                if (v < minValue) {
                    minValue = v;
                }
            }

            if ((variant & SUBSTITUTION) == SUBSTITUTION) {
                size_t v = dp[i - 1][j - 1] + 1;
                if (s[j - 1] != t[i - 1] && v < minValue) {
                    minValue = v;
                }
            }

            if ((variant & TRANSPOSITION) == TRANSPOSITION && i > 1 && j > 1) {
                size_t v = dp[i - 2][j - 2] + 1;
                if (s[j - 1] == t[i - 2] && s[j - 2] == t[i - 1] && v < minValue) {
                    minValue = v;
                }
            }

            // Do nothing
            if (s[j - 1] == t[i - 1] && dp[i - 1][j - 1] < minValue) {
                minValue = dp[i - 1][j - 1];
            }

            dp[i][j] = minValue;
        }
    }

    return dp[tSize][sSize];
}

size_t levenshtein(const std::string &s, const std::string &t) {
    return editDistance(s, t, DELETION | INSERTION | SUBSTITUTION);
}

size_t lcs(const std::string &s, const std::string &t) {
    return editDistance(s, t, DELETION | INSERTION);
}

size_t hamming(const std::string &s, const std::string &t) {
    if (s.length() != t.length()) {
        throw std::invalid_argument("Strings must be of the same length!");
    }

    return editDistance(s, t, SUBSTITUTION);
}

size_t damerauLevenshtein(const std::string &s, const std::string &t) {
    return editDistance(s, t, DELETION | INSERTION | SUBSTITUTION | TRANSPOSITION);
}
