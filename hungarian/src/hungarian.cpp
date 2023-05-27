//
// Created by alexs on 2023-04-28.
//

#include <iostream>
#include <limits>
#include "hungarian.h"

template<class T>
struct MatrixMember {
    T value;
    bool starred;
    bool primed;
};

template<class T>
std::vector<std::vector<MatrixMember<T>>> initializeMatrix(const std::vector<std::vector<T>> &input) {
    int size = input.size();
    std::vector<std::vector<MatrixMember<T>>> matrix;
    matrix.resize(size);

    for (int i = 0; i < size; ++i) {
        matrix[i].resize(size);
        for (int j = 0; j < size; ++j) {
            matrix[i][j].value = input[i][j];
            matrix[i][j].starred = false;
            matrix[i][j].primed = false;
        }
    }

    return matrix;
}

template<class T>
void reduceRows(std::vector<std::vector<MatrixMember<T>>> &matrix) {
    int size = matrix.size();

    for (int i = 0; i < size; ++i) {
        T min = matrix[i][0].value;
        for (int j = 0; j < size; ++j) {
            if (matrix[i][j].value < min) {
                min = matrix[i][j].value;
            }
        }

        for (int j = 0; j < size; ++j) {
            matrix[i][j].value -= min;
        }
    }
}

template<class T>
void reduceColumns(std::vector<std::vector<MatrixMember<T>>> &matrix) {
    int size = matrix.size();

    for (int i = 0; i < size; ++i) {
        T min = matrix[0][i].value;
        for (int j = 0; j < size; ++j) {
            if (matrix[j][i].value < min) {
                min = matrix[j][i].value;
            }
        }

        for (int j = 0; j < size; ++j) {
            matrix[j][i].value -= min;
        }
    }
}

template<class T>
void starArbitraryZeros(std::vector<std::vector<MatrixMember<T>>> &matrix) {
    int size = matrix.size();

    std::vector<bool> starredRows(size, false);
    std::vector<bool> starredColumns(size, false);

    // Initially assign arbitrary zeros
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (matrix[i][j].value == 0 && !starredRows[i] && !starredColumns[j]) {
                starredRows[i] = true;
                starredColumns[j] = true;
                matrix[i][j].starred = true;
            }
        }
    }
}

template<class T>
void coverStarredZeroColumns(std::vector<bool> &coveredColumns, std::vector<std::vector<MatrixMember<T>>> &matrix) {
    int size = matrix.size();
    for (int j = 0; j < size; ++j) {
        for (int k = 0; k < size; ++k) {
            if (matrix[j][k].starred) {
                coveredColumns[k] = true;
            }
        }
    }
}

template<class T>
std::pair<int, int> primeUncoveredZero(std::vector<bool> &coveredRows, std::vector<bool> &coveredColumns,
                                       std::vector<std::vector<MatrixMember<T>>> &matrix) {
    int size = matrix.size();
    for (int j = 0; j < size; ++j) {
        for (int k = 0; k < size; ++k) {
            if (!coveredRows[j] && !coveredColumns[k] && matrix[j][k].value == 0) {
                matrix[j][k].primed = true;
                return {j, k};
            }
        }
    }

    return {-1, -1};
}

template<class T>
int findPrimedZeroColumn(std::vector<std::vector<MatrixMember<T>>> &matrix, int starredZeroRow) {
    int size = matrix.size();
    for (int j = 0; j < size; ++j) {
        if (matrix[starredZeroRow][j].primed) {
            return j;
        }
    }

    return -1;
}

template<class T>
int findStarredZeroColumn(std::vector<std::vector<MatrixMember<T>>> &matrix, int primedZeroRow) {
    int size = matrix.size();
    for (int j = 0; j < size; ++j) {
        if (matrix[primedZeroRow][j].starred) {
            return j;
        }
    }

    return -1;
}

template<class T>
int findStarredZeroRow(std::vector<std::vector<MatrixMember<T>>> &matrix, int primedZeroColumn) {
    int size = matrix.size();
    for (int j = 0; j < size; ++j) {
        if (matrix[j][primedZeroColumn].starred) {
            return j;
        }
    }

    return -1;
}

int getNumberOfLines(std::vector<bool> &coveredRows, std::vector<bool> &coveredColumns) {
    int numberOfLines = 0;
    int size = (int) coveredRows.size();
    for (int j = 0; j < size; ++j) {
        if (coveredRows[j]) {
            ++numberOfLines;
        }

        if (coveredColumns[j]) {
            ++numberOfLines;
        }
    }

    return numberOfLines;
}

template<class T>
T findLowestUncoveredValue(std::vector<bool> &coveredRows, std::vector<bool> &coveredColumns,
                           std::vector<std::vector<MatrixMember<T>>> &matrix) {
    T minValue = std::numeric_limits<T>::max();
    int size = matrix.size();
    for (int j = 0; j < size; ++j) {
        for (int k = 0; k < size; ++k) {
            if (!coveredRows[j] && !coveredColumns[k] && matrix[j][k].value < minValue) {
                minValue = matrix[j][k].value;
            }
        }
    }

    return minValue;
}

