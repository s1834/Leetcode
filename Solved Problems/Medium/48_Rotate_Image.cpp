class Solution {
    public:
        void rotate(vector<vector<int>>& matrix) {
            int n = matrix.size();
            
            //find transpose
            for(int i = 0; i < n; i++) {
                for(int j = i; j < n; j++) swap(matrix[i][j], matrix[j][i]);
            }
            
            //flip horizontally - For clock wise rotation
            for(int i = 0; i < n; i++) reverse(matrix[i].begin(), matrix[i].end());
        }
    };
    
/*
Problem: LeetCode 48 - Rotate Image

Approach: Transpose + Reverse Each Row

Intuition:
----------
We need to rotate an n x n matrix 90 degrees clockwise, in place.

The key observation is that a clockwise rotation can be achieved
using two operations:

1. Transpose the matrix.
2. Reverse every row horizontally.

The transpose swaps rows and columns, while reversing each row
moves the elements into their correct positions after rotation.

--------------------------------------------------
1. Find the Matrix Size
--------------------------------------------------

int n = matrix.size();

Store the number of rows in the square matrix.
Since the matrix is n x n, the number of columns is also n.

--------------------------------------------------
2. Transpose the Matrix
--------------------------------------------------

for(int i = 0; i < n; i++) {
    for(int j = i; j < n; j++)
        swap(matrix[i][j], matrix[j][i]);
}

The transpose converts each element at position (i, j) into
the corresponding position (j, i).

In other words, rows become columns and columns become rows.

For example:

Before transpose:
1 2 3
4 5 6
7 8 9

After transpose:
1 4 7
2 5 8
3 6 9

Why does j start from i?
-----------------------

The elements on the main diagonal, where i == j, remain unchanged
when transposed.

By starting j at i, we swap each pair of symmetric elements only
once and avoid undoing previous swaps.

For example, matrix[0][1] is swapped with matrix[1][0].
There is no need to perform the reverse swap again.

--------------------------------------------------
3. Reverse Every Row
--------------------------------------------------

for(int i = 0; i < n; i++)
    reverse(matrix[i].begin(), matrix[i].end());

After transposing the matrix, reverse each row to complete the
90-degree clockwise rotation.

For example:

After transpose:
1 4 7
2 5 8
3 6 9

After reversing every row:
7 4 1
8 5 2
9 6 3

This is the required clockwise-rotated matrix.

--------------------------------------------------
4. Why the Approach Works
--------------------------------------------------

Consider an element originally at position (i, j).

After transposition, it moves to (j, i).

Reversing row j moves it to column n - 1 - i.

Therefore, its final position is:

(i, j) -> (j, i) -> (j, n - 1 - i)

This is exactly the position required for a 90-degree clockwise
rotation.

Both operations modify the original matrix directly, so no
additional matrix is needed.

--------------------------------------------------
5. Complexity Analysis
--------------------------------------------------

Time Complexity: O(n^2)

- Transposing the matrix processes O(n^2) positions.
- Reversing all rows processes O(n^2) elements in total.

Space Complexity: O(1)

Both operations are performed in place using only a constant
amount of additional space.

Core Idea:
----------
Transpose the matrix by swapping matrix[i][j] with matrix[j][i],
then reverse every row to rotate the image 90 degrees clockwise
without using an extra matrix.
*/