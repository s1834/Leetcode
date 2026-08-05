class Solution {
    public:
        int minimumEffortPath(vector<vector<int>>& heights) {
            vector<vector<int>> directions{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; // all 4 directions
            int n = heights.size(), m = heights[0].size();
    
            vector<vector<int>> result(n, vector<int>(m, INT_MAX)); // stores the minimum effort so far
            priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq; // pq<dist, {x, y}>
            pq.push({0, {0, 0}}); // first column
            result[0][0] = 0;
    
            while(!pq.empty()) {
                int d = pq.top().first;
                int x = pq.top().second.first;
                int y = pq.top().second.second;
                pq.pop();
    
                // check all 4 directions
                for(auto dir : directions) {
                    int a = x + dir[0];
                    int b = y + dir[1];
    
                    if(a >= 0 && b >= 0 && a < n && b < m) {
                        int dist = max(d, abs(heights[x][y] - heights[a][b])); // take the max of abs difference of all heights in the path
                        if (dist < result[a][b]) { // if the max of the abs difference of entire path is less than current
                            result[a][b] = dist;
                            pq.push({dist, {a, b}});
                        }
                    }
                }
            }
    
            return result[n - 1][m - 1];
        }
    };

/*

Idea:
------

Unlike the standard shortest path problem,

the cost of a path is

not

the sum of all edge weights.

Instead,

the effort of a path is defined as the

maximum absolute height difference

between any two consecutive cells along that path.

Our goal is to find a path whose

maximum effort

is as small as possible.

This is a shortest path problem with a modified distance
definition, which can still be solved using

Dijkstra's Algorithm.

------------------------------------------------------------

Key Observation:
----------------

Suppose the current path has effort

d.

Moving to a neighboring cell introduces a new edge with
effort

abs(heightDifference).

The effort of the new path becomes

max(currentEffort, edgeEffort)

because the overall effort is determined by the

largest

height difference encountered anywhere along the path.

Unlike standard Dijkstra,

we do

not

add the edge weight.

Instead,

we propagate the maximum effort seen so far.

------------------------------------------------------------

Approach:
---------

1. Create a matrix

result,

where

result[i][j]

stores the minimum effort required to reach cell

(i,j).

Initially,

every value is

∞,

except

result[0][0] = 0.

2. Use a min-heap.

Each entry stores

{currentEffort, {row, col}}

3. Repeatedly remove the cell having the smallest current
effort.

4. Explore all four neighboring cells.

5. Compute the effort required to move to that neighbor.

Current Path Effort

↓

d

Current Edge Effort

↓

abs(heightDifference)

New Path Effort

↓

max(d, edgeEffort)

6. If this new effort is smaller than the previously stored
effort,

update the cell and push it into the priority queue.

7. After Dijkstra finishes,

the answer is the minimum effort required to reach the
bottom-right cell.

------------------------------------------------------------

Why Use max() Instead of Addition?
----------------------------------

Normal Dijkstra

Distance

=

Current Distance + Edge Weight

--------------------------------

This Problem

Effort

=

max(Current Effort,

Current Edge Difference)

because the path cost is determined only by the

largest

height difference along the entire path.

Example

Height Differences

2

5

1

4

Path Effort

=

max(2,5,1,4)

=

5

not

2 + 5 + 1 + 4

------------------------------------------------------------

Example:
--------

Heights

1  2  2

3  8  2

5  3  5

--------------------------------

Possible Path

1 → 2 → 2 → 2 → 5

Height Differences

1

0

0

3

Maximum Difference

3

--------------------------------

Another Path

1 → 3 → 5 → 3 → 5

Height Differences

2

2

2

2

Maximum Difference

2

Although this path is longer,

its maximum effort is smaller.

Answer

2

------------------------------------------------------------

Visualization:
--------------

Grid

1   2   2

3   8   2

5   3   5

--------------------------------

Path 1

1 → 2 → 2

        ↓

        2

        ↓

        5

Maximum Difference

3

--------------------------------

Path 2

1

↓

3

↓

5

→

3

→

5

Maximum Difference

2

Dijkstra correctly chooses the second path because it
minimizes the maximum edge difference.

------------------------------------------------------------

Why Does This Work?
-------------------

Dijkstra's Algorithm works whenever the path cost is
monotonic,

meaning extending a path can never decrease its cost.

Here,

moving to another cell changes the effort as

max(currentEffort, edgeDifference).

The effort can only stay the same or increase,

never decrease.

Therefore,

once a cell is removed from the priority queue with the
minimum effort,

its optimal effort has already been found.

This guarantees that the algorithm correctly computes the
minimum possible effort for every cell.

------------------------------------------------------------

Time Complexity:
----------------

There are

n × m

cells.

Each cell may be inserted into the priority queue multiple
times.

Each heap operation costs

log(n × m).

Overall Time Complexity

O((n × m) log(n × m))

------------------------------------------------------------

Space Complexity:
-----------------

Result Matrix

O(n × m)

Priority Queue

O(n × m)

Overall Space Complexity

O(n × m)

------------------------------------------------------------

Note:
-----

This problem is a variation of Dijkstra's Algorithm where
the path cost is

the maximum edge weight

instead of

the sum of edge weights.

The only modification from standard Dijkstra is replacing

distance + weight

with

max(currentDistance, weight).

*/