class Solution {
    private:
        void dfs(unordered_map<string, vector<string>>& adj, vector<string>& path, string startNode) {
            while(!adj[startNode].empty()) {
                string newStartNode = adj[startNode].back();
                adj[startNode].pop_back(); // remove the last node (newStartNode) so we dont visit it twice in same path
    
                dfs(adj, path, newStartNode); // from newStartNode check if path exists again
            }
    
            path.push_back(startNode); // once all nodes exhasted push startNode in path
        }
    
    public:
        vector<string> findItinerary(vector<vector<string>>& tickets) {
            // Reverse sort so smallest destination is at the back (read question)
            sort(tickets.rbegin(), tickets.rend());
            
            // create adjacency list
            unordered_map<string, vector<string>> adj;
            for(auto ticket : tickets) adj[ticket[0]].push_back(ticket[1]); // u --> v
            
    
            vector<string> path;
            dfs(adj, path, "JFK");
            reverse(path.begin(), path.end()); // we recieve answers in reverse format
    
            return path;
        }
    };

/*
LeetCode 332. Reconstruct Itinerary

Idea:
------

Each ticket

    [from, to]

can be treated as a directed edge:

    from -> to

We need to use

every ticket exactly once

and start from

    "JFK"

while producing the lexicographically smallest valid
itinerary.

This is exactly an

Eulerian Path

problem in a directed graph.

The important difference from normal DFS is that we must use
every

EDGE

exactly once.

------------------------------------------------------------

Key Observation:
----------------

If we simply perform a normal DFS and add a destination
immediately, we can get stuck at a node even though there are
still unused tickets that need to appear earlier in the
itinerary.

Instead, we use the same idea as

Hierholzer's Algorithm:

    1. Follow unused edges as far as possible.
    2. Remove each edge when it is used.
    3. When a node has no unused outgoing edges, add that node
       to the path.
    4. Reverse the path at the end.

This is why the node is added

AFTER

all its outgoing edges have been exhausted.

------------------------------------------------------------

Building the Graph:
--------------------

For every ticket:

    [from, to]

we create:

    adj[from].push_back(to)

For example:

tickets:

    JFK -> SFO
    JFK -> ATL
    ATL -> JFK
    SFO -> ATL

Graph:

              SFO
             / 
           JFK
          /   \
        ATL

The graph represents all available flights.

------------------------------------------------------------

Why Reverse Sort?
-----------------

The problem requires the

lexicographically smallest

valid itinerary.

Your DFS takes:

    adj[startNode].back()

which means it always takes the LAST destination from the
vector.

Therefore, we sort the tickets in reverse lexicographical
order:

    sort(tickets.rbegin(), tickets.rend());

Example:

Destinations:

    ATL
    SFO

After reverse sorting:

    SFO
    ATL

After inserting them into the adjacency list:

    adj["JFK"] = {"SFO", "ATL"}

Now:

    back()

returns:

    "ATL"

which is the lexicographically smaller destination.

Therefore,

reverse sorting + taking back()

allows us to efficiently choose the smallest destination.

------------------------------------------------------------

Why Not Sort Normally?
----------------------

If we sorted normally:

    ATL
    SFO

then:

    back()

would return:

    SFO

which is the larger destination.

We would therefore need to use:

    front()

or remove from the beginning,

which is inefficient for a vector.

By reverse sorting,

the smallest destination is placed at the back.

------------------------------------------------------------

DFS:
----

The main DFS is:

    while(!adj[startNode].empty()) {

        string newStartNode =
            adj[startNode].back();

        adj[startNode].pop_back();

        dfs(adj, path, newStartNode);
    }

The important part is:

    adj[startNode].pop_back();

This removes the ticket immediately after using it.

Therefore,

the same ticket cannot be used twice.

------------------------------------------------------------

Why Remove Tickets Instead of Using visited?
---------------------------------------------

We cannot simply mark airports as visited.

An airport may need to be visited multiple times.

For example:

    JFK -> ATL
    ATL -> JFK

We must visit

JFK

again.

What must be used exactly once is the

ticket / edge,

not the airport / node.

Therefore, removing an edge from the adjacency list is the
correct way to mark a ticket as used.

------------------------------------------------------------

Why Add Nodes After DFS?
------------------------

This is the most important part:

    path.push_back(startNode);

is executed only after

    while(!adj[startNode].empty())

has finished.

That means:

    "We only add this airport after all of its remaining
     outgoing tickets have been used."

This is the core idea of Hierholzer's Algorithm.

------------------------------------------------------------

Example:
--------

Suppose we have:

    JFK -> KUL
    JFK -> NRT
    NRT -> JFK

We want:

    JFK -> NRT -> JFK -> KUL

Start:

    JFK

The smallest destination is:

    KUL

But if we immediately choose KUL:

    JFK -> KUL

we get stuck at KUL while

    NRT -> JFK

has not been used.

Hierholzer's Algorithm handles this correctly.

The traversal may initially go:

    JFK -> NRT -> JFK -> KUL

When KUL has no outgoing edges:

    path.push_back("KUL")

Then DFS returns to JFK:

    path.push_back("JFK")

and so on.

The nodes are collected in reverse order.

------------------------------------------------------------

Why Reverse the Final Path?
----------------------------

Because nodes are added while DFS is returning,

the path is constructed backwards.

For example, DFS may produce:

    KUL
    JFK
    NRT
    JFK

So:

    path = [KUL, JFK, NRT, JFK]

After:

    reverse(path.begin(), path.end());

we get:

    JFK -> NRT -> JFK -> KUL

which is the required itinerary.

------------------------------------------------------------

Lexicographically Smallest:
----------------------------

There is an important subtlety here.

We want the smallest valid itinerary,

but we cannot simply choose the smallest destination and
permanently commit to it.

Sometimes the smallest destination can lead to a dead end
while unused tickets remain.

Hierholzer's algorithm solves this by adding nodes only after
their outgoing edges are exhausted.

The reverse-sorted adjacency list ensures that whenever we
need to choose an available edge,

the lexicographically smallest destination is processed first
from the back.

The final reversed Eulerian path therefore gives the required
lexicographically smallest itinerary.

------------------------------------------------------------

Example:
--------

Tickets:

    ["MUC","LHR"]
    ["JFK","MUC"]
    ["SFO","SJC"]
    ["LHR","SFO"]

Graph:

    JFK
     |
    MUC
     |
    LHR
     |
    SFO
     |
    SJC

DFS:

    JFK
      ↓
    MUC
      ↓
    LHR
      ↓
    SFO
      ↓
    SJC

Nodes are added while returning:

    SJC
    SFO
    LHR
    MUC
    JFK

Reverse:

    JFK
    MUC
    LHR
    SFO
    SJC

------------------------------------------------------------

Why Does This Work?
-------------------

Every ticket is an edge in the graph.

The itinerary must use every ticket exactly once,

so we need an Eulerian path.

Hierholzer's Algorithm guarantees that all edges are included
exactly once.

The DFS removes an edge when it is used,

so no ticket can be reused.

A node is added to the answer only after all of its outgoing
unused edges have been processed,

which allows cycles and subpaths to be inserted correctly.

Finally,

reversing the path gives the actual Eulerian itinerary.

The reverse sorting ensures that the destinations are
processed in lexicographical order.

------------------------------------------------------------

Time Complexity:
----------------

Let

E = number of tickets.

Sorting the tickets:

    O(E log E)

Each ticket is inserted into the graph once and removed once.

DFS:

    O(E)

Overall:

    O(E log E)

------------------------------------------------------------

Space Complexity:
-----------------

Adjacency List:

    O(E)

Path:

    O(E)

Recursion Stack:

    O(E)

Overall:

    O(E)

------------------------------------------------------------

Main Pattern to Remember:
--------------------------

"Use every EDGE exactly once"

        ↓

Eulerian Path

        ↓

Hierholzer's Algorithm

        ↓

Remove edge when used

        ↓

DFS until no outgoing edges

        ↓

Add node while backtracking

        ↓

Reverse the path

        ↓

Valid itinerary

For the lexicographical requirement:

    reverse sort

        +

    take back()

        ↓

smallest available destination

*/