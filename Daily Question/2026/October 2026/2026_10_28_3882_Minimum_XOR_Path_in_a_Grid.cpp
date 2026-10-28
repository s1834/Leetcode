class Solution {
    public:
        int minCost(vector<vector<int>>& grid) {
            int m = grid.size();
            int n = grid[0].size();
    
            vector<vector<bitset<1024>>> dp(m, vector<bitset<1024>>(n)); //dp[i][j] = it stores a bitset<1024> {0, 0, 1, 1, 0, .....}
    
            dp[0][0][grid[0][0]] = 1;
    
            for(int i = 0; i < m; i++) {
                for(int j = 0; j < n; j++) {
                    if(i == 0 && j == 0) continue;
    
                    bitset<1024> up; //[i-1][j]
                    bitset<1024> left; //[i][j-1]
    
                    if(i > 0) up = dp[i-1][j];
                    if(j > 0) left = dp[i][j-1];
    
                    bitset<1024> combined = up | left; //OR operation
    
                    for(int xorVal = 0; xorVal < 1024; xorVal++) {
                        if(combined[xorVal]) {
                            int resultXorVal = xorVal ^ grid[i][j];
                            dp[i][j][resultXorVal] = 1;
                        }
                    }
                }
            }
    
            //dp[m-1][n-1]
            for(int xorVal = 0; xorVal < 1024; xorVal++) {
                if(dp[m-1][n-1][xorVal]) return xorVal;
            }
    
            return -1;
        }
    };

