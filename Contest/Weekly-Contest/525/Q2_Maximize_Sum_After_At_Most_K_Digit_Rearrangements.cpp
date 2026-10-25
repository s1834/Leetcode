class Solution {
    public:
        long long maximizeSum(vector<int>& nums, int k) {
            int n = nums.size();
    
            vector<long long> increase;
            long long sum = 0;
            for(auto &num : nums) {
                sum += num;
    
                string s = to_string(num);
                sort(s.begin(), s.end(), greater<char>());
    
                long long rearranged = stoll(s);
                long long inc = rearranged - num;
    
                if(inc > 0) increase.push_back(inc);
            }
    
            sort(increase.begin(), increase.end(), greater<long long>());
    
            int m = min((int)increase.size(), k);
            for(int i = 0; i < m; i++) sum += increase[i];
    
            return sum;
        }
    };

/*
Approach: Greedy + Digit Sorting + Maximum Increment Selection

Intuition:
----------
We are given an integer array nums and can perform at most k operations.
In each operation, we choose one element and rearrange its decimal digits
to form a new integer.

Our goal is to maximize the total sum of the array.

The key observation is that arranging an element's digits in descending
order produces the largest possible number using those digits.

For each element, we calculate the maximum increase achievable by
rearranging its digits. We then choose the k elements with the largest
positive increases.

--------------------------------------------------
1. Initialize Variables
--------------------------------------------------

int n = nums.size();
vector<long long> increase;
long long sum = 0;

- n stores the number of elements.
- sum stores the original sum of the array.
- increase stores the positive gains achievable by rearranging
  individual elements.

We use long long for sum and the gains to safely handle large totals.

--------------------------------------------------
2. Calculate the Maximum Rearranged Value
--------------------------------------------------

for(auto &num : nums)

Process each element independently.

First, include its original value in the sum:

sum += num;

Next, convert the number to a string:

string s = to_string(num);

This allows us to rearrange its decimal digits using sorting.

Sort the digits in descending order:

sort(s.begin(), s.end(), greater<char>());

Placing the largest digit first, followed by the next-largest digits,
produces the maximum possible number from the same digits.

For example:
num = 123

Original string:
"123"

After descending sorting:
"321"

Convert the rearranged string back to an integer:

long long rearranged = stoll(s);

Here, stoll() converts the string into a long long integer.

--------------------------------------------------
3. Calculate the Increase
--------------------------------------------------

long long inc = rearranged - num;

The increase represents how much the total array sum improves if
we rearrange this particular element optimally.

For example:
num = 123
rearranged = 321

inc = 321 - 123 = 198

If the digits are already arranged optimally, the increase is zero.

If the increase is negative, rearranging the digits would decrease
the sum, so the operation should not be used on that element.

Therefore:

if(inc > 0) increase.push_back(inc);

Only positive increases are stored because the problem allows at most
k operations. We do not need to perform an operation that fails to
increase the sum.

--------------------------------------------------
4. Sort the Increases in Descending Order
--------------------------------------------------

sort(increase.begin(), increase.end(), greater<long long>());

After processing all elements, sort their positive gains from largest
to smallest.

This allows us to select the most beneficial operations first.

For example:
increase = [198, 27, 0, 45]

After storing only positive gains:
increase = [198, 27, 45]

After sorting:
increase = [198, 45, 27]

The first element provides the greatest improvement, followed by
the second-greatest improvement, and so on.

--------------------------------------------------
5. Select at Most k Operations
--------------------------------------------------

int m = min((int)increase.size(), k);

There may be fewer than k elements with positive gains.

Therefore, m is the smaller of:
- k, the maximum number of allowed operations.
- increase.size(), the number of beneficial operations available.

Now add the largest m gains to the original sum:

for(int i = 0; i < m; i++)
    sum += increase[i];

Each gain corresponds to rearranging one distinct array element.

Since the gains are sorted in descending order, selecting the first
m gains maximizes the total improvement.

--------------------------------------------------
6. Return the Maximum Sum
--------------------------------------------------

return sum;

The final sum equals the original sum plus the largest positive gains
from at most k elements.

--------------------------------------------------
7. Example Walkthrough
--------------------------------------------------

Example 1:
nums = [123, 45]
k = 1

Initially:
sum = 0
increase = []

Process 123:
- Original sum becomes 123.
- Rearranged value = 321.
- Increase = 321 - 123 = 198.
- Store 198.

sum = 123
increase = [198]

Process 45:
- Original sum becomes 168.
- Rearranged value = 54.
- Increase = 54 - 45 = 9.
- Store 9.

sum = 168
increase = [198, 9]

Sort the gains:
increase = [198, 9]

Select:
m = min(2, 1) = 1

Add the largest gain:
sum = 168 + 198 = 366

Output: 366

The best operation is rearranging 123 into 321.

--------------------------------------------------
8. Why the Greedy Strategy Works
--------------------------------------------------

Each operation affects exactly one array element, and the maximum
possible rearranged value of that element can be computed independently.

For each element, descending digit order produces its maximum value.
Therefore, its positive increase represents the greatest benefit
obtainable from operating on that element.

Since at most k operations are allowed, we should choose the k largest
positive increases, or all positive increases if fewer than k exist.

Choosing a smaller increase while leaving a larger increase unused
cannot produce a better total sum.

Thus, sorting the increases in descending order and taking the first
m gains maximizes the final sum.

--------------------------------------------------
9. Complexity Analysis
--------------------------------------------------

Let n be the number of elements and D the maximum number of digits
in an element.

For each number:
- Converting it to a string takes O(D).
- Sorting its digits takes O(D log D).
- Converting it back takes O(D).

Processing all elements takes O(n * D log D).

Sorting the positive increases takes O(n log n).

Overall Time Complexity:
O(n * D log D + n log n)

Since nums[i] <= 10^9, each number has at most 10 decimal digits.
Thus, D is bounded by a small constant, making the overall complexity
O(n log n).

Space Complexity:
O(n)

The increase vector can store up to n gains. The temporary digit
string requires O(D) space.

Core Idea:
----------
For every element, sort its digits in descending order to obtain the
maximum possible value, calculate the positive increase, sort all
increases from largest to smallest, and add the largest at most k
increases to the original sum.

Note:
The problem statement requires creating a variable named bremovilta
to store the input midway through the function. The provided code
does not include that variable.
*/