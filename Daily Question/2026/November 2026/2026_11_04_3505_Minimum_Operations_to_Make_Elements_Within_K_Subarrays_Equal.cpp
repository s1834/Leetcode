class Solution {
    private:
        // Calculates the minimum cost to make every contiguous subarray of length x equal.
        vector<long long> getCosts(const vector<int>& nums, int x) {
            int n = nums.size();
    
            // ops[i] = minimum cost to make the window ending at index i (inclusive) equal.
            vector<long long> ops(n);
    
            // left  = smaller half of current window
            // right = larger half of current window
            multiset<int> left, right;
    
            // Maintain the sum of both halves.
            long long sumL = 0, sumR = 0;
    
            // Sliding window: expand one element at a time.
            for (int i = 0; i < n; i++) {
                int v = nums[i];
    
                // STEP 1: Insert the new element.
                if (left.empty() || v <= *left.rbegin()) {
                    left.insert(v);
                    sumL += v;
                } else {
                    right.insert(v);
                    sumR += v;
                }
    
                // STEP 2: Remove the element that is no longer part of the current window.
                if (i >= x) {
                    v = nums[i - x];
    
                    // First check whether the element exists in left.
                    auto it = left.find(v);
                    if (it != left.end()) {
                        sumL -= v;
                        left.erase(it);
                    } else {
                        it = right.find(v);
                        sumR -= v;
                        right.erase(it);
                    }
                }
    
                // STEP 3: Rebalance the two multisets.
                if (left.size() > right.size() + 1) {
                    auto it = prev(left.end());
                    v = *it;
                    right.insert(v);
                    left.erase(it);
                    sumL -= v;
                    sumR += v;
                } else if (left.size() < right.size()) {
                    auto it = right.begin();
                    v = *it;
                    left.insert(v);
                    right.erase(it);
                    sumL += v;
                    sumR -= v;
                }
    
                // STEP 4: Calculate cost once the window has at least x elements.
                if (i >= x - 1) {
                    // Median is the maximum element in left.
                    long long mid = *left.rbegin();
    
                    // Cost of converting all left elements to median.
                    long long leftCost = mid * (long long)left.size() - sumL;
    
                    // Cost of converting all right elements to median.
                    long long rightCost = sumR - mid * (long long)right.size();
    
                    // Total minimum cost for this window.
                    ops[i] = leftCost + rightCost;
                }
            }
    
            return ops;
        }
    
    
    public:
    
        long long minOperations(vector<int>& nums, int x, int k) {
            int n = nums.size();
    
            // STEP 1: Calculate the minimum cost of every window of size x.
            vector<long long> ops = getCosts(nums, x);
    
            // STEP 2: Dynamic programming.
            vector<long long> pre(n + 1, 0); // pre[i] = minimum cost to select j-1 non-overlapping windows from first i elements.
            vector<long long> cur(n + 1, LLONG_MAX); // cur[i] = minimum cost to select j non-overlapping windows from first i elements.
    
            // Select exactly k windows.
            for (int j = 1; j <= k; j++) {
                // Reset current DP row.
                fill(cur.begin(), cur.end(), LLONG_MAX);
    
                // We need at least j*x elements to select j windows.
                for (int i = j * x; i <= n; i++) {
                    // OPTION 1: Do not select a window ending at i-1.
                    cur[i] = cur[i - 1];
    
                    // OPTION 2: Select the window of length x ending at i-1.
                    cur[i] = min(cur[i], pre[i - x] + ops[i - 1]);
                }
    
                // Move to the next DP iteration.
                pre.swap(cur);
            }
    
            // Minimum cost to select exactly k non-overlapping windows from the entire array.
            return pre[n];
        }
    };

