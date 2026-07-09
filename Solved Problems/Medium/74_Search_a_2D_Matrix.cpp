class Solution {
    bool searchRow(vector<vector<int>>& matrix, int target, int left, int right) {
        if(left > right) return false;

        int mid = left + (right - left) / 2;
        if(matrix[mid][0] <= target && target <= matrix[mid][matrix[mid].size() - 1]) return searchColumn(matrix[mid], target, 0, matrix[mid].size() - 1);
        else if(matrix[mid][0] < target) return searchRow(matrix, target, mid + 1, right);
        else return searchRow(matrix, target, left, mid - 1);

    }

    bool searchColumn(vector<int>& column, int target, int left, int right) {
        if(left > right) return false;

        int mid = left + (right - left) / 2;
        if(column[mid] == target) return true;
        else if(column[mid] < target) return searchColumn(column, target, mid + 1, right);
        else return searchColumn(column, target, left, mid - 1);
    }

public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        return searchRow(matrix, target, 0, matrix.size() - 1);
    }
};

/*

Idea:
------
Since the matrix has two properties:

1. Every row is sorted in increasing order.
2. The first element of every row is greater than the last element
   of the previous row.

We can first locate the correct row using Binary Search.

Once the correct row is found, perform another Binary Search
inside that row.

So the problem is divided into two binary searches:

    1. Binary Search on rows.
    2. Binary Search on columns.

------------------------------------------------------------

Searching the Row:
------------------

For every middle row, compare the target with the
first and last element of that row.

There are three possibilities.

1.

target lies inside the range

[first element ... last element]

Then the target, if present, must be inside this row.

Perform Binary Search on this row.

------------------------------------------------------------

2.

target is greater than the first element but does not
lie inside this row.

Since the previous condition has already failed, this means

    target > last element

Therefore every element in this row is too small.

Search the rows below.

------------------------------------------------------------

3.

Otherwise,

    target < first element

Every element in this row is too large.

Search the rows above.

------------------------------------------------------------

Searching the Column:
---------------------

Once the correct row is found, perform a normal Binary Search.

There are three possibilities.

1.

column[mid] == target

Target found.

------------------------------------------------------------

2.

column[mid] < target

Target must lie on the right.

------------------------------------------------------------

3.

column[mid] > target

Target must lie on the left.

------------------------------------------------------------

Example:
--------

Matrix

[
 [1,3,5,7],
 [10,11,16,20],
 [23,30,34,60]
]

Target = 16

Row Search

Middle Row

[10,11,16,20]

Since

10 <= 16 <= 20

Search inside this row.

Column Search

10 11 16 20

Middle

16

Target found.

------------------------------------------------------------

Another Example:
----------------

Target = 23

Row Search

Middle Row

[10,11,16,20]

Target is greater than the last element.

Search lower rows.

Next Row

[23,30,34,60]

Target lies inside this row.

Binary Search finds 23.

------------------------------------------------------------

Time Complexity:
----------------

Row Binary Search

O(log m)

Column Binary Search

O(log n)

Overall

O(log m + log n)

------------------------------------------------------------

Space Complexity:
-----------------

O(log m + log n)

Due to recursive Binary Search calls.

*/