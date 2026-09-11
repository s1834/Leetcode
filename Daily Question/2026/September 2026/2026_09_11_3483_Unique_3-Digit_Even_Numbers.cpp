class Solution {
    public:
        int totalNumbers(vector<int>& digits) {
            vector<int> v(10, 0);
            for(auto &digit : digits) v[digit]++;
    
            vector<int> result;
            for(int i = 1; i <= 9; i++) { // Hundred's Place (1 - 9)
                if(v[i] == 0) continue;
                v[i]--;
                for(int j = 0; j <= 9; j++) { // Ten's Place (0 - 9)
                    if(v[j] == 0) continue;
                    v[j]--;  
                    for(int k = 0; k <= 8; k += 2) { // One's Place (0, 2, 4, 6, 8)
                        if(v[k] == 0) continue;
                        result.push_back((i * 100) + (j * 10) + k);
                    }
                    v[j]++;
                }
                v[i]++;
            }
    
            return result.size();
        }
    };

/*
    LeetCode 3483. Unique 3-Digit Even Numbers

    Approach:
    ------------------------------------------------------------
    We need to count how many UNIQUE 3-digit even numbers can be
    formed using the given digits.

    There are three positions:

        Hundreds -> 1 to 9
        Tens     -> 0 to 9
        Ones     -> 0, 2, 4, 6, 8

    Since we are given a collection of digits, the same digit can
    only be used as many times as it appears in `digits`.

    Therefore, we maintain a frequency array:

        v[d] = number of times digit d is available



    ------------------------------------------------------------
    Why Use a Frequency Array?
    ------------------------------------------------------------

    Instead of generating permutations and then removing
    duplicates, we store how many copies of every digit exist.

        v[0] -> frequency of 0
        v[1] -> frequency of 1
        ...
        v[9] -> frequency of 9

    This allows us to check whether a digit is available before
    using it.

    It also naturally handles duplicate digits.

    For example:

        digits = [1, 1, 2]

    We have:

        v[1] = 2
        v[2] = 1

    So we can use 1 twice, but cannot use it three times.



    ------------------------------------------------------------
    Hundreds Place:
    ------------------------------------------------------------

    The first digit cannot be zero because the number must be a
    3-digit number.

    Therefore we try:

        for(int i = 1; i <= 9; i++)

    If digit i is available:

        v[i]--;

    This means we temporarily use one copy of i for the hundreds
    place.

    After finishing all possibilities for the remaining positions,
    we restore it:

        v[i]++;



    ------------------------------------------------------------
    Tens Place:
    ------------------------------------------------------------

    The middle digit can be ANY digit from 0 to 9.

    Therefore:

        for(int j = 0; j <= 9; j++)

    If digit j is available:

        v[j]--;

    We temporarily use one copy of j for the tens position.

    After checking all possible last digits, we restore:

        v[j]++;



    ------------------------------------------------------------
    Ones Place:
    ------------------------------------------------------------

    The number must be EVEN.

    A number is even if its last digit is one of:

        0, 2, 4, 6, 8

    Therefore we only try these digits:

        for(int k = 0; k <= 8; k += 2)



    ------------------------------------------------------------
    Why Do We Not Decrease v[k]?
    ------------------------------------------------------------

    At this point, we are only counting whether the number can be
    formed.

    If:

        v[k] > 0

    then at least one copy of k is available, so the number can be
    formed.

    We do not need to modify `v[k]` because there are no more
    positions after the ones place.

    We simply add the constructed number to `result`:

        result.push_back((i * 100) + (j * 10) + k);



    ------------------------------------------------------------
    Why Does This Handle Duplicate Digits Correctly?
    ------------------------------------------------------------

    Suppose:

        digits = [1, 1, 2, 2]

    When we choose the hundreds digit 1, we decrease its frequency.

    This allows the second position to use another 1 because:

        v[1] > 0

    But we cannot use a third 1 because its frequency becomes zero.

    More importantly, we iterate over DIGIT VALUES rather than
    individual copies.

    So if there are multiple copies of the same digit, we do not
    generate the same number multiple times.

    For example, two copies of 1 do NOT cause:

        112
        112

    to be inserted twice.

    The number is generated only once for the digit combination
    (1, 1, 2).



    ------------------------------------------------------------
    Example:
    ------------------------------------------------------------

    digits = [1, 2, 3, 4]

    Choose hundreds digit:

        i = 1

    Choose tens digit:

        j = 2

    Possible even last digits:

        k = 4

    Number:

        1 * 100 + 2 * 10 + 4
        = 124

    Similarly, we can generate:

        134
        214
        234
        314
        324
        342
        ...

    depending on which digits are available.

    Only numbers whose last digit is even are added.



    ------------------------------------------------------------
    Example With Zero:
    ------------------------------------------------------------

    digits = [0, 1, 2]

    Possible 3-digit even numbers include:

        102
        120
        210

    But:

        012

    is NOT valid because 0 cannot be the hundreds digit.

    This is why the first loop starts from 1:

        i = 1 ... 9



    ------------------------------------------------------------
    Important: Backtracking the Frequency Array
    ------------------------------------------------------------

    The code temporarily consumes digits:

        v[i]--;
        v[j]--;

    After exploring that choice, it restores them:

        v[j]++;
        v[i]++;

    This is important because the same digit must be available
    again when trying a different combination.

    For example, after trying:

        1 -> 2 -> 4

    we need the original frequencies restored before trying:

        1 -> 3 -> 2

    This is essentially backtracking using the frequency array.



    ------------------------------------------------------------
    Why Store the Numbers in `result`?
    ------------------------------------------------------------

    The problem asks for the number of unique valid numbers.

    Every valid combination of:

        hundreds digit
        tens digit
        ones digit

    creates exactly one 3-digit number.

    Since we iterate over each digit value only once at each
    position and respect the available frequencies, every valid
    number is generated once.

    Therefore:

        result.size()

    gives the required answer.

    The vector is not actually necessary; we could maintain an
    integer counter instead.

    But in this implementation, `result` is used to store every
    valid number and its size is returned.



    ------------------------------------------------------------
    Algorithm:
    ------------------------------------------------------------

    1. Count the frequency of every digit using `v`.

    2. Choose the hundreds digit from 1 to 9.
       - It cannot be zero.
       - Skip it if unavailable.
       - Temporarily decrease its frequency.

    3. Choose the tens digit from 0 to 9.
       - Skip it if unavailable.
       - Temporarily decrease its frequency.

    4. Choose the ones digit from:
           0, 2, 4, 6, 8
       - Skip it if unavailable.
       - Construct the number and add it to `result`.

    5. Restore the tens digit frequency.

    6. Restore the hundreds digit frequency.

    7. Return the number of generated valid numbers.



    ------------------------------------------------------------
    Complexity:
    ------------------------------------------------------------

    There are at most:

        9 * 10 * 5

    possible digit combinations.

    Therefore the number of iterations is bounded by:

        O(9 * 10 * 5)

    which is effectively:

        O(1)

    because the number of possible digits is always fixed.

    The frequency array also has only 10 elements.



    Space Complexity:
    -----------------

    `v` contains 10 frequencies.

    `result` can contain at most 900 unique 3-digit numbers.

    Therefore the auxiliary/result space is:

        O(900)

    which is effectively:

        O(1)

    with respect to the input size.



    ------------------------------------------------------------
    Core Idea:
    ------------------------------------------------------------

    Count digit frequencies and build the number position by
    position.

        Hundreds -> 1 to 9
        Tens     -> 0 to 9
        Ones     -> 0, 2, 4, 6, 8

    Temporarily decrease the frequency when using a digit and
    restore it after exploring that choice.

    Because we iterate over digit VALUES rather than individual
    copies, duplicate digits do not generate duplicate numbers.

    The last digit is restricted to even digits, which guarantees
    that every generated number is even.
*/