class Solution {
    private:
        bool topologicalSort(int numCourses, unordered_map<int, vector<int>>& adj, vector<int>& indegree) {
            queue<int> q;
            int count = 0;
    
            // push which have indegree as 0
            for(int i = 0; i < numCourses; i++) {
                if(indegree[i] == 0) {
                    count++;
                    q.push(i);
                }
            }
            
            // keep popping and pushing indegree with 0 until queue is empty
            while(!q.empty()) {
                int u = q.front();
                q.pop();
    
                for(int &v : adj[u]) {
                    indegree[v]--;
                    if(indegree[v] == 0) {
                        count++;
                        q.push(v);
                    }
                }
            }
    
            // if count matches numCourses, that means we visited all nodes and no cycle exists
            if(count == numCourses) return true;
            return false;
        }
    
    public:
        bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
            unordered_map<int, vector<int>> adj;
            vector<int> indegree(numCourses, 0); // Kahn's Algorithm
    
            for(auto &x : prerequisites) {
                // x[1]---->x[0]
                adj[x[1]].push_back(x[0]);
                indegree[x[0]]++;
            }
    
            return topologicalSort(numCourses, adj, indegree);
        }
    };

/*

Idea:
------

Each prerequisite represents a dependency between courses.

If

a → b

means

"a must be completed before b",

then we can model the courses as a

Directed Graph.

The problem now becomes:

"Is it possible to visit every node without encountering a
cycle?"

A directed graph can have a valid ordering of all nodes only
if it contains

no cycles.

We use

Kahn's Algorithm (Topological Sort)

to detect whether a cycle exists.

------------------------------------------------------------

Key Observation:
----------------

A course can only be taken when all of its prerequisites
have already been completed.

The

indegree

of a node represents the number of prerequisites that are
still pending.

Initially,

all courses having

indegree = 0

can be taken immediately.

As we complete a course,

its outgoing edges are removed, reducing the indegree of its
dependent courses.

If every course eventually becomes available,

then all courses can be finished.

------------------------------------------------------------

Approach:
---------

1. Build a directed graph.

   prerequisite → course

2. Compute the indegree of every course.

3. Push every course having indegree

0

into the queue.

4. Perform BFS.

   - Remove one course from the queue.
   - Consider it completed.
   - Reduce the indegree of all dependent courses.
   - If any course's indegree becomes

     0,

     push it into the queue.

5. Count how many courses are processed.

6. If all courses are processed,

   return

   true.

   Otherwise,

   some courses are part of a cycle and can never reach
   indegree

   0.

------------------------------------------------------------

Example:
--------

numCourses = 4

Prerequisites

0 → 1

0 → 2

1 → 3

2 → 3

Graph

0

/ \

1   2

\ /

3

--------------------------------

Initial Indegree

0 : 0

1 : 1

2 : 1

3 : 2

Queue

0

--------------------------------

Process

0

Indegree becomes

1 : 0

2 : 0

Queue

1 2

--------------------------------

Process

1

Indegree of

3

becomes

1

--------------------------------

Process

2

Indegree of

3

becomes

0

Queue

3

--------------------------------

Process

3

Visited Courses = 4

Answer = true

------------------------------------------------------------

Cycle Example:
--------------

0 → 1

↑   ↓

3 ← 2

Initial Indegree

0 : 1

1 : 1

2 : 1

3 : 1

No node has indegree

0,

so the queue remains empty.

No course can be completed.

Answer = false.

------------------------------------------------------------

Why Does This Work?
-------------------

Kahn's Algorithm always processes courses whose
prerequisites have already been completed.

Whenever a course is completed,

its outgoing edges are removed,

which may unlock new courses whose indegree becomes

0.

If the graph contains no cycle,

this process eventually visits every course.

However,

if a cycle exists,

every node inside the cycle always has at least one pending
prerequisite.

Their indegree never becomes

0,

so they are never processed.

Therefore,

comparing the number of processed courses with the total
number of courses tells us whether a cycle exists.

------------------------------------------------------------

Time Complexity:
----------------

Building the graph

O(E)

Topological Sort

O(V + E)

Overall Time Complexity

O(V + E)

where

V = number of courses

E = number of prerequisite pairs.

------------------------------------------------------------

Space Complexity:
-----------------

Adjacency List

O(E)

Indegree Array

O(V)

Queue

O(V)

Overall Space Complexity

O(V + E)

*/