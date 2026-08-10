class Solution {
    private:
        void dfs(unordered_map<int, vector<int>>& adj, vector<int>& path, int startNode) {
            while(!adj[startNode].empty()) {
                int newStartNode = adj[startNode].back();
                adj[startNode].pop_back(); // remove the node so we dont visit it twice in same path
    
                dfs(adj, path, newStartNode); // from newStartNode check if path exists again
            }
    
            path.push_back(startNode); // once all nodes exhasted push that in path
        }
    
    public:
        vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
            unordered_map<int, vector<int>> adj;
            unordered_map<int, int> indegree, outdegree;
            // create adjacency list, and keep track of indegree and out degree
            for(auto &pair: pairs) {
                int u = pair[0];
                int v = pair[1];
    
                adj[u].push_back(v); // u --> v
                indegree[v]++;
                outdegree[u]++;
            }
    
            // Find the start node of Euler Path
            int startNode = pairs[0][0];
            for(auto &x : adj) {
                if(outdegree[x.first] - indegree[x.first] == 1) {
                    startNode = x.first;
                    break;
                }
            }
    
            vector<int> path;
            dfs(adj, path, startNode);
            reverse(path.begin(), path.end()); // we recieve answers in reverse format
            
            // create pairs for answer
            int n = path.size();
            vector<vector<int>> ans;
            for(int i = 0; i < n - 1; i++) ans.push_back({path[i], path[i + 1]});
            
            return ans;
        }
    };

