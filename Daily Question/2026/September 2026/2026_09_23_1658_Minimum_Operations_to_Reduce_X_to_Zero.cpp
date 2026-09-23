class Solution {
    public:
        int minOperations(vector<int>& nums, int x) {
            int n = nums.size();
    
            int total = 0;
            for(auto &num : nums) total += num;
            total -= x;
    
            int l = 0, r = 0, curr = 0, maxLength = -1;
            while (r < n) {
                curr += nums[r];
                r++;
    
                while (curr > total && l < r) {
                    curr -= nums[l];
                    l++;
                }
    
                if (curr == total)  maxLength = max(maxLength, r - l);
            }
    
            return (maxLength == -1) ? -1 : n - maxLength;
        }
    };

/*
    LeetCode 1658 - Minimum Operations to Reduce X to Zero
    ------------------------------------------------------------

    Approach:
    ------------------------------------------------------------

    Instead of directly finding which elements to REMOVE from the
    left and right, we find the longest contiguous subarray that
    we can KEEP.

    Let:

        totalSum = sum of all elements

    If the elements we remove must sum to x, then the elements
    that remain must have sum:

        totalSum - x

    Therefore, the problem becomes:

        Find the LONGEST contiguous subarray whose sum is
        totalSum - x.

    If that subarray has length maxLength, then everything outside
    it must be removed.

    Number of operations:

        n - maxLength


    ------------------------------------------------------------
    Key Observation:
    ------------------------------------------------------------

    Removing elements only from the two ends means that the elements
    left after all operations must form ONE contiguous subarray.

    Example:

        nums = [1, 1, 4, 2, 3]
        x = 5

    Total sum:

        1 + 1 + 4 + 2 + 3 = 11

    Required remaining sum:

        11 - 5 = 6

    The longest subarray with sum 6 is:

        [1, 1, 4]

    Its length is:

        3

    Therefore we remove:

        5 - 3 = 2 elements

    So the answer is:

        2


    ------------------------------------------------------------
    Step 1: Calculate the Target Sum
    ------------------------------------------------------------

        int total = 0;
        for(auto &num : nums)
            total += num;

    After calculating the complete array sum, we do:

        total -= x;

    Now `total` represents:

        sum of the subarray that we want to KEEP.


    ------------------------------------------------------------
    Step 2: Sliding Window
    ------------------------------------------------------------

    We use:

        l       -> left boundary
        r       -> right boundary
        curr    -> current window sum
        maxLength -> longest valid window found

    The current window is:

        nums[l ... r-1]

    because r is incremented immediately after adding nums[r].

    Therefore its length is:

        r - l


    ------------------------------------------------------------
    Why Sliding Window Works:
    ------------------------------------------------------------

    All nums[i] are positive.

    Therefore:

        If we move r forward:
            curr increases.

        If we move l forward:
            curr decreases.

    This monotonic behavior allows us to use a sliding window.

    If:

        curr > total

    then the current window is too large.

    Adding more elements can only increase the sum, so we must
    remove elements from the left until:

        curr <= total


    ------------------------------------------------------------
    Step 3: Expand the Window
    ------------------------------------------------------------

        while(r < n) {
            curr += nums[r];
            r++;

    We add the next element to the current window.

    After this:

        window = nums[l ... r-1]

    and:

        length = r - l


    ------------------------------------------------------------
    Step 4: Shrink When Sum Is Too Large
    ------------------------------------------------------------

        while(curr > total && l < r) {
            curr -= nums[l];
            l++;
        }

    If the current sum is greater than the required sum, we remove
    elements from the left.

    Because all values are positive, removing an element can only
    decrease the sum.

    We continue until:

        curr <= total


    ------------------------------------------------------------
    Step 5: Check for a Valid Window
    ------------------------------------------------------------

        if(curr == total)
            maxLength = max(maxLength, r - l);

    If the current window's sum is exactly the required sum, then
    it represents a valid set of elements that can remain.

    We store the LONGEST such window because:

        longer remaining window
                =
        fewer elements removed
                =
        fewer operations


    ------------------------------------------------------------
    Example:
    ------------------------------------------------------------

        nums = [1, 1, 4, 2, 3]
        x = 5

    Total:

        11

    Target remaining sum:

        11 - 5 = 6


    Window progression:

        [1]           sum = 1
        [1,1]         sum = 2
        [1,1,4]       sum = 6   <-- valid, length = 3

    Add 2:

        [1,1,4,2]     sum = 8

    Since:

        8 > 6

    shrink from left:

        [1,4,2]       sum = 7

    Still too large.

    Shrink again:

        [4,2]         sum = 6   <-- valid, length = 2

    The best length is still:

        maxLength = 3


    Add 3:

        [4,2,3]       sum = 9

    Shrink:

        [2,3]         sum = 5

    Not equal to 6.

    Final:

        maxLength = 3


    Answer:

        n - maxLength
        = 5 - 3
        = 2


    ------------------------------------------------------------
    Why This Gives the Minimum Number of Operations:
    ------------------------------------------------------------

    Suppose the longest valid remaining subarray has length L.

    The original array has n elements.

    Therefore the number of elements outside that subarray is:

        n - L

    Those elements can all be removed from the two ends.

    Hence:

        operations = n - L

    Since we maximize L, we automatically minimize the number
    of operations.


    ------------------------------------------------------------
    Why maxLength Starts at -1:
    ------------------------------------------------------------

        int maxLength = -1;

    This means:

        "No valid subarray has been found yet."

    If no subarray has sum:

        totalSum - x

    then maxLength remains -1.

    In that case:

        return -1;


    Otherwise:

        return n - maxLength;


    ------------------------------------------------------------
    Edge Case: x == Total Sum
    ------------------------------------------------------------

    Suppose:

        nums = [1,2,3]
        x = 6

    Then:

        total = 6 - 6 = 0

    We need to keep a subarray with sum 0.

    Since all values are positive, the best remaining subarray
    is the empty subarray.

    Its length is:

        0

    Therefore:

        operations = n - 0
                   = 3

    We remove all elements.


    ------------------------------------------------------------
    Edge Case: x == 0
    ------------------------------------------------------------

    Suppose:

        nums = [1,2,3]
        x = 0

    Then:

        total = 6

    The entire array is already a valid remaining subarray.

    Therefore:

        maxLength = 3

    and:

        answer = 3 - 3 = 0

    No operations are required.


    ------------------------------------------------------------
    Why We Don't Use Prefix Sum + Hash Map:
    ------------------------------------------------------------

    A general "longest subarray with sum target" problem can often
    be solved using prefix sums and a hash map.

    However, here all numbers are positive.

    That gives us the stronger property:

        Increasing the right pointer increases the sum.
        Increasing the left pointer decreases the sum.

    Therefore, a sliding window is sufficient and gives:

        O(n) time
        O(1) extra space


    ------------------------------------------------------------
    Correctness Intuition:
    ------------------------------------------------------------

    Every valid sequence of removals leaves a contiguous subarray.

    If the removed elements sum to x, then the remaining subarray
    must have sum:

        sum(nums) - x

    So every valid solution corresponds to a contiguous subarray
    with the target sum.

    Conversely, every contiguous subarray with this target sum can
    be kept by removing everything before it from the left and
    everything after it from the right.

    Therefore:

        Minimum operations
              =
        n - maximum length of a target-sum subarray.


    ------------------------------------------------------------
    Complexity:
    ------------------------------------------------------------

    Time Complexity:

        O(n)

    The right pointer moves from left to right once.

    The left pointer also moves from left to right at most once
    across the entire execution.

    Therefore, even though there is a nested while loop, the total
    number of pointer movements is O(n).


    Space Complexity:

        O(1)

    Only a few integer variables are used.


    ------------------------------------------------------------
    Core Idea:
    ------------------------------------------------------------

        Remove elements summing to x
                    ↓
        Keep elements summing to sum(nums) - x
                    ↓
        Remaining elements form a contiguous subarray
                    ↓
        Find the LONGEST such subarray
                    ↓
        Answer = n - longestLength


    ------------------------------------------------------------
    Main Takeaway:
    ------------------------------------------------------------

    The important trick is to look at the problem in reverse.

    Instead of asking:

        "Which elements should I remove?"

    ask:

        "Which longest contiguous subarray can I keep?"

    Because all elements are positive, that longest target-sum
    subarray can be found efficiently using a sliding window.

    The final formula is:

        answer = n - maxLength

    where maxLength is the longest subarray whose sum is:

        sum(nums) - x.
*/