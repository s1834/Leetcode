class Solution {
    public:
        int minimumPushes(string word) {
            int n = word.size();
            if(n <= 8) return n;
            else if(n <= 16) return 8 + 2 * (n - 8);
            else if(n <= 24) return 24 + 3 * (n - 16);
            else return 48 + 4 * (n - 24);
        }
    };

/*

Idea:
------
There are

8

available keys

(2 through 9).

Since we are free to remap the letters to any keys,

our goal is to assign letters so that the total number of
key presses is minimized.

Every letter appears exactly once because all characters in
the word are distinct.

Therefore,

we only need to determine how many letters receive

• 1 push,

• 2 pushes,

• 3 pushes,

• 4 pushes.

The optimal strategy is to always assign the easiest
positions (fewest pushes) first.

------------------------------------------------------------

Key Observation:
----------------

There are only

8

keys.

Therefore,

at most

8

letters can occupy the

first position

of the keys.

These letters require only

1

push.

--------------------------------

The next

8

letters must occupy the

second position

of the keys.

These require

2

pushes.

--------------------------------

The next

8

letters occupy the

third position.

These require

3

pushes.

--------------------------------

Finally,

the remaining

2

letters (since there are only

26

letters total)

occupy the

fourth position,

requiring

4

pushes.

Thus,

letters are divided into groups of

8.

------------------------------------------------------------

Why Is This Greedy Strategy Optimal?
------------------------------------

Every letter contributes exactly once to the answer.

Since all letters occur exactly one time,

there is no benefit in assigning one letter a cheaper
position than another.

The only thing that matters is

how many letters

receive each push count.

Therefore,

we always fill all

1-push

positions first,

then all

2-push

positions,

then

3-push,

and finally

4-push

positions.

------------------------------------------------------------

Possible Cases:
---------------

============================================================

Case 1

n ≤ 8

============================================================

Every letter gets its own key.

Each letter requires exactly

1

push.

Total Cost

=

n

------------------------------------------------------------

Case 2

8 < n ≤ 16

============================================================

First

8

letters

↓

1 push each

Remaining

(n - 8)

letters

↓

2 pushes each

Total

=

8

+

2 × (n - 8)

------------------------------------------------------------

Case 3

16 < n ≤ 24

============================================================

First

8

letters

↓

1 push

Next

8

letters

↓

2 pushes

Remaining

(n - 16)

letters

↓

3 pushes

Total

=

8

+

16

+

3 × (n - 16)

=

24

+

3 × (n - 16)

------------------------------------------------------------

Case 4

24 < n ≤ 26

============================================================

First

8

letters

↓

1 push

Next

8

letters

↓

2 pushes

Next

8

letters

↓

3 pushes

Remaining

(n - 24)

letters

↓

4 pushes

Total

=

8

+

16

+

24

+

4 × (n - 24)

=

48

+

4 × (n - 24)

------------------------------------------------------------

Algorithm:
----------

Step 1

Compute

n

=

word.length().

------------------------------------------------------------

Step 2

If

n ≤ 8,

every letter needs only

1

push.

Return

n.

------------------------------------------------------------

Step 3

If

8 < n ≤ 16,

first

8

letters contribute

8

pushes.

Remaining letters contribute

2

pushes each.

------------------------------------------------------------

Step 4

If

16 < n ≤ 24,

first

16

letters contribute

24

pushes.

Remaining letters contribute

3

pushes each.

------------------------------------------------------------

Step 5

Otherwise,

the first

24

letters contribute

48

pushes.

The remaining letters contribute

4

pushes each.

------------------------------------------------------------

Example 1:
----------

word =

"abcde"

Length

5

Since

5 ≤ 8,

every letter occupies the first position of a different
key.

Cost

=

5

------------------------------------------------------------

Example 2:
----------

Length

10

First

8

letters

↓

1 push each

=

8

Remaining

2

letters

↓

2 pushes each

=

4

Total

=

12

------------------------------------------------------------

Example 3:
----------

Length

20

First

8

letters

↓

8

Next

8

letters

↓

16

Remaining

4

letters

↓

12

Total

=

36

------------------------------------------------------------

Visualization:
--------------

Push Count Distribution

Keys

2 3 4 5 6 7 8 9

First Layer

1 1 1 1 1 1 1 1

↓

8 letters

--------------------------------

Second Layer

2 2 2 2 2 2 2 2

↓

Next 8 letters

--------------------------------

Third Layer

3 3 3 3 3 3 3 3

↓

Next 8 letters

--------------------------------

Fourth Layer

4 4

↓

Remaining letters

------------------------------------------------------------

Mathematical Explanation:
-------------------------

Suppose the word contains

n

distinct letters.

The first

8

letters each contribute

1,

so

Contribution

=

8 × 1

--------------------------------

The next

8

letters each contribute

2,

so

Contribution

=

8 × 2 = 16

--------------------------------

The next

8

letters each contribute

3,

so

Contribution

=

8 × 3 = 24

--------------------------------

The remaining

(n - 24)

letters contribute

4

each.

Thus,

the total cost is computed according to the group in which

n

falls.

------------------------------------------------------------

Why Does This Work?
-------------------

Each key provides exactly one position requiring

1

push,

one requiring

2

pushes,

and so on.

Since there are

8

keys,

exactly

8

letters can receive any particular push count.

Because every letter appears exactly once,

all letters have equal importance.

Therefore,

placing as many letters as possible into the cheapest
available positions always minimizes the total number of
pushes.

------------------------------------------------------------

Correctness Proof:
------------------

We prove that the algorithm computes the minimum possible
number of key presses.

There are exactly

8

positions requiring one push,

8

positions requiring two pushes,

8

positions requiring three pushes,

and the remaining positions require four pushes.

Since every letter appears exactly once,

the contribution of each letter depends only on the push
count assigned to it.

Assigning any letter to a more expensive position while a
cheaper position remains unused would strictly increase the
total cost.

Hence,

all cheaper positions must always be filled before any more
expensive position.

The algorithm counts exactly how many letters belong to
each push layer and computes the corresponding total cost.

Therefore,

the computed answer is the minimum possible number of key
presses.

------------------------------------------------------------

Time Complexity:
----------------

Only the length of the word is examined.

No iteration over characters is required.

Overall Time Complexity

O(1)

------------------------------------------------------------

Space Complexity:
-----------------

Only a few integer variables are used.

Overall Auxiliary Space

O(1)

------------------------------------------------------------

Note:
-----

This simplified solution works because

• every character in the word is distinct, and

• every character appears exactly once.

In the harder version of the problem
(LeetCode 3016),

letters may repeat.

There,

characters must first be sorted by frequency so that the
most frequent letters receive the cheapest key positions.

*/