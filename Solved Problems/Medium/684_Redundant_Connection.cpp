// Version 1: DFS
// class Solution {
// private:
//     bool dfs(unordered_map<int, vector<int>>& adj, unordered_set<int>& visited, int u, int v) {
//         // if u == v then we found a cycle
//         if(u == v) return true;

//         // make current node, 'u' as visited
//         visited.insert(u);

//         // explore all nodes in adjacency and keep checking if they are already visited or not
//         for(auto &x : adj[u]) {
//             if(!visited.count(x) && dfs(adj, visited, x, v)) return true;
//         }

//         return false;
//     }

// public:
//     vector<int> findRedundantConnection(vector<vector<int>>& edges) {
//         unordered_map<int, vector<int>> adj;
//         for(auto &edge : edges) {
//             int u = edge[0];
//             int v = edge[1];

//             unordered_set<int> visited;

//             // check if u and v are already connected
//             if(dfs(adj, visited, u, v)) return edge;

//             // add edge to graph
//             adj[u].push_back(v);
//             adj[v].push_back(u);
//         }

//         return {};
//     }
// };

/*

Idea:
------

A tree with

n

nodes always contains exactly

n - 1

edges and has

no cycles.

The given graph starts as a tree and then one extra edge is
added.

Therefore,

there will be exactly

one

edge whose addition creates a cycle.

Our goal is to identify that edge.

Instead of building the entire graph first,

we process the edges one by one.

Before adding a new edge

(u, v),

we check whether

u

and

v

are already connected.

If they are,

adding this edge would create a cycle, making it the
redundant connection.

------------------------------------------------------------

Key Observation:
----------------

Suppose we are about to add an edge

u —— v

If a path already exists between

u

and

v,

then connecting them again creates another path between the
same two nodes.

This forms a cycle.

Therefore,

before inserting every edge,

we simply check whether

u

can already reach

v

using DFS.

------------------------------------------------------------

Approach:
---------

1. Start with an empty graph.

2. Process every edge one by one.

3. Before inserting an edge

(u, v),

perform DFS from

u

to check whether

v

is already reachable.

4. If DFS reaches

v,

then

u

and

v

are already connected.

Adding the current edge would create a cycle, so return this
edge.

5. Otherwise,

insert the edge into the graph and continue.

------------------------------------------------------------

DFS Logic:
----------

DFS checks whether there already exists a path between two
nodes.

Base Case

If

u == v,

we have reached the destination.

Return

true.

Otherwise,

visit all unvisited neighbors recursively.

If any recursive call reaches

v,

return

true.

Otherwise,

return

false.

------------------------------------------------------------

Example:
--------

Edges

[1,2]

[1,3]

[2,3]

--------------------------------

Insert

1 — 2

Graph

1 —— 2

--------------------------------

Insert

1 — 3

Graph

    3
    |
1 —— 2

--------------------------------

Before inserting

2 — 3

Run DFS

2 → 1 → 3

A path already exists.

Adding

2 — 3

creates

2

/ \

1---3

Cycle formed.

Answer

[2,3]

------------------------------------------------------------

Visualization:
--------------

Current Graph

1

/ \

2   3

--------------------------------

New Edge

2 —— 3

DFS

2

↓

1

↓

3

Path Found

↓

Adding the new edge forms a cycle.

------------------------------------------------------------

Why Does This Work?
-------------------

Before adding an edge,

the graph is guaranteed to be acyclic because we only insert
edges that do not create a cycle.

If DFS finds an existing path between the two endpoints,

then they are already connected.

Adding another edge between them creates two distinct paths
between the same nodes,

which is exactly the definition of a cycle in an undirected
graph.

Hence,

the first edge whose endpoints are already connected is the
redundant edge.

------------------------------------------------------------

Time Complexity:
----------------

Let

N

be the number of nodes.

For each edge,

DFS may visit every node and edge already inserted.

Worst Case

O(N)

per DFS.

Since DFS is performed for every edge,

Overall Time Complexity

O(N²)

------------------------------------------------------------

Space Complexity:
-----------------

Adjacency List

O(N)

Visited Set

O(N)

Recursion Stack

O(N)

Overall Space Complexity

O(N)

------------------------------------------------------------

Note:
-----

This solution detects the redundant edge by repeatedly
checking connectivity using DFS.

A more optimal solution uses the

Disjoint Set Union (Union-Find)

data structure, which detects cycles in nearly constant time
per edge, achieving an overall complexity of

O(N · α(N)).

*/





