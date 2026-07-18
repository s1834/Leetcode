class Solution {
    public:
        long long gcdSum(vector<int>& nums) {
            int mx = nums[0], n = nums.size();
            for(int i = 0; i < n; i++) {
                if(nums[i] > mx) mx = nums[i];
                nums[i] = __gcd(nums[i], mx);
            }
    
            sort(nums.begin(), nums.end());
            long long sum = 0, left = 0;
            n--;
            while(left < n) {
                sum += __gcd(nums[left], nums[n]);
                left++;
                n--;
            }
    
            return sum;
        }
    };

/*

Idea:
------
Construct the prefixGcd array as described in the problem.

Instead of creating a separate array, reuse the input array
by replacing each element with

gcd(nums[i], maximum element seen so far).

After constructing the prefixGcd array,

sort it and repeatedly pair the smallest and largest
remaining elements.

The GCD of every formed pair contributes to the final answer.

------------------------------------------------------------

Algorithm:
----------

1.

Traverse the array while maintaining the maximum value
seen so far.

For every element,

update

prefixGcd[i] = gcd(nums[i], currentMaximum)

Store this value directly back into nums.

------------------------------------------------------------

2.

Sort the modified array (prefixGcd).

------------------------------------------------------------

3.

Use two pointers.

Left points to the smallest element.

Right points to the largest element.

------------------------------------------------------------

4.

Form pairs by taking

(nums[left], nums[right])

Add

gcd(nums[left], nums[right])

to the answer.

Move both pointers towards the center.

------------------------------------------------------------

5.

If the array size is odd,

the middle element remains unpaired and is ignored.

------------------------------------------------------------

Example:
--------

nums = [3,6,2,8]

Construct prefixGcd:

Maximums:

3

6

6

8

prefixGcd:

3

6

2

8

------------------------------------------------------------

Sort:

[2,3,6,8]

------------------------------------------------------------

Form pairs:

(2,8)

gcd = 2

(3,6)

gcd = 3

Answer:

2 + 3 = 5

------------------------------------------------------------

Time Complexity:
----------------

Construct prefixGcd:

O(n)

Sorting:

O(n log n)

Pairing:

O(n)

Overall:

O(n log n)

------------------------------------------------------------

Space Complexity:
-----------------

O(1)

The prefixGcd values are stored directly in the input array
and only a few extra variables are used.

(Excluding the space used by the sorting algorithm.)

*/