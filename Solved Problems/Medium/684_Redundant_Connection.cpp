class Solution {
    private:
        bool dfs(unordered_map<int, vector<int>>& adj, unordered_set<int>& visited, int u, int v) {
            // if u == v then we found a cycle
            if(u == v) return true;
    
            // makr current node, 'u' as visited
            visited.insert(u);
    
            // explore all nodes in adjacency and keep checkinf if they are already visited or not
            for(auto &x : adj[u]) {
                if(!visited.count(x) && dfs(adj, visited, x, v)) return true;
            }
    
            return false;
        }
    
    public:
        vector<int> findRedundantConnection(vector<vector<int>>& edges) {
            unordered_map<int, vector<int>> adj;
            for(auto &edge : edges) {
                int u = edge[0];
                int v = edge[1];
    
                unordered_set<int> visited;
    
                // check if u and v are already connected
                if(dfs(adj, visited, u, v)) return edge;
    
                // add edge to graph
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
    
            return {};
        }
    };

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