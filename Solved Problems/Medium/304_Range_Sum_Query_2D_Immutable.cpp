class NumMatrix {
    private:
        vector<vector<int>> prefix;
    
    public:
        NumMatrix(vector<vector<int>>& matrix) {
            int n = matrix.size(), m = matrix[0].size();
    
            prefix.assign(n + 1, vector<int>(m + 1, 0));
    
            for(int i = 1; i <= n; i++) {
                for(int j = 1; j <= m; j++) {
                    prefix[i][j] = matrix[i-1][j-1] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1];
                }
            }
        }
        
        int sumRegion(int row1, int col1, int row2, int col2) {
            return prefix[row2 + 1][col2 + 1] - prefix[row1][col2 + 1] - prefix[row2 + 1][col1] + prefix[row1][col1];
        }
    };
    
    /**
     * Your NumMatrix object will be instantiated and called as such:
     * NumMatrix* obj = new NumMatrix(matrix);
     * int param_1 = obj->sumRegion(row1,col1,row2,col2);
     */

/*

Idea:
------
Since multiple range sum queries need to be answered,
computing the sum by traversing the rectangle every time
would be too slow.

Instead, preprocess the matrix using a 2D Prefix Sum
array.

Each cell in the prefix matrix stores the sum of all
elements from

(0,0)

to

(i-1, j-1).

Once the prefix matrix is built, any rectangular sum can
be obtained in O(1) time using the inclusion-exclusion
principle.

------------------------------------------------------------

2D Prefix Sum:
--------------

A prefix sum at position

prefix[i][j]

represents the sum of all elements inside the rectangle

(0,0) ---------- (0,j-1)
   |                 |
   |                 |
(i-1,0) ------- (i-1,j-1)

Notice that the prefix matrix is created with one extra
row and one extra column filled with zeros.

This avoids handling boundary conditions separately.

------------------------------------------------------------

Building the Prefix Matrix:
---------------------------

For every cell,

prefix[i][j]

contains

Current Cell

+

Upper Prefix

+

Left Prefix

-

Top-Left Prefix

Formula:

prefix[i][j]

=

matrix[i-1][j-1]

+

prefix[i-1][j]

+

prefix[i][j-1]

-

prefix[i-1][j-1]

------------------------------------------------------------

Why subtract Top-Left Prefix?
-----------------------------

Suppose we calculate

Upper Prefix + Left Prefix

The overlapping top-left rectangle gets counted twice.

Visual Representation

+-----------------------+
|##########|###########|
|##########|###########|
|##########|###########|
|-----------+----------|
|########## | Current  |
|########## |  Cell    |
+-----------------------+

Upper Prefix covers

everything above.

Left Prefix covers

everything to the left.

The shaded top-left region belongs to both, so it is
counted twice.

Subtracting

prefix[i-1][j-1]

removes this duplicate contribution.

------------------------------------------------------------

Answering Queries:
------------------

We need the sum inside the rectangle

(row1, col1)

to

(row2, col2)

Visual Representation

+---------------------------+
|//////////|^^^^^^^^^^^^^^^|
|//////////|^^^^^^^^^^^^^^^|
|----------+--------------|
|<<<<<<<<<<|##############|
|<<<<<<<<<<|##############|
|<<<<<<<<<<|##############|
+---------------------------+

############

is the required rectangle.

------------------------------------------------------------

Start with

prefix[row2+1][col2+1]

This contains everything from

(0,0)

to

(row2,col2).

------------------------------------------------------------

Subtract the area above

prefix[row1][col2+1]

------------------------------------------------------------

Subtract the area to the left

prefix[row2+1][col1]

------------------------------------------------------------

The top-left rectangle has now been removed twice.

Add it back once using

prefix[row1][col1]

------------------------------------------------------------

Formula:

Sum =

prefix[row2+1][col2+1]

-

prefix[row1][col2+1]

-

prefix[row2+1][col1]

+

prefix[row1][col1]

------------------------------------------------------------

Example:
--------

Matrix

1 2 3

4 5 6

7 8 9

Prefix Matrix

0   0   0   0

0   1   3   6

0   5  12  21

0  12  27  45

------------------------------------------------------------

Query

row1 = 1

col1 = 1

row2 = 2

col2 = 2

Required Rectangle

5 6

8 9

Answer

45

-

6

-

12

+

1

=

28

which equals

5 + 6 + 8 + 9

------------------------------------------------------------

Why Extra Row and Column?
-------------------------

Creating the prefix matrix of size

(n + 1) × (m + 1)

allows every formula to remain identical even when the
query touches the first row or first column.

Without the extra row/column,

special boundary checks would be required.

------------------------------------------------------------

Time Complexity:
----------------

Constructor:

O(n × m)

The prefix matrix is built once.

sumRegion():

O(1)

Each query requires only four prefix lookups.

------------------------------------------------------------

Space Complexity:
-----------------

O(n × m)

for storing the prefix sum matrix.

*/