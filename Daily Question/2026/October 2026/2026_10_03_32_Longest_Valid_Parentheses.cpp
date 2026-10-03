class Solution {
    public:
        int longestValidParentheses(string s) {
            int result = 0;
            int open = 0, close = 0;
            int n = s.size();
    
            // left to right
            for(int i = 0; i < n; i++) {
                if(s[i] == '(') open++;
                else close++;
    
                if(open == close) result = max(result, open + close);
                else if(close > open) open = close = 0;
            }
    
            open = 0;
            close = 0;
            
            // right to left
             for(int i = n - 1; i >= 0; i--) {
                if(s[i] == '(') open++;
                else close++;
    
                if(open == close) result = max(result, open + close);
                else if(close < open) open = close = 0;
            }
    
            return result;
        }
    };

/*
    ============================================================
    LeetCode 32 - Longest Valid Parentheses
    ============================================================

    Approach:
    ------------------------------------------------------------
    Use two passes with two counters:

        open  -> number of '(' encountered
        close -> number of ')' encountered

    First, scan from left to right to handle cases where there
    are too many closing parentheses.

    Then, scan from right to left to handle cases where there
    are too many opening parentheses.

    Whenever open == close, we have a valid substring of length:

        open + close

    Update `result` with the maximum such length.


    ============================================================
    1. Left-to-Right Pass
    ============================================================

    Count opening and closing parentheses.

        '(' -> open++
        ')' -> close++

    If:

        open == close

    the current substring has equal numbers of opening and
    closing parentheses. Update the maximum length.

    If:

        close > open

    the substring cannot be valid because a closing parenthesis
    appears without a matching opening parenthesis.

    Reset both counters to zero and start a new candidate
    substring.

    This pass handles extra closing parentheses.

    Example:

        ")()())"

    Whenever close exceeds open, reset the counters so that
    invalid prefixes do not affect later substrings.


    ============================================================
    2. Right-to-Left Pass
    ============================================================

    Reset the counters and scan from right to left.

    Again:

        '(' -> open++
        ')' -> close++

    If:

        open == close

    update `result` with `open + close`.

    However, when scanning backward, too many opening
    parentheses means the current substring cannot be valid.

    Therefore, if:

        close < open

    reset both counters.

    This pass handles extra opening parentheses that the
    left-to-right pass alone might miss.

    Example:

        "(()"

    The left-to-right pass never sees close > open, so it cannot
    count the entire string as valid.

    The right-to-left pass detects the unmatched opening
    parenthesis and resets the counters.


    ============================================================
    3. Why Are Two Passes Necessary?
    ============================================================

    Consider:

        "(()"

    The left-to-right pass sees:

        open = 1, close = 0
        open = 2, close = 0
        open = 2, close = 1

    The counters never become equal, so the valid substring
    "()" is not detected by this pass.

    The right-to-left pass handles this imbalance and finds
    the valid substring "()" of length 2.

    Conversely, scanning left to right handles strings with
    unmatched closing parentheses.

    Together, the two passes handle both types of imbalance.


    ============================================================
    Complexity
    ============================================================

    Time:  O(n) - two linear scans of the string.

    Space: O(1) - only counters and the result are maintained.


    ============================================================
    Core Idea
    ============================================================

    Left to right:
        Reset when close > open.

    Right to left:
        Reset when open > close.

    Whenever open == close:
        result = max(result, open + close).

    The two directions ensure that both unmatched closing and
    unmatched opening parentheses are handled.
    ============================================================
*/