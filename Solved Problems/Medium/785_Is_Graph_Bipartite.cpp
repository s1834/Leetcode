class Solution {
    private:
        bool checkBipartiteDFS(vector<vector<int>>& graph, vector<int>& color, int currIndex, int currColor) {
            color[currIndex] = currColor; // assign currColor to current node
    
            // visit each connnected node at currIndex
            for(int &v: graph[currIndex]) {
                if(color[currIndex] == color[v]) return false; // if color is same of connected
                if(color[v] == -1) {
                    // send curr index and the opposite of currColor; 1 - currColor (0, 1)
                    if(!checkBipartiteDFS(graph, color, v, 1 - currColor)) return false;
                }
            }
            return true;
        }
    
    public:
        bool isBipartite(vector<vector<int>>& graph) {
            int n = graph.size(); // graph works as adj
            vector<int> color(n, -1); // assign all as color -1
            for(int i = 0; i < n; i++) {
                if(color[i] == -1) {
                    // check if any adjacent could have same color
                    if(!checkBipartiteDFS(graph, color, i, 1)) return false;
                }
            }
    
            return true;
        }
    };

/*

Idea:
------

A graph is bipartite if its vertices can be divided into two
groups such that no two adjacent vertices belong to the same
group.

Instead of explicitly creating two groups,

we assign one of two colors to every node.

If we can color the entire graph so that every edge connects
nodes of opposite colors,

the graph is bipartite.

Otherwise,

if two adjacent nodes ever receive the same color, the graph
is not bipartite.

We use DFS to perform this coloring.

------------------------------------------------------------

Key Observation:
----------------

Whenever we move from one node to one of its neighbors,

the neighbor must belong to the opposite partition.

Therefore,

if the current node has color

0,

its neighbors must have color

1,

and vice versa.

If a node is ever forced to take two different colors, the
graph cannot be bipartite.

------------------------------------------------------------

Approach:
---------

1. Create a color array initialized with

-1,

meaning every node is initially uncolored.

2. Traverse every node.

   Since the graph may have multiple disconnected
   components, start a DFS from every uncolored node.

3. During DFS,

   - Assign the current color to the node.
   - Visit all its neighbors.
   - If a neighbor already has the same color, return
     false.
   - Otherwise, recursively color the neighbor with the
     opposite color

     (1 - currentColor).

4. If every connected component can be colored successfully,

   return

   true.

------------------------------------------------------------

Example:
--------

Graph

0 ----- 1

|       |

|       |

3 ----- 2

Start DFS

Color(0) = 1

↓

Color(1) = 0

↓

Color(2) = 1

↓

Color(3) = 0

Every adjacent pair has opposite colors.

Answer = true.

------------------------------------------------------------

Non-Bipartite Example:
----------------------

Triangle

0

/ \

1---2

Start DFS

Color(0) = 1

↓

Color(1) = 0

↓

Color(2) = 1

Now,

2

is adjacent to

0,

but both have color

1.

Conflict occurs.

Answer = false.

------------------------------------------------------------

Visualization:
--------------

Color 1

● ----- ○

|       |

|       |

○ ----- ●

Every edge connects different colors.

--------------------------------

Conflict

●

/ \

○---●

Two adjacent nodes have the same color.

Graph is not bipartite.

------------------------------------------------------------

Why Does This Work?
-------------------

DFS explores one connected component at a time while
assigning alternating colors.

Every edge forces its endpoints to have opposite colors.

If this assignment succeeds for the entire graph,

we obtain two valid partitions.

If a conflict is encountered,

it means an odd-length cycle exists, making it impossible to
divide the graph into two independent sets.

Therefore,

the graph is bipartite if and only if no coloring conflict
occurs during DFS.

------------------------------------------------------------

Time Complexity:
----------------

Each node is visited once.

Each edge is examined once.

Overall Time Complexity

O(V + E)

where

V = number of vertices

E = number of edges.

------------------------------------------------------------

Space Complexity:
-----------------

Color Array

O(V)

Recursion Stack

Worst Case

O(V)

Overall Space Complexity

O(V)

*/