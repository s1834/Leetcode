class Solution {
    public:
        long long minimumMaxValue(int n, int index, int value) {
            if (value == 1) return -1;
    
            long long primeFactor = value;
            for(long long i = 2; i * i <= value; i++) {
                if(value % i == 0) {
                    primeFactor = i;
                    break;
                }
            }
    
            // check if enough space on left side
            if(2 * index > value - primeFactor) return -1;
    
            long long right = n - index - 1;
            if(right == 0) return value;
            return value + primeFactor + 2 * (right - 1);
        }
    };

/*
Problem: LeetCode 4098

Approach: Prime Factorization + Greedy Observation

Intuition:
----------
The solution tries to construct the maximum possible value
while satisfying the given constraints.

It uses the smallest prime factor of value to determine
whether the left side has enough space.

If the left-side condition is not satisfied, it returns -1.

Otherwise, it calculates the contribution from the right side
and returns the resulting maximum value.

--------------------------------------------------
1. Handle the Special Case
--------------------------------------------------

if (value == 1) return -1;

If value is 1, the function immediately returns -1 because
the solution requires a prime factor greater than 1.

--------------------------------------------------
2. Find the Smallest Prime Factor
--------------------------------------------------

long long primeFactor = value;

for(long long i = 2; i * i <= value; i++) {
    if(value % i == 0) {
        primeFactor = i;
        break;
    }
}

Initially, primeFactor is set to value.

We then check possible divisors starting from 2.

The first divisor found is the smallest prime factor
of value.

Why does this work?

- We iterate in increasing order.
- If a number has a divisor, it must have a prime factor
  no greater than its square root.
- Therefore, the first divisor found is its smallest
  prime factor.

If no divisor is found, value itself is prime, so
primeFactor remains equal to value.

Examples:

    value = 12  -> primeFactor = 2
    value = 15  -> primeFactor = 3
    value = 49  -> primeFactor = 7
    value = 13  -> primeFactor = 13

--------------------------------------------------
3. Check Whether the Left Side Has Enough Space
--------------------------------------------------

if(2 * index > value - primeFactor) return -1;

This condition checks whether the available value can
satisfy the requirement on the left side.

The available difference is:

    value - primeFactor

The required amount is:

    2 * index

If the required amount exceeds the available difference,
the function returns -1.

Otherwise, the construction can proceed.

--------------------------------------------------
4. Calculate the Number of Elements on the Right
--------------------------------------------------

long long right = n - index - 1;

This calculates how many positions exist to the right
of the given index.

For example:

    n = 6
    index = 2

    right = 6 - 2 - 1 = 3

There are three positions to the right.

--------------------------------------------------
5. Handle the Case With No Right-Side Elements
--------------------------------------------------

if(right == 0) return value;

If the given index is the last position, there are no
elements on its right.

Therefore, the function directly returns value.

--------------------------------------------------
6. Calculate the Final Answer
--------------------------------------------------

return value + primeFactor + 2 * (right - 1);

The result consists of three contributions:

- value: the initial value.
- primeFactor: the smallest prime factor found earlier.
- 2 * (right - 1): an additional contribution based on
  the number of positions to the right.

Since right represents the number of right-side positions,
the formula adds 2 for each position after the first one.

--------------------------------------------------
7. Complexity Analysis
--------------------------------------------------

Time Complexity: O(sqrt(value))

The prime-factor search checks divisors up to sqrt(value).

All remaining calculations take O(1).

Space Complexity: O(1)

Only a constant number of variables are used.

Core Idea:
----------
1. Find the smallest prime factor of value.
2. Check whether the left-side feasibility condition holds.
3. Count the positions on the right.
4. Calculate the answer using the prime factor and right-side
   contribution.

The function returns -1 when its feasibility checks fail.
*/