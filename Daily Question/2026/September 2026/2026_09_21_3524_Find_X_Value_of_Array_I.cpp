class Solution {
    public:
        vector<long long> resultArray(vector<int>& nums, int k) {
            int n = nums.size();
    
            vector<long long> result(k, 0);
            vector<long long> prevCount(k, 0);
    
            for(int i = 0; i < n; i++) {
                // all subarrays ending at index i
                vector<long long> currCount(k, 0);
    
                int currElementRemainder = nums[i] % k;
                currCount[currElementRemainder]++;
    
                for(int oldRem = 0; oldRem <= k - 1; oldRem++) {
                    int newRemainder = ((long long)oldRem * nums[i]) % k;
                    currCount[newRemainder] += prevCount[oldRem];
                }
    
                // Move currCount's data into prevCount instead of copying it (currCount becomes empty, address change of prevCount)
                prevCount = std::move(currCount);
    
                for(int x = 0; x <= k - 1; x++) result[x] += prevCount[x];
            }
            return result;
        }
    };

/*
    LeetCode 3524 - Find X-Sum of All K-Long Subarrays
    ------------------------------------------------------------
    
    Approach:
    ------------------------------------------------------------

    We need to count how many subarrays have each possible remainder
    modulo k.

    Instead of explicitly generating every subarray, we process the
    array from LEFT to RIGHT.

    The important observation is:

        Every subarray has some remainder when divided by k.

    We only need to know:

        How many subarrays ending at the previous index
        have remainder 0, 1, 2, ..., k-1?

    This information is stored in:

        prevCount

    Then, when we process nums[i], we extend every previous subarray
    by nums[i].

    This allows us to calculate all subarrays ending at i without
    explicitly enumerating them.


    ------------------------------------------------------------
    What Does result Mean?
    ------------------------------------------------------------

    We maintain:

        vector<long long> result(k, 0);

    result[r] represents:

        The total number of subarrays seen so far whose product
        has remainder r when divided by k.

    At the end:

        result[r]

    is the number of subarrays of the entire array whose product
    has remainder r modulo k.


    ------------------------------------------------------------
    What Does prevCount Mean?
    ------------------------------------------------------------

    This is the MOST IMPORTANT part of the solution.

        prevCount[r]

    represents:

        Number of subarrays ending at index i-1
        whose product has remainder r modulo k.

    Notice:

        prevCount does NOT contain all subarrays seen so far.

    It contains only subarrays whose RIGHT END is exactly the previous
    position.

    This is what allows us to extend those subarrays when processing
    nums[i].


    ------------------------------------------------------------
    Why Do We Only Keep Subarrays Ending at the Previous Index?
    ------------------------------------------------------------

    Suppose:

        nums = [a, b, c, d]

    When we are processing c, every subarray ending at c must be one
    of:

        [c]
        [b, c]
        [a, b, c]

    These are obtained by:

        1. Starting a new subarray at c
        2. Taking every subarray that ended at b and appending c

    We do NOT need to separately remember older subarrays ending at a
    or earlier positions.

    Why?

    Because any subarray ending at an older position cannot suddenly
    become a subarray ending at c unless we extend it through every
    element in between.

    The previous state already represents all of those possibilities.


    ------------------------------------------------------------
    Step 1: Start a New Subarray
    ------------------------------------------------------------

    For the current element:

        nums[i]

    the subarray containing ONLY this element is:

        [nums[i]]

    Its product is:

        nums[i]

    Therefore its remainder is:

        nums[i] % k

    We calculate:

        int currElementRemainder = nums[i] % k;

    and then:

        currCount[currElementRemainder]++;


    So every element automatically creates one new subarray.


    ------------------------------------------------------------
    Example:
    ------------------------------------------------------------

    Suppose:

        nums[i] = 7
        k = 5

    Then:

        7 % 5 = 2

    The single-element subarray:

        [7]

    has product remainder:

        2

    Therefore:

        currCount[2]++;


    ------------------------------------------------------------
    The MOST IMPORTANT Loop:
    ------------------------------------------------------------

        for(int oldRem = 0; oldRem <= k - 1; oldRem++) {

            int newRemainder =
                ((long long)oldRem * nums[i]) % k;

            currCount[newRemainder] += prevCount[oldRem];
        }


    This loop is the core of the entire solution.


    ------------------------------------------------------------
    What Is oldRem?
    ------------------------------------------------------------

    Suppose we are currently processing:

        nums[i]

    and consider:

        prevCount[oldRem]

    This means:

        There are prevCount[oldRem] subarrays ending at i-1
        whose product has remainder oldRem modulo k.


    For example:

        prevCount[3] = 5

    means:

        There are 5 subarrays ending at i-1 whose product % k = 3.


    ------------------------------------------------------------
    What Happens When We Append nums[i]?
    ------------------------------------------------------------

    Suppose one of those previous subarrays has product:

        P

    and:

        P % k = oldRem


    When we append nums[i], its new product becomes:

        P * nums[i]


    Therefore its new remainder is:

        (P * nums[i]) % k


    Since:

        P % k = oldRem

    we can calculate this using:

        (oldRem * nums[i]) % k


    Therefore:

        newRemainder =
            ((long long)oldRem * nums[i]) % k;


    This is the key mathematical transformation.


    ------------------------------------------------------------
    Why Does Multiplication of the Remainder Work?
    ------------------------------------------------------------

    Suppose:

        P % k = r

    Then we can write:

        P = qk + r

    for some integer q.

    Multiply by nums[i]:

        P * nums[i]
        = (qk + r) * nums[i]

        = qk * nums[i] + r * nums[i]

    The first term is divisible by k:

        qk * nums[i] % k = 0

    Therefore:

        P * nums[i] % k
        = r * nums[i] % k


    So we do NOT need the entire product P.

    We only need its remainder r.


    This is why the DP can store only k states:

        remainder 0
        remainder 1
        ...
        remainder k-1


    ------------------------------------------------------------
    Why Does This Fix Us Not Multiplying All Subarrays?
    ------------------------------------------------------------

    This is the most important conceptual point.

    A brute-force solution might do:

        for every starting index
            for every ending index
                calculate product
                calculate product % k


    There are O(n^2) subarrays.

    We avoid explicitly multiplying every one of them.

    Instead, we GROUP subarrays by their current remainder.

    Suppose:

        prevCount[2] = 100

    This means there are 100 different subarrays ending at i-1
    whose product has remainder 2.

    When nums[i] = 7 and k = 5:

        newRemainder = (2 * 7) % 5
                     = 14 % 5
                     = 4

    Therefore, ALL 100 of those subarrays become subarrays ending
    at i whose new remainder is 4.

    So we can do:

        currCount[4] += 100;

    with ONE operation.

    We do not need to multiply the products of all 100 subarrays
    individually.

    We only need to transform their common remainder.


    ------------------------------------------------------------
    This Is the Compression Trick:
    ------------------------------------------------------------

    Instead of storing:

        subarray 1 -> product remainder
        subarray 2 -> product remainder
        subarray 3 -> product remainder
        ...
        subarray 100 -> product remainder

    we store:

        remainder 0 -> how many?
        remainder 1 -> how many?
        remainder 2 -> how many?
        ...
        remainder k-1 -> how many?


    Therefore, all subarrays with the same remainder are compressed
    into one count.


    ------------------------------------------------------------
    Example of This Compression:
    ------------------------------------------------------------

    Suppose:

        k = 5

    and the previous subarrays ending at i-1 are:

        [2]       -> product % 5 = 2
        [1, 2]    -> product % 5 = 2
        [3, 4]    -> product % 5 = 2
        [4, 2]     -> product % 5 = 2

    Instead of remembering all four products, we simply store:

        prevCount[2] = 4


    Now suppose:

        nums[i] = 3

    Every one of those four subarrays can be extended with 3.

    Their new remainder is:

        (2 * 3) % 5
        = 6 % 5
        = 1


    Therefore:

        currCount[1] += prevCount[2];

    becomes:

        currCount[1] += 4;


    Four subarrays have been processed in constant time.


    ------------------------------------------------------------
    Complete Meaning of the Core Loop:
    ------------------------------------------------------------

        for(int oldRem = 0; oldRem <= k - 1; oldRem++) {

            int newRemainder =
                ((long long)oldRem * nums[i]) % k;

            currCount[newRemainder] += prevCount[oldRem];
        }


    For EVERY possible previous remainder:

        oldRem

    we calculate where that remainder moves after multiplying by
    nums[i]:

        oldRem
            |
            | multiply by nums[i]
            v
        newRemainder

    Then all subarrays belonging to oldRem are moved into the
    corresponding new remainder bucket.


    ------------------------------------------------------------
    Example of the Transition:
    ------------------------------------------------------------

    Let:

        k = 5
        nums[i] = 3


    Suppose:

        prevCount:

        remainder      count
        ---------------------
            0            2
            1            4
            2            3
            3            5
            4            1


    Process remainder 0:

        (0 * 3) % 5 = 0

        currCount[0] += 2


    Process remainder 1:

        (1 * 3) % 5 = 3

        currCount[3] += 4


    Process remainder 2:

        (2 * 3) % 5 = 1

        currCount[1] += 3


    Process remainder 3:

        (3 * 3) % 5 = 4

        currCount[4] += 5


    Process remainder 4:

        (4 * 3) % 5 = 2

        currCount[2] += 1


    So every previous group is transformed according to:

        newRemainder = oldRem * nums[i] % k


    ------------------------------------------------------------
    Why currCount Is Separate From prevCount:
    ------------------------------------------------------------

    We use:

        vector<long long> currCount(k, 0);

    because currCount must represent:

        subarrays ending at CURRENT index i


    while prevCount represents:

        subarrays ending at PREVIOUS index i-1


    We must not modify prevCount while calculating currCount.

    Otherwise, newly created subarrays could accidentally be processed
    again during the same iteration.

    That would count some subarrays multiple times.


    So the transition is:

        prevCount
             |
             | append nums[i]
             v
        currCount


    Only AFTER the entire transition is finished do we replace
    prevCount with currCount.


    ------------------------------------------------------------
    What Does This Line Do?
    ------------------------------------------------------------

        prevCount = std::move(currCount);


    This is an important C++ detail.


    Normally, if we wrote:

        prevCount = currCount;


    C++ would copy the contents of currCount into prevCount.

    That means the k elements of currCount would be copied.


    With:

        prevCount = std::move(currCount);


    we are telling C++:

        "The contents/resources of currCount can be transferred to
         prevCount. I no longer need currCount's old contents."


    Since currCount is a vector, this can transfer ownership of its
    dynamically allocated memory instead of copying every element.


    Conceptually:

        Before:

        prevCount  ---> [old data]
        currCount  ---> [new data]


        After:

        prevCount  ---> [new data]
        currCount  ---> empty/moved-from state


    The important point is that the data generated for the current
    iteration becomes the data used as the previous state in the
    NEXT iteration.


    ------------------------------------------------------------
    Why Is currCount Allowed to Be "Moved"?
    ------------------------------------------------------------

    currCount is created fresh in every iteration:

        vector<long long> currCount(k, 0);


    We use it to calculate the current state.

    Once we finish:

        prevCount = std::move(currCount);


    we don't need currCount anymore.

    Therefore, moving is appropriate.

    We are effectively saying:

        "Take the vector storage from currCount and make it
         the storage of prevCount."


    After the move, currCount is still a valid C++ vector object,
    but its contents are in a moved-from state.

    We do NOT use currCount again in this iteration.


    ------------------------------------------------------------
    Why Not Move Earlier?
    ------------------------------------------------------------

    We cannot do:

        prevCount = std::move(currCount);

    before the transition is complete.

    We still need currCount to receive all the new remainder counts:

        currCount[newRemainder] += prevCount[oldRem];


    So the correct order is:

        1. Create currCount
        2. Add [nums[i]] to currCount
        3. Transform every old remainder from prevCount
        4. Move currCount into prevCount
        5. Add prevCount to the global result


    ------------------------------------------------------------
    Updating result:
    ------------------------------------------------------------

    After:

        prevCount = std::move(currCount);

    prevCount now represents ALL subarrays ending at i.

    Therefore, every count in prevCount needs to be added to the
    global answer:

        for(int x = 0; x <= k - 1; x++)
            result[x] += prevCount[x];


    This is different from prevCount.

    Remember:

        prevCount
            =
        subarrays ending at CURRENT index


        result
            =
        subarrays ending ANYWHERE in the array


    Therefore:

        result[x] += prevCount[x]

    adds the current ending position's subarrays into the global total.


    ------------------------------------------------------------
    Why Does result Not Double Count?
    ------------------------------------------------------------

    Every non-empty subarray has exactly ONE ending index.

    For example:

        nums = [a, b, c]

    Subarrays ending at a:

        [a]

    Subarrays ending at b:

        [b]
        [a,b]

    Subarrays ending at c:

        [c]
        [b,c]
        [a,b,c]


    Every subarray appears exactly once according to its ending position.

    Therefore, when we add:

        prevCount

    to result at each index, every subarray is added exactly once.


    ------------------------------------------------------------
    Small Complete Example:
    ------------------------------------------------------------

    Consider:

        nums = [2, 3, 4]
        k = 5


    ------------------------------------------------------------
    i = 0, nums[i] = 2
    ------------------------------------------------------------

    New single-element subarray:

        [2]

    Remainder:

        2 % 5 = 2

    Therefore:

        currCount[2] = 1


    There are no previous subarrays yet.

    Move:

        prevCount = [0,0,1,0,0]


    Add to result:

        result[2] += 1


    So:

        result = [0,0,1,0,0]


    ------------------------------------------------------------
    i = 1, nums[i] = 3
    ------------------------------------------------------------

    Start new subarray:

        [3]

    Remainder:

        3 % 5 = 3

    Therefore:

        currCount[3] = 1


    Now extend the previous subarray:

        [2]

    Its old remainder is:

        2

    After multiplying by 3:

        (2 * 3) % 5 = 1


    So:

        [2,3]

    has remainder 1.

    Therefore:

        currCount[1] += prevCount[2]


    resulting in:

        currCount[1] = 1
        currCount[3] = 1


    These correspond to:

        [2,3] -> remainder 1
        [3]   -> remainder 3


    Add them to result.


    ------------------------------------------------------------
    i = 2, nums[i] = 4
    ------------------------------------------------------------

    Start new subarray:

        [4]

    Remainder:

        4


    Previous subarrays were:

        [2,3] -> remainder 1
        [3]   -> remainder 3


    Extend [2,3]:

        (1 * 4) % 5 = 4

    Therefore:

        [2,3,4] -> remainder 4


    Extend [3]:

        (3 * 4) % 5 = 12 % 5 = 2

    Therefore:

        [3,4] -> remainder 2


    And the new single-element subarray:

        [4] -> remainder 4


    So:

        currCount[2] = 1
        currCount[4] = 2


    These represent exactly all subarrays ending at index 2.


    ------------------------------------------------------------
    What We Are Actually Doing:
    ------------------------------------------------------------

    At every index i, we are performing:

        New subarray:
            [nums[i]]

        +

        Extend every subarray ending at i-1:
            [previous ... i-1] + nums[i]

        =

        ALL subarrays ending at i


    This is why no subarray is missed.


    ------------------------------------------------------------
    Why We Don't Need to Multiply Every Subarray:
    ------------------------------------------------------------

    Suppose there are:

        1,000,000

    subarrays ending at the previous index.

    We do NOT individually calculate:

        product(subarray) * nums[i]

    for all 1,000,000 subarrays.

    Instead, suppose their remainders are grouped as:

        remainder 0 -> 100,000 subarrays
        remainder 1 -> 200,000 subarrays
        remainder 2 -> 300,000 subarrays
        remainder 3 -> 250,000 subarrays
        remainder 4 -> 150,000 subarrays


    We only have k groups.

    For each group, we perform ONE remainder transition:

        newRemainder = oldRem * nums[i] % k

    and move the entire count.

    This is the fundamental optimization.


    ------------------------------------------------------------
    DP Interpretation:
    ------------------------------------------------------------

    The state can be thought of as:

        prevCount[r]

    = number of subarrays ending at the previous index whose product
      modulo k is r.


    Transition:

        currCount[(r * nums[i]) % k]
            += prevCount[r]


    Plus the new one-element subarray:

        currCount[nums[i] % k]++


    This is essentially dynamic programming where the state space is
    only:

        k possible remainders.


    ------------------------------------------------------------
    Why long long Is Used:
    ------------------------------------------------------------

    The number of subarrays can be as large as:

        n * (n + 1) / 2

    which can exceed the range of a normal int for sufficiently large n.

    Therefore:

        vector<long long> result
        vector<long long> prevCount
        vector<long long> currCount

    are used to safely store counts.


    The multiplication also uses:

        (long long)oldRem * nums[i]

    before taking modulo k.

    This prevents the multiplication from being performed only in
    32-bit integer arithmetic.


    ------------------------------------------------------------
    Complexity:
    ------------------------------------------------------------

    Let:

        n = nums.size()

    and:

        k = modulo value


    For every one of the n elements, we iterate through all k possible
    remainders:

        O(n * k)


    The final result update also takes O(k) per element.

    Therefore:

        Time Complexity = O(n * k)


    Space Complexity:

        prevCount -> O(k)
        currCount -> O(k)
        result    -> O(k)

    Therefore:

        Space Complexity = O(k)


    ------------------------------------------------------------
    Core Idea:
    ------------------------------------------------------------

    We do NOT enumerate all O(n^2) subarrays.

    Instead:

        1. Group subarrays by their product % k.

        2. For every current element, extend every group.

        3. If a group has remainder oldRem, after appending nums[i]:

               newRem = (oldRem * nums[i]) % k

        4. Store the resulting groups in currCount.

        5. Move currCount into prevCount.

        6. Add prevCount to the global result.


    ------------------------------------------------------------
    Main Takeaway:
    ------------------------------------------------------------

    The most important idea is STATE COMPRESSION.

    We do not care about the actual product of a subarray.

    We only care about:

        product % k


    Therefore, all subarrays with the same remainder behave identically
    when we append a new number.

    If:

        prevCount[r] = X

    then ALL X subarrays can be transformed together:

        newRemainder = (r * nums[i]) % k

        currCount[newRemainder] += X


    This single transition:

        currCount[newRemainder] += prevCount[oldRem];

    represents the extension of potentially MANY subarrays at once.

    That is exactly how the solution avoids explicitly multiplying
    every possible subarray and reduces the problem from enumerating
    O(n^2) subarrays to maintaining only k remainder states.
*/