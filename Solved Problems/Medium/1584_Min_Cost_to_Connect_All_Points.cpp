class Solution {
    private:
        int primsAlgorithm(vector<vector<pair<int, int>>>& adj, int& v) {
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // node, weight
            pq.push({0, 0}); // put {weight, node} = {0, 0} to start pq
            vector<bool> inMST(v, false); // check if node is already visited
            int sum = 0;
    
            while(!pq.empty()) {
                auto p = pq.top();
                pq.pop();
    
                int weight = p.first;
                int node = p.second;
    
                if(inMST[node]) continue; // if already visited
                
                // mark visited
                inMST[node] = true;
                sum += weight;
    
                // visit all adjacent nodes of current node
                for(auto &v : adj[node]) {
                    int neighbor = v.first;
                    int neighborWeight = v.second;
                    
                    // if not visited, push in pq
                    if(!inMST[neighbor]) pq.push({neighborWeight, neighbor});
                }
            }
            
            return sum;
        }
    
    public:
        int minCostConnectPoints(vector<vector<int>>& points) {
            int v = points.size();
            vector<vector<pair<int, int>>> adj(v); // i -> j, weight
            for(int i = 0; i < v; i++) {
                for(int j = i + 1; j < v; j++) {
                    int x1 = points[i][0];
                    int y1 = points[i][1];
    
                    int x2 = points[j][0];
                    int y2 = points[j][1];
    
                    int dist = abs(x1 - x2) + abs(y1 - y2); // manhattan distance 
    
                    adj[i].push_back({j, dist});
                    adj[j].push_back({i, dist});
                }
            }
            
            return primsAlgorithm(adj, v);
        }
    };

