class Solution {
    public:
        bool sumGame(string num) {
            int leftSum = 0, rightSum = 0, leftQ = 0, rightQ = 0, n = num.size();
            for(int i = 0; i < n / 2; i++) {
                if(num[i] == '?') leftQ++;
                else leftSum += num[i] - '0';
            }
            for(int i = n / 2; i < n; i++) {
                if(num[i] == '?') rightQ++;
                else rightSum += num[i] - '0';
            }
    
            return 2 * (leftSum - rightSum) + 9 * (leftQ - rightQ) != 0;
        }
    };

/*
LeetCode 1927. Sum Game

Approach:
---------

We have a string of even length containing digits and '?'.

Alice and Bob take turns replacing '?' with digits from 0 to 9.

After all '?' are replaced, Alice wins if the sum of the digits
in the LEFT half is different from the sum of the digits in the
RIGHT half.

Bob wins if both sums are equal.

The important idea is to determine whether the current state can
ever be made equal.

------------------------------------------------------------

Variables:
----------

    leftSum
        = sum of already-known digits in the left half

    rightSum
        = sum of already-known digits in the right half

    leftQ
        = number of '?' in the left half

    rightQ
        = number of '?' in the right half

We don't need to simulate every possible replacement.

Instead, we look at the difference between the two halves.

------------------------------------------------------------

Calculate the Known Sums and '?' Counts:
-----------------------------------------

    for(int i = 0; i < n / 2; i++) {
        if(num[i] == '?')
            leftQ++;
        else
            leftSum += num[i] - '0';
    }

For the left half, we separate:

    known digits -> leftSum
    unknown digits -> leftQ

We do the same for the right half.

------------------------------------------------------------

What Are We Actually Checking?
-------------------------------

Let:

    D = leftSum - rightSum

Initially, the known digits create a difference:

    D

The '?' characters can potentially change this difference.

The question is:

    "Can Bob make the final left sum equal to the final
     right sum?"

If Bob cannot make them equal, Alice wins.

So the entire problem reduces to:

    Can the final difference become 0?

------------------------------------------------------------

The Important Return Condition:
-------------------------------

    return 2 * (leftSum - rightSum)
           + 9 * (leftQ - rightQ) != 0;

This is the most important part of the solution.

Let's understand where this formula comes from.

Define:

    sumDiff = leftSum - rightSum

and:

    qDiff = leftQ - rightQ

The condition becomes:

    2 * sumDiff + 9 * qDiff != 0

If this value is:

    0

then Bob can force the two sums to be equal.

If this value is:

    != 0

then Alice can force the sums to remain different.

Therefore:

    expression != 0  -> Alice wins -> true
    expression == 0  -> Bob wins   -> false

------------------------------------------------------------

Why Does the Number 9 Appear?
------------------------------

A '?' can be replaced with any digit:

    0, 1, 2, ..., 9

So the largest possible difference between two replacements
is:

    9 - 0 = 9

Consider a pair consisting of:

    one '?' on the left
    one '?' on the right

Bob/Alice can effectively create a difference between their
contributions.

The important quantity is therefore the maximum adjustment:

    9

per unmatched '?'.

------------------------------------------------------------

Why Does the Number 2 Appear?
-----------------------------

This is because Alice and Bob take turns.

If there are more '?' on one side than the other, the players
can control the unmatched '?' on that side.

The known-sum difference must therefore be considered twice
when comparing it against the imbalance in the number of '?'.

That produces:

    2 * (leftSum - rightSum)

while the unmatched '?' contribute:

    9 * (leftQ - rightQ)

Combining both gives:

    2 * (leftSum - rightSum)
    +
    9 * (leftQ - rightQ)

------------------------------------------------------------

Understanding the Formula Through the Final Equality:
------------------------------------------------------

Suppose after all replacements the sums are:

    finalLeft
    finalRight

Bob wants:

    finalLeft == finalRight

Therefore:

    finalLeft - finalRight == 0

The known digits already contribute:

    leftSum - rightSum

The '?' replacements contribute the remaining difference.

Because players choose digits strategically, the condition for
Bob to be able to force equality reduces to:

    2 * (leftSum - rightSum)
    + 9 * (leftQ - rightQ)
    == 0

So:

    if expression == 0:
        Bob can force equality
        Alice loses
        return false

    if expression != 0:
        Alice can force inequality
        Alice wins
        return true

------------------------------------------------------------

Example 1:
-----------

Suppose:

    num = "5023"

There are no '?'.

Left half:

    5 + 0 = 5

Right half:

    2 + 3 = 5

So:

    leftSum - rightSum = 0

and:

    leftQ - rightQ = 0

Expression:

    2 * 0 + 9 * 0
    = 0

Therefore:

    return false

The sums are already equal, so Alice does not win.

------------------------------------------------------------

Example 2:
-----------

Suppose:

    num = "25??"

Left:

    2 + 5 = 7
    leftQ = 0

Right:

    rightQ = 2
    rightSum = 0

So:

    leftSum - rightSum = 7

    leftQ - rightQ = -2

Expression:

    2 * 7 + 9 * (-2)

    = 14 - 18

    = -4

Since:

    -4 != 0

we return:

    true

Alice wins.

------------------------------------------------------------

Example 3:
-----------

Suppose:

    num = "??25"

Left:

    leftSum = 0
    leftQ = 2

Right:

    rightSum = 7
    rightQ = 0

Expression:

    2 * (0 - 7)
    + 9 * (2 - 0)

    = -14 + 18

    = 4

Since:

    4 != 0

Alice wins.

This is symmetric to the previous case.

------------------------------------------------------------

The Critical Case: Expression == 0
-----------------------------------

Suppose:

    leftSum - rightSum = 9
    leftQ - rightQ = -2

Then:

    2 * 9 + 9 * (-2)

    = 18 - 18

    = 0

This means the known-sum advantage and the '?' imbalance
perfectly cancel each other.

Therefore Bob can force the final sums to be equal.

So:

    expression == 0

means:

    Bob wins

and because the function asks whether Alice wins:

    return false

------------------------------------------------------------

Why Do We Only Care About the Difference?
------------------------------------------

We don't actually care about the absolute values of the two
sums.

For example:

    left = 20
    right = 15

and:

    left = 100
    right = 95

both have the same difference:

    left - right = 5

The important question is only:

    Can the difference become 0?

Therefore, tracking:

    leftSum - rightSum

is enough.

------------------------------------------------------------

A Useful Way to Remember the Return:
-------------------------------------

Think of:

    2 * (leftSum - rightSum)
    + 9 * (leftQ - rightQ)

as the "remaining imbalance".

If:

    imbalance == 0

the game can end with equal sums.

Therefore:

    Bob wins
    Alice loses
    return false

If:

    imbalance != 0

the game cannot be balanced under optimal play.

Therefore:

    Alice wins
    return true

So the final condition is:

    imbalance != 0

------------------------------------------------------------

Overall Flow:
-------------

        Separate the string
              /      \
        Left half   Right half
            |           |
         sum + ?      sum + ?
            \           /
             \         /
              ↓       ↓
       Calculate imbalance

    2 * (leftSum - rightSum)
    + 9 * (leftQ - rightQ)

              |
        +-----+-----+
        |           |
       == 0        != 0
        |           |
      Bob wins    Alice wins
        |           |
      false        true

------------------------------------------------------------

Complexity:
-----------

We scan every character once:

    Time Complexity: O(n)

We only store four integers:

    leftSum
    rightSum
    leftQ
    rightQ

So:

    Space Complexity: O(1)

------------------------------------------------------------

Main Idea to Remember:
----------------------

The whole problem is reduced to checking whether the two halves
can be balanced.

Track:

    leftSum
    rightSum
    leftQ
    rightQ

Then calculate:

    2 * (leftSum - rightSum)
    + 9 * (leftQ - rightQ)

The final interpretation is:

    == 0
        -> Bob can make sums equal
        -> Alice loses
        -> false

    != 0
        -> Alice can force sums to be different
        -> Alice wins
        -> true

The key formula to remember is:

    2 * sumDifference + 9 * questionMarkDifference

and the key return condition is:

    expression != 0
*/