// Version 2: Disjoint Set Union (DSU)
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
    public:
        vector<int> findRedundantConnection(vector<vector<int>>& edges) {
            DSU dsu(edges.size());
    
            for(auto &edge : edges) {
                int u = edge[0];
                int v = edge[1];
    
                unordered_set<int> visited;
    
                // if both have same parent they are already connected
                if(dsu.find(u) == dsu.find(v)) return edge;
    
                // add edge between u and v
                dsu.Union(u, v);
            }
    
            return {};
        }
    };

/*

Idea:
------

A tree is an undirected graph that is

connected

and contains

no cycles.

The given graph starts as a tree and then exactly one extra
edge is added.

Therefore,

only one edge is responsible for creating a cycle.

Instead of repeatedly checking connectivity using DFS,

we use the

Disjoint Set Union (DSU)

data structure to efficiently maintain connected
components.

------------------------------------------------------------

Key Observation:
----------------

If two nodes already belong to the

same connected component,

then there already exists a path between them.

Adding another edge between these two nodes creates a cycle.

Therefore,

before connecting two nodes,

we simply check whether they already have the same parent.

If they do,

the current edge is the redundant connection.

------------------------------------------------------------

Approach:
---------

1. Initialize every node as its own parent.

   Initially, every node forms an independent set.

2. Process each edge one by one.

3. For every edge

   (u, v),

   find the representative (parent) of both nodes.

4. If both nodes already have the same parent,

   they are already connected.

   Adding the current edge creates a cycle, so return it.

5. Otherwise,

   merge their two sets using Union by Rank.

------------------------------------------------------------

DSU Operations:
---------------

1. Find(x)

Returns the representative (ultimate parent) of the set
containing

x.

Path Compression

is used so that every visited node directly points to the
ultimate parent, making future queries much faster.

--------------------------------

2. Union(x, y)

Connects the two sets containing

x

and

y.

Union by Rank

attaches the smaller tree under the larger one, keeping the
overall tree shallow.

------------------------------------------------------------

Example:
--------

Edges

[1,2]

[1,3]

[2,3]

--------------------------------

Initially

1   2   3

Each node is its own parent.

--------------------------------

Edge

1 — 2

Different parents

Merge

{1,2}

--------------------------------

Edge

1 — 3

Different parents

Merge

{1,2,3}

--------------------------------

Edge

2 — 3

find(2)

↓

1

find(3)

↓

1

Both have the same parent.

Adding this edge forms a cycle.

Answer

[2,3]

------------------------------------------------------------

Visualization:
--------------

Initially

1    2    3

--------------------------------

After Union(1,2)

    1
   /
  2

3

--------------------------------

After Union(1,3)

    1
   / \
  2   3

--------------------------------

Trying to connect

2 —— 3

Both already belong to the same component.

Cycle detected.

------------------------------------------------------------

Why Does This Work?
-------------------

DSU maintains the connected components of the graph as edges
are processed.

If two nodes belong to different components,

connecting them cannot create a cycle, so we safely merge
their components.

If they already belong to the same component,

there is already a path between them.

Adding another edge creates an additional path, forming a
cycle.

Hence,

the first edge whose endpoints already share the same parent
is the redundant connection.

------------------------------------------------------------

Optimization:
-------------

Path Compression

makes every visited node directly point to the ultimate
parent, reducing the height of the trees.

Union by Rank

always attaches the shorter tree under the taller one,
keeping the structure balanced.

Together,

these optimizations make each DSU operation nearly constant
time.

------------------------------------------------------------

Time Complexity:
----------------

Let

N

be the number of edges.

Each

Find

and

Union

operation takes

O(α(N))

where

α

is the inverse Ackermann function, which grows extremely
slowly and is practically constant.

Overall Time Complexity

O(N · α(N))

≈ O(N)

------------------------------------------------------------

Space Complexity:
-----------------

Parent Array

O(N)

Rank Array

O(N)

Overall Space Complexity

O(N)

*/