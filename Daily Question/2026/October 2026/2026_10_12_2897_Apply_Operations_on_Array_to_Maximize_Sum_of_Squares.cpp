class Solution {
    public:
        int maxSum(vector<int>& nums, int k) {
            int MOD = 1e9+7;
            
            vector<int> count(32, 0);
            for(int &num : nums) {
                for(int b = 0; b < 32; b++) {
                    if(num & (1 << b)) count[b]++; //found a '1' in this bit position b
                }
            }
    
            long long result = 0;
            while(k--) {
                long long curr = 0;
                for(int b = 0; b < 32; b++) {
                    if(count[b] > 0) {
                        count[b]--;
                        curr = (curr | (1 << b));
                    }
                }
                result = (result + (curr * curr)) % MOD;
            }
    
            return result;
        }
    };

/*
    Approach: Bit Manipulation + Greedy + Frequency Counting

    The goal is to select exactly `k` numbers from `nums` and maximize
    the sum of their squares.

    We are allowed to construct each selected number using the set bits
    available across the original array. A bit can be used in a constructed
    number only if at least one unused occurrence of that bit remains.

    The key observation is that we should distribute the available set bits
    across the `k` numbers as evenly as possible in terms of their bit
    positions, while ensuring that every constructed number uses the
    highest-value bits available to it.

    Instead of directly constructing all possible numbers, we count how
    many times each bit appears across the entire array. We then greedily
    build each of the `k` numbers using these bit counts.

    ------------------------------------------------------------
    Key Observation: Why do we count bits instead of numbers?
    ------------------------------------------------------------

    Consider:

        nums = [2, 1, 3]

    Their binary representations are:

        2 = 010
        1 = 001
        3 = 011

    Count the occurrences of each bit:

        Bit 0: 1 appears in 1 and 3  -> count[0] = 2
        Bit 1: 1 appears in 2 and 3  -> count[1] = 2
        Bit 2: no number has it      -> count[2] = 0

    Therefore:

        count = [2, 2, 0, ...]

    This tells us that we have two available occurrences of bit 0
    and two available occurrences of bit 1.

    We do not need to remember which original number contributed each bit.
    We only need to know how many occurrences of every bit are available.

    This is sufficient because the constructed numbers depend on the
    available bit positions, not on which original number supplied them.

    ------------------------------------------------------------
    Step 1: Initialize the bit-frequency array
    ------------------------------------------------------------

        vector<int> count(32, 0);

    An integer is represented using 32 bit positions in this code.

    `count[b]` stores the total number of elements in `nums` whose
    bit at position `b` is set to 1.

    For example:

        count[0] = 3

    means that three elements in the array have their least significant
    bit set.

    Initially, every count is zero because we have not processed any
    elements.

    ------------------------------------------------------------
    Step 2: Count set bits across all numbers
    ------------------------------------------------------------

        for(int &num : nums) {
            for(int b = 0; b < 32; b++) {
                if(num & (1 << b)) count[b]++;
            }
        }

    The outer loop processes every number in `nums`.

    The inner loop checks all 32 bit positions of the current number.

    Expression:

        (1 << b)

    creates a number whose only set bit is at position `b`.

    Examples:

        b = 0  -> 0001
        b = 1  -> 0010
        b = 2  -> 0100
        b = 3  -> 1000

    Expression:

        num & (1 << b)

    performs a bitwise AND between `num` and the mask.

    If the result is nonzero, bit `b` of `num` is set to 1.

    Therefore:

        if(num & (1 << b)) count[b]++;

    increases the frequency of that bit.

    Example:

        num = 5

    Binary representation:

        5 = 0101

    Checking the bits:

        b = 0 -> 0101 & 0001 != 0 -> count[0]++
        b = 1 -> 0101 & 0010 == 0 -> no change
        b = 2 -> 0101 & 0100 != 0 -> count[2]++
        b = 3 -> 0101 & 1000 == 0 -> no change

    Thus, the number 5 contributes one occurrence each to bit positions
    0 and 2.

    After processing the entire array, `count[b]` tells us exactly how
    many constructed numbers can potentially use bit `b`.

    ------------------------------------------------------------
    Step 3: Greedily construct exactly k numbers
    ------------------------------------------------------------

        long long result = 0;

        while(k--) {
            long long curr = 0;

            for(int b = 0; b < 32; b++) {
                if(count[b] > 0) {
                    count[b]--;
                    curr = (curr | (1 << b));
                }
            }

            result = (result + (curr * curr)) % MOD;
        }

    The outer loop executes exactly `k` times.

    Each iteration constructs one number, stored in `curr`.

    Initially:

        curr = 0

    We then examine every bit position.

    If:

        count[b] > 0

    at least one unused occurrence of bit `b` remains.

    We perform two operations:

        count[b]--;

    This consumes one available occurrence of that bit.

        curr = curr | (1 << b);

    This sets bit `b` in the current number.

    The bitwise OR operator combines the selected bits. Since `curr`
    starts at zero, every selected bit is turned on without changing
    any other bit.

    Notice that each bit position is considered at most once while
    constructing a particular number. Therefore, `curr` contains at
    most one copy of each bit position, as expected for a binary number.

    ------------------------------------------------------------
    Why does the greedy construction work?
    ------------------------------------------------------------

    The objective is to maximize:

        x1^2 + x2^2 + ... + xk^2

    where each `xi` is constructed from the available bit occurrences.

    For non-negative numbers, concentrating larger available bit
    contributions into the same number can increase the sum of squares.

    For example, compare two ways to distribute two occurrences of
    the same bit, where the bit has value 1:

        Distribution A: [1, 1]
        Sum of squares = 1^2 + 1^2 = 2

        Distribution B: [1 | 1, 0]
        Sum of squares = 1^2 + 0^2 = 1

    This example illustrates that the distribution must be considered
    across all numbers, not merely by maximizing each number independently.

    More generally, the algorithm constructs each number using every
    bit position that still has an available occurrence. It consumes
    one occurrence of each such bit before moving to the next number.

    This ensures that a bit position is reused in later numbers only
    when its frequency allows it.

    The important detail is that the code processes all bit positions
    from 0 to 31 for each constructed number, and it decrements each
    positive count immediately. Thus, no available bit occurrence is
    used more than once.

    ------------------------------------------------------------
    Step 4: Calculate the square and update the answer
    ------------------------------------------------------------

        result = (result + (curr * curr)) % MOD;

    Once `curr` has been constructed, we calculate its square:

        curr * curr

    and add it to the running result.

    The modulo operation keeps the result within the required range:

        MOD = 1e9 + 7

    Since the problem asks for the sum of squares modulo `10^9 + 7`,
    we apply the modulo after adding each square.

    `long long` is used for `result` and `curr` to support larger values
    and avoid many common integer-overflow issues during arithmetic.

    ------------------------------------------------------------
    Detailed Example
    ------------------------------------------------------------

    Input:

        nums = [2, 1, 3]
        k = 2

    Binary representations:

        2 = 010
        1 = 001
        3 = 011

    After counting the bits:

        count[0] = 2
        count[1] = 2
        count[2] = 0

    All higher bit counts are also zero.

    First iteration: construct the first number

        curr = 0

    Bit 0:

        count[0] = 2 > 0

        count[0] becomes 1
        curr = 001 = 1

    Bit 1:

        count[1] = 2 > 0

        count[1] becomes 1
        curr = 011 = 3

    Bit 2 and all remaining positions:

        Their counts are zero, so nothing changes.

    The first constructed number is:

        curr = 3

    Update the result:

        result = 0 + 3^2
               = 9

    Remaining counts:

        count[0] = 1
        count[1] = 1

    Second iteration: construct the second number

        curr = 0

    Bit 0:

        count[0] = 1 > 0

        count[0] becomes 0
        curr = 001 = 1

    Bit 1:

        count[1] = 1 > 0

        count[1] becomes 0
        curr = 011 = 3

    The second constructed number is:

        curr = 3

    Update the result:

        result = (9 + 3^2) % MOD
               = 18

    Final answer:

        18

    ------------------------------------------------------------
    Important Detail: Why is count[b] decremented?
    ------------------------------------------------------------

    Suppose:

        count[2] = 3

    This means three available numbers contribute a set bit at position 2.

    The value of this bit is:

        1 << 2 = 4

    The algorithm can use this bit in three separately constructed
    numbers, but not in four.

    Every time a constructed number uses bit 2:

        count[2]--

    Once the count reaches zero, no later constructed number can use
    that bit.

    This is how the code tracks the available supply of every bit
    position.

    ------------------------------------------------------------
    Complexity Analysis
    ------------------------------------------------------------

    Let:
        n = nums.size()
        B = 32, the number of bit positions
        k = number of constructed values

    Time Complexity:

        O(n * B + k * B)

    Counting bits requires checking B positions for every input number.

    Constructing the k numbers also checks B positions per number.

    Since B = 32 is constant, this simplifies to:

        O(n + k)

    Space Complexity:

        O(B) = O(1)

    The `count` vector always contains 32 entries, independent of the
    input size. Apart from this fixed-size array, the algorithm uses
    only a constant number of variables.

    ------------------------------------------------------------
    Core Idea
    ------------------------------------------------------------

    Count how many times every bit appears across the input.

    Construct exactly k numbers by taking one available occurrence of
    every bit position for each number, decrementing the corresponding
    frequencies as the bits are consumed.

    Square each constructed number, accumulate the squares modulo
    10^9 + 7, and return the result.
*/