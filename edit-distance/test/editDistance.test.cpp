//
// Created by alexs on 2023-05-06.
//

#include "gtest/gtest.h"
#include "../src/editDistance.h"

TEST(editDistance, levenshtein) {
    EXPECT_EQ(levenshtein("cat", "cut"), 1);
    EXPECT_EQ(levenshtein("dog", "dot"), 1);
    EXPECT_EQ(levenshtein("book", "back"), 2);
    EXPECT_EQ(levenshtein("hike", "bike"), 1);
    EXPECT_EQ(levenshtein("fast", "last"), 1);
    EXPECT_EQ(levenshtein("cave", "save"), 1);
    EXPECT_EQ(levenshtein("stack", "steak"), 2);
    EXPECT_EQ(levenshtein("happy", "hippo"), 2);
    EXPECT_EQ(levenshtein("pen", "pencil"), 3);
    EXPECT_EQ(levenshtein("rain", "train"), 1);
    EXPECT_EQ(levenshtein("", ""), 0);
}

TEST(editDistance, damerauLevenshtein) {
    EXPECT_EQ(damerauLevenshtein("hello", "hallo"), 1);
    EXPECT_EQ(damerauLevenshtein("keyboard", "keybord"), 1);
    EXPECT_EQ(damerauLevenshtein("chocolate", "chocolat"), 1);
    EXPECT_EQ(damerauLevenshtein("island", "isladn"), 1);
    EXPECT_EQ(damerauLevenshtein("purple", "puprle"), 1);
    EXPECT_EQ(damerauLevenshtein("footprint", "fotoprint"), 1);
    EXPECT_EQ(damerauLevenshtein("elephant", "ephelant"), 4);
    EXPECT_EQ(damerauLevenshtein("abacus", "bacus"), 1);
    EXPECT_EQ(damerauLevenshtein("tomato", "potato"), 2);
    EXPECT_EQ(damerauLevenshtein("telephone", "telephon"), 1);
    EXPECT_EQ(damerauLevenshtein("", ""), 0);
}

TEST(editDistance, lcs) {
    EXPECT_EQ(lcs("", ""), 0);
    EXPECT_EQ(lcs("abcdefg", "hijklmn"), 14);
    EXPECT_EQ(lcs("abcdefg", "abcdfg"), 1);
    EXPECT_EQ(lcs("abcbdab", "bdcaba"), 5);
    EXPECT_EQ(lcs("computer", "housekeeper"), 11);
    EXPECT_EQ(lcs("tree", "three"), 1);
    EXPECT_EQ(lcs("stackoverflow", "stackexchange"), 14);
    EXPECT_EQ(lcs("openai", "openai-gpt3"), 5);
    EXPECT_EQ(lcs("Hello, how are you?", "Hi, how are you?"), 5);
    EXPECT_EQ(lcs("abcdefg", "acdfg"), 2);
}
