class DSU {
    public:
        vector<int> parent;
        vector<int> rank;
    
        DSU(int n) {
            // resize to fit all nodes
            parent.resize(n + 1);
            rank.resize(n + 1);
    
            // initally assign each node as its parent and rank as 0
            for(int i = 1; i <= n; i++) {
                parent[i] = i;
                rank[i] = 0;
            }
        }
    
        int find(int x) {
            if(parent[x] == x) return x; // if parent has parent as itself
            return parent[x] = find(parent[x]); // else find the parent of parent and do path compression
        }
    
        void Union(int x, int y) {
            int xParent = find(x);
            int yParent = find(y);
    
            if(xParent == yParent) return; // if both have same parent, they belong to same set
    
            if(rank[xParent] > rank[yParent]) parent[yParent] = xParent; // if xParent has higher rank(more children), make it parent of y
            else if(rank[xParent] < rank[yParent]) parent[xParent] = yParent; // if yParent has higher rank(more children), make it parent of x
            else { // if both have equal rank(equal children), make anyone as parent and increase that parent rank
                parent[yParent] = xParent;
                rank[xParent]++;
            }
        }
    };
    
    class Solution {
    private:
        int Kruskal(int& n, vector<vector<int>>& edges, int skipEdge, int addEdge) {
            DSU dsu(n);
            int sum = 0, m = edges.size();
    
            // union the edge we want to add
            if(addEdge != -1) {
                dsu.Union(edges[addEdge][0], edges[addEdge][1]);
                sum += edges[addEdge][2];
            }
    
            for(int i = 0; i < m; i++) {
                if(i == skipEdge) continue; // if we need to skip this adge
                
                int u = edges[i][0];
                int v = edges[i][1];
                int weight = edges[i][2];
    
                int uParent = dsu.find(u);
                int vParent = dsu.find(v);
    
                if(uParent != vParent) {
                    dsu.Union(u, v);
                    sum += weight;
                }
            }
            
            // if parent not common / not a single graph
            for(int i = 0; i < n; i++) {
                if(dsu.find(i) != dsu.find(0)) return INT_MAX;
            }
    
            return sum;
        }
    
    public:
        vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
            int m = edges.size();
            for(int i = 0; i < m; i++) edges[i].push_back(i); // number each node edges[i] = [ai, bi, weighti, original index
            
            // custom comparator, compares weight
            auto lambda = [&](vector<int>& v1, vector<int>& v2) {
                return v1[2] < v2[2];
            };
            sort(edges.begin(), edges.end(), lambda);
    
            int mstWeight = Kruskal(n, edges, -1, -1);
            vector<int> critical; // paths which increase the mstWeight, if they are removed
            vector<int> pseudoCritical; // paths that keep the mstWeight same, if they are added
            
            for(int i = 0; i < m; i++) {
                if(Kruskal(n, edges, i, -1) > mstWeight) critical.push_back(edges[i][3]); // skip ith Edge
                else if(Kruskal(n, edges, -1, i) == mstWeight) pseudoCritical.push_back(edges[i][3]); // add ith Edge
            }
    
            return {critical, pseudoCritical};
        }
    };

