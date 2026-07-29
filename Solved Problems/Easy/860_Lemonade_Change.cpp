class Solution {
    public:
        bool lemonadeChange(vector<int>& bills) {
            int five = 0, ten = 0;
            for(auto x : bills) {
                if(x == 5) five++;
                else if(x == 10) {
                    if(!five) return false;
                    five--;
                    ten++;
                } else {
                    int need = 20;
                    if(ten) {
                        ten--;
                        if(five) five--;
                        else return false;
                    } else {
                        if(five >= 3) five -= 3;
                        else return false;
                    }
                }
            }
            return true;
        }
    };

/*

Idea:
------
Each customer buys one lemonade costing

$5.

Customers pay using only

$5,

$10,

or

$20

bills.

We must always return the correct change immediately.

Since customers are processed one after another,

we cannot postpone giving change or reorder the customers.

Therefore,

at every step,

we simply maintain how many

$5

and

$10

bills we currently possess.

Whenever a customer arrives,

we greedily give change using the available bills.

If at any point we cannot provide the required change,

the answer is immediately

false.

------------------------------------------------------------

Key Observation:
----------------

The only bills we ever need to keep track of are

$5

and

$10.

Why?

Because

$20

bills are never used to give change.

They are only received from customers.

Therefore,

storing the number of

$20

bills serves no purpose.

------------------------------------------------------------

Possible Cases:
---------------

Every customer pays using one of three bills.

============================================================

Case 1

Customer Pays with $5

============================================================

No change is required.

Simply keep the

$5

bill.

five++

------------------------------------------------------------

Example

Before

five = 2

ten = 1

Customer pays

$5

After

five = 3

ten = 1

------------------------------------------------------------

Case 2

Customer Pays with $10

============================================================

The lemonade costs

$5,

so we must return

$5

as change.

Therefore,

we must have at least one

$5

bill.

If not,

serving the customer is impossible.

Otherwise,

give one

$5

bill,

receive one

$10

bill.

five--

ten++

------------------------------------------------------------

Example

Before

five = 3

ten = 0

Customer pays

$10

Give

$5

Receive

$10

After

five = 2

ten = 1

------------------------------------------------------------

Case 3

Customer Pays with $20

============================================================

The lemonade costs

$5,

so we must return

$15

as change.

There are two possible ways.

Option 1

$10 + $5

--------------------------------

Option 2

$5 + $5 + $5

The greedy strategy always prefers

$10 + $5.

------------------------------------------------------------

Why Prefer $10 + $5?
--------------------

Suppose we have

five = 3

ten = 1

Giving

$10 + $5

Leaves

five = 2

ten = 0

--------------------------------

Giving

$5 + $5 + $5

Leaves

five = 0

ten = 1

The first option preserves more

$5

bills.

This is always better because

every future

$10

customer requires one

$5

bill as change.

Therefore,

keeping as many

$5

bills as possible increases our ability to serve future
customers.

Hence,

whenever possible,

we always use

$10 + $5

before using

three $5 bills.

------------------------------------------------------------

Greedy Choice:
--------------

Whenever a customer pays

$20,

1.

If one

$10

and one

$5

are available,

use them.

Otherwise,

2.

Use three

$5

bills.

If neither option is possible,

return

false.

------------------------------------------------------------

Algorithm:
----------

Step 1

Maintain two counters

five

and

ten.

------------------------------------------------------------

Step 2

Process customers one by one.

------------------------------------------------------------

Step 3

If customer pays

$5,

increase

five.

------------------------------------------------------------

Step 4

If customer pays

$10,

one

$5

bill is needed.

If unavailable,

return

false.

Otherwise,

update both counters.

------------------------------------------------------------

Step 5

If customer pays

$20,

first try giving

$10 + $5.

If not possible,

try

three $5 bills.

If neither is possible,

return

false.

------------------------------------------------------------

Step 6

If every customer is successfully served,

return

true.

------------------------------------------------------------

Example 1:
----------

Bills

[5,5,5,10,20]

Initially

five = 0

ten = 0

--------------------------------

Customer

5

five = 1

--------------------------------

Customer

5

five = 2

--------------------------------

Customer

5

five = 3

--------------------------------

Customer

10

Give one

$5

five = 2

ten = 1

--------------------------------

Customer

20

Need

$15

Use

$10 + $5

five = 1

ten = 0

Every customer receives correct change.

Answer

true

------------------------------------------------------------

Example 2:
----------

Bills

[5,5,10,10,20]

After first four customers

five = 0

ten = 2

Last customer pays

$20

Need

$15

Although we have

$10,

there is no

$5

bill.

Cannot make

$15.

Answer

false

------------------------------------------------------------

Example 3:
----------

Bills

[10]

First customer pays

$10.

Need

$5

change.

No

$5

bill exists.

Return

false.

------------------------------------------------------------

Why Does the Greedy Strategy Work?
----------------------------------

The only scarce resource is the

$5

bill.

Every future

$10

customer requires one

$5

bill.

A

$10

bill is useful only when combined with a

$5

bill to make

$15.

Therefore,

whenever possible,

using one

$10

bill instead of two extra

$5

bills preserves the maximum number of

$5

bills.

Since no future decision can benefit from keeping the

$10

bill instead of two

$5

bills,

this greedy choice is always optimal.

------------------------------------------------------------

Why Does This Work?
-------------------

Customers are processed in fixed order,

and change must be given immediately.

The algorithm always maintains the exact number of

$5

and

$10

bills currently available.

For every payment,

it performs the only valid change-making operation.

For

$20,

it greedily uses

$10 + $5

whenever possible because it preserves more

$5

bills for future transactions.

If correct change cannot be given at any step,

no alternative sequence of actions could have helped,

since previous customers cannot be revisited.

Therefore,

the algorithm correctly determines whether every customer
can be served.

------------------------------------------------------------

Correctness Proof:
------------------

We prove that the algorithm returns the correct answer.

For customers paying

$5,

no change is required,

so accepting the bill is always correct.

For customers paying

$10,

the only possible change is one

$5

bill.

If no

$5

bill exists,

serving the customer is impossible.

For customers paying

$20,

there are only two valid ways to return

$15:

one

$10

and one

$5,

or

three

$5

bills.

Whenever both are available,

the algorithm chooses

$10 + $5,

which preserves two additional

$5

bills.

Since

$5

bills are strictly more valuable for future transactions,

this greedy choice never reduces future possibilities.

Thus,

if the algorithm fails,

no valid change exists.

If it succeeds for every customer,

every customer has received correct change.

Therefore,

the algorithm is correct.

------------------------------------------------------------

Time Complexity:
----------------

Let

n

be the number of customers.

Each customer is processed exactly once.

Overall Time Complexity

O(n)

------------------------------------------------------------

Space Complexity:
-----------------

Only two integer counters are maintained.

Overall Auxiliary Space

O(1)

------------------------------------------------------------

Note:
-----

This is a classic

Greedy Algorithm

because every decision is made using only the current
information,

and the locally optimal choice

(using

$10 + $5

before

three $5 bills)

also leads to the globally optimal solution.

*/