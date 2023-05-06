//
// Created by alexs on 2023-05-06.
//

#ifndef DSA_EDITDISTANCE_H
#define DSA_EDITDISTANCE_H

#include <string>

#define DELETION 0b00000001
#define INSERTION 0b00000010
#define SUBSTITUTION 0b00000100
#define TRANSPOSITION 0b00001000

/**
 * Function to calculate edit distance between 2 strings.
 * @param s - first string
 * @param t - second string
 * @param variant - bit map to choose operations
 * @return edit distance between s and t
 */
size_t editDistance(const std::string &s, const std::string &t, unsigned char variant);

size_t levenshtein(const std::string &s, const std::string &t);

size_t lcs(const std::string &s, const std::string &t);

size_t hamming(const std::string &s, const std::string &t);

size_t damerauLevenshtein(const std::string &s, const std::string &t);

#endif //DSA_EDITDISTANCE_H
