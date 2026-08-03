class Solution {
    private:
        void dfs(unordered_map<string, vector<pair<string, double>>>& adj, unordered_set<string>& visited, double& div, double prod, string src, string dst) {
            if(visited.find(src) != visited.end()) return; // already visited
    
            visited.insert(src);
            if(src ==  dst) { // divisor (b) found
                div = prod; 
                return;
            }
    
            for(auto &x : adj[src]) {
                string v = x.first; // a
                double value = x.second; // b
                dfs(adj, visited, div, prod * value, v, dst); // prod * value = multiply the values of between nodes
            }
        }
    
    public:
        vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
            unordered_map<string, vector<pair<string, double>>> adj;
            int n = equations.size();
    
            // create adjacency list unordered_map<dividend, {divisor, dividend/divisor}>
            for(int i = 0; i < n; i++) {
                string u = equations[i][0]; // a
                string v = equations[i][1]; // b
                double value = values[i]; // a / b
    
                adj[u].push_back({v, value}); // a / b
                adj[v].push_back({u, 1.0 / value}); // b / a
            }
    
            vector<double> ans;
            for(auto &query : queries) {
                string src = query[0]; // a
                string dst = query[1]; // b
    
                double div = -1.0; // division
                double prod = 1.0; // current product of graph
                
                if(adj.find(src) != adj.end()) {
                    unordered_set<string> visited;
                    dfs(adj, visited, div, prod, src, dst);
                }
    
                ans.push_back(div);
            }
    
            return ans;
        }
    };

/*

Idea:
------

Each equation

a / b = value

can be viewed as a weighted edge in a graph.

For example,

a / b = 2

means

a → b

(weight = 2)

and

b → a

(weight = 1/2)

Every variable becomes a graph node.

To answer a query

a / c,

we simply need to find a path from

a

to

c.

The answer is obtained by multiplying the edge weights along
that path.

We use DFS to search for the destination while maintaining
the product of all edge weights traversed so far.

------------------------------------------------------------

Key Observation:
----------------

Division is transitive.

If

a / b = 2

and

b / c = 3

then

a / c

=

(a / b) × (b / c)

=

2 × 3

=

6

Therefore,

instead of performing mathematical manipulations,

we only need to find a path between two variables and
multiply the weights along that path.

------------------------------------------------------------

Approach:
---------

1. Build a weighted graph.

   For every equation

   a / b = value

   add

   a → b

   with weight

   value

   and

   b → a

   with weight

   1 / value.

2. For every query

   src / dst,

   perform DFS.

3. Maintain a running product

   prod,

   which stores the multiplication of all edge weights from
   the source to the current node.

4. If the destination is reached,

   store

   prod

   as the answer.

5. If no path exists,

   return

   -1.

------------------------------------------------------------

Graph Construction:
-------------------

Equation

a / b = 2

becomes

a --------2--------> b

b ------1/2-------> a

--------------------------------

Equation

b / c = 3

becomes

b --------3--------> c

c ------1/3-------> b

Final Graph

a --2--> b --3--> c

------------------------------------------------------------

DFS Traversal:
--------------

Suppose we want

a / c

Start

prod = 1

--------------------------------

Move

a → b

prod

=

1 × 2

=

2

--------------------------------

Move

b → c

prod

=

2 × 3

=

6

Destination reached.

Answer = 6

------------------------------------------------------------

Example:
--------

Equations

a / b = 2

b / c = 3

Queries

a / c

b / a

a / e

--------------------------------

Query

a / c

DFS

a

↓

b

↓

c

Product

1 × 2 × 3

=

6

Answer

6

--------------------------------

Query

b / a

DFS

b

↓

a

Product

1 × (1/2)

=

0.5

Answer

0.5

--------------------------------

Query

a / e

No path exists.

Answer

-1

------------------------------------------------------------

Visualization:
--------------

Weighted Graph

        2
a --------------> b
^                |
|                |
|1/2            |3
|                |
+------- c <-----+
        1/3

Query

a / c

↓

DFS Path

a → b → c

↓

Multiply

2 × 3

↓

6

------------------------------------------------------------

Why Does This Work?
-------------------

Each edge represents a valid division relationship.

Following a path through the graph corresponds to repeatedly
substituting one equation into another.

Since

(a / b)

×

(b / c)

=

a / c,

multiplying the edge weights along the path gives the correct
division result.

DFS explores every reachable variable while maintaining the
current product.

The visited set prevents revisiting variables and avoids
infinite recursion caused by cycles.

If the destination is reached,

the accumulated product is exactly the required answer.

------------------------------------------------------------

Time Complexity:
----------------

Let

V = number of variables

E = number of equations

Q = number of queries

Building the graph

O(E)

--------------------------------

Each DFS

Worst Case

O(V + E)

--------------------------------

For

Q

queries,

Overall Time Complexity

O(E + Q × (V + E))

------------------------------------------------------------

Space Complexity:
-----------------

Adjacency List

O(E)

Visited Set

O(V)

Recursion Stack

O(V)

Overall Space Complexity

O(V + E)

------------------------------------------------------------

Note:
-----

This solution performs an independent DFS for every query.

If the number of queries is very large,

another approach using

Weighted Union-Find (DSU)

can answer each query in nearly constant time after the graph
is built.

*/