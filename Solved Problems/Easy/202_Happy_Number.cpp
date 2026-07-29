class Solution {
    private:
        int sum(int n) {
            int sum = 0;
            while(n) {
                sum += pow(n % 10, 2);
                n /= 10;
            }
    
            return sum;
        }
    
    public:
        bool isHappy(int n) {
            set<int> visited;
            while(visited.count(n) == 0) {
                visited.insert(n);
                n = sum(n);
                if(n == 1) return true;
            }
            return false;
        }
    };

/*

Idea:
------
A number is called

Happy

if repeatedly replacing it with the

sum of the squares of its digits

eventually reaches

1.

If the process never reaches

1,

the sequence must eventually repeat,

forming a cycle.

Therefore,

the problem reduces to detecting whether the generated
sequence

• reaches

1,

or

• enters a cycle.

To detect a cycle,

we store every previously seen number in a

set.

If the same number appears again,

the sequence has entered a loop,

so it can never become

1.

------------------------------------------------------------

Transformation Rule:
--------------------

For every number,

replace it with

(sum of squares of its digits)

Example

n = 19

Digits

1

9

↓

1² + 9²

↓

1 + 81

↓

82

Repeat the same process.

------------------------------------------------------------

Helper Function:
----------------

The function

sum(n)

computes

"The sum of the squares of all digits of

n."

Example

n = 82

Digits

8

2

Calculation

8² + 2²

=

64 + 4

=

68

Return

68.

------------------------------------------------------------

Example Transformation:
-----------------------

n = 19

19

↓

82

↓

68

↓

100

↓

1

Since the sequence reaches

1,

19

is a Happy Number.

------------------------------------------------------------

Cycle Detection:
----------------

Some numbers never reach

1.

Instead,

they repeatedly produce the same sequence.

Example

2

↓

4

↓

16

↓

37

↓

58

↓

89

↓

145

↓

42

↓

20

↓

4

Notice

4

appears again.

Once a previously seen number repeats,

the entire sequence will continue repeating forever.

Therefore,

the number is

not

happy.

------------------------------------------------------------

Why Use a Set?
--------------

The

visited

set stores every number generated during the process.

Before processing a number,

check whether it already exists in the set.

If it does,

a cycle has been detected.

Return

false.

Otherwise,

insert the number and continue.

------------------------------------------------------------

Algorithm:
----------

Step 1

Create an empty set

visited.

------------------------------------------------------------

Step 2

Repeat until a number repeats.

------------------------------------------------------------

Step 3

Insert the current number into

visited.

------------------------------------------------------------

Step 4

Replace the number with the sum of the squares of its
digits.

------------------------------------------------------------

Step 5

If the new number becomes

1,

return

true.

------------------------------------------------------------

Step 6

If the number has already appeared before,

a cycle exists.

Return

false.

------------------------------------------------------------

Example 1:
----------

Input

19

Initially

visited = {}

--------------------------------

Insert

19

Next

82

visited

{19}

--------------------------------

Insert

82

Next

68

visited

{19,82}

--------------------------------

Insert

68

Next

100

visited

{19,82,68}

--------------------------------

Insert

100

Next

1

Reached

1

Answer

true

------------------------------------------------------------

Example 2:
----------

Input

2

Sequence

2

↓

4

↓

16

↓

37

↓

58

↓

89

↓

145

↓

42

↓

20

↓

4

The number

4

appears again.

Cycle detected.

Answer

false.

------------------------------------------------------------

Visualization:
--------------

Happy Number

19

↓

82

↓

68

↓

100

↓

1

Success

--------------------------------

Non-Happy Number

2

↓

4

↓

16

↓

37

↓

58

↓

89

↓

145

↓

42

↓

20

↓

4

↓

...

Cycle

------------------------------------------------------------

Why Must a Cycle Exist?
-----------------------

The generated numbers cannot increase forever.

For an integer with

d

digits,

the maximum possible sum of squared digits is

81 × d

because

9² = 81.

Eventually,

even very large numbers become much smaller after applying
the transformation repeatedly.

For example,

999999

↓

6 × 81

↓

486

After several transformations,

every sequence eventually enters a relatively small range of
numbers.

Within this finite range,

either

• the sequence reaches

1,

or

• some number repeats.

Once a number repeats,

all future numbers repeat in exactly the same order,

forming a cycle.

------------------------------------------------------------

Why Does This Work?
-------------------

Every iteration produces exactly one next number.

The sequence is deterministic,

meaning the same number always generates the same next
number.

Therefore,

if a number is ever generated twice,

the entire sequence from that point onward repeats forever.

The

visited

set detects this repeated state.

If

1

is reached before any repetition,

the number is happy.

Otherwise,

the sequence enters a cycle and can never reach

1.

------------------------------------------------------------

Correctness Proof:
------------------

We prove that the algorithm correctly determines whether a
number is happy.

Each iteration replaces the current number by the sum of
the squares of its digits,

which is exactly the transformation defined in the problem.

If the sequence reaches

1,

the algorithm immediately returns

true,

which matches the definition of a happy number.

Suppose the sequence never reaches

1.

Since repeated transformations eventually fall into a
finite range of values,

some number must eventually appear more than once.

Because the transformation is deterministic,

repeating a number causes the entire remaining sequence to
repeat,

forming a cycle.

The

visited

set detects the first repeated number,

and the algorithm returns

false.

Therefore,

the algorithm returns

true

if and only if the given number is happy.

------------------------------------------------------------

Time Complexity:
----------------

Let

k

be the number of unique numbers generated before reaching

1

or entering a cycle.

Each transformation processes all digits of the current
number.

If

d

is the number of digits,

one transformation takes

O(d).

Overall Time Complexity

O(k × d)

Since the generated values quickly become small,

both

k

and

d

are bounded by small constants in practice.

Thus,

the practical running time is effectively

O(1).

------------------------------------------------------------

Space Complexity:
-----------------

The

visited

set stores every unique number generated before
termination.

Worst-case Auxiliary Space

O(k)

In practice,

this is also effectively

O(1)

because only a small finite number of values can appear.

------------------------------------------------------------

Note:
-----

This solution detects cycles using a

Set.

An alternative solution uses

Floyd's Cycle Detection Algorithm
(Tortoise and Hare),

which detects the cycle in

O(1)

extra space without storing previously visited numbers.

*/