class Solution {
    private:
        void dfs(vector<vector<int>>& isConnected, vector<bool>& visited, int i) {
            visited[i] = true;
            for(int j = 0; j < isConnected.size(); j++) {
                if(isConnected[i][j] == 1 && !visited[j]) dfs(isConnected, visited, j);
            }
        }
    
    public:
        int findCircleNum(vector<vector<int>>& isConnected) {
            int n = isConnected.size(), provinces = 0;
            vector<bool> visited (n, false);
            
            for(int i = 0; i < n; i++) {
                if(!visited[i]) {
                    provinces++;
                    dfs(isConnected, visited, i);
                }
            }
    
            return provinces;
        }
    };

/*

Idea:
------
The cities form an

Undirected Graph,

where

• Every city is a node.

• An edge exists between two cities if

isConnected[i][j] == 1.

A

province

is simply a

Connected Component

in this graph.

Therefore,

the problem reduces to

"Count the number of connected components in an
undirected graph."

We solve this using

Depth First Search (DFS).

------------------------------------------------------------

Graph Representation:
---------------------

The input is given as an

Adjacency Matrix.

If

isConnected[i][j] == 1

then

City i

is directly connected to

City j.

Example

isConnected =

[
 [1,1,0],
 [1,1,0],
 [0,0,1]
]

Graph

      0 ------ 1

      2

There are

2

connected components,

so the answer is

2.

------------------------------------------------------------

Key Observation:
----------------

If two cities belong to the same province,

then there exists a path between them.

Starting a DFS from any city visits

every city

reachable from it.

Thus,

one DFS completely discovers

one entire province.

Whenever we find an unvisited city,

it must belong to a

new province.

------------------------------------------------------------

Visited Array:
--------------

visited[i]

indicates whether city

i

has already been explored.

Initially,

all cities are unvisited.

During DFS,

every reachable city is marked visited.

This prevents

• infinite recursion,

• revisiting cities,

• counting the same province multiple times.

------------------------------------------------------------

DFS State:
----------

The recursive function

dfs(isConnected, visited, i)

means

"Visit city

i

and recursively visit every city directly or indirectly
connected to it."

------------------------------------------------------------

DFS Algorithm:
--------------

Starting from city

i,

mark it as visited.

Then,

check every other city

j.

If

isConnected[i][j] == 1

and

city

j

has not been visited,

recursively perform DFS on

j.

Eventually,

every city in the same connected component gets visited.

------------------------------------------------------------

Main Algorithm:
---------------

Step 1

Create a

visited

array initialized to

false.

------------------------------------------------------------

Step 2

Iterate over every city.

------------------------------------------------------------

Step 3

If the current city has already been visited,

it already belongs to some previously discovered
province.

Skip it.

------------------------------------------------------------

Step 4

Otherwise,

this city starts a

new province.

Increment

provinces.

------------------------------------------------------------

Step 5

Run DFS from that city.

DFS marks every city in the same province as visited.

------------------------------------------------------------

Step 6

Continue scanning the remaining cities.

------------------------------------------------------------

Example:
--------

Input

[
 [1,1,0],
 [1,1,0],
 [0,0,1]
]

Initially

visited

=

[F, F, F]

--------------------------------

City

0

Not visited.

Province count

=

1

Run DFS.

Visited becomes

[T, T, F]

Cities

0

and

1

belong to the same province.

--------------------------------

City

1

Already visited.

Skip.

--------------------------------

City

2

Not visited.

Province count

=

2

Run DFS.

Visited becomes

[T, T, T]

Finished.

Answer

2

------------------------------------------------------------

Example:
--------

Input

[
 [1,0,0],
 [0,1,0],
 [0,0,1]
]

Graph

0

1

2

No city is connected to another.

DFS starts

three

times.

Answer

3

------------------------------------------------------------

Example:
--------

Input

[
 [1,1,1],
 [1,1,1],
 [1,1,1]
]

Graph

0

|\

| \

|  \

1---2

Everything is connected.

Only one DFS is required.

Answer

1

------------------------------------------------------------

Recursion Tree:
---------------

Suppose

0

is connected to

1

and

1

is connected to

2.

DFS

0

↓

1

↓

2

Every reachable city is visited before returning.

------------------------------------------------------------

Why Does This Work?
-------------------

Whenever DFS starts from an unvisited city,

it recursively visits

every city

reachable from it.

Since a province is defined as a maximal group of cities
connected by paths,

DFS completely explores exactly one province.

After DFS finishes,

every city belonging to that province has been marked as
visited.

Therefore,

future iterations never count that province again.

Each time we encounter another unvisited city,

it must belong to an entirely different connected
component,

so incrementing the province count is correct.

------------------------------------------------------------

Correctness Proof:
------------------

We prove that the algorithm returns the exact number of
provinces.

Consider any city that has not yet been visited.

Since none of the previously executed DFS traversals could
reach it,

it cannot belong to any previously discovered province.

Therefore,

it starts a new connected component,

and incrementing

provinces

is correct.

The subsequent DFS visits every city reachable from that
starting city.

Hence,

every city belonging to that connected component becomes
visited.

No city from another province is visited because there is
no path connecting different provinces.

Thus,

each province is counted exactly once,

and no province is missed.

Therefore,

the final value of

provinces

equals the number of connected components in the graph.

------------------------------------------------------------

Time Complexity:
----------------

Let

n

be the number of cities.

For every DFS call,

we scan the entire row of the adjacency matrix.

Since every city is visited exactly once,

every row is processed once.

Overall Time Complexity:

O(n²)

------------------------------------------------------------

Space Complexity:
-----------------

Visited Array

O(n)

--------------------------------

Recursion Stack

Worst case

O(n)

(for a completely connected chain of recursive calls)

Overall Auxiliary Space:

O(n)

------------------------------------------------------------

Note:
-----

This solution uses DFS.

The problem can also be solved using

• Breadth First Search (BFS)

or

• Disjoint Set Union (Union-Find / DSU),

both of which also count connected components.

*/