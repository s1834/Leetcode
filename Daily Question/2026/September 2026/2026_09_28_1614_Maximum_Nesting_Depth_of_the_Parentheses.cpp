class Solution {
    public:
        int maxDepth(string s) {
            int open = 0, maxOpen = 0;
            for(auto &x : s) {
                if(x == '(') open++;
                else if(x == ')') {
                    maxOpen = max(maxOpen, open);
                    open--;
                }
            }
            return maxOpen;
        }
    };

/*
    ------------------------------------------------------------
    LeetCode 1614 - Maximum Nesting Depth of the Parentheses
    ------------------------------------------------------------

    Approach:
    ------------------------------------------------------------
    Maintain `open` as the current number of unmatched opening
    parentheses, which is exactly the current nesting depth.

        '(' -> open++
        ')' -> record current depth, then open--

    `maxOpen` stores the maximum depth seen so far.

    Example:

        "(1+(2*3)+((8)/4))+1"

    At the deepest point, there are 3 simultaneously open
    parentheses, so the answer is 3.

    ------------------------------------------------------------
    Why It Works:
    ------------------------------------------------------------
    Every '(' enters one nesting level and every ')' leaves one.
    Therefore `open` always represents the current depth.
    Taking the maximum value of `open` gives the maximum nesting
    depth.

    ------------------------------------------------------------
    Complexity:
    ------------------------------------------------------------
    Time:  O(n)  - each character is processed once.
    Space: O(1)  - only two counters are used.

    ------------------------------------------------------------
    Core Idea:
    ------------------------------------------------------------
    Count the currently open parentheses and keep the maximum.
    ============================================================
*/