/*
LeetCode 1489. Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree

Idea:
------

This problem is based on the concept of a

Minimum Spanning Tree (MST).

We first find the minimum possible MST weight using

Kruskal's Algorithm.

Then, for every edge, we perform two experiments:

1. SKIP the edge
   → If the MST becomes more expensive (or impossible),
     the edge is CRITICAL.

2. FORCE the edge into the MST
   → If we can still construct an MST with the same minimum
     weight, the edge is PSEUDO-CRITICAL.

------------------------------------------------------------

Definitions:
------------

CRITICAL EDGE:

An edge is critical if removing it increases the MST weight.

In other words,

    MST without this edge > original MST

or the graph becomes disconnected.

This means the edge is necessary for every MST.

------------------------------------------------------------

PSEUDO-CRITICAL EDGE:

An edge is pseudo-critical if it can belong to an MST.

We force the edge into the MST first.

If the resulting MST still has the original minimum weight,

then the edge can be part of an MST.

It may not be present in every MST,

but it is present in at least one MST.

------------------------------------------------------------

Overall Approach:
-----------------

1. Add the original index to every edge.

2. Sort all edges by weight.

3. Find the weight of the normal MST.

4. For every edge:

       a. Skip the edge and calculate MST.

          If the new MST weight is greater than the original
          MST weight,

              → Critical Edge

       b. Force the edge into the MST and calculate MST.

          If the MST weight remains equal to the original
          MST weight,

              → Pseudo-Critical Edge

5. Return both lists using the original edge indices.

------------------------------------------------------------

Why Store the Original Index?
-----------------------------

Initially each edge is:

    [u, v, weight]

After:

    edges[i].push_back(i);

it becomes:

    [u, v, weight, originalIndex]

This is necessary because we sort the edges by weight.

After sorting,

the position of an edge in the vector is no longer its
original position.

For example:

Before sorting:

    edge 0
    edge 1
    edge 2

After sorting:

    edge 2
    edge 0
    edge 1

The problem asks us to return the

original indices,

so we store that index inside every edge.

------------------------------------------------------------

Why Sort Edges?
---------------

Kruskal's Algorithm always processes edges in increasing
order of weight.

For example:

    [0,1,1]
    [1,2,2]
    [2,3,3]
    [0,3,5]

Kruskal tries:

    weight 1
    weight 2
    weight 3
    weight 5

and only takes an edge if it connects two different
components.

------------------------------------------------------------

DSU:
----

The DSU (Disjoint Set Union) keeps track of which nodes
currently belong to the same connected component.

Initially:

    0
    1
    2
    3

Every node is its own component.

After:

    Union(0,1)

we have:

    {0,1}
    {2}
    {3}

After:

    Union(1,2)

we have:

    {0,1,2}
    {3}

This allows Kruskal to quickly determine whether adding an
edge would create a cycle.

------------------------------------------------------------

find():
--------

    int find(int x)

returns the representative (parent/root) of the component
containing x.

This line:

    parent[x] = find(parent[x]);

performs

PATH COMPRESSION.

It makes future find operations faster by directly connecting
x to the root of its component.

------------------------------------------------------------

Union():
--------

Before joining two nodes,

we find their component representatives:

    xParent = find(x)
    yParent = find(y)

If:

    xParent == yParent

then both nodes already belong to the same component.

Adding this edge would create a cycle,

so we skip it.

Otherwise,

we merge the two components.

Your implementation uses

UNION BY RANK

to keep the DSU tree shallow.

------------------------------------------------------------

Kruskal Function:
-----------------

Your helper:

    Kruskal(n, edges, skipEdge, addEdge)

is designed to calculate the MST under two possible
conditions:

    skipEdge

and

    addEdge

This allows the same function to be reused for both
critical-edge and pseudo-critical-edge testing.

------------------------------------------------------------

1. Forcing an Edge:
--------------------

If:

    addEdge != -1

you first add that edge:

    dsu.Union(edges[addEdge][0],
              edges[addEdge][1]);

and add its weight:

    sum += edges[addEdge][2];

This guarantees that the MST being constructed contains this
edge.

This is used for checking pseudo-critical edges.

------------------------------------------------------------

2. Skipping an Edge:
--------------------

Inside the main loop:

    if(i == skipEdge) continue;

means that this edge is completely ignored.

This is used to check whether the edge is critical.

------------------------------------------------------------

Normal Kruskal:
---------------

For every edge:

    u = edges[i][0]
    v = edges[i][1]

we find their parents.

If they belong to different components:

    dsu.Union(u, v);

and add the edge weight to the MST:

    sum += weight;

If they already have the same parent,

we skip the edge because it would create a cycle.

------------------------------------------------------------

Checking Whether an MST Exists:
--------------------------------

After processing all edges,

your code checks:

    for(int i = 0; i < n; i++) {
        if(dsu.find(i) != dsu.find(0))
            return INT_MAX;
    }

If every node has the same representative as node 0,

the graph is connected.

Otherwise,

some node is disconnected,

so a spanning tree cannot be formed.

Returning:

    INT_MAX

allows the caller to treat this as an MST that is more
expensive than the original MST.

------------------------------------------------------------

Finding the Original MST:
--------------------------

First:

    int mstWeight = Kruskal(n, edges, -1, -1);

Here:

    skipEdge = -1
    addEdge  = -1

so no edge is skipped or forced.

This calculates the normal MST.

Suppose:

    mstWeight = 10

This becomes the reference value for every edge.

------------------------------------------------------------

Testing Critical Edges:
------------------------

For edge i:

    Kruskal(n, edges, i, -1)

means:

    "Build the MST without edge i."

Suppose:

    Original MST = 10

and after removing edge i:

    MST = 14

Then:

    14 > 10

so edge i is critical.

Why?

Because removing it makes the best possible spanning tree
more expensive.

Therefore, that edge is necessary for every MST.

Your code:

    if(Kruskal(n, edges, i, -1) > mstWeight)
        critical.push_back(edges[i][3]);

------------------------------------------------------------

Example:

Suppose the MST is:

    0 --1-- 1 --2-- 2

Total:

    3

If we remove the edge with weight 1,

the cheapest alternative may cost:

    5

Therefore:

    5 > 3

so that edge is critical.

------------------------------------------------------------

Testing Pseudo-Critical Edges:
------------------------------

For edge i:

    Kruskal(n, edges, -1, i)

means:

    "Force edge i into the MST."

Suppose:

    Original MST = 10

and after forcing edge i:

    MST = 10

Then the edge can participate in an MST with the optimal
weight.

Therefore, it is pseudo-critical.

Your code:

    else if(Kruskal(n, edges, -1, i) == mstWeight)
        pseudoCritical.push_back(edges[i][3]);

------------------------------------------------------------

Example:

Suppose there are two edges with the same weight that can
connect the same components:

    A ----1---- B

and

    A ----1---- C

There may be multiple valid MSTs with the same total weight.

An edge does not need to be present in every MST to be useful.

If forcing the edge still gives the minimum MST weight,

it is pseudo-critical.

------------------------------------------------------------

Important Difference:
---------------------

Critical:

    Remove edge

        ↓

    MST becomes more expensive

        ↓

    CRITICAL

--------------------------------

Pseudo-Critical:

    Force edge

        ↓

    MST remains minimum

        ↓

    PSEUDO-CRITICAL

--------------------------------

An edge can conceptually be checked through both tests.

The critical test identifies edges that are mandatory.

The force test identifies edges that can participate in some
optimal MST.

------------------------------------------------------------

Why Does This Work?
-------------------

The original MST gives us the minimum possible spanning-tree
weight.

For every edge, we ask two questions:

Question 1:

    "Can I completely remove this edge and still obtain an
     MST with the same weight?"

If NO,

the edge is critical.

Question 2:

    "Can I force this edge into the MST without increasing
     the minimum weight?"

If YES,

the edge is pseudo-critical.

These two tests exactly match the definitions of critical and
pseudo-critical edges.

------------------------------------------------------------

Small Example:
--------------

Suppose:

    MST weight = 6

Edge A:

    Without A → MST weight = 8

Therefore:

    A is CRITICAL.

--------------------------------

Edge B:

    Force B → MST weight = 6

Therefore:

    B is PSEUDO-CRITICAL.

--------------------------------

Edge C:

    Without C → MST = 6
    Force C    → MST = 7

C is neither critical nor pseudo-critical.

------------------------------------------------------------

Why Use Kruskal Multiple Times?
--------------------------------

A straightforward way to classify each edge is to simply
rebuild the MST for that edge.

For every edge:

    1. Run Kruskal without it.
    2. Run Kruskal forcing it.

Since Kruskal is efficient with DSU,

this approach is simple and reliable.

The trade-off is that we run Kruskal many times.

------------------------------------------------------------

Time Complexity:
----------------

Let:

    E = number of edges
    V = number of vertices

Sorting:

    O(E log E)

Normal MST:

    O(E α(V))

For every edge,

we run Kruskal twice in the worst case:

    O(E × E α(V))

Therefore:

    O(E² α(V))

plus sorting.

Since

    α(V)

is the inverse Ackermann function and grows extremely slowly,

this is commonly treated as approximately:

    O(E²)

after sorting.

------------------------------------------------------------

Space Complexity:
-----------------

DSU:

    O(V)

Edges:

    O(E)

Overall auxiliary space:

    O(V + E)

------------------------------------------------------------

Main Pattern to Remember:
--------------------------

This problem is a very useful combination of:

    MST
      +
    Kruskal
      +
    DSU

The key classification trick is:

        Original MST
             |
       +-----+-----+
       |           |
       ↓           ↓
   Skip edge    Force edge
       |           |
       ↓           ↓
  MST becomes   MST remains
   expensive     minimum
       |           |
       ↓           ↓
   Critical    Pseudo-Critical

So whenever you see:

    "Find edges that are present in every MST"

think about

    removing the edge

and whenever you see:

    "Find edges that can belong to an MST"

think about

    forcing the edge.

*/