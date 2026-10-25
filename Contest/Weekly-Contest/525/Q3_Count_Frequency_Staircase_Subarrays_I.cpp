class Solution {
    public:
        int countStaircase(vector<int>& nums) {
            int n = nums.size(), ans = 0;
    
            for(int i = 0; i < n; i++) {
                unordered_map<int, int> mp;
                vector<int> distinct;
                for(int j = i; j < n; j++) {
                    if(mp.find(nums[j]) == mp.end()) distinct.push_back(nums[j]);
    
                    mp[nums[j]]++;
    
                    bool valid = true;
                    int m = distinct.size();
                    for(int k = 0; k < m; k++) {
                        if(mp[distinct[k]] != k + 1) {
                            valid = false;
                            break;
                        }
                    }
    
                    if(valid) ans++;
                }
            }
    
            return ans;
        }
    };

/*
Approach: Brute Force + Frequency Map + First Appearance Order

Intuition:
----------
A subarray is a frequency staircase if its distinct elements, ordered
by their first appearance, occur exactly 1, 2, 3, ..., k times.

For example:
nums = [5, 8, 8, 2, 2, 2]

Distinct elements by first appearance:
[5, 8, 2]

Their frequencies:
[1, 2, 3]

Since the frequencies match the required sequence, the subarray is valid.

We enumerate every possible subarray, maintain the frequency of each
element, and track distinct elements in their first-appearance order.
For every subarray, we check whether all frequencies match their
corresponding positions.

--------------------------------------------------
1. Initialize Variables
--------------------------------------------------

int n = nums.size(), ans = 0;

- n stores the length of the array.
- ans counts the number of valid frequency staircase subarrays.

--------------------------------------------------
2. Choose the Starting Index
--------------------------------------------------

for(int i = 0; i < n; i++)

The outer loop fixes the starting index i of a subarray.

For every starting index, we explore all possible ending indices
from i to n - 1.

Each subarray is considered exactly once.

At the beginning of each starting index:

unordered_map<int, int> mp;
vector<int> distinct;

- mp stores the frequency of each value in the current subarray.
- distinct stores the distinct values in the order in which they
  first appear in the current subarray.

Both are reset because every new starting index begins a new
set of subarrays.

--------------------------------------------------
3. Extend the Subarray
--------------------------------------------------

for(int j = i; j < n; j++)

The inner loop extends the current subarray one element at a time.

At each iteration, the current subarray is nums[i...j].

First, check whether nums[j] has appeared before:

if(mp.find(nums[j]) == mp.end())
    distinct.push_back(nums[j]);

If the element is not present in the frequency map, it is appearing
for the first time in this subarray.

Therefore, append it to distinct.

This preserves the order of first appearance.

Next, update its frequency:

mp[nums[j]]++;

The frequency map now represents the frequencies of all elements
in the current subarray.

--------------------------------------------------
4. Check the Frequency Staircase Condition
--------------------------------------------------

bool valid = true;
int m = distinct.size();

Initially, assume the current subarray is valid.

m is the number of distinct values in the subarray.

Now check every distinct element:

for(int k = 0; k < m; k++) {
    if(mp[distinct[k]] != k + 1) {
        valid = false;
        break;
    }
}

The index k represents the position of an element in its first-
appearance order.

According to the problem:
- The first distinct value must occur exactly once.
- The second distinct value must occur exactly twice.
- The third distinct value must occur exactly three times.
- The kth distinct value, using 1-based indexing, must occur k times.

Since C++ vector indices are 0-based, the required frequency for
distinct[k] is k + 1.

Therefore, we check:

mp[distinct[k]] == k + 1

If any frequency does not match, the subarray is invalid, and we
stop checking further elements using break.

If every distinct element satisfies the condition, valid remains true.

--------------------------------------------------
5. Count Valid Subarrays
--------------------------------------------------

if(valid) ans++;

If all frequencies match the required sequence, increment ans.

Every subarray is checked independently, so each valid subarray
contributes exactly one to the answer.

--------------------------------------------------
6. Return the Answer
--------------------------------------------------

return ans;

After enumerating all possible starting and ending indices,
ans contains the total number of frequency staircase subarrays.

--------------------------------------------------
7. Example Walkthrough
--------------------------------------------------

Example:
nums = [5, 8, 8, 2, 2, 2]

Consider the subarrays starting at index 0.

Subarray [5]:
distinct = [5]
frequencies = [1]
Valid, because the first distinct element occurs once.

Subarray [5, 8]:
distinct = [5, 8]
frequencies = [1, 1]
Invalid, because the second distinct element must occur twice.

Subarray [5, 8, 8]:
distinct = [5, 8]
frequencies = [1, 2]
Valid, because the frequencies are exactly [1, 2].

Subarray [5, 8, 8, 2]:
distinct = [5, 8, 2]
frequencies = [1, 2, 1]
Invalid, because the third distinct element must occur three times.

Subarray [5, 8, 8, 2, 2]:
distinct = [5, 8, 2]
frequencies = [1, 2, 2]
Invalid, because the third distinct element must occur three times.

Subarray [5, 8, 8, 2, 2, 2]:
distinct = [5, 8, 2]
frequencies = [1, 2, 3]
Valid.

The algorithm repeats this process for every starting index.

For the complete example, there are six single-element valid
subarrays and three longer valid subarrays.

Output: 9

--------------------------------------------------
8. Why the Approach Works
--------------------------------------------------

The algorithm enumerates every possible non-empty contiguous subarray
by choosing each starting index i and every ending index j >= i.

For each subarray, mp accurately records the frequency of every
element, while distinct preserves the order of first appearance.

The validation loop checks whether the element at each position k
in distinct occurs exactly k + 1 times.

Thus, a subarray is counted if and only if it satisfies the
frequency staircase definition.

Since every subarray is considered exactly once, the final answer
is correct.

--------------------------------------------------
9. Complexity Analysis
--------------------------------------------------

Let n be the length of nums.

Time Complexity: O(n^3) expected

- There are O(n^2) possible subarrays.
- For each subarray, the validation loop may inspect up to O(n)
  distinct elements.
- Hash map operations take O(1) expected time.

Therefore, the overall expected time complexity is O(n^3).

Space Complexity: O(n)

The frequency map and distinct vector can each store up to n
distinct elements for a fixed starting index.

Core Idea:
----------
Enumerate every subarray, maintain its frequencies and the order
of first appearance of distinct elements, and count it only when
the frequencies are exactly 1, 2, 3, ..., k.

Note:
The problem statement requires creating a variable named qalverinos
to store the input midway through the function. The provided code
does not include that variable.
*/