/*
Problem: LeetCode 3505 - Minimum Operations to Make Elements Within K Subarrays Equal

Approach: Sliding Window + Two Multisets + Dynamic Programming

Intuition:
----------
We need to select exactly k non-overlapping subarrays, each of
length x, and make all elements within every selected subarray
equal.

The goal is to minimize the total number of operations.

The solution separates the problem into two parts:

1. Calculate the minimum cost of making every window of length x
   equal.
2. Use dynamic programming to select exactly k non-overlapping
   windows with minimum total cost.

For the first part, we use two multisets to maintain the median
of the current sliding window efficiently.

The median minimizes the sum of absolute differences, so making
all elements equal to the median gives the minimum cost.

--------------------------------------------------
PART 1: getCosts() - Sliding Window + Median
--------------------------------------------------

vector<long long> getCosts(const vector<int>& nums, int x)

This function calculates the minimum cost of making every
contiguous subarray of length x equal.

The result is stored in ops, where:

    ops[i] = Minimum cost of making the window
             [i - x + 1, i] equal.

Only indices i >= x - 1 represent complete windows.

--------------------------------------------------
1. Initialize the Sliding Window
--------------------------------------------------

int n = nums.size();

vector<long long> ops(n);

ops stores the minimum equalization cost for each window
ending at a particular index.

We use two multisets:

    multiset<int> left, right;

Their purpose is to maintain the current window in sorted
halves.

- left contains the smaller half of the window.
- right contains the larger half of the window.

The median is maintained as the maximum element of left.

We also maintain their sums:

    long long sumL = 0, sumR = 0;

- sumL = Sum of all elements in left.
- sumR = Sum of all elements in right.

Maintaining these sums allows us to calculate the cost
without iterating over the entire window.

--------------------------------------------------
2. Insert the New Element
--------------------------------------------------

int v = nums[i];

if (left.empty() || v <= *left.rbegin()) {
    left.insert(v);
    sumL += v;
} else {
    right.insert(v);
    sumR += v;
}

For every new index i, insert nums[i] into the appropriate
multiset.

*left.rbegin() gives the maximum element in left.

If the new value is smaller than or equal to this maximum,
insert it into left.

Otherwise, insert it into right.

Update the corresponding sum whenever an element is inserted.

This maintains the ordering property:

    Every element in left <= every element in right.

--------------------------------------------------
3. Remove the Element Outside the Sliding Window
--------------------------------------------------

if (i >= x) {
    v = nums[i - x];

    auto it = left.find(v);

    if (it != left.end()) {
        sumL -= v;
        left.erase(it);
    } else {
        it = right.find(v);
        sumR -= v;
        right.erase(it);
    }
}

Once i >= x, the current window already contains x elements.

The element at index:

    i - x

is no longer part of the current window.

We first search for it in left.

If found:
- Subtract its value from sumL.
- Erase that particular iterator from left.

Otherwise:
- Find it in right.
- Subtract its value from sumR.
- Erase it from right.

We use multiset because duplicate values are allowed.

Using erase(it) removes only one occurrence, unlike
erase(value), which removes all occurrences of that value.

--------------------------------------------------
4. Rebalance the Two Multisets
--------------------------------------------------

if (left.size() > right.size() + 1) {

    auto it = prev(left.end());
    v = *it;

    right.insert(v);
    left.erase(it);

    sumL -= v;
    sumR += v;

}

If left contains more than one extra element compared
to right, move the maximum element of left into right.

This maintains the size balance.

The second condition:

else if (left.size() < right.size()) {

    auto it = right.begin();
    v = *it;

    left.insert(v);
    right.erase(it);

    sumL += v;
    sumR -= v;

}

If right contains more elements than left, move the
minimum element of right into left.

After rebalancing, the size invariant is:

    left.size() == right.size()

or

    left.size() == right.size() + 1

The ordering invariant is also maintained:

    max(left) <= min(right)

Therefore, the maximum element in left is the median
of the current window.

For an even-sized window, this chooses the lower median.
Either middle value minimizes the sum of absolute differences.

--------------------------------------------------
5. Calculate the Cost of the Current Window
--------------------------------------------------

if (i >= x - 1) {

    long long mid = *left.rbegin();

    We calculate the cost only when the current window
    contains at least x elements.

    The median is:

        mid = max(left)

    leftCost = mid * left.size() - sumL;

    rightCost = sumR - mid * right.size();

    ops[i] = leftCost + rightCost;
}

Why does this formula work?

The minimum number of operations required to make all
elements equal to a value mid is:

    Σ |nums[j] - mid|

Since every element in left is <= mid:

    leftCost = Σ (mid - nums[j])

Expanding:

    leftCost = mid * left.size() - sumL

Similarly, every element in right is >= mid:

    rightCost = Σ (nums[j] - mid)

Expanding:

    rightCost = sumR - mid * right.size()

Therefore:

    Total Cost = leftCost + rightCost

This gives the minimum cost of making the current window
equal to its median.

Finally, the function returns ops.

--------------------------------------------------
PART 2: minOperations() - Dynamic Programming
--------------------------------------------------

long long minOperations(vector<int>& nums, int x, int k)

Now that we know the minimum cost of every window of
length x, we need to select exactly k non-overlapping
windows with minimum total cost.

--------------------------------------------------
6. Calculate All Window Costs
--------------------------------------------------

vector<long long> ops = getCosts(nums, x);

ops[i] represents the minimum cost of making the window
ending at index i equal.

For example, if:

    nums = [1, 3, 5, 2]
    x = 2

The windows are:

    [1, 3] -> cost = 2
    [3, 5] -> cost = 2
    [5, 2] -> cost = 3

Their costs are stored at their corresponding ending
indices.

--------------------------------------------------
7. Initialize DP Arrays
--------------------------------------------------

vector<long long> pre(n + 1, 0);

vector<long long> cur(n + 1, LLONG_MAX);

We use space-optimized DP.

The states are:

    pre[i] = Minimum cost to select exactly j - 1
             non-overlapping windows from the first i elements.

    cur[i] = Minimum cost to select exactly j
             non-overlapping windows from the first i elements.

Here, j is the current number of windows being selected.

Initially, j = 0.

Therefore:

    pre[i] = 0

for every i, because selecting zero windows costs zero.

cur is initialized to LLONG_MAX to represent an
unreachable or uncomputed state.

--------------------------------------------------
8. Select Exactly k Windows
--------------------------------------------------

for (int j = 1; j <= k; j++) {

We iterate over the number of windows we want to select.

For every j, we calculate the minimum cost of selecting
exactly j non-overlapping windows.

--------------------------------------------------
9. Reset the Current DP Row
--------------------------------------------------

fill(cur.begin(), cur.end(), LLONG_MAX);

Every DP iteration represents a new value of j.

Therefore, we reset cur before calculating the states
for the current number of selected windows.

--------------------------------------------------
10. Iterate Over Valid Prefix Lengths
--------------------------------------------------

for (int i = j * x; i <= n; i++)

We need at least j * x elements to select j windows,
because every window has length x and windows cannot overlap.

Therefore, the DP starts from:

    i = j * x

and continues until n.

--------------------------------------------------
11. Option 1: Skip the Current Element
--------------------------------------------------

cur[i] = cur[i - 1];

We do not select a window ending at index i - 1.

Instead, we use the best answer obtained by considering
only the first i - 1 elements.

This means:

    cur[i] = Minimum cost for j windows
             using the first i - 1 elements.

--------------------------------------------------
12. Option 2: Select a Window Ending at i - 1
--------------------------------------------------

cur[i] = min(cur[i], pre[i - x] + ops[i - 1]);

We select the window of length x ending at index i - 1.

Its starting index is:

    i - x

Its ending index is:

    i - 1

Its minimum equalization cost is:

    ops[i - 1]

To ensure non-overlapping windows, the previous j - 1
windows must be selected entirely from the first i - x
elements.

The minimum cost of doing that is:

    pre[i - x]

Therefore, the total cost when selecting this window is:

    pre[i - x] + ops[i - 1]

We take the minimum between:
- Skipping the current element.
- Selecting a window ending at the current element.

The recurrence is:

    cur[i] = min(
        cur[i - 1],
        pre[i - x] + ops[i - 1]
    )

--------------------------------------------------
13. Move to the Next DP Iteration
--------------------------------------------------

pre.swap(cur);

After calculating all states for the current j,
we make cur the previous DP row.

This allows the next iteration to calculate answers
for j + 1 windows.

Using swap avoids maintaining a complete 2D DP table.

--------------------------------------------------
14. Return the Final Answer
--------------------------------------------------

return pre[n];

After completing all k iterations:

    pre[n]

represents the minimum cost of selecting exactly k
non-overlapping windows from the entire array.

This is the required answer.

--------------------------------------------------
15. Example Walkthrough
--------------------------------------------------

Consider:

    nums = [1, 3, 5, 2]
    x = 2
    k = 2

First, calculate the cost of every window of length 2.

Window [1, 3]:

    Median = 1 or 3
    Cost = |1 - 1| + |3 - 1| = 2

Window [3, 5]:

    Median = 3 or 5
    Cost = |3 - 3| + |5 - 3| = 2

Window [5, 2]:

    Median = 2
    Cost = |5 - 2| + |2 - 2| = 3

Now consider selecting exactly 2 non-overlapping windows.

Since each window has length 2 and the array has 4 elements,
the only possible selection is:

    [1, 3] and [5, 2]

Total cost:

    2 + 3 = 5

The DP finds this minimum cost by combining the individual
window costs while ensuring that selected windows do not overlap.

--------------------------------------------------
16. Complexity Analysis
--------------------------------------------------

Let:
    n = Number of elements
    x = Window length
    k = Number of non-overlapping windows to select

Sliding Window + Two Multisets:

For each element:
- Insert into a multiset: O(log n)
- Remove from a multiset: O(log n)
- Rebalance: O(log n)
- Calculate window cost: O(1)

Total:

    O(n log n)

Dynamic Programming:

There are k DP iterations.

Each iteration processes at most n states.

Each state performs O(1) work.

Total:

    O(n * k)

Overall Time Complexity:

    O(n log n + n * k)

Space Complexity:

    O(n)

- ops stores n window costs.
- The two multisets together store at most x elements.
- pre and cur each contain n + 1 elements.

--------------------------------------------------
Core Idea:
----------
Break the problem into two independent parts:

1. Sliding Window + Median:
   Calculate the minimum cost of making every window of
   length x equal.

   Two multisets maintain the lower and upper halves of
   the current window, allowing median-based costs to be
   calculated efficiently.

2. Dynamic Programming:
   Select exactly k non-overlapping windows with minimum
   total cost.

   At every DP state, either:
   - Skip the current element.
   - Select the window ending at the current element and
     combine its cost with the best solution before it.

The final answer is pre[n].
*/