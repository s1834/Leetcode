class Solution {
    public:
        int networkDelayTime(vector<vector<int>>& times, int n, int k) {
            // create adjacency list
            unordered_map<int, vector<pair<int, int>>> adj; // unordered_map<u, pair<v, weight>> adj;
            for(auto &x : times) {
                int u = x[0];
                int v = x[1];
                int w = x[2];
                adj[u].push_back({v, w});
            }
    
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // min heap {shortest distance, node}
            vector<int> result(n + 1, INT_MAX); // result[i] = shortest distance from source k to node i
            result[k] = 0;
            pq.push({0, k});
    
            while(!pq.empty()) {
                int dist = pq.top().first;
                int u = pq.top().second;
                pq.pop();
                
                // if a shorter path already exist, skip calculating agian
                if (dist > result[u]) continue;
                
                for(auto &node: adj[u]) {
                    int v = node.first;
                    int d = node.second;
                    
                    // If going through u gives a shorter path to v
                    if(d + dist < result[v]) {
                        result[v] = d + dist;
                        pq.push({result[v], v});
                    }
                }
            }
    
            // Find the maximum shortest distance
            int mx = INT_MIN;
            for (int i = 1; i <= n; i++) {
                if (result[i] == INT_MAX) return -1;
                mx = max(mx, result[i]);
            }
    
            return mx;
        }
    };

/*

Idea:
------

The graph represents a network where

• Nodes represent computers.

• Directed edges represent the time required for a signal to
  travel between two computers.

Starting from node

k,

we need to find the minimum time required for the signal to
reach every other node.

Since all edge weights are non-negative,

Dijkstra's Algorithm

is the optimal choice for finding the shortest distance from
one source to every other node.

Once the shortest distance to every node is known,

the answer is simply the

maximum

among those distances, because the signal is fully propagated
only after the last node receives it.

------------------------------------------------------------

Key Observation:
----------------

The signal travels independently along different paths.

For every node,

we only care about the

minimum

time required to reach it.

If a node can be reached through multiple paths,

the shortest one should always be chosen.

Dijkstra's Algorithm guarantees this for graphs with
non-negative edge weights.

------------------------------------------------------------

Approach:
---------

1. Build the adjacency list.

   Each edge

   u → v

   stores the transmission time (weight).

2. Initialize a distance array.

   distance[i]

   stores the shortest known time from the source

   k

   to node

   i.

   Initially,

   every distance is

   ∞,

   except

   distance[k] = 0.

3. Use a min-heap (priority queue).

   The node with the smallest current distance is always
   processed first.

4. While the priority queue is not empty,

   • Remove the node with the smallest distance.

   • Ignore it if a shorter path has already been found.

   • Relax all outgoing edges.

     If

     distance[u] + weight < distance[v],

     update the distance of

     v

     and push it into the priority queue.

5. After Dijkstra finishes,

   • If any node is still unreachable,

     return

     -1.

   • Otherwise,

     return the maximum value in the distance array.

------------------------------------------------------------

Example:
--------

n = 4

Source = 2

Edges

2 → 1 (1)

2 → 3 (1)

3 → 4 (1)

Graph

      1
   2 -----> 1
   |
   |1
   v
   3
   |
   |1
   v
   4

--------------------------------

Initial Distance

1 : ∞

2 : 0

3 : ∞

4 : ∞

--------------------------------

Process Node 2

Update

1 = 1

3 = 1

--------------------------------

Process Node 1

No updates.

--------------------------------

Process Node 3

Update

4 = 2

--------------------------------

Final Distances

1 : 1

2 : 0

3 : 1

4 : 2

Maximum Distance

2

Answer = 2

------------------------------------------------------------

Visualization:
--------------

Priority Queue

(0,2)

↓

Process

2

↓

Update

1

3

↓

Priority Queue

(1,1)

(1,3)

↓

Process

1

↓

No changes

↓

Process

3

↓

Update

4

↓

Priority Queue

(2,4)

↓

Process

4

Finished.

------------------------------------------------------------

Why Skip Outdated Entries?
---------------------------

Suppose the priority queue contains

(10,5)

Later,

a shorter path is found,

and

(6,5)

is pushed.

Eventually,

both entries remain inside the priority queue.

When

(10,5)

is removed,

it no longer represents the shortest distance.

Therefore,

we skip it using

if(dist > result[u]) continue;

This avoids unnecessary edge relaxations and keeps Dijkstra
efficient.

------------------------------------------------------------

Why Does This Work?
-------------------

Dijkstra's Algorithm always processes the node with the
smallest currently known distance.

Since all edge weights are non-negative,

once a node is processed with its minimum distance,

that distance can never be improved.

By repeatedly relaxing outgoing edges,

the algorithm eventually computes the shortest distance from
the source to every reachable node.

The signal reaches all nodes only after the farthest node
receives it,

so taking the maximum shortest distance gives the total time
required for the entire network.

If any node remains unreachable,

the signal can never reach every node,

so the answer is

-1.

------------------------------------------------------------

Time Complexity:
----------------

Building the graph

O(E)

Dijkstra's Algorithm

Each edge may generate one priority queue insertion.

Overall Time Complexity

O((V + E) log V)

where

V = number of nodes

E = number of edges.

------------------------------------------------------------

Space Complexity:
-----------------

Adjacency List

O(E)

Distance Array

O(V)

Priority Queue

O(V)

Overall Space Complexity

O(V + E)

*/