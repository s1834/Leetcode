class Solution {
    public:
        int largestInteger(vector<int>& nums, int k) {
            unordered_map<int, int> mp;
            int n = nums.size();
            for(int i = 0; i <= n - k; i++) {
                unordered_set<int> s;
                for(int j = i; j < i + k; j++) s.insert(nums[j]);
                for(auto &x : s) mp[x]++;
            }
    
            int ans = -1;
            for(auto &x : mp) {
                if(x.second == 1) ans = max(ans, x.first);
            }
    
            return ans;
        }
    };

/*
LeetCode 3471. Find the Largest Almost Missing Integer

Approach:
---------

We are given an array nums and a window size k.

We consider every contiguous subarray of size k.

For each window, we want to know which numbers appear in that
window. A number is "almost missing" if it appears in exactly
ONE of all the size-k windows.

Finally, among all such numbers, return the largest one.

------------------------------------------------------------

Sliding Windows:
----------------

There are:

    n - k + 1

windows of size k.

For example:

    nums = [1, 2, 3, 2]
    k = 2

The windows are:

    [1, 2]
    [2, 3]
    [3, 2]

We process each of these windows one by one.

------------------------------------------------------------

Why Use a Set for Each Window?
------------------------------

Inside each window:

    unordered_set<int> s;

we insert every number:

    for(int j = i; j < i + k; j++)
        s.insert(nums[j]);

The important reason for using a set is that we only care
whether a number appears in the window or not.

We do NOT want to count multiple occurrences of the same
number inside the same window multiple times.

For example:

    window = [2, 2, 3]

The set becomes:

    {2, 3}

We want to count this window only once for 2, even though 2
appears twice inside it.

------------------------------------------------------------

Count In How Many Windows Each Number Appears:
-----------------------------------------------

After building the set for the current window:

    for(auto &x : s) mp[x]++;

Here:

    mp[x]

represents:

    "In how many size-k windows does x appear?"

For example, if:

    mp[5] = 1

then 5 appears in exactly one window.

If:

    mp[5] = 3

then 5 appears in three different windows.

------------------------------------------------------------

Why We Count Windows, Not Occurrences:
---------------------------------------

This is an important distinction.

Suppose:

    nums = [5, 5, 2]
    k = 2

The first window is:

    [5, 5]

Even though 5 occurs twice, it appears in only ONE window.

Using the set:

    {5}

ensures:

    mp[5]++

happens only once for that window.

------------------------------------------------------------

Finding the Answer:
-------------------

After processing all windows:

    int ans = -1;

We check every number:

    for(auto &x : mp) {
        if(x.second == 1)
            ans = max(ans, x.first);
    }

We only consider numbers that appeared in exactly one window:

    x.second == 1

Among them, we want the largest value:

    ans = max(ans, x.first);

If no number satisfies this condition, ans remains:

    -1

------------------------------------------------------------

Example:
--------

nums = [1, 2, 3, 2]
k = 2

Windows:

    [1, 2]
    [2, 3]
    [3, 2]

Process first window:

    {1, 2}

So:

    mp[1] = 1
    mp[2] = 1

Second window:

    {2, 3}

Now:

    mp[2] = 2
    mp[3] = 1

Third window:

    {3, 2}

Now:

    mp[3] = 2
    mp[2] = 3

Final counts:

    1 -> 1
    2 -> 3
    3 -> 2

Only 1 appears in exactly one window.

Therefore:

    answer = 1

------------------------------------------------------------

Window Loop:
------------

    for(int i = 0; i <= n - k; i++)

The starting index of a size-k window can range from:

    0

up to:

    n - k

For example:

    n = 5
    k = 3

The windows start at:

    i = 0
    i = 1
    i = 2

So:

    i <= n - k

correctly processes all windows.

------------------------------------------------------------

Inner Loop:
------------

    for(int j = i; j < i + k; j++)

This processes exactly k elements:

    i
    i + 1
    ...
    i + k - 1

So each iteration creates one contiguous window of size k.

------------------------------------------------------------

Why Not Just Count nums[j] Directly?
-------------------------------------

If we did:

    mp[nums[j]]++;

directly for every element, duplicate values inside the same
window would be counted multiple times.

But the problem is about whether a number occurs in a window,
not how many times it occurs inside that window.

Therefore, we first create:

    unordered_set<int> s

and then update mp using the unique values from that window.

------------------------------------------------------------

Overall Flow:
-------------

        Generate every size-k window
                    |
                    ↓
          Put window values in set
                    |
                    ↓
       Each unique value appears in
          this window -> mp[x]++
                    |
                    ↓
        Process all windows
                    |
                    ↓
       Find values with mp[x] == 1
                    |
                    ↓
        Take the maximum such value
                    |
                    ↓
                 answer

------------------------------------------------------------

Key Difference Between s and mp:
---------------------------------

There are two different jobs:

    s

is temporary and belongs to ONE window.

It answers:

    "Which unique numbers are present in this window?"

While:

    mp

is maintained across ALL windows.

It answers:

    "In how many windows does this number appear?"

For example:

    Window 1 -> s = {1, 2}
    Window 2 -> s = {2, 3}

After processing both:

    mp[1] = 1
    mp[2] = 2
    mp[3] = 1

------------------------------------------------------------

Complexity:
-----------

There are:

    O(n - k + 1)

windows.

For every window, we process k elements to build the set.

So:

    Time Complexity: O((n - k + 1) * k)

which is:

    O(n * k)

in the worst case.

The set for one window can contain at most k distinct values,
and mp can contain up to n distinct values.

Therefore:

    Space Complexity: O(n)

for the map and:

    O(k)

for the temporary set.

Overall:

    Space Complexity: O(n + k)

which is O(n) in terms of the input size.

------------------------------------------------------------

Main Pattern to Remember:
--------------------------

The key idea is:

    "Count in how many WINDOWS a number appears."

Not:

    "Count how many times a number appears."

So:

    For every window
        ↓
    Remove duplicates using a set
        ↓
    Increase mp[x] once for every unique x
        ↓
    Find mp[x] == 1
        ↓
    Return the largest such x

The set is what prevents duplicate occurrences of the same
number inside one window from incorrectly increasing its count.
*/