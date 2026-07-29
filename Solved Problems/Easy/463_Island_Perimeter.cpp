class Solution {
    private:
        int dfs(vector<vector<int>>& grid, vector<vector<int>>& visited, int i, int j) {
            int row = grid.size(), col = grid[0].size();
    
            // if we are outside grid, add 1
            if(i >= row || i < 0 || j >= col || j < 0) return 1;
            
            // if water, add 1
            if(grid[i][j] == 0) return 1;
    
            // Already visited land
            if(visited[i][j]) return 0;
    
            visited[i][j] = 1;
    
            int perimeter = 0;
    
            // Check all four directions
            perimeter += dfs(grid, visited, i-1, j); // up
            perimeter += dfs(grid, visited, i+1, j); // down
            perimeter += dfs(grid, visited, i, j-1); // left
            perimeter += dfs(grid, visited, i, j+1); // right
    
            return perimeter;
        }
    
    public:
        int islandPerimeter(vector<vector<int>>& grid) {
            int row = grid.size(), col = grid[0].size();
    
            vector<vector<int>> visited(row, vector<int>(col, 0));
    
            for(int i = 0; i < row; i++) {
                for(int j = 0; j < col; j++) {
                    if(grid[i][j] == 1) return dfs(grid, visited, i, j);
                }
            }
    
            return 0;
        }
    };

/*

Idea:
------
The perimeter of an island is formed by every side of a
land cell that is adjacent to

• Water, or

• The boundary of the grid.

Instead of checking every edge separately,

we perform a

Depth First Search (DFS)

starting from the first land cell.

For every land cell,

we recursively explore its four neighbours.

Whenever the DFS reaches

• outside the grid, or

• a water cell,

it means the current edge contributes

1

to the perimeter.

The sum of all such boundary edges gives the total island
perimeter.

------------------------------------------------------------

Key Observation:
----------------

Each land cell has

4

possible edges.

An edge contributes to the perimeter only if it is not
shared with another land cell.

Therefore,

during DFS,

every recursive call can be interpreted as checking one
edge of the current land cell.

If that edge touches water or lies outside the grid,

it contributes

1

to the perimeter.

------------------------------------------------------------

Visited Matrix:
---------------

Since neighbouring land cells recursively call each other,

the same land cell may otherwise be visited multiple times.

The

visited

matrix ensures that every land cell is processed only
once.

If a land cell has already been visited,

it contributes

0

because its perimeter has already been counted.

------------------------------------------------------------

DFS State:
----------

The recursive function

dfs(grid, visited, i, j)

returns

"The total perimeter contributed by the connected island
starting from cell

(i, j)."

------------------------------------------------------------

Base Cases:
-----------

Case 1

Outside the Grid

If

(i, j)

lies outside the grid,

the current edge is exposed.

Return

1.

--------------------------------

Case 2

Water Cell

If

grid[i][j] == 0,

the current edge touches water.

Return

1.

--------------------------------

Case 3

Already Visited Land

If

visited[i][j]

is true,

this land cell has already been processed.

Return

0.

Otherwise,

the same perimeter would be counted multiple times.

------------------------------------------------------------

Recursive Step:
---------------

If the current cell is unvisited land,

mark it as visited.

Now,

explore all four neighbouring cells.

Up

↓

dfs(i-1, j)

--------------------------------

Down

↓

dfs(i+1, j)

--------------------------------

Left

↓

dfs(i, j-1)

--------------------------------

Right

↓

dfs(i, j+1)

Each recursive call returns

either

1

if that side contributes to the perimeter,

or

the perimeter contributed by neighbouring land.

The total perimeter of the current component is simply the
sum of all four recursive calls.

------------------------------------------------------------

Algorithm:
----------

Step 1

Create a

visited

matrix.

------------------------------------------------------------

Step 2

Find the first land cell.

The problem guarantees there is exactly one island, so one
DFS is sufficient.

------------------------------------------------------------

Step 3

Start DFS from that land cell.

------------------------------------------------------------

Step 4

Whenever DFS reaches

water

or

outside the grid,

return

1.

------------------------------------------------------------

Step 5

Whenever DFS reaches an already visited land cell,

return

0.

------------------------------------------------------------

Step 6

Otherwise,

mark the land as visited,

recursively explore all four directions,

and return their total perimeter contribution.

------------------------------------------------------------

Example:
--------

Grid

1 1

1 0

Visual

■■

■□

--------------------------------

Start DFS from

(0,0)

Explore

Up

↓

Outside

Return

1

--------------------------------

Left

↓

Outside

Return

1

--------------------------------

Right

↓

Land

Continue DFS

--------------------------------

Down

↓

Land

Continue DFS

Every exposed edge contributes

1.

Total perimeter

=

8

------------------------------------------------------------

Example:
--------

Grid

1

Single land cell

Its four neighbours are

Top

Outside

↓

1

Bottom

Outside

↓

1

Left

Outside

↓

1

Right

Outside

↓

1

Total

=

4

------------------------------------------------------------

Recursion Tree:
---------------

Suppose

Grid

1 1

1 0

DFS

          (0,0)
        /   |   |   \
      Out  (1,0) Out (0,1)
             |
            ...

Whenever recursion reaches

water

or

outside,

that branch contributes exactly

1

to the answer.

------------------------------------------------------------

Why Does Returning 1 Work?
--------------------------

Think of every recursive call as checking

one edge

of the current land cell.

If that edge touches

another land cell,

the recursion continues.

If that edge touches

water

or

the boundary,

that edge becomes part of the island perimeter.

Therefore,

returning

1

correctly counts that exposed edge.

------------------------------------------------------------

Why Does This Work?
-------------------

DFS visits every land cell exactly once.

For every visited land cell,

all four edges are examined.

If an edge is adjacent to another land cell,

DFS simply continues without immediately contributing to
the perimeter.

If an edge is adjacent to water or lies outside the grid,

that edge contributes exactly

1

to the perimeter.

Since every exposed edge is encountered exactly once,

and every internal shared edge is ignored,

the total returned by DFS equals the island perimeter.

------------------------------------------------------------

Correctness Proof:
------------------

We prove that the algorithm returns the correct perimeter
of the island.

Every land cell is visited exactly once because of the

visited

matrix.

For every visited land cell,

all four neighbouring positions are examined.

If a neighbouring position is outside the grid or contains
water,

the corresponding edge is exposed and contributes exactly

1

to the perimeter.

If the neighbour is another land cell,

that edge is internal to the island and therefore does not
contribute directly to the perimeter.

The recursive DFS continues exploring that neighbouring
land cell.

Already visited land cells contribute

0,

preventing duplicate counting.

Thus,

every exposed boundary edge is counted exactly once,

while every internal edge contributes nothing.

Hence,

the final sum returned by DFS is exactly the perimeter of
the island.

------------------------------------------------------------

Time Complexity:
----------------

Let

m

be the number of rows,

and

n

be the number of columns.

Each land cell is visited at most once.

Each visit performs constant work by exploring four
directions.

Overall Time Complexity:

O(m × n)

------------------------------------------------------------

Space Complexity:
-----------------

Visited Matrix

O(m × n)

--------------------------------

Recursion Stack

In the worst case,

the entire island may be connected,

leading to recursion depth

O(m × n).

Overall Auxiliary Space:

O(m × n)

------------------------------------------------------------

Note:
-----

This problem also has an elegant iterative solution.

For every land cell,

start with

4

edges.

Subtract

2

for every shared edge with its upper or left neighbour.

That approach also runs in

O(m × n)

time while using

O(1)

extra space.

*/