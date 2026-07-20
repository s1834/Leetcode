class Solution {
    public:
        vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
            int row = grid.size(), column = grid[0].size();
            vector<vector<int>> ans(row, vector<int>(column));
            for(int i = 0; i < row; i++) {
                for(int j = 0; j < column; j++) {
                    int idx1D = i * column + j;
                    int newIdx1D = (idx1D + k) % (row * column);
                    ans[newIdx1D / column][newIdx1D % column] = grid[i][j];
                }
            }
            return ans;
        }
    };

/*

Idea:
------
Instead of physically shifting the grid

k

times, observe that the grid can be viewed as a single
1D array.

Once every element is mapped to its corresponding
1D index,

shifting the grid simply becomes shifting positions in
that 1D array.

Finally,

convert every shifted 1D index back into its
corresponding 2D position.

------------------------------------------------------------

Mathematical Mapping:
---------------------

Suppose the grid has

R rows

and

C columns.

Every cell

(i, j)

can be uniquely represented by a single index.

Formula:

1D Index

=

i × C + j

------------------------------------------------------------

Why does this work?
-------------------

Every complete row contains exactly

C

elements.

So,

before reaching row

i,

there are

i × C

elements.

Adding the column number gives the exact position in the
flattened array.

Example:

Grid

1 2 3
4 5 6
7 8 9

Rows = 3

Columns = 3

Indices become

Value      1D Index

1              0

2              1

3              2

4              3

5              4

6              5

7              6

8              7

9              8

Notice

(0,0)

→ 0×3+0 = 0

(0,2)

→ 0×3+2 = 2

(1,0)

→ 1×3+0 = 3

(2,1)

→ 2×3+1 = 7

------------------------------------------------------------

Shifting by k:
--------------

Suppose the total number of elements is

N = R × C

If an element is currently at index

idx,

after shifting by

k,

its new position becomes

(idx + k) % N

The modulo is necessary because once we move past the
last index,

we wrap around to the beginning.

------------------------------------------------------------

Example:

Grid

1 2 3
4 5 6
7 8 9

Flattened

[1,2,3,4,5,6,7,8,9]

Indices

0 1 2 3 4 5 6 7 8

Suppose

k = 2

Element

1

Current Index = 0

New Index

(0 + 2) % 9

= 2

--------------------------------

Element

8

Current Index = 7

New Index

(7 + 2) % 9

= 0

because

9 % 9 = 0

--------------------------------

Element

9

Current Index = 8

New Index

(8 + 2) % 9

= 1

New flattened array

[8,9,1,2,3,4,5,6,7]

------------------------------------------------------------

Converting Back to 2D:
----------------------

Once the new 1D index is known,

we convert it back into

(row, column).

Formula

Row

=

newIndex / C

Column

=

newIndex % C

------------------------------------------------------------

Why does this work?

Suppose

Columns = 4

Indices

0 1 2 3

belong to Row 0

Indices

4 5 6 7

belong to Row 1

Indices

8 9 10 11

belong to Row 2

For example,

Index = 10

Row

10 / 4

= 2

Column

10 % 4

= 2

Therefore,

Index 10 corresponds to

(2,2)

------------------------------------------------------------

Complete Example:
-----------------

Grid

1 2 3

4 5 6

Rows = 2

Columns = 3

Flattened

Index

0 1 2 3 4 5

Values

1 2 3 4 5 6

Suppose

k = 2

--------------------------------

Element

1

Index = 0

New Index = 2

Placed at

Row = 2 / 3 = 0

Column = 2 % 3 = 2

--------------------------------

Element

2

Index = 1

New Index = 3

Placed at

(1,0)

--------------------------------

Element

5

Index = 4

New Index

(4+2)%6 = 0

Placed at

(0,0)

--------------------------------

Element

6

Index = 5

New Index

(5+2)%6 = 1

Placed at

(0,1)

Final Grid

5 6 1

2 3 4

Exactly the required shifted grid.

------------------------------------------------------------

Algorithm:
----------

1.

Compute

Rows

and

Columns.

------------------------------------------------------------

2.

Create an answer matrix of the same size.

------------------------------------------------------------

3.

For every cell

(i, j),

compute its 1D index

idx

=

i × Columns + j

------------------------------------------------------------

4.

Compute its shifted index

newIdx

=

(idx + k)

%

(Rows × Columns)

------------------------------------------------------------

5.

Convert

newIdx

back into

(newRow, newColumn)

using

newRow

=

newIdx / Columns

newColumn

=

newIdx % Columns

------------------------------------------------------------

6.

Place the current element into its new position.

------------------------------------------------------------

7.

Return the shifted grid.

------------------------------------------------------------

Time Complexity:
----------------

O(R × C)

Every element is processed exactly once.

------------------------------------------------------------

Space Complexity:
-----------------

O(R × C)

for storing the shifted grid.

*/