/*
Problem: LeetCode 3882 - Minimum Cost / Minimum XOR Path

Approach: Dynamic Programming + Bitset + XOR State Tracking

Intuition:
----------
We need to find the minimum XOR value obtainable along a path from
the top-left cell (0, 0) to the bottom-right cell (m - 1, n - 1).

The path can move only:
- Down
- Right

The XOR of a path is obtained by XORing the values of all cells
visited along that path.

The key observation is that reaching the same cell can produce
multiple different XOR values depending on the path taken.

Therefore, instead of storing only one XOR value for each cell,
we maintain a bitset of all XOR values that are achievable at that
cell.

Since the code uses bitset<1024>, it tracks XOR values from 0 to 1023.

--------------------------------------------------
1. Initialize Grid Dimensions
--------------------------------------------------

int m = grid.size();
int n = grid[0].size();

Store the number of rows and columns in the grid.

--------------------------------------------------
2. Define the DP State
--------------------------------------------------

vector<vector<bitset<1024>>> dp(
    m, vector<bitset<1024>>(n)
);

dp[i][j] represents the set of all XOR values achievable by paths
from the starting cell (0, 0) to cell (i, j).

Each dp[i][j] is a bitset containing 1024 bits.

Interpretation:
- dp[i][j][x] == 1 means XOR value x is achievable at cell (i, j).
- dp[i][j][x] == 0 means XOR value x has not been recorded as
  achievable at that cell.

For example, if the bitset represents:

{0, 1, 1, 0, 1, ...}

then the XOR values corresponding to set bits are achievable.

This representation allows us to track multiple possible XOR values
without maintaining a separate collection of integers for each cell.

--------------------------------------------------
3. Initialize the Starting Cell
--------------------------------------------------

dp[0][0][grid[0][0]] = 1;

There is only one path to the starting cell: the path containing
the starting cell itself.

Therefore, the initial XOR value is grid[0][0].

Set the corresponding bit to 1 to record this value.

--------------------------------------------------
4. Traverse the Grid
--------------------------------------------------

for(int i = 0; i < m; i++) {
    for(int j = 0; j < n; j++) {

Process every cell row by row, from top to bottom and left to right.

if(i == 0 && j == 0) continue;

The starting cell has already been initialized, so skip it.

--------------------------------------------------
5. Collect XOR States From Previous Cells
--------------------------------------------------

bitset<1024> up;
bitset<1024> left;

These temporary bitsets represent the possible XOR values arriving
from the cell above and the cell to the left.

The bitsets are initialized to zero, so they represent no available
states until a valid predecessor is assigned.

From Above:
-----------

if(i > 0) up = dp[i-1][j];

If the current cell has a row above it, copy the XOR states from
dp[i - 1][j].

From the Left:
--------------

if(j > 0) left = dp[i][j-1];

If the current cell has a column to its left, copy the XOR states
from dp[i][j - 1].

Only these two predecessor cells are considered because movement
is restricted to down and right.

--------------------------------------------------
6. Combine the Available XOR States
--------------------------------------------------

bitset<1024> combined = up | left;

The bitwise OR combines the possible XOR values from both
predecessors.

If a particular bit is set in either up or left, it will also be
set in combined.

This means combined contains every XOR value that can reach the
current cell before including the current cell's value.

If the same XOR value is achievable through both predecessors,
it is still represented by one set bit, which is sufficient because
we only care whether a value is achievable.

--------------------------------------------------
7. Apply the Current Cell's XOR
--------------------------------------------------

for(int xorVal = 0; xorVal < 1024; xorVal++) {

Enumerate every possible XOR value from 0 through 1023.

if(combined[xorVal]) {

Process only values that are achievable from at least one
predecessor.

int resultXorVal = xorVal ^ grid[i][j];

When entering the current cell, XOR the previous path value with
grid[i][j].

For example:

Previous XOR = 5
Current cell value = 3

New XOR = 5 ^ 3 = 6

The XOR operation combines the previous path's accumulated value
with the current cell's value.

dp[i][j][resultXorVal] = 1;

Mark the resulting XOR value as achievable at the current cell.

After processing all possible XOR states, dp[i][j] contains every
XOR value that can be obtained by a valid path from (0, 0) to (i, j).

--------------------------------------------------
8. Find the Minimum XOR at the Destination
--------------------------------------------------

for(int xorVal = 0; xorVal < 1024; xorVal++) {

Scan all possible XOR values in increasing order.

if(dp[m-1][n-1][xorVal]) return xorVal;

The first set bit encountered corresponds to the smallest achievable
XOR value at the bottom-right cell.

Because the values are checked from 0 upward, the first achievable
value is the minimum.

If no value is found, return -1.

return -1;

Under the intended XOR-state range and a non-empty grid, at least
one valid path exists, so a reachable destination should have at
least one achievable XOR value.

--------------------------------------------------
9. Example Walkthrough
--------------------------------------------------

Consider:

grid = [
    [1, 2],
    [3, 4]
]

There are two possible paths from the top-left to the bottom-right.

Path 1: Right, then Down
-----------------------

Cells visited:
1 -> 2 -> 4

XOR:
1 ^ 2 ^ 4 = 7

Therefore, XOR value 7 is achievable at the destination.

Path 2: Down, then Right
------------------------

Cells visited:
1 -> 3 -> 4

XOR:
1 ^ 3 ^ 4 = 6

Therefore, XOR value 6 is also achievable at the destination.

The destination bitset contains both 6 and 7 as achievable values.

Scanning in increasing order finds 6 first.

Output: 6

--------------------------------------------------
10. Why the Algorithm Works
--------------------------------------------------

1. Initialization correctly records the XOR value at the starting cell.

2. Every valid path to a non-starting cell must arrive either from
   the cell above or from the cell to the left.

3. Combining both predecessor bitsets includes all achievable XOR
   values from either direction.

4. XORing each available state with the current cell's value
   correctly computes the XOR for paths entering that cell.

5. By processing cells in row-major order, predecessor states are
   available before they are needed.

6. At the destination, scanning XOR values in increasing order
   returns the minimum achievable value.

Therefore, the DP tracks all reachable XOR values and selects the
minimum at the destination.

--------------------------------------------------
11. Complexity Analysis
--------------------------------------------------

Let m be the number of rows and n be the number of columns.
Let B = 1024 be the number of tracked XOR states.

Time Complexity: O(m * n * B)

For each cell, the algorithm combines two bitsets and iterates
through all B possible XOR values.

Since B is fixed at 1024, this is effectively O(m * n) for the
given implementation.

Space Complexity: O(m * n * B)

Each grid cell stores a bitset of B bits.

With B fixed at 1024, the DP storage is effectively O(m * n).

Core Idea:
----------
For every cell, use a bitset to record all XOR values achievable
through paths arriving from above or from the left. XOR each state
with the current cell's value, then return the smallest achievable
XOR value at the destination.
*/