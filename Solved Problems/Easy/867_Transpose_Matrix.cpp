class Solution {
    public:
        vector<vector<int>> transpose(vector<vector<int>>& matrix) {
            int row = matrix.size(), col = matrix[0].size();
            vector<vector<int>> ans(col, vector<int>(row));
            for(int i = 0; i < row; i++) {
                for(int j = 0; j < col; j++) ans[j][i] = matrix[i][j];
            }
            return ans;
        }
    };

/*

Idea:
------
The transpose of a matrix is obtained by swapping its

rows

and

columns.

In other words,

every element located at

(i, j)

in the original matrix moves to

(j, i)

in the transposed matrix.

Since the number of rows and columns may be different,

we create a new matrix with dimensions

(columns × rows)

and place every element in its transposed position.

------------------------------------------------------------

Key Observation:
----------------

For every element

matrix[i][j],

its position in the transpose is always

transpose[j][i].

Mathematically,

Original

A(i, j)

↓

Transpose

Aᵀ(j, i)

Thus,

the solution simply swaps the row and column indices of
every element.

------------------------------------------------------------

Matrix Dimensions:
------------------

Suppose the original matrix has

R

rows and

C

columns.

Original Matrix

R × C

After transposition,

Rows become Columns,

and

Columns become Rows.

Transpose Matrix

C × R

Therefore,

the answer matrix is initialized as

vector<vector<int>> ans(col, vector<int>(row));

------------------------------------------------------------

Example:
--------

Original Matrix

1 2 3

4 5 6

Dimensions

2 × 3

Transpose

1 4

2 5

3 6

Dimensions

3 × 2

Notice

Every element

(i, j)

moves to

(j, i).

------------------------------------------------------------

Element Mapping:
----------------

Original

matrix[0][0] = 1

↓

ans[0][0] = 1

--------------------------------

matrix[0][1] = 2

↓

ans[1][0] = 2

--------------------------------

matrix[0][2] = 3

↓

ans[2][0] = 3

--------------------------------

matrix[1][0] = 4

↓

ans[0][1] = 4

--------------------------------

matrix[1][1] = 5

↓

ans[1][1] = 5

--------------------------------

matrix[1][2] = 6

↓

ans[2][1] = 6

------------------------------------------------------------

Algorithm:
----------

Step 1

Determine

row

and

col

of the original matrix.

------------------------------------------------------------

Step 2

Create an empty matrix having dimensions

col × row.

------------------------------------------------------------

Step 3

Traverse every element of the original matrix.

------------------------------------------------------------

Step 4

Place

matrix[i][j]

into

ans[j][i].

------------------------------------------------------------

Step 5

After processing every element,

return the transposed matrix.

------------------------------------------------------------

Example Walkthrough:
--------------------

Input

[
 [1,2,3],
 [4,5,6]
]

Initially

ans

=

[
 [0,0],
 [0,0],
 [0,0]
]

--------------------------------

i = 0

j = 0

ans[0][0] = 1

--------------------------------

j = 1

ans[1][0] = 2

--------------------------------

j = 2

ans[2][0] = 3

--------------------------------

i = 1

j = 0

ans[0][1] = 4

--------------------------------

j = 1

ans[1][1] = 5

--------------------------------

j = 2

ans[2][1] = 6

Final Answer

[
 [1,4],
 [2,5],
 [3,6]
]

------------------------------------------------------------

Visualization:
--------------

Original

      Columns
        0 1 2
Rows 0 [1 2 3]
     1 [4 5 6]

Transpose

      Columns
        0 1
Rows 0 [1 4]
     1 [2 5]
     2 [3 6]

Every

(row, column)

becomes

(column, row).

------------------------------------------------------------

Why Does This Work?
-------------------

A transpose is defined by exchanging the row index and the
column index of every matrix element.

The algorithm visits every element exactly once and copies
it to its new location

(j, i)

inside the answer matrix.

Since every element is placed according to the mathematical
definition of matrix transpose,

the resulting matrix is exactly the transpose of the
original matrix.

------------------------------------------------------------

Correctness Proof:
------------------

We prove that the algorithm returns the correct transpose.

Consider any element

matrix[i][j].

By definition,

the transpose of a matrix satisfies

transpose[j][i] = matrix[i][j].

During traversal,

the algorithm assigns

ans[j][i] = matrix[i][j]

for every valid pair

(i, j).

Since every element of the original matrix is processed
exactly once,

every position in the transpose receives the correct value,

and no value is overwritten incorrectly.

Therefore,

the returned matrix satisfies the definition of matrix
transpose for every element,

making the algorithm correct.

------------------------------------------------------------

Time Complexity:
----------------

Let

R

be the number of rows,

and

C

be the number of columns.

Every element is visited exactly once.

Overall Time Complexity

O(R × C)

------------------------------------------------------------

Space Complexity:
-----------------

A new matrix of size

C × R

is created.

Overall Auxiliary Space

O(R × C)

------------------------------------------------------------

Note:
-----

The transpose is created in a separate matrix because the
input matrix may not be square.

An in-place transpose is only possible for

square matrices

(N × N).

*/