class Solution {
    public:
        int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
            int n = grid.size(); // size of n x n grid
            if(n == 0 || grid[0][0] != 0) return -1; // check if size == 0 and if starting position is 0 or not
            
    
            priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq; //pq<distance, <x, y>>
            vector<vector<int>> result(n, vector<int>(n, INT_MAX));
            pq.push({1, {0, 0}}); // push first coordinate
            result[0][0] = 1; // increase its size to 1;
    
            
            vector<vector<int>> directions{{1, 1}, {0, 1}, {1, 0}, {-1, 0}, {0, -1}, {-1, -1}, {1, -1}, {-1, 1}}; // all 8 directions
            while(!pq.empty()){
                int d = pq.top().first;
                int x = pq.top().second.first;
                int y = pq.top().second.second;
                pq.pop();
    
                // add all 8 directions
                for(auto dir : directions) {
                    int a = x + dir[0];
                    int b = y + dir[1];
                    
                    // if directions are in bound, current a,b is 0 and d + 1 < already stored result
                    if(a >= 0 && b >= 0 && a < n && b < n && grid[a][b] == 0 && d + 1 < result[a][b]) {
                        pq.push({d + 1, {a, b}});
                        result[a][b] = d + 1;
                    }
                }
            }
    
            if(result[n - 1][n - 1] == INT_MAX) return -1; // if path doesnt exist
            return result[n -1][n - 1];
        }
    };

/*

Idea:
------

We are given an

n × n

binary matrix where

0

represents an open cell and

1

represents a blocked cell.

We need to find the length of the

shortest clear path

from the top-left cell

(0,0)

to the bottom-right cell

(n-1,n-1),

moving in any of the

8 directions.

Since every move has the same cost (1 step),

this can be solved using a shortest path algorithm.

This solution uses

Dijkstra's Algorithm,

where every cell is treated as a graph node and every valid
move has weight

1.

------------------------------------------------------------

Key Observation:
----------------

Each empty cell

(0)

can move to at most

8

neighboring cells.

Therefore,

the grid can be viewed as an unweighted graph where

• Every empty cell is a node.

• Every valid move between neighboring cells is an edge of
  weight

  1.

Dijkstra's Algorithm computes the shortest distance from the
source cell to every reachable cell.

------------------------------------------------------------

Approach:
---------

1. If the starting cell

(0,0)

is blocked,

return

-1

because no path exists.

2. Create a distance matrix.

   result[i][j]

   stores the shortest distance from the source to cell

   (i,j).

   Initialize every cell to

   ∞,

   except

   result[0][0] = 1

   since the path includes the starting cell.

3. Use a min-heap.

   Each entry stores

   {distance, {row, col}}

4. Repeatedly remove the cell having the smallest current
   distance.

5. Explore all

8

possible directions.

6. If moving to a neighboring cell gives a shorter distance,

   update its distance and push it into the priority queue.

7. After the traversal,

   if the destination still has distance

   ∞,

   return

   -1.

   Otherwise,

   return its shortest distance.

------------------------------------------------------------

Eight Possible Moves:
---------------------

From any cell,

we may move to

↑

↓

←

→

↖

↗

↙

↘

This is represented using

directions

=

{

(1,1)

(0,1)

(1,0)

(-1,0)

(0,-1)

(-1,-1)

(1,-1)

(-1,1)

}

------------------------------------------------------------

Example:
--------

Grid

0 1 0

0 0 0

1 0 0

--------------------------------

Start

(0,0)

Distance = 1

↓

Possible Moves

↓

(1,0)

↓

(1,1)

↓

(2,2)

Destination reached.

Shortest Path Length

4

------------------------------------------------------------

Visualization:
--------------

Grid

S  X  .

| \

|  \

.---.

    |

    |

    E

S = Start

E = End

X = Blocked Cell

Dijkstra explores cells in increasing order of distance
until the destination receives its minimum distance.

------------------------------------------------------------

Why Update Only Shorter Paths?
------------------------------

Suppose a cell has already been reached with distance

5.

If another path reaches it with distance

7,

there is no reason to process the longer path.

Therefore,

we only update a neighbor when

currentDistance + 1

is smaller than the previously stored distance.

This guarantees that every cell always stores its shortest
known path from the source.

------------------------------------------------------------

Why Does This Work?
-------------------

Dijkstra's Algorithm always processes the cell with the
smallest currently known distance.

Whenever a neighboring cell can be reached with a shorter
path,

its distance is updated and it is added to the priority
queue.

Since all edge weights are non-negative,

once the shortest distance to a cell is finalized,

it can never be improved.

Eventually,

the destination either receives its shortest distance or
remains unreachable.

------------------------------------------------------------

Time Complexity:
----------------

There are

n²

cells.

Each cell may be inserted into the priority queue multiple
times, but every update performs a

log(n²)

heap operation.

Overall Time Complexity

O(n² log n)

------------------------------------------------------------

Space Complexity:
-----------------

Distance Matrix

O(n²)

Priority Queue

O(n²)

Overall Space Complexity

O(n²)

------------------------------------------------------------

Note:
-----

Since every move has the same cost

(1),

this problem can also be solved using

Breadth First Search (BFS),

which achieves

O(n²)

time complexity and is more optimal.

This implementation uses Dijkstra's Algorithm, which still
correctly computes the shortest path.

*/