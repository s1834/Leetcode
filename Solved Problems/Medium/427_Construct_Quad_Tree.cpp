/*
// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;
    
    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};
*/

class Solution {
    private:
        bool isSame(vector<vector<int>>& grid, int x, int y, int n) {
            int val = grid[x][y];
            for(int i = x; i < x + n; i++) {
                for(int j = y; j < y + n; j++) {
                    if(grid[i][j] != val) return false;
                }
            }
            return true;
        }
    
        Node* build(vector<vector<int>>& grid, int x, int y, int n) {
            if(isSame(grid, x, y, n)) {
                return new Node(grid[x][y], true);
            } else {
                Node* root = new Node(1, false);
    
                root->topLeft = build(grid, x, y, n /2);
                root->topRight = build(grid, x, y + n /2, n / 2);
                root->bottomLeft = build(grid, x + n / 2, y, n / 2);
                root->bottomRight = build(grid, x + n / 2, y + n / 2, n / 2);
    
                return root;
            }
        }
    
    public:
        Node* construct(vector<vector<int>>& grid) {
            return build(grid, 0, 0, grid.size());
        }
    };

/*

Idea:
------
A Quad Tree represents a square grid recursively.

For every square region,

there are only two possibilities:

1.

Every cell inside the region has the same value.

Then,

this region can be represented by a single

Leaf Node.

------------------------------------------------------------

2.

The region contains both

0

and

1.

Then,

it must be divided into four equal quadrants,

and each quadrant is recursively represented by its own
Quad Tree.

This is exactly a Divide and Conquer problem.

------------------------------------------------------------

Quad Tree Representation:
-------------------------

Every node represents one square region.

--------------------------------

Leaf Node

Represents a region where every cell has the same value.

Example

1 1
1 1

↓

Leaf Node

value = 1

isLeaf = true

--------------------------------

Internal Node

Represents a mixed region.

It has four children:

• Top Left

• Top Right

• Bottom Left

• Bottom Right

------------------------------------------------------------

Algorithm:
----------

For every square region

(x, y, size)

Step 1

Check whether every cell in this square has the same
value.

This is done using

isSame().

------------------------------------------------------------

Step 2

If every cell is identical,

create a

Leaf Node

whose value is that common value.

No further recursion is needed.

------------------------------------------------------------

Step 3

Otherwise,

the square contains both

0

and

1,

so it cannot be represented by one node.

Split the square into four equal quadrants.

--------------------------------

Top Left

(x, y)

--------------------------------

Top Right

(x, y + size/2)

--------------------------------

Bottom Left

(x + size/2, y)

--------------------------------

Bottom Right

(x + size/2, y + size/2)

------------------------------------------------------------

Step 4

Recursively construct Quad Trees for all four quadrants.

------------------------------------------------------------

Step 5

Create an internal node

(isLeaf = false)

whose four children are the recursively constructed
subtrees.

------------------------------------------------------------

Uniformity Check:
-----------------

The helper function

isSame()

checks whether every element inside the current square
equals the first element.

Suppose the region begins at

(x, y).

Let

value = grid[x][y]

Traverse every cell inside the square.

If any cell differs,

the region is mixed.

Return

false.

Otherwise,

all cells are identical,

so return

true.

------------------------------------------------------------

Why Does This Work?
-------------------

Every square region is processed independently.

If the region is uniform,

the Quad Tree definition states that it should be
represented by a single leaf node.

If the region is mixed,

the Quad Tree definition requires dividing it into four
equal quadrants.

Since each recursive call handles one smaller square,

the recursion eventually reaches regions that are
uniform,

at which point recursion stops.

Thus,

every region is represented exactly according to the Quad
Tree definition.

------------------------------------------------------------

Example:
--------

Grid

1 1
1 1

--------------------------------

Entire grid is uniform.

Create

Leaf Node

value = 1

isLeaf = true

Finished.

------------------------------------------------------------

Example:
--------

Grid

1 1
1 0

--------------------------------

Entire grid is not uniform.

Split into four

1 × 1

quadrants.

Top Left

1

↓

Leaf

--------------------------------

Top Right

1

↓

Leaf

--------------------------------

Bottom Left

1

↓

Leaf

--------------------------------

Bottom Right

0

↓

Leaf

--------------------------------

Create one internal node whose four children are these
leaf nodes.

------------------------------------------------------------

Recursive Decomposition:
------------------------

Suppose

n = 8

The recursion divides the grid as

8 × 8

↓

4 × 4

↓

2 × 2

↓

1 × 1

Every recursive call works on one smaller square until a
uniform region is obtained.

------------------------------------------------------------

Time Complexity:
----------------

Let

N

be the side length of the grid.

For each recursive call,

isSame()

checks every cell in the current square.

The grid is recursively divided into four smaller
quadrants.

In the worst case (every region is mixed until reaching
individual cells),

the total running time is

O(N² log N)

------------------------------------------------------------

Space Complexity:
-----------------

The recursion depth is

log₂(N)

because each recursive call halves the side length.

Ignoring the memory required for the output Quad Tree,

the auxiliary recursion stack is

O(log N)

The Quad Tree itself stores one node for every region
created.

*/