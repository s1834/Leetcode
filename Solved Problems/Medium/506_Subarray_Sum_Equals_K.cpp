class Solution {
    public:
        int subarraySum(vector<int>& nums, int k) {
            unordered_map<int, int> prefix;
            int ans = 0, sum = 0;
            prefix[sum]++;
            for(auto x : nums) {
                sum += x;
                if(prefix.find(sum - k) != prefix.end()) ans += prefix[sum - k];
                prefix[sum]++;
            }
    
            return ans;
        }
    };

/*

Idea:
------
We need to count the number of subarrays whose sum is
exactly k.

A brute force approach would check every possible
subarray, resulting in O(n²) time.

Instead, we use Prefix Sums along with a Hash Map to
find the required subarrays in O(n) time.

------------------------------------------------------------

Key Observation:
----------------

Suppose

PrefixSum[i]

represents the sum of elements from index

0

to

i.

For a subarray

(l ... r)

its sum is

PrefixSum[r] - PrefixSum[l-1]

We need

PrefixSum[r] - PrefixSum[l-1] = k

Rearranging,

PrefixSum[l-1] = PrefixSum[r] - k

Therefore,

while processing the current prefix sum,

if we have already seen

(currentPrefixSum - k),

then every occurrence of that prefix sum represents one
valid subarray ending at the current index.

------------------------------------------------------------

Algorithm:
----------

1.

Maintain

sum

as the running prefix sum.

------------------------------------------------------------

2.

Use a hash map

prefix

where

prefix[x]

stores how many times the prefix sum

x

has appeared.

------------------------------------------------------------

3.

Initialize

prefix[0] = 1

This represents an empty prefix before the array begins,
allowing subarrays starting from index 0 to be counted.

------------------------------------------------------------

4.

Traverse the array.

For every element,

• Update the running prefix sum.

• Check whether

(sum - k)

already exists in the map.

If yes,

add its frequency to the answer since each occurrence
forms a valid subarray ending at the current position.

• Store the current prefix sum in the map.

------------------------------------------------------------

Why Does This Work?
-------------------

Suppose the current prefix sum is

S.

If an earlier prefix sum was

S - k,

then

Current Prefix Sum

-

Previous Prefix Sum

=

S - (S - k)

=

k

Hence,

the subarray between those two prefix sums has sum k.

If

(S - k)

appears multiple times,

each occurrence corresponds to a different valid
subarray.

------------------------------------------------------------

Example:
--------

nums = [1, 2, 3]

k = 3

Initially

prefix = {0 : 1}

----------------

After reading 1

sum = 1

Need

1 - 3 = -2

Not found.

Store

1

----------------

After reading 2

sum = 3

Need

3 - 3 = 0

Found once.

Answer = 1

Subarray

[1,2]

Store

3

----------------

After reading 3

sum = 6

Need

6 - 3 = 3

Found once.

Answer = 2

Subarray

[3]

------------------------------------------------------------

Example with Negative Numbers:
------------------------------

nums = [1, -1, 1]

k = 1

Prefix Sums

1

0

1

Notice that prefix sum

0

appears before the last element.

When the final prefix sum becomes

1,

we need

1 - 1 = 0,

which has occurred once.

This correctly counts the subarray

[1]

ending at the last index.

This demonstrates why the prefix-sum approach works even
when negative numbers are present, unlike the sliding
window technique.

------------------------------------------------------------

Time Complexity:
----------------

O(n)

Each element is processed once, and every hash map
operation is O(1) on average.

------------------------------------------------------------

Space Complexity:
-----------------

O(n)

In the worst case, every prefix sum is distinct and is
stored in the hash map.

*/