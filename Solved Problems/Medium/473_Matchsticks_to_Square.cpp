class Solution {
    bool dfs(vector<int>& matchsticks, vector<int>& sides, int idx, int target) {
        if(idx == matchsticks.size()) {
            return sides[0] == target && sides[1] == target && sides[2] == target && sides[3] == target;
        }

        for(int i = 0; i < 4; i++) {
            if(sides[i] + matchsticks[idx] <= target) {
                sides[i] += matchsticks[idx];
                if(dfs(matchsticks, sides, idx + 1, target)) return true;
                sides[i] -= matchsticks[idx];
            }
        }
        return false;
    }

public:
    bool makesquare(vector<int>& matchsticks) {
        long long side = 0;
        for(auto& x : matchsticks) side += x;
        if(side % 4) return false;
        side /= 4;
        vector<int> sides(4, 0);
        sort(matchsticks.begin(), matchsticks.end(), greater<int>());
        return dfs(matchsticks, sides, 0, side);
    }
};

/*

Idea:
------
We are given matchsticks and must determine whether all of
them can be used exactly once to form a square.

A square has four sides of equal length.

Therefore,

the problem reduces to assigning every matchstick to one
of the four sides such that

1.

Every matchstick is used exactly once.

2.

The sum of lengths on each side equals

Total Sum / 4.

Since every matchstick has four possible choices (one for
each side),

this becomes a classic

Backtracking + Depth First Search (DFS)

problem.

------------------------------------------------------------

Key Observation:
----------------

Let

Total Length = Sum of all matchsticks.

A square is possible only if

Total Length

is divisible by

4.

If not,

it is impossible to divide the matchsticks equally among
four sides.

Therefore,

the very first check is

Total Length % 4 == 0.

The target length of each side becomes

Target = Total Length / 4.

------------------------------------------------------------

DFS State:
----------

The recursive function

dfs(idx)

means:

"We have already placed the first

idx

matchsticks.

Can the remaining matchsticks be placed so that all four
sides eventually become equal to

Target?"

The vector

sides

stores the current length of each side.

Example

sides = [5,3,5,2]

means

Side 1 = 5

Side 2 = 3

Side 3 = 5

Side 4 = 2

Every recursive call decides

which side should receive the current matchstick.

------------------------------------------------------------

Recursive Choice:
-----------------

Suppose

Current Matchstick = matchsticks[idx]

There are at most

4

choices.

Place it on

Side 1

or

Side 2

or

Side 3

or

Side 4.

However,

a placement is allowed only if

Current Side Length + Matchstick Length ≤ Target.

Otherwise,

that side would exceed the required length and can never
be part of a valid square.

------------------------------------------------------------

Backtracking:
-------------

Whenever a matchstick is placed,

its length is added to one side.

Example

Current

Sides

[4,5,3,2]

Current Matchstick

= 2

Choose

Side 3

Sides become

[4,5,5,2]

Now recursively place the remaining matchsticks.

--------------------------------

If this choice eventually fails,

remove the matchstick.

Sides become

[4,5,3,2]

Then try another side.

This process of

Choose

↓

Explore

↓

Undo

is exactly

Backtracking.

------------------------------------------------------------

Base Case:
----------

When

idx == matchsticks.size()

every matchstick has already been assigned.

Now check whether

all four sides equal

Target.

If yes,

a valid square has been formed.

Return

true.

Otherwise,

return

false.

------------------------------------------------------------

Why Sorting Helps:
------------------

Before starting DFS,

the matchsticks are sorted in

descending order.

Largest matchsticks are placed first.

Example

Original

[1,1,2,2,5]

Sorted

[5,2,2,1,1]

Why?

Suppose

Target = 4.

The first matchstick

5

already exceeds the target.

The algorithm immediately discovers that no solution is
possible.

Without sorting,

many smaller matchsticks might be placed first,

causing the algorithm to explore a huge number of useless
states before eventually failing.

Therefore,

placing larger matchsticks first greatly improves pruning
and reduces the search space.

------------------------------------------------------------

Algorithm:
----------

Step 1

Compute the total sum of all matchsticks.

------------------------------------------------------------

Step 2

If the total sum is not divisible by

4,

return

false.

------------------------------------------------------------

Step 3

Target Side Length

=

Total Sum / 4.

------------------------------------------------------------

Step 4

Sort the matchsticks in descending order.

------------------------------------------------------------

Step 5

Initialize four sides with length

0.

------------------------------------------------------------

Step 6

Process the matchsticks one by one.

For every matchstick,

try placing it on each of the four sides.

------------------------------------------------------------

Step 7

If adding the matchstick exceeds

Target,

skip that side.

------------------------------------------------------------

Step 8

Otherwise,

place the matchstick,

recursively process the next one,

and if necessary,

remove it while backtracking.

------------------------------------------------------------

Step 9

If every matchstick has been placed and all four sides
equal

Target,

return

true.

Otherwise,

return

false.

------------------------------------------------------------

Recursion Tree Example:
-----------------------

Matchsticks

[2,2,2,2]

Target

= 2

Start

Sides

[0,0,0,0]

                     [0,0,0,0]
                           |
                  Place first 2
                           |
                    [2,0,0,0]
                           |
                  Place second 2
                     /   |   \
             [2,2,0,0] ...

Continue until

[2,2,2,2]

All sides reach the target.

Return

true.

------------------------------------------------------------

Example:
--------

Input

[1,1,2,2,2]

Total

=

8

Target

=

2

Sorted

[2,2,2,1,1]

--------------------------------

Place

2

↓

Sides

[2,0,0,0]

--------------------------------

Place

2

↓

Sides

[2,2,0,0]

--------------------------------

Place

2

↓

Sides

[2,2,2,0]

--------------------------------

Place

1

↓

Sides

[2,2,2,1]

--------------------------------

Place last

1

↓

Sides

[2,2,2,2]

All four sides equal the target.

Return

true.

------------------------------------------------------------

Example:
--------

Input

[3,3,3,3,4]

Total

=

16

Target

=

4

Sorted

[4,3,3,3,3]

Place

4

↓

Sides

[4,0,0,0]

Now every remaining matchstick has length

3.

No two

3's

can fit into the remaining sides because

3 + 3 > 4.

Every recursive branch eventually fails.

Return

false.

------------------------------------------------------------

Why Does This Work?
-------------------

The algorithm considers every possible assignment of each
matchstick to one of the four sides.

A matchstick is placed only if it does not cause the
current side to exceed the required target length.

Thus,

every recursive state always represents a valid partial
construction.

Backtracking guarantees that if one placement fails,

all remaining valid placements are explored.

Since every possible assignment is examined exactly when
it remains feasible,

the algorithm returns

true

iff

there exists at least one way to distribute all
matchsticks into four equal-length sides.

------------------------------------------------------------

Mathematical View:
------------------

Let

f(idx, s1, s2, s3, s4)

represent whether the remaining matchsticks starting from

idx

can complete the four side lengths

s1,

s2,

s3,

and

s4.

For the current matchstick

L,

the transition is

f(idx)

=

OR

over every side

i

such that

si + L ≤ Target

of

f(idx + 1)

after adding

L

to side

i.

The recursion succeeds if any transition reaches the
state

(Target, Target, Target, Target).

------------------------------------------------------------

Time Complexity:
----------------

Let

n

be the number of matchsticks.

Each matchstick can be placed into at most

4

different sides.

Therefore,

the worst-case recursion explores

4^n

states.

Sorting requires

O(n log n).

Overall Worst-Case Time Complexity:

O(4^n)

(The exponential search dominates.)

In practice,

sorting the matchsticks in descending order prunes a large
number of invalid branches,

making the solution much faster than the theoretical
worst case.

------------------------------------------------------------

Space Complexity:
-----------------

The recursion depth is at most

n,

since one recursive call is made for each matchstick.

The vector

sides

always stores exactly

4

integers.

Ignoring the recursion stack,

only constant extra memory is used.

Auxiliary Space:

O(n)

due to recursion.

*/