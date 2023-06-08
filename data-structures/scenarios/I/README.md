# First scenario

Insertions in the middle of the list. Read anywhere.

# Implementation

An array is divided in 2 parts: left and right.
Sizes of both parts are maintained to be equal.
An insertion in the middle of array will hit in 2 possible cases:

1. Inserting approximately in the end of left part. This will take ~O(1).
2. Inserting in the start of right part. The right part is stored in reverse order, so inserting in the end of right
   part is ~O(1) too.

# Example

If we have an array [1, 5, 2, 5, 3, 4, 6, 7, 2, 2, 3, 4, 1, 0, 7, 8]

Left part: [1, 5, 2, 5, 3, 4, 6, 7]
Right part:  [8, 7, 0, 1, 4, 3, 2, 2] (reverse order)

- Get(5) - take an element from left part as 5 < _size(left)
- Get(9) - take an element with index: (_size(right) - 1) - (9 - _size(left)), from right part
- Insert(9, 42) - insert in the end of right part. New right part is: [8, 7, 0, 1, 4, 3, 2, 42, 2]
- Insert(8, 24) - casually insert in left part

Also, after every insertion we need to check if sizes of both parts are nearly equal. If sizes differ 2 times, then do
rebalance.
