class Solution {
    private:
        int findMultiply(int num) {
            int mul = 1;
            while(num) {
                mul *= 10;
                num /= 10;
            }
            return mul;
        }
        
    public:
        int minMergedInteger(vector<int>& nums) {
            int ans = INT_MAX;
            int n = nums.size();
            for(int i = 0; i < n - 1; i += 2) ans = min(ans, (nums[i] * findMultiply(nums[i + 1])) + nums[i + 1]);
            return ans;
        }
    };

/*
Problem: LeetCode 4097

Approach: Greedy + Digit Count

Intuition:
----------
We need to merge two consecutive numbers into a single integer
by concatenating them.

For example:
    12 and 345

Merged integer:
    12345

To concatenate two numbers:
    first * 10^(number of digits in second) + second

The solution checks consecutive pairs at even indices and
returns the minimum merged integer among those pairs.

--------------------------------------------------
1. Helper Function: findMultiply()
--------------------------------------------------

int findMultiply(int num) {
    int mul = 1;

    while(num) {
        mul *= 10;
        num /= 10;
    }

    return mul;
}

This function calculates the smallest power of 10 greater
than the given number's digit range.

In other words, it returns 10 raised to the number of
digits in num.

Example:
    num = 7
    mul = 10

    num = 45
    mul = 100

    num = 123
    mul = 1000

This multiplier is used to shift the first number to the
left before appending the second number.

--------------------------------------------------
2. Initialize the Answer
--------------------------------------------------

int ans = INT_MAX;
int n = nums.size();

- ans stores the minimum merged integer found so far.
- n stores the size of the input array.

INT_MAX ensures that the first valid merged value will
replace the initial answer.

--------------------------------------------------
3. Iterate Through Consecutive Pairs
--------------------------------------------------

for(int i = 0; i < n - 1; i += 2)

The loop processes pairs of elements at indices:

    (0, 1), (2, 3), (4, 5), ...

The index increases by 2 because each iteration considers
the next consecutive pair without overlapping previously
processed pairs.

--------------------------------------------------
4. Merge the Two Numbers
--------------------------------------------------

(nums[i] * findMultiply(nums[i + 1])) + nums[i + 1]

Suppose:
    nums[i] = 12
    nums[i + 1] = 345

findMultiply(345) returns 1000.

Therefore:

    12 * 1000 + 345
    = 12000 + 345
    = 12345

This effectively concatenates the two numbers.

--------------------------------------------------
5. Update the Minimum Answer
--------------------------------------------------

ans = min(ans, mergedValue);

For every processed pair, calculate its merged integer
and update ans if the newly calculated value is smaller.

Finally, return ans.

--------------------------------------------------
6. Example Walkthrough
--------------------------------------------------

Input:
nums = [12, 34, 5, 67]

Initially:
    ans = INT_MAX

First pair: (12, 34)

    findMultiply(34) = 100

    merged = 12 * 100 + 34
           = 1234

    ans = 1234

Second pair: (5, 67)

    findMultiply(67) = 100

    merged = 5 * 100 + 67
           = 567

    ans = min(1234, 567)
        = 567

Final answer:
    567

--------------------------------------------------
7. Complexity Analysis
--------------------------------------------------

Let D be the maximum number of digits in an element.

Time Complexity: O(n * D)

- We process approximately n/2 pairs.
- findMultiply() takes O(D) time per pair.
- Updating the minimum takes O(1).

Space Complexity: O(1)

Only a constant number of extra variables are used.

Core Idea:
----------
Use a power of 10 based on the number of digits in the
second number to concatenate two integers:

    merged = first * 10^(digits(second)) + second

Process consecutive non-overlapping pairs and return
the minimum merged value.
*/