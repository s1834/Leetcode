// Version 1: Using stack

// class Solution {
// public:
//     int minAddToMakeValid(string s) {
//         stack<char> st;
//         int n = s.size(), count = 0;
//         for (int i = 0; i < n; i++) {
//             if (s[i] == '(') {
//                 st.push(s[i]);
//             } else {
//                 if (!st.empty() && st.top() == '(') {
//                     st.pop();
//                 } else {
//                     st.push(s[i]);
//                 }
//             }
//         }

//         while(!st.empty()) {
//             st.pop();
//             count++;
//         }

//         return count;
//     }
// };

// Version 2: Open Bracket Counter

class Solution {
    public:
        int minAddToMakeValid(string s) {
            int open = 0, add = 0;
            for(auto &x : s) {
                if(x == '(') open++;
                else {
                    if(open > 0) open--;
                    else add++;
                }
            }
    
            return open + add;
        }
    };

/*
    ============================================================
    LeetCode 921 - Minimum Add to Make Parentheses Valid
    ============================================================

    Approach: Greedy
    ------------------------------------------------------------

    We need to find the minimum number of '(' or ')' that must
    be added so that the entire string becomes a valid
    parentheses string.

    We maintain two variables:

        open -> number of currently unmatched '('
        add  -> number of ')' that must be added

    We process the string from left to right.

    ============================================================
    1. Handling '('
    ============================================================

    If we encounter '(':

        open++;

    This opening parenthesis can potentially match a ')' that
    appears later.

    So we keep track of it as an unmatched opening parenthesis.

    ============================================================
    2. Handling ')'
    ============================================================

    If we encounter ')', there are two cases.

    ------------------------------------------------------------
    Case 1: There is an unmatched '('
    ------------------------------------------------------------

    If:

        open > 0

    then the current ')' can match one of those opening
    parentheses.

        open--;

    No additional parenthesis is required.

    ------------------------------------------------------------
    Case 2: There is no unmatched '('
    ------------------------------------------------------------

    If:

        open == 0

    then the current ')' has nothing before it that can match it.

    We must add an '(' before this ')' to make it valid.

        add++;

    We don't actually modify the string; we only count how many
    parentheses need to be added.

    ============================================================
    3. Why Do We Return open + add?
    ============================================================

    After processing the entire string:

        open

    represents opening parentheses that are still unmatched.

    Each unmatched '(' requires one ')' to be added after it.

    Therefore:

        open

    is exactly the number of additional ')' characters required.

    Meanwhile:

        add

    is the number of additional '(' characters required for
    unmatched ')' encountered during the traversal.

    Hence:

        answer = open + add;

    ============================================================
    4. Example: "())"
    ============================================================

    Start:

        open = 0
        add = 0

    Character 1: '('

        open = 1

    Character 2: ')'

        open > 0

        open = 0

    Character 3: ')'

        open == 0

        This ')' has no matching '('.

        add = 1

    Final:

        open = 0
        add = 1

    Answer:

        1

    We can add '(' before the final ')':

        "()()"

    ============================================================
    5. Example: "((("
    ============================================================

    Every character is '(':

        open = 3

    No ')' is available to match them.

    Therefore we need three ')' characters:

        "((()))"

    Answer:

        open + add
        = 3 + 0
        = 3

    ============================================================
    6. Example: "()))(("
    ============================================================

    Process from left to right:

        '(' -> open = 1
        ')' -> open = 0
        ')' -> add = 1
        ')' -> add = 2
        '(' -> open = 1
        '(' -> open = 2

    At the end:

        add = 2
        open = 2

    Therefore:

        answer = 2 + 2 = 4

    We need:
        - 2 '(' to match the two unmatched ')'
        - 2 ')' to match the two remaining '('

    ============================================================
    7. Why This Greedy Approach Is Optimal
    ============================================================

    Whenever we encounter ')', using an available unmatched
    '(' is always optimal because it resolves both parentheses
    without adding anything.

    If no '(' exists, the ')' cannot be matched by anything
    appearing later. Therefore, we must add an '('.

    Similarly, after the entire traversal, every remaining '('
    must be matched by adding a ')'.

    Thus, every required addition is counted exactly once.

    ============================================================
    Complexity
    ============================================================

    Time:  O(n)

        We scan the string exactly once.

    Space: O(1)

        Only two counters are maintained.

    ============================================================
    Core Idea
    ============================================================

    `open` = unmatched '(' currently available.

    `add` = number of '(' we must add for unmatched ')'.

    For '(':
        open++

    For ')':
        if(open > 0)
            open--;
        else
            add++;

    At the end:

        answer = open + add

    because every remaining '(' needs one ')' and every
    unmatched ')' already required one '('.
    ============================================================
*/
