class Solution {
    public:
        string maxSumOfSquares(int num, int sum) {
            string result = "";
            while(sum >= 9) {
                result += "9";
                sum -= 9;
                num--;
            }
    
            if(sum > 0) {
                result += to_string(sum);
                sum = 0;
                num--;
            }
    
            while(num > 0) {
                result += "0";
                num--;
            }
    
            if(num < 0) return "";
    
            return result;
        }
    };

/*
    Approach: Greedy + Digit Construction

    The goal is to construct a number represented as a string containing
    exactly `num` digits such that the sum of its digits equals `sum`,
    while maximizing the sum of the squares of its digits.

    Each digit must be between 0 and 9.

    The key observation is that, to maximize the sum of squares, we
    should make the digits as large as possible. Therefore, we greedily
    place as many 9s as possible, followed by the remaining positive
    sum (if any), and then fill the remaining positions with zeros.

    ------------------------------------------------------------
    Key Observation: Why should we choose 9 first?
    ------------------------------------------------------------

    We want to maximize:

        d1^2 + d2^2 + ... + dnum^2

    subject to:

        d1 + d2 + ... + dnum = sum

    and:

        0 <= di <= 9

    For a fixed total digit sum, concentrating the sum into larger
    digits produces a larger sum of squares.

    For example, consider a total sum of 12.

        Digits [6, 6]:
            Sum of digits   = 12
            Sum of squares  = 6^2 + 6^2 = 72

        Digits [9, 3]:
            Sum of digits   = 12
            Sum of squares  = 9^2 + 3^2 = 90

    The second arrangement has a larger sum of squares.

    Therefore, we should use as many 9s as possible before using a
    smaller digit for the remaining sum.

    ------------------------------------------------------------
    Step 1: Initialize the result
    ------------------------------------------------------------

        string result = "";

    `result` stores the digits of the number we construct.

    We use a string because the answer is built digit by digit, and
    appending digits is straightforward.

    The variables mean:

        num  -> number of digit positions still available
        sum  -> digit sum still to be assigned
        result -> digits constructed so far

    As we append each digit, we decrease `num` because one position
    has been filled.

    ------------------------------------------------------------
    Step 2: Greedily append as many 9s as possible
    ------------------------------------------------------------

        while(sum >= 9) {
            result += "9";
            sum -= 9;
            num--;
        }

    A digit can contribute at most 9 to the total sum.

    Therefore, whenever `sum >= 9`, we can assign a digit of 9.

    Each iteration performs three operations:

        1. Append "9" to the result.
        2. Subtract 9 from the remaining sum.
        3. Decrease num because one digit position is occupied.

    The loop continues until the remaining sum is smaller than 9.

    Example:

        num = 4
        sum = 23

    First iteration:

        result = "9"
        sum = 23 - 9 = 14
        num = 3

    Second iteration:

        result = "99"
        sum = 14 - 9 = 5
        num = 2

    The remaining sum is now 5, so we cannot append another 9
    without exceeding the required digit sum.

    ------------------------------------------------------------
    Step 3: Append the remaining positive sum
    ------------------------------------------------------------

        if(sum > 0) {
            result += to_string(sum);
            sum = 0;
            num--;
        }

    After the previous loop, `sum` is between 0 and 8.

    If it is positive, it can be represented by a single digit.

    We append that digit directly using:

        to_string(sum)

    For the previous example:

        result = "99"
        sum = 5
        num = 2

    We append 5:

        result = "995"
        sum = 0
        num = 1

    One digit position remains, and the entire required digit sum
    has now been assigned.

    If `sum` is already zero, this step is skipped because no
    additional positive digit is needed.

    ------------------------------------------------------------
    Step 4: Fill the remaining positions with zeros
    ------------------------------------------------------------

        while(num > 0) {
            result += "0";
            num--;
        }

    Once the required sum has been assigned, any remaining digit
    positions must contain zeros.

    Adding zeros does not change the digit sum:

        sum + 0 = sum

    It also does not increase the sum of squares:

        0^2 = 0

    Continuing the example:

        result = "995"
        num = 1

    We append one zero:

        result = "9950"
        num = 0

    The result now contains exactly four digits, and their sum is:

        9 + 9 + 5 + 0 = 23

    ------------------------------------------------------------
    Step 5: Check whether the construction was possible
    ------------------------------------------------------------

        if(num < 0) return "";

    If `num` becomes negative, we have used more digit positions
    than were available.

    This can happen when the required sum cannot fit into the
    requested number of digits.

    For example:

        num = 2
        sum = 25

    The algorithm appends two 9s:

        result = "99"
        sum = 7
        num = 0

    A further positive digit is still required, but no digit
    positions remain.

    The next step appends 7 and decreases `num` to -1:

        result = "997"
        num = -1

    The final check detects that the construction exceeded the
    available number of positions and returns an empty string.

    ------------------------------------------------------------
    Detailed Example
    ------------------------------------------------------------

    Input:

        num = 3
        sum = 20

    Initially:

        result = ""
        num = 3
        sum = 20

    First loop iteration:

        Append 9
        result = "9"
        sum = 11
        num = 2

    Second loop iteration:

        Append 9
        result = "99"
        sum = 2
        num = 1

    The loop stops because sum < 9.

    Remaining-sum step:

        Append 2
        result = "992"
        sum = 0
        num = 0

    No zeros are required.

    Final result:

        "992"

    The digit sum is:

        9 + 9 + 2 = 20

    The sum of squares is:

        9^2 + 9^2 + 2^2 = 166

    ------------------------------------------------------------
    Edge Cases
    ------------------------------------------------------------

    1. sum = 0

       All digit positions are filled with zeros.

       Example:

           num = 3, sum = 0

           result = "000"

    2. sum is a multiple of 9

       Only 9s are appended during the greedy loop.

       Example:

           num = 3, sum = 18

           result = "990"

    3. sum is smaller than 9

       No 9s are appended. The remaining sum is placed into one
       digit, and all other positions are filled with zeros.

       Example:

           num = 4, sum = 5

           result = "5000"

    4. The required sum is too large

       If the sum cannot fit into `num` digits, the construction
       uses too many positions and returns an empty string.

    ------------------------------------------------------------
    Correctness Intuition
    ------------------------------------------------------------

    Every digit is at most 9, so assigning 9 whenever the remaining
    sum permits it maximizes the contribution of that position.

    After assigning as many 9s as possible, the remaining positive
    sum is smaller than 9 and therefore fits into one digit.

    Any positions left afterward are filled with zeros, preserving
    the required sum without adding to the sum of squares.

    If the construction requires more than `num` positions, the
    requested digit sum is impossible to represent using exactly
    `num` digits, so returning an empty string is appropriate.

    ------------------------------------------------------------
    Complexity Analysis
    ------------------------------------------------------------

    Time Complexity: O(num)

        Each digit position is filled at most once. The loops
        together construct at most `num` digits when the input
        is valid.

    Space Complexity: O(num)

        The result string stores the constructed number and can
        contain up to `num` digits.

    ------------------------------------------------------------
    Core Idea
    ------------------------------------------------------------

    Maximize the sum of squares by concentrating the required digit
    sum into as many 9s as possible, placing the remaining positive
    sum into one digit, and filling all unused positions with zeros.

    If the construction requires more positions than are available,
    return an empty string.
*/