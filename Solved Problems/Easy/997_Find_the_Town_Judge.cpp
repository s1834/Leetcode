// Version 1

// class Solution {
// public:
//     int findJudge(int n, vector<vector<int>>& trust) {
//         if(n == 1) return 1;
//         unordered_map<int, int> indegree;
//         int siz = trust.size();
//         for (int i = 0; i < siz; i++) {
//             indegree[trust[i][0]] = -1;
//             if(indegree[trust[i][1]] != -1) {
//                 indegree[trust[i][1]]++;
//             }
//         }

//         for(auto x : indegree) {
//             if(x.second == n - 1) {
//                 return x.first;
//             } 
//         }
//         return -1;
//     }
// };

// Version 2

class Solution {
    public:
        int findJudge(int n, vector<vector<int>>& trust) {
            vector<int> inDegree(n + 1, 0), outDegree(n + 1, 0);
    
            for (auto x : trust) {
                outDegree[x[0]]++;
                inDegree[x[1]]++;
            }
    
            for (int i = 1; i <= n; i++) {
                if (inDegree[i] == n - 1 && outDegree[i] == 0) return i;
            }
    
            return -1;
        }
    };

/*

Idea:
------
The Town Judge has two defining properties:

1.

Everyone trusts the judge.

Therefore,

the judge must have

in-degree = n - 1

because every other person trusts them.

--------------------------------

2.

The judge trusts nobody.

Therefore,

the judge must have

out-degree = 0.

Thus,

the problem reduces to finding a node in a directed graph
whose

• In-degree = n - 1

• Out-degree = 0

------------------------------------------------------------

Graph Representation:
---------------------

Each person is represented as a node.

Each trust relationship

[a, b]

represents a directed edge

a → b

meaning

Person

a

trusts

Person

b.

Example

trust =

[[1,3],
 [2,3]]

Graph

1 ─────► 3 ◄───── 2

Here,

Person

3

has

In-degree

=

2

Out-degree

=

0

Therefore,

3

is the judge.

------------------------------------------------------------

Key Observation:
----------------

Instead of checking every person's trust relationships
individually,

we simply count

1.

How many people trust each person.

(In-degree)

--------------------------------

2.

How many people each person trusts.

(Out-degree)

Once these counts are known,

finding the judge becomes a simple linear scan.

------------------------------------------------------------

In-Degree:
----------

inDegree[i]

stores

"The number of people who trust person

i."

Whenever we see an edge

u → v,

increment

inDegree[v].

------------------------------------------------------------

Out-Degree:
-----------

outDegree[i]

stores

"The number of people trusted by person

i."

Whenever we see an edge

u → v,

increment

outDegree[u].

------------------------------------------------------------

Algorithm:
----------

Step 1

Create two arrays

inDegree

and

outDegree

of size

n + 1.

------------------------------------------------------------

Step 2

Traverse every trust relationship

[a, b].

Increment

outDegree[a]

because

a

trusts someone.

Increment

inDegree[b]

because

b

is trusted by someone.

------------------------------------------------------------

Step 3

Check every person

1

through

n.

If

inDegree[i] == n - 1

and

outDegree[i] == 0,

then

i

satisfies both judge properties.

Return

i.

------------------------------------------------------------

Step 4

If no such person exists,

return

-1.

------------------------------------------------------------

Example:
--------

n = 3

trust =

[[1,3],
 [2,3]]

Initially

inDegree

=

[0,0,0,0]

outDegree

=

[0,0,0,0]

--------------------------------

Process

1 → 3

outDegree

=

[0,1,0,0]

inDegree

=

[0,0,0,1]

--------------------------------

Process

2 → 3

outDegree

=

[0,1,1,0]

inDegree

=

[0,0,0,2]

--------------------------------

Check every person

Person 1

inDegree = 0

Not Judge

--------------------------------

Person 2

inDegree = 0

Not Judge

--------------------------------

Person 3

inDegree = 2 = n - 1

outDegree = 0

Judge Found

Answer

3

------------------------------------------------------------

Example:
--------

n = 3

trust =

[[1,2],
 [2,3]]

Graph

1 → 2 → 3

In-degree

Person 1 = 0

Person 2 = 1

Person 3 = 1

No person has

in-degree = 2

Answer

-1

------------------------------------------------------------

Example:
--------

n = 4

trust =

[[1,3],
 [2,3],
 [4,3]]

Graph

1 ─┐

2 ─┼────► 3

4 ─┘

Person

3

In-degree

=

3

Out-degree

=

0

Judge

=

3

------------------------------------------------------------

Why Does This Work?
-------------------

The judge must satisfy two necessary and sufficient
conditions.

First,

every other person must trust the judge.

Therefore,

the judge must receive exactly

n - 1

incoming edges.

Second,

the judge trusts nobody.

Therefore,

the judge must have zero outgoing edges.

The algorithm computes these values for every person.

Any person satisfying both conditions is guaranteed to be
the judge.

If no person satisfies both,

then no judge exists.

------------------------------------------------------------

Correctness Proof:
------------------

We prove that the algorithm returns the correct judge.

Suppose the algorithm returns person

x.

Since

outDegree[x] = 0,

person

x

trusts nobody.

Since

inDegree[x] = n - 1,

every other person trusts

x.

Therefore,

x

satisfies both defining properties of the town judge.

Conversely,

suppose a town judge exists.

By definition,

every other person trusts the judge,

so their

in-degree

must equal

n - 1.

Also,

the judge trusts nobody,

so their

out-degree

must equal

0.

The algorithm checks every person,

so it will necessarily identify and return the judge.

If no person satisfies both conditions,

then no town judge exists,

and returning

-1

is correct.

------------------------------------------------------------

Time Complexity:
----------------

Let

m

be the number of trust relationships.

Processing every edge

O(m)

--------------------------------

Scanning all

n

people

O(n)

Overall Time Complexity

O(n + m)

------------------------------------------------------------

Space Complexity:
-----------------

Two arrays

inDegree

and

outDegree

each of size

n + 1.

Overall Auxiliary Space

O(n)

------------------------------------------------------------

Note:
-----

The graph itself is never explicitly constructed.

Only the in-degree and out-degree counts are required,
making this solution both simple and optimal.

*/