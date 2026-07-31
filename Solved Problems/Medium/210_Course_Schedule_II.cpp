class Solution {
    private:
        vector<int> topologicalSort(int numCourses, unordered_map<int, vector<int>>& adj, vector<int>& indegree) {
            queue<int> q;
            vector<int> ans;
    
            // push which have indegree as 0
            for(int i = 0; i < numCourses; i++) {
                if(indegree[i] == 0) {
                    q.push(i);
                    ans.push_back(i);
                }
            }
    
            // keep popping and pushing indegree with 0 until queue is empty
            while(!q.empty()) {
                int u = q.front();
                q.pop();
    
                for(int& v: adj[u]) {
                    indegree[v]--;
                    if(indegree[v] == 0) {
                        q.push(v);
                        ans.push_back(v);
                    }
                }
            }
    
            // if ans.size() matches numCourses, that means we visited all nodes and no cycle exists
            if(ans.size() == numCourses) return ans;
            return {};
        }
    
    public:
        vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
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

The prerequisites form a

Directed Graph,

where an edge

a → b

means

"a must be completed before b."

Unlike LeetCode 207, where we only check whether all courses
can be finished,

here we must return

one valid order

in which the courses can be completed.

We use

Kahn's Algorithm (Topological Sort)

to construct this ordering.

------------------------------------------------------------

Key Observation:
----------------

A course can only be taken when all its prerequisites have
been completed.

The

indegree

of a node represents the number of prerequisites that are
still pending.

Initially,

every course having

indegree = 0

can be taken immediately.

As we complete a course,

its outgoing edges are removed, reducing the indegree of its
dependent courses.

Whenever another course reaches

indegree = 0,

it becomes available to take.

------------------------------------------------------------

Approach:
---------

1. Build the directed graph.

   prerequisite → course

2. Compute the indegree of every course.

3. Push every course with

indegree = 0

into the queue.

These are the courses that can be taken immediately.

4. Perform BFS (Topological Sort).

   - Remove a course from the queue.
   - Add it to the answer.
   - Reduce the indegree of all dependent courses.
   - If any course reaches indegree

     0,

     push it into the queue.

5. Continue until the queue becomes empty.

6. If the answer contains all courses,

   return the ordering.

   Otherwise,

   the graph contains a cycle, making it impossible to finish
   every course, so return an empty vector.

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

Answer

[0]

--------------------------------

Process

0

Indegree

1 : 0

2 : 0

Queue

1 2

Answer

[0,1,2]

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

Answer

[0,1,2,3]

A valid course ordering is

[0,1,2,3]

Another valid ordering could also be

[0,2,1,3]

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

so the queue is empty.

No ordering exists.

Return

{}.

------------------------------------------------------------

Why Does This Work?
-------------------

Kahn's Algorithm always processes courses whose
prerequisites have already been completed.

Each processed course is added to the final ordering.

Removing a course also removes all of its outgoing edges,
which may unlock additional courses.

If the graph has no cycle,

every course eventually reaches indegree

0

and appears exactly once in the answer.

If a cycle exists,

the courses inside the cycle always have at least one
remaining prerequisite,

so they never reach indegree

0.

Thus,

the answer contains fewer than

numCourses

elements, indicating that no valid ordering exists.

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

Answer Vector

O(V)

Overall Space Complexity

O(V + E)

*/