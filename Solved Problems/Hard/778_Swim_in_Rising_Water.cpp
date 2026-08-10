class Solution {
    public:
        int swimInWater(vector<vector<int>>& grid) {
            vector<vector<int>> directions{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; // all 4 directions
            int n = grid.size();
    
            priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq; // pq<time, {x, y}>
            vector<vector<bool>> visited(n, vector<bool>(n, false));
            pq.push({grid[0][0], {0, 0}}); // first column
    
            while(!pq.empty()) {
                int time = pq.top().first;
                int x = pq.top().second.first;
                int y = pq.top().second.second;
                pq.pop();
    
                if (visited[x][y]) continue;
                visited[x][y] = true; // mark visited
    
                if(x == n - 1 && y == n - 1) return time; // reached (n - 1, n - 1)
    
                // visit all 4 directions
                for(auto &dir : directions) {
                    int a = x + dir[0];
                    int b = y + dir[1];
    
                    if(a >= 0 && b >= 0 && a < n && b < n && !visited[a][b]) pq.push({max(time, grid[a][b]), {a, b}}); // pq.push({maximum time to reach so far, {coordinates}})
                }   
            }
    
            return -1;
        }
    };

/*
LeetCode 778. Swim in Rising Water

Idea:
------

We are given an n x n grid where

    grid[i][j]

represents the elevation of that cell.

At time

    t,

we are allowed to enter any cell whose elevation is

    <= t.

We need to find the minimum time at which we can travel from

    (0, 0)

to

    (n - 1, n - 1).

This can be treated as a shortest path problem using
Dijkstra's Algorithm.

The important difference is that the cost of a path is NOT
the sum of the elevations.

Instead, the time required for a path is the

maximum elevation

of any cell along that path.

------------------------------------------------------------

Key Observation:
----------------

Suppose we have a path:

    A -> B -> C -> D

with elevations:

    1, 4, 2, 7

To travel through this path, the water must rise to at least

    max(1, 4, 2, 7) = 7

Therefore, the cost of the entire path is

    maximum elevation encountered on the path.

Our goal is to find a path whose maximum elevation is as
small as possible.

------------------------------------------------------------

Why Dijkstra?
-------------

In normal Dijkstra:

    newDistance =
        currentDistance + edgeWeight

Here, the path cost is the maximum elevation encountered.

Therefore:

    newTime =
        max(currentTime, grid[a][b])

So instead of adding the next cell's elevation,

we take the maximum of:

    • the time required to reach the current cell
    • the elevation of the next cell

This gives the minimum possible time required to reach that
neighbor through the current path.

------------------------------------------------------------

Approach:
---------

1. Start at

       (0, 0)

   The initial time is:

       grid[0][0]

   because the water must already be at least the elevation
   of the starting cell.

2. Use a min-heap containing:

       {time, {row, col}}

   where

       time

   is the minimum known time required to reach that cell.

3. Always process the cell with the smallest current time.

4. If the cell has already been processed,

       continue.

5. Mark the cell as visited.

6. If we reached

       (n - 1, n - 1),

   return the current time.

7. Explore all four neighboring cells.

8. For a neighbor:

       newTime =
           max(time, grid[a][b])

   because the water must be high enough for both the current
   path and the new cell.

9. Push the neighbor into the priority queue.

------------------------------------------------------------

Why Do We Use visited?
----------------------

The same cell can be pushed into the priority queue multiple
times with different possible times.

For example, a cell might be reachable with:

    time = 10

and later another path might reach it with:

    time = 7

Because the priority queue is a min-heap,

the smaller value will be processed first.

Once we remove a cell from the priority queue and mark it
visited,

we know that we have reached it with the minimum possible
time.

Any later entry for the same cell can therefore be ignored.

This is the same principle used in Dijkstra's Algorithm.

------------------------------------------------------------

Example:
--------

Consider:

    0  2
    1  3

Start:

    (0,0)

Elevation:

    0

So:

    time = 0

--------------------------------

Move to

    (1,0)

Elevation:

    1

New time:

    max(0,1) = 1

--------------------------------

Move to

    (1,1)

Elevation:

    3

New time:

    max(1,3) = 3

Destination reached.

Answer:

    3

------------------------------------------------------------

Another Example:
-----------------

Suppose:

    0  2  5
    1  3  6
    4  7  8

One possible path is:

    0 -> 2 -> 5 -> 6 -> 8

Its required time is:

    max(0,2,5,6,8)

    = 8

Another path may have a smaller maximum elevation.

The algorithm explores paths in increasing order of their
required time and therefore finds the minimum possible value.

------------------------------------------------------------

Visualization:
--------------

Suppose we have:

    0   2   3

    1   4   5

    2   3   7

The priority queue initially contains:

    {0, (0,0)}

Process:

    (0,0)

Possible neighbors:

    (1,0) -> max(0,1) = 1
    (0,1) -> max(0,2) = 2

Priority Queue:

    {1, (1,0)}
    {2, (0,1)}

The cell with the smaller required time is always processed
first.

This is exactly the idea behind Dijkstra.

------------------------------------------------------------

Why max(time, grid[a][b])?
--------------------------

This is the most important line:

    pq.push({
        max(time, grid[a][b]),
        {a, b}
    });

Suppose:

    time = 5

and the next cell has elevation:

    3

We only need the water to reach:

    max(5,3) = 5

because the water is already high enough for the new cell.

--------------------------------

Suppose:

    time = 5

and the next cell has elevation:

    8

Then we must wait until the water reaches:

    max(5,8) = 8

Therefore,

the maximum is exactly the amount of time required to reach
that cell through the current path.

------------------------------------------------------------

Why Can We Return Immediately?
------------------------------

This line:

    if(x == n - 1 && y == n - 1)
        return time;

is safe because the priority queue is a min-heap.

Therefore, cells are processed in increasing order of their
required time.

When the destination is removed from the priority queue for
the first time,

there cannot be another path reaching it with a smaller
required time.

So the current

    time

is the optimal answer.

------------------------------------------------------------

Difference From Normal Shortest Path:
--------------------------------------

Normal Dijkstra:

    path cost = sum of edge weights

Example:

    2 + 5 + 3 = 10

--------------------------------

This problem:

    path cost = maximum value along the path

Example:

    max(2,5,3) = 5

Therefore, the transition is:

    Normal Dijkstra:

        newDist = dist + weight

    This problem:

        newTime = max(time, grid[a][b])

This is the main modification needed to apply Dijkstra here.

------------------------------------------------------------

Why Does This Work?
-------------------

For every possible path,

the required time is determined by its highest cell.

Dijkstra always explores the path with the smallest current
required time first.

When moving to a new cell,

the required time can only stay the same or increase:

    max(currentTime, newElevation)

Therefore, once a cell is removed from the min-heap,

we have found the minimum possible time required to reach it.

Eventually,

the destination is removed from the heap.

The time associated with it is therefore the minimum possible
water level needed to reach the destination.

------------------------------------------------------------

Time Complexity:
----------------

There are

    n²

cells.

Each cell can be inserted into the priority queue, and each
heap operation costs:

    O(log(n²))

which is:

    O(log n)

Therefore:

    O(n² log n)

time complexity.

------------------------------------------------------------

Space Complexity:
-----------------

Visited array:

    O(n²)

Priority queue:

    O(n²)

Directions:

    O(1)

Overall:

    O(n²)

space complexity.

------------------------------------------------------------

Main Pattern to Remember:
--------------------------

When you see:

    "Find a path minimizing the maximum value encountered"

think:

    Dijkstra

but instead of:

    distance + edgeWeight

use:

    max(currentCost, nextCost)

For this problem:

    Cell
      ↓
    Grid elevation
      ↓
    Path cost = maximum elevation
      ↓
    Dijkstra
      ↓
    Minimum possible maximum
      ↓
    Minimum time to reach destination

*/