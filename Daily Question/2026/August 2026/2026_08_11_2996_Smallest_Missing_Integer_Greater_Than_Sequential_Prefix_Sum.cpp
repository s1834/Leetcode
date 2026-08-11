class Solution {
    public:
        int missingInteger(vector<int>& nums) {
            int num = nums[0], sum = nums[0], n = nums.size();
            for(int i = 1; i < n; i++) {
                if(nums[i] != num + 1) break;
                num++;
                sum += num;
            }
    
            set<int> s;
            for(auto &x : nums) s.insert(x);
    
            while(sum) {
                if(s.find(sum) == s.end()) return sum;
                sum++;
            }
    
            return -1;
        }
    };

/*
LeetCode 2996. Smallest Missing Integer Greater Than Sequential Prefix Sum

Idea:
------

We need to find the longest sequential prefix starting from
nums[0].

A sequential prefix means every next element is exactly one
greater than the previous element.

For example:

    nums = [3,4,5,1,2]

The sequential prefix is:

    [3,4,5]

because:

    3 -> 4 -> 5

but 5 -> 1 is not consecutive.

We first calculate the sum of this sequential prefix.

Then we need to find the smallest integer greater than or
equal to that sum which does not exist in nums.

------------------------------------------------------------

Step 1: Find the Sequential Prefix
-----------------------------------

We initialize:

    int num = nums[0];
    int sum = nums[0];

Here:

    num

represents the last number in the sequential prefix.

And:

    sum

stores the sum of all numbers in that prefix.

For example:

    nums = [3,4,5,1,2]

Initially:

    num = 3
    sum = 3

------------------------------------------------------------

Now we traverse from index 1:

    if(nums[i] != num + 1) break;

The next number must be exactly:

    num + 1

If it is,

we update:

    num++;

and add it to the sum:

    sum += num;

For:

    [3,4,5,1,2]

we get:

    3

then:

    4

then:

    5

At 1:

    1 != 5 + 1

so we stop.

Therefore:

    sequential prefix = [3,4,5]

and:

    sum = 3 + 4 + 5
        = 12

------------------------------------------------------------

Why Do We Need num?
--------------------

We need to know what the next expected value is.

Suppose:

    num = 5

Then the next number must be:

    6

So we check:

    nums[i] != num + 1

If the value is 6:

    continue

and update:

    num = 6

If it is anything else:

    break

because the sequential prefix has ended.

------------------------------------------------------------

Step 2: Store All Numbers in a Set
-----------------------------------

After finding the sequential prefix, we need to quickly check
whether a number exists in nums.

So we create:

    set<int> s;

and insert every number:

    for(auto &x : nums)
        s.insert(x);

Now:

    s.find(x)

can tell us whether x exists in the array.

------------------------------------------------------------

Why Use a Set?
--------------

Suppose:

    sum = 12

We need to check:

    Is 12 present?
    Is 13 present?
    Is 14 present?
    ...

until we find a missing value.

A set allows us to perform this lookup efficiently.

------------------------------------------------------------

Step 3: Find the Smallest Missing Integer
------------------------------------------

We start from:

    sum

and keep increasing it:

    while(sum) {

        if(s.find(sum) == s.end())
            return sum;

        sum++;
    }

If sum exists in the array,

we cannot return it.

So we try:

    sum + 1

Then:

    sum + 2

and so on.

The first value that does not exist is the answer.

------------------------------------------------------------

Example:
--------

nums = [3,4,5,1,2]

Sequential prefix:

    [3,4,5]

Sum:

    3 + 4 + 5 = 12

Set:

    {1,2,3,4,5}

Now check:

    12 -> missing

Therefore:

    answer = 12

------------------------------------------------------------

Another Example:
-----------------

nums = [1,2,3,2,5]

Sequential prefix:

    [1,2,3]

Sum:

    1 + 2 + 3 = 6

Set contains:

    1,2,3,5

Check:

    6 -> missing

Therefore:

    answer = 6

------------------------------------------------------------

Example Where We Need To Increment:
------------------------------------

Suppose:

    nums = [1,2,3,6,7]

Sequential prefix:

    [1,2,3]

Sum:

    6

But 6 already exists.

So:

    6 -> exists
    7 -> exists

Next:

    8 -> missing

Therefore:

    answer = 8

This is exactly what:

    while(sum)

does.

------------------------------------------------------------

Important Detail:
-----------------

The sequential prefix is determined only from the

beginning

of the array.

For example:

    nums = [1,2,4,3,5]

The prefix is:

    [1,2]

We stop at 4 because:

    4 != 2 + 1

Even though 3 exists later,

we do NOT continue.

The problem specifically asks for the sequential prefix
starting from nums[0].

------------------------------------------------------------

Why Does the Algorithm Work?
-----------------------------

There are two separate tasks:

1. Find the sequential prefix.

   We start from nums[0] and continue while every next number
   is exactly one greater than the previous number.

2. Find the smallest missing number starting from its sum.

   We check the sum itself, then increment it until we find a
   value that does not occur in nums.

Because we check the candidates in increasing order,

the first missing value is automatically the smallest possible
answer.

------------------------------------------------------------

Overall Flow:
-------------

nums

  ↓

Find longest sequential prefix

  ↓

Calculate its sum

  ↓

Put all nums into a set

  ↓

Start checking from prefix sum

  ↓

Does sum exist?

   Yes
    ↓
  sum++

   No
    ↓
 return sum

------------------------------------------------------------

Time Complexity:
----------------

Finding the sequential prefix:

    O(n)

Building the set:

    O(n log n)

Checking for the missing integer:

    O(k log n)

where k is the number of consecutive values starting from the
sum that already exist.

So overall:

    O(n log n)

in the worst case.

------------------------------------------------------------

Space Complexity:
-----------------

The set stores the elements of nums:

    O(n)

Therefore:

    O(n)

extra space.

------------------------------------------------------------

Main Concept to Remember:
--------------------------

This problem combines two simple ideas:

    1. Find a consecutive/sequential prefix
    2. Find the first missing value starting from its sum

The important condition is:

    nums[i] == num + 1

and after finding the prefix:

    sum = sum of prefix

then:

    while(sum exists)
        sum++;

The first number not present in the set is the answer.

*/