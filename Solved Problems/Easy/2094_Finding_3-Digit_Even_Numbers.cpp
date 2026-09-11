class Solution {
    public:
        vector<int> findEvenNumbers(vector<int>& digits) {
            vector<int> v(10, 0);
            for(auto &digit : digits) v[digit]++;
    
            vector<int> result;
            for(int i = 1; i <= 9; i++) { // Hundred's Place (1 - 9)
                if(v[i] == 0) continue;
                v[i]--;
                for(int j = 0; j <= 9; j++) { // Ten's Place (0 - 9)
                    if(v[j] == 0) continue;
                    v[j]--;  
                    for(int k = 0; k <= 8; k += 2) { // One's Place (0, 2, 4, 6, 8)
                        if(v[k] == 0) continue;
                        result.push_back((i * 100) + (j * 10) + k);
                    }
                    v[j]++;
                }
                v[i]++;
            }
    
            return result;
        }
    };

/*
LeetCode 2094. Finding 3-Digit Even Numbers

Approach:
---------

The goal is to form every possible 3-digit even number using the
given digits.

A valid number must satisfy:

    1. It has exactly 3 digits.
    2. The hundreds digit cannot be 0.
    3. The digits must be available in the input with the correct
       frequency.
    4. The units digit must be even.

We use a frequency array to keep track of how many times each digit
appears.

    v[digit] = frequency of digit

This is important because the same digit may appear multiple times
in the input.

For example:

    digits = [2, 2, 4]

We can form:

    224

because digit 2 appears twice.

But if:

    digits = [2, 4, 5]

we cannot form 224 because there is only one 2.

------------------------------------------------------------

Step 1: Count Frequency of Every Digit
--------------------------------------

    vector<int> v(10, 0);

    for(auto &digit : digits)
        v[digit]++;

Since digits are only from 0 to 9, a fixed array of size 10 is
enough.

------------------------------------------------------------

Step 2: Choose the Hundreds Digit
---------------------------------

The hundreds digit cannot be 0, otherwise the number would not be
a 3-digit number.

Therefore:

    for(int i = 1; i <= 9; i++)

Here:

    i = hundreds digit

We first check whether this digit is available:

    if(v[i] == 0) continue;

Then temporarily consume one occurrence:

    v[i]--;

This is important because the same digit may need to be used again
for the tens or units position, and we must respect its frequency.

------------------------------------------------------------

Step 3: Choose the Tens Digit
-----------------------------

The tens digit can be anything from 0 to 9.

    for(int j = 0; j <= 9; j++)

We again check whether this digit is available:

    if(v[j] == 0) continue;

Then consume one occurrence:

    v[j]--;

At this point:

    i = hundreds digit
    j = tens digit

------------------------------------------------------------

Step 4: Choose the Units Digit
------------------------------

For the number to be even, its last digit must be one of:

    0, 2, 4, 6, 8

Therefore:

    for(int k = 0; k <= 8; k += 2)

We check whether the required even digit is available:

    if(v[k] == 0) continue;

If it is available, we have successfully formed a valid
3-digit even number.

------------------------------------------------------------

Construct the Number
---------------------

The number is:

    (i * 100) + (j * 10) + k

For example:

    i = 1
    j = 2
    k = 4

Number:

    100 + 20 + 4
    = 124

We add it to result:

    result.push_back((i * 100) + (j * 10) + k);

------------------------------------------------------------

Why Don't We Decrease v[k]?
---------------------------

Notice that we do NOT do:

    v[k]--;

This is because we are only using k to generate the current
candidate number.

After generating the number, we immediately move to the next
possible units digit.

Since the hundreds and tens digits have already been temporarily
removed from the frequency array, v[k] correctly tells us whether
another occurrence of k was available for the units position.

There is no need to restore k because we never permanently modify it.

------------------------------------------------------------

Backtracking
------------

After finishing all possible units digits for the current tens
digit, we restore the tens digit:

    v[j]++;

This allows the same digit to be considered for another candidate.

Similarly, after finishing all possible tens digits for the current
hundreds digit, we restore the hundreds digit:

    v[i]++;

This gives us the original frequency array before trying the next
hundreds digit.

So the structure is:

    Choose hundreds
        |
        v
    Remove hundreds
        |
        v
    Choose tens
        |
        v
    Remove tens
        |
        v
    Choose even units
        |
        v
    Create number
        |
        v
    Restore tens
        |
        v
    Restore hundreds

------------------------------------------------------------

Example:
---------

    digits = [1, 2, 3, 0]

Possible hundreds digits:

    1, 2, 3

Suppose:

    i = 1

Now choose tens digit.

Suppose:

    j = 2

Remaining digits are:

    0, 3

The units digit must be even.

Only:

    0

is available.

Therefore:

    120

is a valid number.

------------------------------------------------------------

Handling Duplicate Digits
--------------------------

The frequency array automatically handles duplicates.

For example:

    digits = [1, 1, 2, 2, 4]

When we choose:

    i = 1

we decrease:

    v[1]--

There is still another 1 available.

Therefore, the number:

    112

can be formed if the required digits are available.

This avoids incorrectly using a digit more times than it occurs
in the input.

------------------------------------------------------------

Why Do We Return result.size()?
--------------------------------

Every valid 3-digit even number is pushed into result.

Therefore:

    result.size()

is exactly the number of distinct valid numbers that can be formed.

Even if the same number can be formed using different copies of
the same digit, it is pushed only once for a particular digit
combination because we iterate over the digit values rather than
individual indices.

------------------------------------------------------------

Algorithm:
----------

    1. Create a frequency array for digits 0-9.

    2. Try every possible hundreds digit from 1 to 9.

    3. Temporarily remove that digit.

    4. Try every possible tens digit from 0 to 9.

    5. Temporarily remove that digit.

    6. Try every possible even units digit:
           0, 2, 4, 6, 8

    7. If the units digit is available, construct the number and
       store it.

    8. Restore the tens digit.

    9. Restore the hundreds digit.

    10. Return the number of valid numbers.

------------------------------------------------------------

Time Complexity:
----------------

There are at most:

    9 choices for hundreds digit
    10 choices for tens digit
    5 choices for units digit

Therefore:

    O(9 * 10 * 5)

which is effectively:

    O(1)

because the number of possible digits is fixed.

------------------------------------------------------------

Space Complexity:
-----------------

Frequency array:

    O(10)

Result can contain at most all 3-digit even numbers from 100 to
998, so the result size is bounded by a constant.

Ignoring the output array:

    O(1)

Including the output:

    O(number of valid answers)

------------------------------------------------------------

Core Idea:
----------

Use a frequency array to handle duplicate digits, then try:

    Hundreds -> 1 to 9
    Tens     -> 0 to 9
    Units    -> 0, 2, 4, 6, 8

while temporarily decreasing the frequency of selected digits.

The key conditions are:

    Hundreds != 0
    Units % 2 == 0
    Every digit must be available in sufficient quantity.
*/