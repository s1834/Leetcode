class Solution {
    private:
        vector<int> topologicalSort(vector<vector<int>>& edges, int& k) {
            unordered_map<int, vector<int>> adj;
            vector<int> indegree(k + 1, 0);
    
            // create adjacency list and indegree
            for(auto &edge : edges) {
                int u = edge[0];
                int v = edge[1];
    
                adj[u].push_back(v); // u --> v
                indegree[v]++;
            }
    
            // push all in queue with indegree as 0
            queue<int> q;
            int count = 0;
            for(int i = 1; i <= k; i++) {
                if(indegree[i] == 0) {
                    q.push(i);
                    count++;
                }
            }
    
            // create topological order
            vector<int> topologicalOrder;
            while(!q.empty()) {
                int u = q.front();
                q.pop();
    
                topologicalOrder.push_back(u);
    
                for(int &v : adj[u]) {
                    indegree[v]--;
                    if(indegree[v] == 0) {
                        q.push(v);
                        count++;
                    }
                }
            }
    
            if(count != k) return {}; // if all nodes not visited return {}
            return topologicalOrder;
        }
    
    public:
        vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
            // do topological sort on both row and col conditions to find the desired order
            vector<int> topologicalRow = topologicalSort(rowConditions, k);
            vector<int> topologicalCol = topologicalSort(colConditions, k);
    
            // found cycle, answer not possible
            if(topologicalRow.empty() || topologicalCol.empty()) return {};
    
            vector<vector<int>> ans (k, vector<int>(k, 0));
            for(int i = 0; i < k; i++) {
                for(int j = 0; j < k; j++) {
                    if(topologicalRow[i] == topologicalCol[j]) ans[i][j] = topologicalRow[i]; // if both row and col index found push it in ans
                }
            }
    
            return ans;
        }
    };

