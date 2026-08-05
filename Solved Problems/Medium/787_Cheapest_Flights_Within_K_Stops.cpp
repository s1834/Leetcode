class Solution {
    public:
        int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
            vector<int> prices(n, INT_MAX);
            prices[src] = 0;
    
            for(int i = 0; i <= k; i++) {
                vector<int> temp = prices;
    
                for(auto flight : flights) {
                    int from = flight[0];
                    int to = flight[1];
                    int price = flight[2];
    
                    if(prices[from] == INT_MAX) continue; // check with prices not temp
                    if(prices[from] + price < temp[to]) temp[to] = prices[from] + price; // prices[from], not temp[from]
                }
                prices = temp;
            }
    
            if(prices[dst] == INT_MAX) return -1;
            return prices[dst];
        }
    };

/*

Idea:
------

Unlike the standard shortest path problem,

we are allowed to use at most

k

stops.

This means the path can contain at most

k + 1

edges.

Since the number of edges is limited,

we use the

Bellman-Ford Algorithm,

which computes the shortest distances using a fixed number of
edge relaxations.

After

k + 1

iterations,

every path containing at most

k + 1

edges has been considered.

------------------------------------------------------------

Key Observation:
----------------

Bellman-Ford works by repeatedly relaxing every edge.

After

i

iterations,

the algorithm correctly computes the shortest distance using
at most

i

edges.

Since a route with

k

stops contains

k + 1

edges,

performing exactly

k + 1

relaxation rounds guarantees that every valid route has been
considered.

------------------------------------------------------------

Approach:
---------

1. Create a distance array

prices,

where

prices[i]

stores the minimum cost to reach city

i.

Initially,

prices[src] = 0

and every other city has cost

∞.

2. Perform

k + 1

iterations.

3. During each iteration,

create a temporary copy

temp

of the current distance array.

4. Relax every flight.

If

prices[from] + cost < temp[to],

update

temp[to].

5. After processing all flights,

replace

prices

with

temp.

6. After all iterations,

if

dst

is still unreachable,

return

-1.

Otherwise,

return the minimum cost.

------------------------------------------------------------

Why Use a Temporary Array?
--------------------------

This is the most important part of the algorithm.

During one iteration,

we should only use the distances computed in the

previous

iteration.

Suppose we have

0 → 1

↓

1 → 2

If we update

prices

directly,

updating

1

may immediately affect the update of

2

within the same iteration.

This would incorrectly allow paths containing more edges
than permitted.

Therefore,

all updates of the current iteration are stored in

temp,

while all relaxations read values only from

prices.

After finishing the iteration,

prices

is replaced with

temp.

------------------------------------------------------------

Example:
--------

Flights

0 → 1

100

1 → 2

100

0 → 2

500

Source

0

Destination

2

k = 1

--------------------------------

Initial

prices

[0,∞,∞]

--------------------------------

Iteration 1

Relax

0 → 1

prices

↓

[0,100,∞]

Relax

0 → 2

prices

↓

[0,100,500]

--------------------------------

Iteration 2

Relax

1 → 2

prices

↓

[0,100,200]

Answer

200

The cheapest valid route is

0 → 1 → 2

using exactly one stop.

------------------------------------------------------------

Visualization:
--------------

Flights

0

| \

100 500

|    \

1 ---> 2

   100

--------------------------------

Iteration 1

Reach

1

and

2

directly.

--------------------------------

Iteration 2

Use

1

to improve

2.

Final Cost

200

------------------------------------------------------------

Why Does This Work?
-------------------

Bellman-Ford guarantees that after

i

iterations,

the shortest paths using at most

i

edges have been computed.

Since a route with

k

stops contains exactly

k + 1

edges,

performing

k + 1

iterations ensures that every valid route is considered.

Using a temporary array prevents updates made during the
current iteration from influencing other relaxations in the
same iteration,

ensuring that every iteration represents exactly one
additional edge.

Therefore,

the final distance array contains the minimum cost among all
routes using at most

k

stops.

------------------------------------------------------------

Time Complexity:
----------------

Let

V = number of cities

E = number of flights

We perform

k + 1

iterations.

Each iteration processes every flight once.

Overall Time Complexity

O((k + 1) × E)

------------------------------------------------------------

Space Complexity:
-----------------

Distance Array

O(V)

Temporary Array

O(V)

Overall Space Complexity

O(V)

------------------------------------------------------------

Note:
-----

Although this is a shortest path problem,

Dijkstra's Algorithm cannot be directly applied because the
constraint is based on the

number of stops,

not just the total cost.

Bellman-Ford naturally handles this by limiting the number
of edge relaxations, making it the ideal solution for this
problem.

*/