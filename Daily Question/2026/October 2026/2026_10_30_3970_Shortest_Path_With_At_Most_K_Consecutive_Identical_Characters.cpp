class Solution {
    private:
        typedef tuple<int, int, int> T; // tuple<distance, node, count>
    
    public:
        int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
            unordered_map<int, vector<vector<int>>> adj; // Adjacency list
    
            for(auto &edge : edges) {
                int u = edge[0];
                int v = edge[1];
                int w = edge[2];
                adj[u].push_back({v, w}); // u --> v with weight w
            }
    
            vector<vector<int>> result(n, vector<int>(k + 1, INT_MAX)); // Minimum distance for each (node, count) state
            priority_queue<T, vector<T>, greater<T>> pq; // min-heap
            result[0][1] = 0; // Start at node 0 with distance 0 and count 1
            pq.push({0, 0, 1});
    
            while(!pq.empty()) {
                auto [d, node, count] = pq.top();
                pq.pop();
                
                if(d > result[node][count]) continue;  // Skip if consecutive count exceeds k
    
                if(node == n - 1) return d; // Destination reached
    
                for (auto &vec : adj[node]) {
                    int adjNode = vec[0];
                    int wt = vec[1];
    
                    int newCount = (labels[adjNode] == labels[node] ? count + 1 : 1);
    
                    if(newCount > k) continue; // Skip if a shorter distance to this state has already been found
    
                    int newDist = d + wt;
                    if(newDist < result[adjNode][newCount]) {
                        result[adjNode][newCount] = newDist;
                        pq.push({newDist, adjNode, newCount});
                    }
                }
            }
    
            return -1;
        }
    };