/*
LeetCode 2392. Build a Matrix With Conditions

Idea:
------

We need to arrange the numbers

    1 ... k

inside a

    k x k

matrix.

There are two independent types of conditions:

1. rowConditions

   [a, b]

   means:

       a must appear above b

2. colConditions

   [a, b]

   means:

       a must appear to the left of b

The important observation is that the row and column
constraints are independent.

Therefore, we can solve them separately using

Topological Sort.

First find a valid ordering of all numbers for the rows.

Then find a valid ordering of all numbers for the columns.

Finally, place every number at the intersection of its row
position and column position.

------------------------------------------------------------

Key Observation:
----------------

For a condition

    [a, b]

we create a directed edge:

    a -> b

This means:

    a must come before b

A topological ordering gives us an ordering of all nodes such
that every directed edge goes from an earlier node to a later
node.

Therefore:

    rowConditions
          ↓
    Topological Sort
          ↓
    Valid Row Ordering

and

    colConditions
          ↓
    Topological Sort
          ↓
    Valid Column Ordering

------------------------------------------------------------

Example:
--------

Suppose

    k = 3

rowConditions:

    [1,2]
    [3,2]

This means:

    1 must be above 2
    3 must be above 2

A valid row ordering is:

    [1,3,2]

--------------------------------

Suppose column conditions are:

    [2,3]
    [1,3]

A valid column ordering is:

    [1,2,3]

Now each number has a row position and a column position:

    Number 1:
        row = 0
        col = 0

    Number 2:
        row = 2
        col = 1

    Number 3:
        row = 1
        col = 2

Therefore:

        col
       0  1  2

row 0  1  0  0

row 1  0  0  3

row 2  0  2  0

------------------------------------------------------------

Topological Sort:
-----------------

Your helper function performs

Kahn's Algorithm

for topological sorting.

The first step is to build:

    adj

where

    adj[u]

contains all nodes that must come after

    u.

For every condition:

    [u, v]

we add:

    u -> v

and increase:

    indegree[v]++

because v has one more prerequisite.

------------------------------------------------------------

Why Indegree?
-------------

The indegree of a node represents how many nodes must appear
before it.

For example:

    1 -> 3
    2 -> 3

Then:

    indegree[3] = 2

because both 1 and 2 must come before 3.

A node with

    indegree = 0

has no remaining prerequisites,

so it can safely be placed next in the topological ordering.

------------------------------------------------------------

Kahn's Algorithm:
-----------------

First push every node whose indegree is

    0

into the queue.

Then repeatedly:

    1. Remove a node from the queue.

    2. Add it to the topological ordering.

    3. Remove its outgoing edges.

    4. Decrease the indegree of its neighbors.

    5. If a neighbor's indegree becomes 0,
       push it into the queue.

This continues until the queue becomes empty.

------------------------------------------------------------

Cycle Detection:
----------------

A topological ordering exists only if the graph is acyclic.

Suppose we have:

    1 -> 2
    2 -> 3
    3 -> 1

Every node has an incoming edge.

Therefore,

there is no node with indegree 0,

and Kahn's Algorithm cannot process all nodes.

Your code keeps track of:

    count

which represents the number of nodes processed.

At the end:

    if(count != k) return {};

means:

    "We could not process all k nodes,
     therefore a cycle exists."

So there is no valid ordering.

------------------------------------------------------------

Why Perform Topological Sort Twice?
------------------------------------

The row and column constraints are separate graphs.

For example:

rowConditions:

    1 -> 2

only tells us:

    row(1) < row(2)

It says nothing about their columns.

Similarly,

colConditions:

    2 -> 3

only tells us:

    col(2) < col(3)

Therefore, we independently calculate:

    topologicalRow

and

    topologicalCol

These two orderings determine the final coordinates.

------------------------------------------------------------

Finding the Position:
----------------------

Suppose:

    topologicalRow = [3,1,2]

Then:

    3 -> row 0
    1 -> row 1
    2 -> row 2

Similarly, if:

    topologicalCol = [1,2,3]

then:

    1 -> col 0
    2 -> col 1
    3 -> col 2

Therefore:

    1 -> (1,0)
    2 -> (2,1)
    3 -> (0,2)

Each number is placed exactly once.

------------------------------------------------------------

Your Matrix Construction:
--------------------------

This part:

    for(int i = 0; i < k; i++) {
        for(int j = 0; j < k; j++) {

            if(topologicalRow[i] == topologicalCol[j])
                ans[i][j] = topologicalRow[i];

        }
    }

works by finding the same number in both orderings.

If

    topologicalRow[i] == topologicalCol[j]

then that number belongs at:

    row i
    column j

So:

    ans[i][j] = number

All other cells remain

    0.

------------------------------------------------------------

Example:
--------

Suppose:

    topologicalRow = [2,1,3]

    topologicalCol = [1,3,2]

Positions:

Number 1:

    row = 1
    col = 0

Number 2:

    row = 0
    col = 2

Number 3:

    row = 2
    col = 1

Matrix:

    0  0  2
    1  0  0
    0  3  0

------------------------------------------------------------

Why Does This Work?
-------------------

A topological ordering guarantees that every condition is
satisfied.

For row conditions:

    [a,b]

the row ordering guarantees:

    position(a) < position(b)

Therefore,

a appears above b.

For column conditions:

    [a,b]

the column ordering guarantees:

    position(a) < position(b)

Therefore,

a appears to the left of b.

Because each number gets exactly one row position and exactly
one column position,

we can combine the two independent orderings into a single
matrix.

If either graph contains a cycle,

there is no valid ordering for that dimension,

so constructing the matrix is impossible and we return:

    {}

------------------------------------------------------------

Important Pattern:
------------------

This problem is a very useful example of using

Topological Sort

for multiple independent constraints.

The pattern is:

    Conditions
        |
        +----------+
        |          |
        ↓          ↓
      Rows      Columns
        |          |
        ↓          ↓
     Topological Sort
        |          |
        ↓          ↓
    Row Order    Col Order
        \          /
         \        /
          ↓      ↓
        Position
          ↓
        Matrix

------------------------------------------------------------

Time Complexity:
----------------

Let

    E1 = number of row conditions
    E2 = number of column conditions

Topological sort for rows:

    O(k + E1)

Topological sort for columns:

    O(k + E2)

Constructing the matrix using your nested loops:

    O(k²)

Therefore:

    O(k + E1 + k + E2 + k²)

which simplifies to:

    O(k² + E1 + E2)

------------------------------------------------------------

Space Complexity:
-----------------

Row graph:

    O(k + E1)

Column graph:

    O(k + E2)

Queue:

    O(k)

Matrix:

    O(k²)

Overall:

    O(k² + E1 + E2)

The matrix itself already requires

    O(k²)

space.

------------------------------------------------------------

Main Concept to Remember:
--------------------------

When a problem gives separate ordering constraints like:

    "a must be above b"

and

    "a must be left of b"

think:

        Independent ordering problems

                ↓

        Topological Sort twice

                ↓

        Row ordering + Column ordering

                ↓

        Assign each number its
        (row, column)

                ↓

             Build Matrix

*/