/*
LeetCode 2097. Valid Arrangement of Pairs

Idea:
------

Each pair

    [u, v]

can be treated as a directed edge:

    u ----> v

The problem asks us to arrange all pairs such that:

    pairs[i][1] == pairs[i + 1][0]

In graph terms, this means:

    We need to use every edge exactly once
    and form a continuous path.

This is exactly an

Eulerian Path

problem in a directed graph.

An Eulerian Path is a path that visits every edge exactly
once.

------------------------------------------------------------

Key Observation:
----------------

For every node, we keep track of:

    indegree  = number of edges entering the node
    outdegree = number of edges leaving the node

For a directed graph to have an Eulerian Path:

1. If there is a node whose

       outdegree = indegree + 1

   that node must be the starting node.

2. All other nodes must have equal

       indegree = outdegree

3. If there is no such starting node, we can start from any
   node having an outgoing edge.

Therefore, we first find the node satisfying:

    outdegree[node] - indegree[node] == 1

If no such node exists, we use the first pair's starting
node.

------------------------------------------------------------

Building the Graph:
--------------------

For every pair:

    [u, v]

we add:

    u -> v

to the adjacency list.

We also update:

    indegree[v]++
    outdegree[u]++

Example:

pairs =

    [[5,1], [4,5], [11,9], [9,4]]

Graph:

    11 -> 9 -> 4 -> 5 -> 1

The required answer is therefore:

    [11,9]
    [9,4]
    [4,5]
    [5,1]

------------------------------------------------------------

Finding the Start Node:
-----------------------

Suppose a node has:

    outdegree = 3
    indegree  = 2

Then there is one extra outgoing edge.

Therefore, the Eulerian path must start there.

This is why we check:

    if(outdegree[x.first] - indegree[x.first] == 1)

and use that node as

    startNode.

If every node has equal indegree and outdegree,

the graph has an Eulerian Circuit,

meaning we can start at any node with an outgoing edge.

Your code uses:

    pairs[0][0]

as the default starting node.

------------------------------------------------------------

The Important Part: DFS
-----------------------

The DFS is not a normal DFS where we simply visit every node.

We are trying to use

every edge exactly once.

That is why we remove every edge from the adjacency list
when we use it:

    int newStartNode = adj[startNode].back();

    adj[startNode].pop_back();

This means that edge has now been consumed and cannot be
used again.

------------------------------------------------------------

Why Do We Push the Node After DFS?
-----------------------------------

This is the most important idea in this solution.

We do NOT immediately add

    startNode

to the path.

Instead, we first exhaust all outgoing edges:

    while(!adj[startNode].empty()) {
        ...
        dfs(...)
    }

Only after all outgoing edges have been consumed do we do:

    path.push_back(startNode);

This produces the path in

reverse order.

------------------------------------------------------------

Example:
--------

Suppose the graph is:

    11 -> 9 -> 4 -> 5 -> 1

Start at

    11

DFS:

    11
     |
     v
     9
     |
     v
     4
     |
     v
     5
     |
     v
     1

Node 1 has no outgoing edges.

So:

    path.push_back(1)

Then return to 5:

    path = [1,5]

Then return to 4:

    path = [1,5,4]

Then:

    path = [1,5,4,9]

Finally:

    path = [1,5,4,9,11]

This is the reverse of the required path.

Therefore:

    reverse(path.begin(), path.end());

gives:

    [11,9,4,5,1]

------------------------------------------------------------

Why Is This Called Hierholzer's Algorithm?
-------------------------------------------

The DFS technique being used here is essentially

Hierholzer's Algorithm

for finding an Eulerian path.

The important idea is:

    Follow unused edges until you get stuck.

Then add the current node to the answer while returning
from recursion.

Because edges are removed as they are used,

every edge is processed exactly once.

------------------------------------------------------------

Why Can We Remove Edges Immediately?
-------------------------------------

Suppose:

    A -> B

is selected.

We immediately remove it:

    adj[A].pop_back();

This guarantees that the same edge cannot be selected again.

This is different from normal graph DFS where we usually
mark nodes as visited.

Here,

we need to visit a node multiple times if necessary.

For example:

    A -> B
    B -> A

We may visit A twice.

Therefore, the thing that must be marked as used is the

edge,

not the node.

------------------------------------------------------------

Important Difference:
---------------------

Normal DFS:

    visited[node]

Eulerian Path:

    used edge

This is why your code does not have a normal

visited

array.

Instead, it removes edges from the adjacency list.

------------------------------------------------------------

Example With a Branch:
----------------------

Consider:

    A -> B
    A -> C
    B -> A

We need to use all three edges.

One possible traversal:

    A -> C

C has no more outgoing edges,

so C is added to the answer.

Then return to A:

    A -> B

Then:

    B -> A

Finally A is added.

The nodes are initially collected in reverse order.

After reversing, we obtain:

    A -> B -> A -> C

which uses every edge exactly once.

------------------------------------------------------------

Why Does the Algorithm Work?
----------------------------

The graph satisfies the conditions for an Eulerian path.

Starting from the correct start node,

DFS continuously consumes unused edges.

Whenever a node still has unused outgoing edges,

we continue traversing.

When a node has no remaining outgoing edges,

it can safely be placed into the final path.

Because nodes are added while the recursion unwinds,

subpaths that need to be inserted into an already discovered
path are naturally placed in the correct position.

This is the key idea behind Hierholzer's Algorithm.

------------------------------------------------------------

Creating the Final Answer:
--------------------------

After DFS,

path

contains the sequence of nodes:

    [u0, u1, u2, ...]

After reversing it,

we have:

    u0 -> u1 -> u2 -> ...

The original problem wants pairs,

not just nodes.

Therefore we convert consecutive nodes into pairs:

    {path[i], path[i + 1]}

For example:

    path = [11, 9, 4, 5, 1]

becomes:

    [11,9]
    [9,4]
    [4,5]
    [5,1]

------------------------------------------------------------

Why Does path.size() = pairs.size() + 1?
-----------------------------------------

If we use

E

edges in a continuous path,

we need

E + 1

vertices.

For example:

    A -> B -> C -> D

has:

    3 edges

and:

    4 vertices

Therefore,

after using all pairs,

the path contains exactly

pairs.size() + 1

nodes.

------------------------------------------------------------

Time Complexity:
----------------

Let

E = number of pairs.

Every edge is:

    • added to the adjacency list once
    • removed from the adjacency list once
    • processed once

Therefore, the DFS takes:

    O(E)

Building the graph also takes:

    O(E)

Creating the final answer takes:

    O(E)

Overall:

    O(E)

------------------------------------------------------------

Space Complexity:
-----------------

Adjacency List:

    O(E)

Path:

    O(E)

Answer:

    O(E)

Recursion Stack:

    O(E)

Overall:

    O(E)

------------------------------------------------------------

Overall Flow:
-------------

Pairs

    ↓

Build Directed Graph

    ↓

Calculate indegree / outdegree

    ↓

Find Eulerian Path Start Node

    ↓

DFS / Hierholzer's Algorithm

    ↓

Consume every edge exactly once

    ↓

Add nodes while backtracking

    ↓

Reverse path

    ↓

Convert consecutive nodes back to pairs

    ↓

Valid Arrangement

------------------------------------------------------------

Main Concept to Remember:
--------------------------

The important pattern for this problem is:

    "Use every EDGE exactly once"

                    ↓

             Eulerian Path

                    ↓

        Hierholzer's Algorithm

                    ↓

    Remove edges during DFS

                    ↓

    Add nodes while backtracking

                    ↓

             Reverse result

*/