/*
LeetCode 1584. Min Cost to Connect All Points

Idea:
------

Treat every point as a node in a graph.

The cost of connecting two points is their Manhattan distance:

    |x1 - x2| + |y1 - y2|

Since every pair of points can be connected, this forms a
complete weighted graph.

We need to connect all points with minimum total cost.

This is exactly the

Minimum Spanning Tree (MST)

problem.

Here we use

Prim's Algorithm

to construct the MST.

------------------------------------------------------------

Key Observation:
----------------

For every pair of points,

    i <-> j

is an edge whose weight is their Manhattan distance.

For example:

points = [[0,0], [2,2], [3,1]]

Edges:

0 <-> 1
cost = |0-2| + |0-2| = 4

0 <-> 2
cost = |0-3| + |0-1| = 4

1 <-> 2
cost = |2-3| + |2-1| = 2

So the graph becomes:

        4
   0 -------- 1
    \         /
     \4     /2
       \   /
         2

We need to select edges that:

1. Connect every point.
2. Do not create a cycle.
3. Have minimum possible total cost.

That is exactly an MST.

------------------------------------------------------------

Prim's Algorithm:
-----------------

Prim's Algorithm starts from any node and repeatedly chooses
the cheapest edge that connects a new node to the current MST.

In this code:

    pq.push({0, 0});

means:

    {edgeWeight, node}

We start from node 0 with cost 0.

Then:

1. Take the minimum-weight edge from the priority queue.
2. If the node is already part of the MST, skip it.
3. Otherwise, add the node to the MST.
4. Add the edge's weight to the total cost.
5. Push all edges from this node to unvisited neighbors.
6. Repeat until every node is included.

------------------------------------------------------------

Why Does the Priority Queue Store {weight, node}?
------------------------------------------------

The priority queue is a min-heap:

    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    >

Therefore, the pair with the smallest

    weight

comes first.

For example:

    {2, 3}
    {5, 1}
    {7, 4}

The queue gives:

    {2, 3}

first.

This allows Prim's Algorithm to always choose the cheapest
available edge.

------------------------------------------------------------

Example:
--------

Suppose we have:

    0 ----4---- 1
     \          /
      4        2
       \      /
          2

Start from node 0.

Initial:

    pq = {(0,0)}

Take node 0.

Add:

    cost = 0

Push its edges:

    {4,1}
    {4,2}

--------------------------------

Take:

    {4,1}

Node 1 is not in MST.

Add:

    cost = 4

Now explore node 1.

It has an edge to node 2 with cost 2.

Push:

    {2,2}

--------------------------------

Priority Queue:

    {2,2}
    {4,2}

The minimum is:

    {2,2}

Take node 2.

Add:

    cost = 4 + 2 = 6

Node 2 is now connected.

Final MST cost:

    6

------------------------------------------------------------

Why Do We Need inMST?
----------------------

The array

    inMST[node]

tells us whether a node has already been included in the
Minimum Spanning Tree.

For example:

    inMST[2] = true

means node 2 has already been connected.

This is important because the same node can appear multiple
times in the priority queue.

For example:

    {2,2}
    {4,2}
    {7,2}

When {2,2} is processed, node 2 enters the MST.

Later, when {4,2} is removed:

    if(inMST[node]) continue;

skips it because node 2 is already connected.

------------------------------------------------------------

Important Point:
----------------

The priority queue may contain multiple edges leading to the
same node.

We do NOT need to update or delete the old entries.

We simply ignore them when the node has already been added
to the MST.

This is a common implementation technique for Prim's
Algorithm.

------------------------------------------------------------

Building the Graph:
--------------------

This part:

    for(int i = 0; i < v; i++) {
        for(int j = i + 1; j < v; j++) {

calculates the distance between every pair of points.

For every pair:

    i <-> j

we calculate:

    abs(x1 - x2) + abs(y1 - y2)

and add:

    adj[i].push_back({j, dist});
    adj[j].push_back({i, dist});

because the graph is undirected.

------------------------------------------------------------

Why j = i + 1?
---------------

We only need to calculate each pair once.

For example, we need:

    0 - 1

but we don't need to separately calculate:

    1 - 0

because they have the same distance.

Therefore:

    j = i + 1

avoids duplicate calculations.

We still add both directions to the adjacency list because
the graph itself is undirected.

------------------------------------------------------------

Complete Graph:
---------------

Every point can be directly connected to every other point.

Therefore, with

V

points, the number of edges is:

    V * (V - 1) / 2

This is why the adjacency list can become large.

------------------------------------------------------------

Why Does Prim's Algorithm Work?
-------------------------------

At every step, Prim's Algorithm chooses the cheapest edge
that connects a new node to the existing MST.

This is guaranteed to be safe by the

Cut Property

of Minimum Spanning Trees:

For any cut separating the already-built MST from the
remaining nodes, the minimum-weight edge crossing that cut
can safely be included in an MST.

Prim's Algorithm repeatedly applies this idea until all nodes
are connected.

Therefore, the final set of edges has minimum possible total
cost.

------------------------------------------------------------

Visualization:
--------------

Suppose we have:

    A       B
    •-------•
     \     /
      \   /
       \ /
        • C

Prim's Algorithm can be viewed as:

Step 1:

    A

Current MST:

    {A}

--------------------------------

Step 2:

Choose cheapest edge from A.

    A ---- B

Current MST:

    {A, B}

--------------------------------

Step 3:

Choose cheapest edge connecting the MST to an outside node.

    A ---- B
            \
             C

Current MST:

    {A, B, C}

All points are now connected.

------------------------------------------------------------

Time Complexity:
----------------

Let

    V = number of points

Because every pair of points is connected,

the graph has

    E = O(V²)

edges.

Building the complete graph:

    O(V²)

Prim's Algorithm using a priority queue:

    O(E log E)

which becomes:

    O(V² log V)

Overall:

    O(V² log V)

------------------------------------------------------------

Space Complexity:
-----------------

The adjacency list stores every edge.

Since the graph is complete:

    O(V²)

The priority queue can also contain many edges:

    O(V²)

The inMST array:

    O(V)

Overall:

    O(V²)

------------------------------------------------------------

Important:
----------

Your solution is using the general Prim's Algorithm approach:

    Points
       ↓
    Complete Graph
       ↓
    Manhattan Distance = Edge Weight
       ↓
    Minimum Spanning Tree
       ↓
    Prim's Algorithm
       ↓
    Minimum Total Cost

The key transformation to recognize in this problem is:

"Connect all points with minimum total cost"

    ↓

"Find the Minimum Spanning Tree."

*/