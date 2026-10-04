class Solution {
    public:
        bool checkValidString(string s) {
            stack<int> st1, st2;
            int n = s.size();
            for(int i = 0; i < n; i++) {
                if(s[i] == '(') {
                    st1.push(i);
                } else if (s[i] == '*') {
                    st2.push(i);
                } else {
                    if(!st1.empty()) {
                        st1.pop();
                    } else if(!st2.empty()) {
                        st2.pop();
                    } else {
                        return false;
                    }
                }
            }
    
            while(!st1.empty() && !st2.empty()) {
                if (st1.top() > st2.top()) {
                    return false;
                }
                st1.pop();
                st2.pop();
            }
    
            if(st1.empty()) {
                return true;
            }
            return false;
        }
    };


/*
    ============================================================
    LeetCode 678 - Valid Parenthesis String
    ============================================================

    Approach: Greedy Matching Using Two Stacks
    ------------------------------------------------------------

    The string contains three types of characters:

        '(' -> Opening parenthesis
        ')' -> Closing parenthesis
        '*' -> Can represent '(', ')' or an empty string

    The goal is to determine whether we can assign a valid
    interpretation to every '*' such that the resulting string
    contains balanced parentheses.

    We use two stacks to store INDICES instead of characters:

        st1 -> Indices of unmatched '('
        st2 -> Indices of '*'

    Indices are important because a '*' can act as ')' for an
    unmatched '(' only if it appears AFTER that '('.


    ============================================================
    1. Traverse the String from Left to Right
    ============================================================

    We process every character and try to match each closing
    parenthesis as soon as possible.

    Case 1: s[i] == '('

        st1.push(i);

        Store the index of this opening parenthesis because it
        needs a matching ')' later.

    Case 2: s[i] == '*'

        st2.push(i);

        Store the wildcard index because we may need to use it
        as '(' or ')' later.

    Case 3: s[i] == ')'

        A closing parenthesis needs a matching opening
        parenthesis before it.

        We follow this priority:

        1. If st1 is not empty:
               Match ')' with an actual '('.
               Pop st1.

        2. Otherwise, if st2 is not empty:
               Use '*' as '(' to match ')'.
               Pop st2.

        3. If both stacks are empty:
               No opening parenthesis or wildcard is available
               to match this ')'.

               Return false immediately.

    Why do we return false immediately?

        Once a prefix contains more closing parentheses than
        can be matched by preceding '(' or '*', no character
        appearing later can fix that invalid prefix.


    ============================================================
    2. Why Do We Prefer '(' Over '*'?
    ============================================================

    When we encounter ')', we first match it with an actual
    opening parenthesis from st1.

    We use '*' only when no unmatched '(' is available.

    This preserves wildcard characters whenever possible,
    allowing them to help match other parentheses later.

    For example:

        s = "(*))"

        Index:  0   1   2   3
        Char:   (   *   )   )

        At index 2, ')' matches '(' at index 0.

        At index 3, no unmatched '(' remains, so '*' at index 1
        is used as '('.

        The resulting interpretation is:

            "()()"

        Therefore, the string is valid.


    ============================================================
    3. Handle Remaining Opening Parentheses
    ============================================================

    After the first traversal, every ')' has been matched.

    However, some '(' may remain in st1.

    These opening parentheses can potentially be matched using
    the remaining '*' characters, interpreting them as ')'.

    But there is an important ordering condition:

        The '*' must appear AFTER the '(' it closes.

    This is why we compare:

        st1.top() > st2.top()

    If this condition is true, the unmatched '(' occurs after
    the available '*'.

    That '*' cannot close this '(' because it appears earlier
    in the string.

    Therefore:

        if (st1.top() > st2.top())
            return false;

    Otherwise, the '*' appears after the '(' and can act as
    its closing parenthesis.

    We then remove both indices:

        st1.pop();
        st2.pop();

    Each such pair represents one valid '(' ... ')' match.


    ============================================================
    4. Why Are Indices Necessary?
    ============================================================

    Consider:

        s = "(*"

    After traversal:

        st1 = [0]
        st2 = [1]

    Since index 0 is before index 1, '*' can act as ')'.

    The resulting string is:

        "()"

    So the string is valid.

    Now consider:

        s = "*("

    After traversal:

        st1 = [1]
        st2 = [0]

    Here:

        st1.top() = 1
        st2.top() = 0

    Since 1 > 0, the '*' appears before the '('.

    It cannot close that opening parenthesis, so the string
    is invalid.

    Without indices, we could not correctly distinguish
    these two cases.


    ============================================================
    5. Final Validation
    ============================================================

    After matching remaining '(' with available '*':

        if(st1.empty())
            return true;

    If st1 is empty, every opening parenthesis has been matched.

    Any unused '*' can be interpreted as an empty string,
    so it does not make the string invalid.

    If st1 is not empty, some opening parentheses remain
    unmatched, meaning the string cannot be made valid.

    Therefore, return false.


    ============================================================
    6. Correctness Intuition
    ============================================================

    During the left-to-right traversal:

        - Every ')' is matched with an earlier '(' whenever
          possible.
        - Otherwise, '*' is used as '('.
        - If neither is available, the string is invalid.

    After the traversal:

        - Only unmatched '(' and unused '*' need consideration.
        - Each remaining '*' used as ')' must appear after
          its corresponding '('.
        - If all unmatched '(' can be paired this way, the
          remaining '*' can be treated as empty strings.

    Thus, the algorithm returns true exactly when a valid
    interpretation of the string exists.


    ============================================================
    7. Complexity Analysis
    ============================================================

    Time Complexity: O(n)

        Every character is processed once.
        Each index is pushed and popped at most once.

    Space Complexity: O(n)

        In the worst case, the stacks can store indices for
        a linear number of characters.


    ============================================================
    Core Idea
    ============================================================

    1. Match ')' with '(' first, then use '*' as '(' if needed.
    2. If neither is available, return false.
    3. Match remaining '(' with '*' that appears AFTER it.
    4. If any '(' remains unmatched, return false.
    5. Otherwise, return true.

    The two stacks track unmatched parentheses and wildcard
    positions so that both matching and ordering are respected.
    ============================================================
*/