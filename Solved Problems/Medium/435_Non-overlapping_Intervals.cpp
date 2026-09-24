class Solution {
    private:
        int n;
        vector<int> nextIdx;
        vector<int> dp;
    
        int findNext(vector<vector<int>>& intervals, int endPoint) {
            int left = 0, right = n - 1;
            int result = n;
            while(left <= right) {
                int mid = left + (right - left) / 2;
                if(intervals[mid][0] >= endPoint) {
                    result = mid;
                    right = mid - 1;
                } else left = mid + 1;
            }
    
            return result;
        }
    
        int solve(vector<vector<int>>& intervals, int i) {
            if(i == n) return 0;
    
            if(dp[i] != -1) return dp[i];
    
            int take = 1 + solve(intervals, nextIdx[i]);
            int skip = solve(intervals, i + 1);
    
            return dp[i] = max(take, skip);
        }
    
    public:
        int eraseOverlapIntervals(vector<vector<int>>& intervals) {
            n = intervals.size();
            sort(intervals.begin(), intervals.end());
    
            dp.assign(n, -1);
    
            nextIdx.resize(n);
            for(int i = 0; i < n; i++) nextIdx[i] = findNext(intervals, intervals[i][1]);
    
            return n - solve(intervals, 0);
        }
    };

/*
    LeetCode 435 - Non-overlapping Intervals
    ------------------------------------------------------------

    Approach:
    ------------------------------------------------------------

    We are given a collection of intervals and need to remove the
    MINIMUM number of intervals so that the remaining intervals do
    not overlap.

    Instead of directly deciding which intervals to erase, we solve
    the complementary problem:

        Find the MAXIMUM number of non-overlapping intervals
        that we can keep.

    If we can keep `maxKeep` intervals out of n intervals, then:

        intervals to remove = n - maxKeep


    Therefore, the main problem becomes:

        Find the maximum number of non-overlapping intervals.


    This solution uses:

        1. Sorting
        2. Binary search
        3. Dynamic programming + memoization


    ------------------------------------------------------------
    Key Observation:
    ------------------------------------------------------------

    After sorting the intervals, suppose we are currently considering:

        intervals[i]

    We have two choices:

        1. TAKE intervals[i]
        2. SKIP intervals[i]


    If we take intervals[i], we cannot take an interval that starts
    before the end of intervals[i].

    Therefore, we need to find the first interval j such that:

        intervals[j][0] >= intervals[i][1]

    This interval is the first one that can safely come after
    intervals[i].

    We precompute this index using binary search and store it in:

        nextIdx[i]


    ------------------------------------------------------------
    Why >= Is Used:
    ------------------------------------------------------------

    Two intervals are considered non-overlapping if the second
    interval starts exactly when the first one ends.

    For example:

        [1, 3]
        [3, 5]

    These intervals do NOT overlap.

    Therefore, after choosing:

        [1, 3]

    an interval starting at:

        3

    is valid.

    Hence we search for:

        intervals[j][0] >= intervals[i][1]

    and NOT:

        intervals[j][0] > intervals[i][1]


    ------------------------------------------------------------
    Step 1: Sort the Intervals
    ------------------------------------------------------------

        sort(intervals.begin(), intervals.end());

    This sorts the intervals lexicographically.

    Primarily, they are sorted by:

        start time

    and if starts are equal, then by:

        end time


    Example:

        Before sorting:

            [2,3]
            [1,2]
            [3,4]
            [1,5]

        After sorting:

            [1,2]
            [1,5]
            [2,3]
            [3,4]


    Sorting is important because once intervals are ordered by their
    starting position, we can use binary search to find the next
    compatible interval.


    ------------------------------------------------------------
    Step 2: Find the Next Compatible Interval
    ------------------------------------------------------------

    The helper function:

        findNext(intervals, endPoint)

    finds the first interval whose starting point is >= endPoint.


    The binary search is:

        int left = 0;
        int right = n - 1;
        int result = n;


    `result = n` means:

        "No compatible interval was found."


    During binary search:

        if(intervals[mid][0] >= endPoint)

    then interval[mid] is compatible.

    However, it may not be the FIRST compatible interval.

    Therefore:

        result = mid;
        right = mid - 1;

    We continue searching toward the left.


    Otherwise:

        intervals[mid][0] < endPoint

    means this interval starts too early and overlaps the current
    interval.

    Therefore:

        left = mid + 1;


    ------------------------------------------------------------
    Why Binary Search Works:
    ------------------------------------------------------------

    Because the intervals are sorted by starting position.

    Therefore, their starting points are also sorted:

        start[0] <= start[1] <= start[2] <= ...


    Once we find an interval whose start is >= endPoint, every
    interval after it also has a start >= endPoint.

    So we can use binary search to find the FIRST such interval.


    ------------------------------------------------------------
    Example of findNext():
    ------------------------------------------------------------

    Suppose:

        intervals =

        [1,2]
        [2,3]
        [4,5]
        [6,8]


    Suppose the current interval ends at:

        endPoint = 3


    We need:

        start >= 3


    Check the intervals:

        [1,2] -> start = 1 -> invalid
        [2,3] -> start = 2 -> invalid
        [4,5] -> start = 4 -> valid
        [6,8] -> start = 6 -> valid


    The FIRST compatible interval is:

        index = 2


    Therefore:

        nextIdx[i] = 2


    ------------------------------------------------------------
    Step 3: Precompute nextIdx
    ------------------------------------------------------------

        nextIdx.resize(n);

        for(int i = 0; i < n; i++)
            nextIdx[i] =
                findNext(intervals, intervals[i][1]);


    For every interval i:

        intervals[i][1]

    is its ending point.

    We find the first interval whose starting point is at least
    this ending point.


    Therefore:

        nextIdx[i]

    means:

        The first interval that can be selected AFTER intervals[i].


    ------------------------------------------------------------
    Meaning of nextIdx:
    ------------------------------------------------------------

    Suppose:

        intervals[i] = [1,4]

    and:

        nextIdx[i] = 3


    This means:

        intervals[0]
        intervals[1]
        intervals[2]

    cannot immediately follow [1,4], while:

        intervals[3]

    is the first compatible interval.

    Therefore, if we TAKE interval i, the next recursive state is:

        solve(intervals, nextIdx[i])


    ------------------------------------------------------------
    Step 4: DP State
    ------------------------------------------------------------

    The DP array is:

        vector<int> dp;


    Define:

        dp[i]

    as:

        Maximum number of non-overlapping intervals that can be
        selected from intervals[i ... n-1].


    In other words:

        solve(intervals, i)

    answers:

        "Starting from interval i, what is the maximum number
         of non-overlapping intervals I can keep?"


    ------------------------------------------------------------
    Base Case:
    ------------------------------------------------------------

        if(i == n) return 0;


    If:

        i == n

    then there are no intervals left to process.

    Therefore, we can select:

        0 intervals.


    ------------------------------------------------------------
    Memoization:
    ------------------------------------------------------------

        if(dp[i] != -1)
            return dp[i];


    The same state i may be reached through different choices.

    Without memoization, we could repeatedly solve the same suffix
    of the interval array.

    Therefore, once:

        solve(intervals, i)

    has been calculated, we store it in:

        dp[i]


    ------------------------------------------------------------
    Step 5: TAKE vs SKIP
    ------------------------------------------------------------

    At every interval i, there are exactly two possibilities.


    ------------------------------------------------------------
    Choice 1: TAKE intervals[i]
    ------------------------------------------------------------

        int take =
            1 + solve(intervals, nextIdx[i]);


    If we keep interval i:

        +1

    interval is selected.

    After selecting it, we cannot select overlapping intervals.

    Therefore, we jump directly to:

        nextIdx[i]

    which is the first compatible interval.


    So:

        take =
            1 + best answer after nextIdx[i]


    ------------------------------------------------------------
    Choice 2: SKIP intervals[i]
    ------------------------------------------------------------

        int skip =
            solve(intervals, i + 1);


    If we remove interval i, we simply move to the next interval:

        i + 1


    Therefore:

        skip =
            best answer starting from i+1


    ------------------------------------------------------------
    DP Recurrence:
    ------------------------------------------------------------

    Combining the two choices:

        dp[i] =
            max(
                take,
                skip
            )


    More explicitly:

        dp[i] =
            max(
                1 + dp[nextIdx[i]],
                dp[i + 1]
            )


    where:

        1 + dp[nextIdx[i]]
            = keep current interval

        dp[i + 1]
            = remove current interval


    ------------------------------------------------------------
    Example:
    ------------------------------------------------------------

    Consider:

        intervals =

        [1,2]
        [2,3]
        [3,4]
        [1,3]


    After sorting:

        [1,2]
        [1,3]
        [2,3]
        [3,4]


    For [1,2]:

        next compatible interval starts >= 2

        [2,3]

    Therefore:

        nextIdx[0] = 2


    At index 0:

        TAKE [1,2]

        take =
            1 + solve(2)


        SKIP [1,2]

        skip =
            solve(1)


    We choose whichever gives the larger number of
    non-overlapping intervals.


    ------------------------------------------------------------
    Visualizing the TAKE Choice:
    ------------------------------------------------------------

        [1-----------2]
                    |
                    | next compatible interval
                    v
                    [2-----------3]
                                  |
                                  v
                                  [3-----------4]


    If we select:

        [1,2]

    we jump to the first interval beginning at >= 2.

    This automatically prevents overlap.


    ------------------------------------------------------------
    Why We Don't Need to Check Every Later Interval After Taking:
    ------------------------------------------------------------

    Suppose we take:

        intervals[i] = [1,4]

    There might be many intervals between i and nextIdx[i]:

        [2,3]
        [2,5]
        [3,7]

    All of them start before 4.

    Therefore, all overlap with [1,4].

    The first interval with:

        start >= 4

    is the earliest possible interval that can follow.

    So jumping directly to nextIdx[i] skips every incompatible
    interval safely.


    ------------------------------------------------------------
    Why Maximizing Kept Intervals Solves the Original Problem:
    ------------------------------------------------------------

    Suppose:

        n = 6

    and we can keep:

        4 non-overlapping intervals.

    Then we need to remove:

        6 - 4 = 2


    intervals.

    More generally:

        removed = n - kept


    Therefore, maximizing:

        kept

    automatically minimizes:

        removed.


    The final line:

        return n - solve(intervals, 0);


    does exactly this.


    ------------------------------------------------------------
    Complete Example:
    ------------------------------------------------------------

    Suppose:

        intervals = [
            [1,2],
            [2,3],
            [3,4],
            [1,3]
        ]


    We want the maximum number of non-overlapping intervals.

    One possible selection is:

        [1,2]
        [2,3]
        [3,4]

    These are all compatible because touching endpoints are allowed.

    Therefore:

        maximum kept = 3

    There are:

        n = 4

    intervals total.

    So:

        minimum removals
            = 4 - 3
            = 1


    We remove:

        [1,3]


    ------------------------------------------------------------
    Why This Is a DP Problem:
    ------------------------------------------------------------

    At every interval, the decision is:

        TAKE
        or
        SKIP


    But different decision paths can reach the same interval index.

    For example, multiple earlier choices may eventually lead to:

        solve(intervals, 5)

    The answer from index 5 onward is always the same.

    Therefore, instead of recomputing it, we store:

        dp[5]


    This is the overlapping-subproblems property of dynamic
    programming.


    ------------------------------------------------------------
    Why Sorting Is Required Before Binary Search:
    ------------------------------------------------------------

    The binary search in findNext() relies on:

        intervals[mid][0]

    being ordered.

    Without sorting, we could not determine whether to move:

        left = mid + 1

    or:

        right = mid - 1


    Sorting creates the required monotonic order of start positions.


    ------------------------------------------------------------
    Complexity:
    ------------------------------------------------------------

    Let:

        n = number of intervals.


    Sorting:

        O(n log n)


    Finding nextIdx for every interval:

        n binary searches

        O(n log n)


    DP:

        There are n states.

    Each state does O(1) work because nextIdx has already been
    precomputed.

        O(n)


    Therefore, total:

        O(n log n)


    ------------------------------------------------------------
    Space Complexity:
    ------------------------------------------------------------

    We maintain:

        dp       -> O(n)
        nextIdx  -> O(n)

    The recursion depth can also reach:

        O(n)

    Therefore the total auxiliary space is:

        O(n)


    ------------------------------------------------------------
    Core Idea:
    ------------------------------------------------------------

    The solution transforms:

        "Remove the minimum number of overlapping intervals"

    into:

        "Keep the maximum number of non-overlapping intervals."


    For every interval:

        TAKE:
            keep it
            jump to next compatible interval

        SKIP:
            remove it
            move to i + 1


    The recurrence is:

        dp[i] =
            max(
                1 + dp[nextIdx[i]],
                dp[i + 1]
            )


    Finally:

        answer = n - dp[0]


    ------------------------------------------------------------
    Main Takeaway:
    ------------------------------------------------------------

    The three important ideas are:

        1. Sort intervals by their start position.

        2. For every interval, use binary search to find the first
           interval whose start >= current end.

        3. Use DP to choose between:
           
               TAKE current interval
               SKIP current interval


    The key transition is:

        take = 1 + solve(intervals, nextIdx[i])

        skip = solve(intervals, i + 1)

        dp[i] = max(take, skip)


    Once the maximum number of non-overlapping intervals is known,
    the minimum number to erase is simply:

        n - maximumKept.
*/