/*
Problem: LeetCode 3970 - Shortest Path

Approach: Dijkstra's Algorithm + State-Based Dynamic Programming

Intuition:
----------
We need to find the minimum-cost path from node 0 to node n - 1,
while ensuring that the number of consecutive nodes having the
same label does not exceed k.

A normal Dijkstra algorithm stores only the minimum distance to
each node.

However, reaching the same node with different consecutive label
counts represents different states.

For example, we might reach node 3:
- With distance 10 and consecutive count 1.
- With distance 8 and consecutive count 2.

Both states must be maintained because their future transitions
may behave differently.

Therefore, instead of storing only the node, we use the state:

(node, count)

where count represents the number of consecutive nodes with the
same label along the current path, including the current node.

We then apply Dijkstra's algorithm over these expanded states.

--------------------------------------------------
1. Define the State Tuple
--------------------------------------------------

typedef tuple<int, int, int> T;

The tuple stores:

(distance, node, count)

- distance: Total cost to reach the current node.
- node: Current vertex.
- count: Number of consecutive nodes with the same label.

This tuple is used in the priority queue so that states are
processed in increasing order of distance.

--------------------------------------------------
2. Build the Adjacency List
--------------------------------------------------

unordered_map<int, vector<vector<int>>> adj;

The adjacency list stores the outgoing edges of every node.

Each edge contains:
- Destination node.
- Edge weight.

for(auto &edge : edges) {
    int u = edge[0];
    int v = edge[1];
    int w = edge[2];

    adj[u].push_back({v, w});
}

For every directed edge:

u -> v with weight w

store v and w in the adjacency list of u.

This allows us to efficiently explore all outgoing edges
from the current node.

--------------------------------------------------
3. Initialize the DP / Distance Table
--------------------------------------------------

vector<vector<int>> result(
    n, vector<int>(k + 1, INT_MAX)
);

result[node][count] represents the minimum distance required
to reach a particular node with a particular consecutive
label count.

The second dimension has size k + 1 because the valid count
ranges from 1 to k.

Initially, every state has distance INT_MAX, meaning that
it has not been reached yet.

Why do we need a 2D distance array?
-----------------------------------

Because reaching the same node with different consecutive
counts creates different future possibilities.

For example:

result[3][1] = 10
result[3][2] = 8

These are separate states and must not overwrite each other.

--------------------------------------------------
4. Initialize the Min-Heap
--------------------------------------------------

priority_queue<T, vector<T>, greater<T>> pq;

Create a min-heap that stores states in the order:

(distance, node, count)

The state with the smallest distance is processed first.

Initialize the starting state:

result[0][1] = 0;
pq.push({0, 0, 1});

We start at node 0 with:
- Distance = 0.
- Consecutive count = 1.

The initial count is 1 because the starting node itself
contributes to the consecutive label sequence.

--------------------------------------------------
5. Process States Using Dijkstra
--------------------------------------------------

while(!pq.empty()) {

    auto [d, node, count] = pq.top();
    pq.pop();

Extract the state having the minimum distance.

Here:
- d is the current shortest known distance.
- node is the current vertex.
- count is the current consecutive label count.

Skip Outdated States
--------------------

if(d > result[node][count]) continue;

A state may be inserted into the priority queue multiple times
when a better distance is discovered.

If the popped distance is greater than the currently recorded
minimum distance, this state is outdated and can be ignored.

This is the standard stale-entry optimization in Dijkstra's
algorithm.

--------------------------------------------------
6. Check Whether the Destination Is Reached
--------------------------------------------------

if(node == n - 1) return d;

Since the priority queue processes states in increasing order
of distance, the first valid state reaching the destination
has the minimum possible distance.

Therefore, return d immediately.

--------------------------------------------------
7. Explore All Outgoing Edges
--------------------------------------------------

for(auto &vec : adj[node]) {

    int adjNode = vec[0];
    int wt = vec[1];

For every outgoing edge, extract:
- adjNode: The neighboring vertex.
- wt: The edge weight.

Calculate the New Consecutive Count
-----------------------------------

int newCount =
    (labels[adjNode] == labels[node] ? count + 1 : 1);

This is the most important transition in the algorithm.

Compare the label of the neighboring node with the label
of the current node.

Case 1: Labels Are Equal
------------------------

If:

labels[adjNode] == labels[node]

Then the consecutive sequence continues, so increment count:

newCount = count + 1;

Case 2: Labels Are Different
----------------------------

Otherwise, the consecutive sequence is broken.

Start a new sequence with the neighboring node:

newCount = 1;

For example:

labels along the path:
a -> a -> a -> b -> b

Consecutive counts:
1 -> 2 -> 3 -> 1 -> 2

The count resets whenever the label changes.

--------------------------------------------------
8. Enforce the Constraint
--------------------------------------------------

if(newCount > k) continue;

If the new consecutive count exceeds k, this transition
violates the problem constraint.

Therefore, skip this edge and do not insert the resulting
state into the priority queue.

Only valid states are considered further.

--------------------------------------------------
9. Calculate and Relax the New Distance
--------------------------------------------------

int newDist = d + wt;

The new distance is the current distance plus the weight
of the traversed edge.

Now check whether this gives a better distance to the
neighboring state:

if(newDist < result[adjNode][newCount]) {

If the newly calculated distance is smaller, update the
distance table:

result[adjNode][newCount] = newDist;

Push the improved state into the priority queue:

pq.push({newDist, adjNode, newCount});

The state now represents reaching adjNode with consecutive
count newCount at distance newDist.

--------------------------------------------------
10. Handle an Unreachable Destination
--------------------------------------------------

return -1;

If the priority queue becomes empty without reaching node
n - 1, no valid path exists.

Return -1.

--------------------------------------------------
11. Example Walkthrough
--------------------------------------------------

Consider:

n = 4
labels = "aabb"
k = 2

Edges:
0 -> 1, weight 2
1 -> 2, weight 3
2 -> 3, weight 4

Starting state:
(node = 0, count = 1, distance = 0)

Transition: 0 -> 1
------------------

labels[0] = 'a'
labels[1] = 'a'

Labels match, so:

newCount = 1 + 1 = 2

Distance:
0 + 2 = 2

New state:
(node = 1, count = 2, distance = 2)

Transition: 1 -> 2
------------------

labels[1] = 'a'
labels[2] = 'b'

Labels differ, so:

newCount = 1

Distance:
2 + 3 = 5

New state:
(node = 2, count = 1, distance = 5)

Transition: 2 -> 3
------------------

labels[2] = 'b'
labels[3] = 'b'

Labels match, so:

newCount = 1 + 1 = 2

Distance:
5 + 4 = 9

We reach the destination with a valid consecutive count.

Output: 9

--------------------------------------------------
12. Why the Algorithm Works
--------------------------------------------------

1. State Representation:
   The pair (node, count) captures all information needed to
   determine whether the next transition is valid.

2. Correct Transitions:
   When the next node has the same label, the consecutive count
   increases. Otherwise, it resets to 1.

3. Constraint Enforcement:
   States with count greater than k are discarded, so every
   explored path satisfies the consecutive-label constraint.

4. Dijkstra's Greedy Property:
   Since edge weights are non-negative, Dijkstra processes states
   in non-decreasing order of their minimum possible distances.

5. Destination Optimality:
   The first valid destination state removed from the min-heap
   has the minimum distance among all valid paths.

Therefore, Dijkstra over the expanded state space finds the
shortest valid path.

--------------------------------------------------
13. Complexity Analysis
--------------------------------------------------

Let:
- n = Number of nodes.
- E = Number of directed edges.
- k = Maximum allowed consecutive count.

Number of States:
-----------------

Each node can have at most k possible consecutive-count states.

Total states = O(n * k)

Transitions:
------------

Each state can explore the outgoing edges of its node.

Total transitions = O(E * k)

Using a priority queue, each successful relaxation takes
logarithmic heap time.

Time Complexity:
O((n * k + E * k) * log(n * k))

Equivalent:
O(k * (n + E) * log(n * k))

Space Complexity:
O(n * k + E)

- O(n * k) for the distance table.
- O(n * k) for priority queue states in the usual complexity bound.
- O(E) for the adjacency list.

Core Idea:
----------
Use Dijkstra's algorithm with an expanded state (node, count).
Maintain the shortest distance for every node and consecutive-label
count, reset the count when the label changes, and discard states
that exceed k.
*/