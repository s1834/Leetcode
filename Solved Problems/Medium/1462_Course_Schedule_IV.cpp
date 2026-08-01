class Solution {
    private:
        unordered_map<int, unordered_set<int>> topologicalSort(int numCourses, unordered_map<int, vector<int>>& adj, vector<int>& indegree) {
            queue<int> q;
    
            // push which have indegree as 0
            for(int i = 0; i < numCourses; i++) {
                if(indegree[i] == 0) q.push(i);
            }
    
            // keep popping and pushing indegree with 0 until queue is empty
            unordered_map<int, unordered_set<int>> mp;
            while(!q.empty()) {
                int u = q.front();
                q.pop();
    
                for(int &v: adj[u]) {
                    mp[v].insert(u); // insert u as a dependency/prerequisite in its adjacency list
    
                    for(auto &x : mp[u]) mp[v].insert(x); // insert prerequisites of u as a dependency/prerequisite in its adjacency list
    
                    indegree[v]--; // decrease in degeree of adjacency list nodes of u
                    if(indegree[v] == 0) q.push(v);  // push if indegree becomes 0
                }
            }
    
            return mp;
        }
    
    public:
        vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
            unordered_map<int, vector<int>> adj;
            vector<int> indegree(numCourses, 0); // Kahn's Algorithm
            
            for(auto &x : prerequisites) {
                // x[0]---->x[1]
                adj[x[0]].push_back(x[1]);
                indegree[x[1]]++;
            }
    
            unordered_map<int, unordered_set<int>> mp(topologicalSort(numCourses, adj, indegree));
    
            int q = queries.size();
            vector<bool> ans(q, false);
            for(int i = 0; i < q; i++) {
                // in queries[i] = [ui, vi]
                // check if mp[vi] contains ui as a prerequisite
                ans[i] = mp[queries[i][1]].contains(queries[i][0]);
            }
    
            return ans;  
        }
    };

/*

Idea:
------

The graph represents prerequisite relationships between
courses.

An edge

a → b

means

course

a

must be completed before course

b.

For each query

[u, v],

we need to determine whether

u

is a

direct or indirect

prerequisite of

v.

Instead of performing a DFS/BFS for every query,

we use

Kahn's Algorithm (Topological Sort)

to propagate prerequisite information while processing the
graph.

------------------------------------------------------------

Key Observation:
----------------

Suppose

u → v

If

u

is a prerequisite of

v,

then

every prerequisite of

u

is also automatically a prerequisite of

v.

For example,

0 → 1 → 2

Course

2

depends on

1.

Since

1

depends on

0,

course

2

also depends on

0.

Thus,

Prerequisites(2)

=

{1, 0}

This observation allows us to build the complete set of
prerequisites for every course while performing the
topological traversal.

------------------------------------------------------------

Approach:
---------

1. Build the directed graph.

   prerequisite → course

2. Compute the indegree of every course.

3. Push every course with

indegree = 0

into the queue.

4. Perform Kahn's Topological Sort.

   For every edge

   u → v

   • Insert

     u

     into the prerequisite set of

     v.

   • Insert every prerequisite of

     u

     into the prerequisite set of

     v.

     This propagates all indirect prerequisites.

   • Reduce the indegree of

     v.

   • If its indegree becomes

     0,

     push it into the queue.

5. After processing all courses,

   each course stores the complete set of its direct and
   indirect prerequisites.

6. Answer every query by simply checking whether

   u

   exists in the prerequisite set of

   v.

------------------------------------------------------------

Example:
--------

Courses

0 → 1

1 → 2

1 → 3

Graph

0

|

1

/ \

2   3

--------------------------------

Initially

Prerequisites

0 : {}

1 : {}

2 : {}

3 : {}

--------------------------------

Process

0

1 depends on 0

Prerequisites

1 : {0}

--------------------------------

Process

1

2 depends on

1

and everything required by

1.

Prerequisites

2 : {1,0}

Similarly,

3 : {1,0}

--------------------------------

Final Map

0 : {}

1 : {0}

2 : {1,0}

3 : {1,0}

Now every query can be answered in

O(1)

average time using the hash set.

------------------------------------------------------------

Visualization:
--------------

Graph

0

↓

1

↙ ↘

2   3

--------------------------------

Propagation

0

↓

1

↓

{0}

↓

2

↓

{1,0}

3

↓

{1,0}

Each node inherits all prerequisite information from its
parent before being processed.

------------------------------------------------------------

Why Does This Work?
-------------------

Kahn's Algorithm processes courses in topological order.

Therefore,

when a course

u

is processed,

its prerequisite set has already been completely computed.

When processing an edge

u → v,

we simply copy

u

and all of

u's

prerequisites into

v's

prerequisite set.

Since every prerequisite chain eventually flows through the
topological order,

every direct and indirect prerequisite is propagated exactly
once.

Thus,

after the traversal,

each course stores its complete prerequisite information,
allowing every query to be answered efficiently.

------------------------------------------------------------

Time Complexity:
----------------

Building the graph

O(E)

Topological Sort

For every edge,

we may copy prerequisite sets.

Worst Case

O(V² + E)

Answering Queries

O(Q)

Average

(O(1) lookup per query)

Overall Time Complexity

O(V² + E + Q)

------------------------------------------------------------

Space Complexity:
-----------------

Adjacency List

O(E)

Indegree Array

O(V)

Prerequisite Sets

Worst Case

O(V²)

Queue

O(V)

Overall Space Complexity

O(V² + E)

*/