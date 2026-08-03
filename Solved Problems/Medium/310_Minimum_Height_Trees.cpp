class Solution {
    private:
        vector<int> topologicalSort(int n, unordered_map<int, vector<int>>& adj, vector<int>& indegree) {
            queue<int> q;
            
            for(int i = 0; i < n; i++) if(indegree[i] == 1) q.push(i); // if indegree 1, push in queue (leaf node)
    
            while(n > 2) {
                int size = q.size();
                n -= size;
                
                while(size--) {
                    int u = q.front();
                    q.pop();
    
                    for(auto &v : adj[u]) {
                        indegree[v]--;
                        if(indegree[v] == 1) q.push(v);
                    }
                }
            }
    
            vector<int> ans;
            while(!q.empty()) {
                ans.push_back(q.front());
                q.pop();
            }
    
            return ans;
        }
    
    public:
        vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
            if (n == 1) return {0}; // n = 1; edges = []
    
            // create adjacency list of undirected graph
            unordered_map<int, vector<int>> adj;
            vector<int> indegree(n, 0);
            for(auto &edge : edges) {
                int u = edge[0];
                int v = edge[1];
    
                indegree[u]++;
                indegree[v]++;
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
    
            return topologicalSort(n, adj, indegree); // perfrom topological sort until 1 or 2 are left
        }
    };


/*

Idea:
------

For a tree,

the root that produces the minimum height is always located
at the

center

of the tree.

Instead of trying every node as the root,

we repeatedly remove all leaf nodes.

As the outer layers are peeled away,

the tree gradually shrinks until only its center(s) remain.

Those remaining node(s) are the roots of all Minimum Height
Trees.

This process is very similar to Kahn's Algorithm (Topological
Sort), except instead of removing nodes with indegree

0,

we repeatedly remove nodes with indegree

1

(the leaf nodes).

------------------------------------------------------------

Key Observation:
----------------

Leaf nodes can never be the center of a tree because they
are the farthest nodes from most other vertices.

If we remove every leaf simultaneously,

the height of every possible rooted tree decreases by one.

Repeating this process eventually leaves only

1

or

2

nodes.

These remaining nodes are called the

centroids

of the tree and always produce the minimum possible height.

------------------------------------------------------------

Approach:
---------

1. Build the adjacency list of the tree.

2. Compute the degree (indegree) of every node.

   Since this is an undirected graph,

   indegree simply represents the number of neighbors.

3. Push every node having

degree = 1

into the queue.

These are the current leaf nodes.

4. While more than

2

nodes remain,

   • Remove all current leaves.

   • Decrease the degree of all their neighbors.

   • Whenever a neighbor becomes a leaf
     (degree becomes

     1),

     push it into the queue.

5. After all outer layers are removed,

   the remaining

1

or

2

nodes are the centroids.

Return them as the answer.

------------------------------------------------------------

Example:
--------

Tree

      3
    / | \
   0  1  2
        |
        4

--------------------------------

Initial Leaves

0

1

4

Queue

0 1 4

--------------------------------

Remove Them

Remaining Tree

3

|

2

Now

2

becomes a leaf.

Queue

2

--------------------------------

Remove

2

Remaining Node

3

Only one node remains.

Answer

[3]

------------------------------------------------------------

Example 2:
----------

Tree

0 — 1 — 2 — 3

Initial Leaves

0

3

↓

Remove

↓

1 — 2

Two nodes remain.

Answer

[1,2]

A tree may have either

one

or

two

centroids.

------------------------------------------------------------

Visualization:
--------------

Initial Tree

        3
      / | \
     0  1  2
           |
           4

--------------------------------

Remove Outer Layer

        3
        |
        2

--------------------------------

Remove Again

3

Center Found

------------------------------------------------------------

Why Does This Work?
-------------------

Every iteration removes the nodes that are farthest from the
center.

Since all leaves are removed simultaneously,

the relative structure of the remaining tree is preserved.

Eventually,

only the innermost node(s) remain.

These nodes have the smallest maximum distance to every
other node,

which means they produce the minimum possible tree height
when chosen as the root.

Therefore,

repeatedly trimming leaves always converges to the centroid(s)
of the tree.

------------------------------------------------------------

Relation to Kahn's Algorithm:
-----------------------------

This algorithm is essentially a variation of

Topological Sort.

Standard Kahn's Algorithm

↓

Starts with nodes having

indegree = 0

(DAG).

--------------------------------

Minimum Height Trees

↓

Starts with nodes having

degree = 1

(leaf nodes in a tree).

Instead of removing sources,

we repeatedly remove leaves until only the center remains.

------------------------------------------------------------

Time Complexity:
----------------

Building the graph

O(V)

Each edge is processed exactly once while removing leaves.

Overall Time Complexity

O(V)

where

V = number of nodes.

(Since a tree has

V - 1

edges.)

------------------------------------------------------------

Space Complexity:
-----------------

Adjacency List

O(V)

Degree Array

O(V)

Queue

O(V)

Overall Space Complexity

O(V)

*/