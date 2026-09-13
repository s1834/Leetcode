class Solution {
    private:
        int n;
        
        int countOverlaps(vector<vector<int>>& img1, vector<vector<int>>& img2, int rowOff, int colOff) {
            int overlaps = 0;
    
            for(int i = 0; i < n ; i++) { // row
                for(int j = 0; j < n; j++) { // col
                    int row = i + rowOff;
                    int col = j + colOff;
    
                    if(row < 0 || row >= n || col < 0 || col >= n) continue;
    
                    if(img1[i][j] == 1 && img2[row][col] == 1) overlaps++;
                }
            }
    
            return overlaps;
        }
    
    public:
        int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
            n = img1.size();
            int overlaps = 0;
            for(int i = -n + 1; i < n; i++) { // row offst (-n + 1 -> n -1)
                for(int j = -n + 1; j < n; j++) { // column offset (-n + 1 -> n -1)
                    overlaps = max(overlaps, countOverlaps(img1, img2, i, j));
                }
            }
    
            return overlaps;
        }
    };

/*
LeetCode 835. Image Overlap

Approach:
---------

We need to find the maximum number of overlapping 1s after shifting
one image relative to the other.

The important observation is:

    We do NOT need to actually shift the image.

Instead, we try every possible row and column offset and calculate
how many positions contain 1 in both images after applying that
offset.

------------------------------------------------------------

Understanding the Offset
------------------------

Suppose we use:

    rowOff
    colOff

for the shift.

For every cell (i, j) in img1, its corresponding position in img2
after shifting is:

    row = i + rowOff
    col = j + colOff

So we compare:

    img1[i][j]

with:

    img2[i + rowOff][j + colOff]

If both are 1, we have one overlap.

------------------------------------------------------------

Why Are Offsets From -n + 1 To n - 1?
--------------------------------------

The image has dimensions:

    n x n

For two n x n images, the maximum useful shift in either direction
is n - 1.

Therefore:

    rowOff = -(n - 1) ... (n - 1)
    colOff = -(n - 1) ... (n - 1)

which is written as:

    for(int i = -n + 1; i < n; i++)

and:

    for(int j = -n + 1; j < n; j++)

We try every possible relative position of the two images where
at least one cell can still overlap.

------------------------------------------------------------

Example of Offset
-----------------

Suppose:

    rowOff = 1
    colOff = 2

For a cell:

    img1[i][j]

we compare it with:

    img2[i + 1][j + 2]

So img1 is effectively shifted one row down and two columns right
relative to img2.

If:

    img1[i][j] == 1
    img2[i + 1][j + 2] == 1

then these two 1s overlap.

------------------------------------------------------------

Step 1: countOverlaps()
-----------------------

The helper function:

    countOverlaps(img1, img2, rowOff, colOff)

calculates the number of overlapping 1s for ONE particular shift.

We start with:

    int overlaps = 0;

Then check every position of img1:

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)

For every cell, calculate the corresponding position in img2:

    int row = i + rowOff;
    int col = j + colOff;

------------------------------------------------------------

Boundary Check
--------------

The shifted position may fall outside img2.

For example, if:

    row = -1

there is no such row in img2.

Therefore we ignore that position:

    if(row < 0 || row >= n || col < 0 || col >= n)
        continue;

This ensures that we only access valid positions.

------------------------------------------------------------

Checking Overlap
----------------

After confirming that the shifted position is inside img2:

    if(img1[i][j] == 1 && img2[row][col] == 1)
        overlaps++;

We increase the count only when both corresponding cells contain 1.

For example:

    img1 cell = 1
    img2 cell = 1

gives:

    overlap + 1

But:

    1 and 0
    0 and 1
    0 and 0

all contribute:

    0

------------------------------------------------------------

Step 2: Try Every Shift
------------------------

Inside largestOverlap():

    int overlaps = 0;

This stores the maximum overlap found so far.

We then try every possible row offset:

    for(int i = -n + 1; i < n; i++)

and every possible column offset:

    for(int j = -n + 1; j < n; j++)

For each combination, calculate:

    countOverlaps(img1, img2, i, j)

and update:

    overlaps = max(overlaps,
                   countOverlaps(img1, img2, i, j));

Therefore, after checking all possible shifts, overlaps contains
the maximum possible number of overlapping 1s.

------------------------------------------------------------

Why Don't We Actually Shift the Image?
---------------------------------------

Actually creating a shifted image for every possible offset would
require additional work and space.

Instead, we simulate the shift using:

    row = i + rowOff
    col = j + colOff

This gives exactly the same result without modifying either image.

So:

    Original img1 coordinate:
        (i, j)

    Shifted corresponding coordinate in img2:
        (i + rowOff, j + colOff)

This is the key idea of the solution.

------------------------------------------------------------

Example:
---------

Suppose:

    img1 =

    1 0
    0 0

and:

    img2 =

    0 1
    0 0

If we use:

    rowOff = 0
    colOff = 1

then the 1 at:

    img1[0][0]

is compared with:

    img2[0][1]

Both are 1.

Therefore:

    overlaps = 1

The algorithm tries every possible offset and keeps the largest
value.

------------------------------------------------------------

Algorithm:
----------

    1. Store n = size of the image.

    2. Try every possible row offset from:
           -(n - 1) to (n - 1)

    3. For every row offset, try every possible column offset from:
           -(n - 1) to (n - 1)

    4. For the current offset:
           - Visit every cell of img1.
           - Calculate its shifted position in img2.
           - Ignore positions outside img2.
           - If both cells contain 1, increase overlap count.

    5. Keep the maximum overlap over all offsets.

    6. Return the maximum overlap.

------------------------------------------------------------

Complexity:
-----------

There are:

    (2n - 1)

possible row offsets and:

    (2n - 1)

possible column offsets.

Therefore, the number of shifts is:

    (2n - 1)^2

which is approximately:

    O(n^2)

For every shift, we examine all:

    n * n

cells.

Therefore:

    Time Complexity = O(n^4)

More precisely:

    O((2n - 1)^2 * n^2)

which simplifies to:

    O(n^4)

------------------------------------------------------------

Space Complexity:
-----------------

We do not create any additional n x n matrix.

Only a few integer variables are used.

Therefore:

    O(1)

extra space.

------------------------------------------------------------

Core Idea:
----------

Instead of physically shifting the image, try every possible
(rowOffset, columnOffset).

For every offset:

    img1[i][j]
            |
            v
    img2[i + rowOffset][j + columnOffset]

If both positions contain 1, count an overlap.

Finally:

    answer = maximum overlap across all possible shifts.

The key trick is using coordinate offsets to simulate image
shifting without actually modifying the matrices.
*/