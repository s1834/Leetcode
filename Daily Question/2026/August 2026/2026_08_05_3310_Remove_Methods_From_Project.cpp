class Solution {
    public:
        vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
            vector<vector<int>> adj(n); // create adjacency list
            for(auto &x : invocations) {
                int u = x[0];
                int v = x[1];
                adj[u].push_back(v);
            }
    
            vector<bool> result(n, true);
            queue<int> q;
            q.push(k);
            result[k] = false;
    
            while(!q.empty()) {
                int u = q.front();
                q.pop();
    
                for(auto &v : adj[u]) {
                     if (result[v]) { 
                        result[v] = false;
                        q.push(v);
                    }
                }
            }
    
            // even if a single non-suspicious method calls a suspicious one, then we cant remot that entire set
            for (auto &x : invocations) {
                int u = x[0];
                int v = x[1];
    
                if (result[u] && !result[v]) {
                    vector<int> ans;
                    for (int i = 0; i < n; i++) ans.push_back(i);
                    return ans;
                }
            }
    
            // Otherwise, return all remaining (non-suspicious) methods
            vector<int> ans;
            for (int i = 0; i < n; i++) {
                if (result[i]) ans.push_back(i);
            }
    
            return ans;
        }
    };

/*

Idea:
------

The bug originates from method

k.

Every method that can be reached from

k

(directly or indirectly)

is also considered suspicious.

However,

we are allowed to remove this entire suspicious group only if

no method outside the group invokes any method inside the
group.

Therefore, the solution consists of two steps:

1. Find every suspicious method.

2. Check whether any non-suspicious method calls a suspicious
   one.

If such an invocation exists,

the suspicious methods cannot be isolated, so nothing can be
removed.

------------------------------------------------------------

Key Observation:
----------------

The invocation relationships form a

directed graph.

An edge

u → v

means

method

u

invokes method

v.

Starting from the buggy method

k,

every reachable node becomes suspicious.

This is simply a graph traversal problem.

After identifying the suspicious methods,

we only need to verify whether there exists an incoming edge
from outside the suspicious group.

If yes,

the group cannot be removed.

------------------------------------------------------------

Approach:
---------

Step 1

Build the directed graph using the invocation list.

Each node stores the methods it invokes.

------------------------------------------------------------

Step 2

Perform BFS starting from

k.

Every reachable method is marked as

suspicious.

The array

result[i]

stores

true

↓

method is currently considered safe.

false

↓

method is suspicious.

------------------------------------------------------------

Step 3

Traverse every invocation again.

For every edge

u → v

check whether

u

is safe

and

v

is suspicious.

If such an edge exists,

it means a method outside the suspicious group depends on a
method inside the group.

Therefore,

removing the suspicious methods would break the project.

Return all methods without removing anything.

------------------------------------------------------------

Step 4

If no such incoming edge exists,

remove every suspicious method and return only the remaining
safe methods.

------------------------------------------------------------

Example 1:
----------

n = 5

k = 0

Invocations

0 → 1

0 → 2

1 → 2

3 → 4

--------------------------------

Graph

0

/ \

1   2

|

2

3

|

4

--------------------------------

BFS from

0

Suspicious

{0,1,2}

Safe

{3,4}

--------------------------------

Check Incoming Edges

No safe method invokes

0

1

or

2.

Therefore,

remove the suspicious group.

Answer

[3,4]

------------------------------------------------------------

Example 2:
----------

Invocations

1 → 2

0 → 1

3 → 2

Buggy Method

1

--------------------------------

Suspicious Methods

{1,2}

--------------------------------

Safe Methods

{0,3}

--------------------------------

Edge

0 → 1

Safe

↓

Suspicious

Invalid.

Similarly,

3 → 2

also enters the suspicious group.

Since outside methods invoke suspicious methods,

the group cannot be removed.

Return every method.

------------------------------------------------------------

Visualization:
--------------

Buggy Method

k

↓

Reachable Methods

↓

Suspicious Group

+---------+

| 0 1 2 |

+---------+

      ↑

      |

Safe Method

3

If an edge enters the suspicious group,

the group cannot be isolated.

Otherwise,

the entire group can safely be removed.

------------------------------------------------------------

Why Does This Work?
-------------------

BFS correctly marks every method reachable from the buggy
method,

which matches the definition of suspicious methods.

Afterwards,

the only condition for removing the group is that

no external method invokes a suspicious one.

Checking every invocation verifies exactly this condition.

If an incoming edge from outside exists,

removing the suspicious group would leave another method
calling a deleted method,

which is not allowed.

Otherwise,

the suspicious group is completely isolated and can be
removed safely.

------------------------------------------------------------

Time Complexity:
----------------

Let

N = number of methods

M = number of invocations

Building the graph

O(M)

--------------------------------

BFS Traversal

O(N + M)

--------------------------------

Checking Incoming Edges

O(M)

--------------------------------

Overall Time Complexity

O(N + M)

------------------------------------------------------------

Space Complexity:
-----------------

Adjacency List

O(M)

Visited/Suspicious Array

O(N)

Queue

O(N)

Overall Space Complexity

O(N + M)

*/