template<class T>
void subtractFromNotCoveredCells(std::vector<bool> &coveredRows, std::vector<bool> &coveredColumns,
                                 std::vector<std::vector<MatrixMember<T>>> &matrix, T subtrahend) {
    int size = matrix.size();
    for (int j = 0; j < size; ++j) {
        for (int k = 0; k < size; ++k) {
            if (!coveredRows[j] && !coveredColumns[k]) {
                matrix[j][k].value -= subtrahend;
            }
        }
    }
}

template<class T>
void addToCoveredTwiceCells(std::vector<bool> &coveredRows, std::vector<bool> &coveredColumns,
                            std::vector<std::vector<MatrixMember<T>>> &matrix, T addend) {
    int size = matrix.size();
    for (int j = 0; j < size; ++j) {
        for (int k = 0; k < size; ++k) {
            if (coveredRows[j] && coveredColumns[k]) {
                matrix[j][k].value += addend;
            }
        }
    }
}

template<class T>
std::vector<MatrixMember<T> *>
getZerosPath(std::vector<std::vector<MatrixMember<T>>> &matrix, int primedZeroRow, int primedZeroColumn) {
    std::vector<MatrixMember<T> *> path;

    while (true) {
        path.push_back(&matrix[primedZeroRow][primedZeroColumn]);

        int starredZeroRow = findStarredZeroRow(matrix, primedZeroColumn);
        if (starredZeroRow == -1) {
            break;
        }

        path.push_back(&matrix[starredZeroRow][primedZeroColumn]);

        primedZeroRow = starredZeroRow;
        primedZeroColumn = findPrimedZeroColumn(matrix, starredZeroRow);
    }

    return path;
}

template<class T>
void resetZerosState(std::vector<std::vector<MatrixMember<T>>> &matrix) {
    int size = matrix.size();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j].starred = false;
            matrix[i][j].primed = false;
        }
    }
}

template<class T>
Output hungarian(const std::vector<std::vector<T>> &input) {
    size_t size = input.size();

    if (size <= 1) {
        throw std::invalid_argument("Size of given matrix cannot be less than 2!");
    }

    if (size != input[0].size()) {
        throw std::invalid_argument("Matrix must be square matrix!");
    }

    // Construct output object
    Output output;
    output.resize(size);
    for (int i = 0; i < size; ++i) {
        output[i].resize(size);
        std::fill(output[i].begin(), output[i].end(), false);
    }

    // Construct matrix object
    auto matrix = initializeMatrix(input);

    // STEP 1
    // Rows reduction O(N^2)
    reduceRows(matrix);

    // STEP 2
    // Columns reduction O(N^2)
    reduceColumns(matrix);

    // Main hungarian algorithm loop
    while (true) {
        // STEP 3
        // Reset zeros state
        resetZerosState(matrix);

        // Star arbitrary zeros O(N^2)
        starArbitraryZeros(matrix);

        std::vector<bool> coveredRows(size, false);
        std::vector<bool> coveredColumns(size, false);

        // STEP 4

        // While there are uncovered zeros
        bool foundStarredZeroInPreviousStep = false;
        while (true) {
            if (!foundStarredZeroInPreviousStep) {
                // Cover all columns that have starred zero
                coverStarredZeroColumns(coveredColumns, matrix);
            }

            // Find a non-covered zero and prime it
            auto primedZeroCoords = primeUncoveredZero(coveredRows, coveredColumns, matrix);
            int primedZeroRow = primedZeroCoords.first;
            int primedZeroColumn = primedZeroCoords.second;

            // If all zeros are covered - break the loop
            if (primedZeroRow == -1) {
                break;
            }

            int starredZeroColumn = findStarredZeroColumn(matrix, primedZeroRow);

            if (starredZeroColumn != -1) {
                // There exists a starred zero on the same row
                coveredRows[primedZeroRow] = true;
                coveredColumns[starredZeroColumn] = false;
                foundStarredZeroInPreviousStep = true;
            } else {
                // There is no starred zero on the same row

                // Construct the path
                auto path = getZerosPath(matrix, primedZeroRow, primedZeroColumn);

                // Unstar starred zeros and star primed zeros
                for (auto fragment: path) {
                    if (fragment->starred) {
                        fragment->starred = false;
                    }

                    if (fragment->primed) {
                        fragment->primed = false;
                        fragment->starred = true;
                    }
                }

                // Unprime all zeros and uncover all lines
                for (int j = 0; j < size; ++j) {
                    coveredColumns[j] = false;
                    coveredRows[j] = false;
                    for (int k = 0; k < size; ++k) {
                        if (matrix[j][k].primed) {
                            matrix[j][k].primed = false;
                        }
                    }
                }

                foundStarredZeroInPreviousStep = false;
            }
        }

        // Count number of lines used to cover all zeros
        int numberOfLines = getNumberOfLines(coveredRows, coveredColumns);

        // Leave the loop when the number of lines is equal to size
        if (numberOfLines == size) {
            break;
        }

        // STEP 5

        // Find the lowest uncovered value
        auto minValue = findLowestUncoveredValue(coveredRows, coveredColumns, matrix);

        // Subtract the lowest value from not covered cells
        subtractFromNotCoveredCells(coveredRows, coveredColumns, matrix, minValue);

        // Add the lowest value to covered twice cells
        addToCoveredTwiceCells(coveredRows, coveredColumns, matrix, minValue);
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (matrix[i][j].starred) {
                output[i][j] = true;
            }
        }
    }

    return output;
}

template Output hungarian(const std::vector<std::vector<int>> &input);
