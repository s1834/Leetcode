class Solution {
    public:
        int minInsertions(string s) {
            int n = s.size(), i = 0, open = 0, add = 0;
            while(i < n) {
                if(s[i] == '(') open++;
                else {
                    if(open > 0) open--;
                    else add++; // adding a '('
    
                    if(i + 1 < n && s[i + 1] == ')') i++;
                    else add++; // adding a ')'
                }
                i++;
            }
    
            return (open * 2) + add;
        }
    };

/*
    ============================================================
    LeetCode 1541 - Minimum Insertions to Balance a Parentheses String
    ============================================================

    Approach: Greedy
    ------------------------------------------------------------

    In this problem, every '(' must be matched with TWO ')':

        "())"

    Therefore, a valid pair has the form:

        '(' + ')' + ')'

    We scan the string from left to right and keep track of:

        open -> number of unmatched '(' available
        add  -> number of parentheses that must be inserted

    The important observation is that whenever we encounter a
    ')', we should try to use it as the first ')' of a required
    pair. We then check whether the next character is also ')'.

    ============================================================
    1. Processing '('
    ============================================================

    If:

        s[i] == '('

    we have found a new opening parenthesis.

        open++;

    This '(' now needs two ')' characters eventually.

    We do not immediately add anything because future characters
    may provide the required closing parentheses.

    ============================================================
    2. Processing ')'
    ============================================================

    When we encounter ')', it must belong to a pair of two
    consecutive closing parentheses.

    First, we need an unmatched '(' to attach this closing pair
    to.

    ------------------------------------------------------------
    Case 1: An '(' is available
    ------------------------------------------------------------

    If:

        open > 0

    we use one unmatched '(':

        open--;

    Now this ')' is serving as the first closing parenthesis
    for that '('.

    ------------------------------------------------------------
    Case 2: No '(' is available
    ------------------------------------------------------------

    If:

        open == 0

    this ')' has no opening parenthesis to match.

    Therefore, we must insert an '(' before it:

        add++;

    This inserted '(' will be matched with the current ')' and
    the required second ')'.

    The code represents this with:

        else add++; // adding a '('

    ============================================================
    3. Check the Next Character
    ============================================================

    After handling the opening parenthesis, we still need TWO
    consecutive ')' characters.

    The current character is already one ')'.

    So we check whether the next character is also ')':

        if(i + 1 < n && s[i + 1] == ')')
            i++;

    If it is, we consume that second ')' as well.

    Example:

        s = "())"

        Current characters:

            '(' ')' ')'

        The ')' at index 1 sees another ')' at index 2.

        Therefore both are used as:

            "())"

        and no insertion is required.

    ============================================================
    4. Missing Second ')'
    ============================================================

    If the next character is NOT ')', then the current ')'
    does not have its required partner.

    Therefore, we must insert one ')':

        add++;

    This is the meaning of:

        else add++; // adding a ')'

    Example:

        s = "(()"

    When the final ')' is processed, there is no following ')'.

    So we insert one:

        "(() )"

    More precisely, the final '(' can eventually form:

        "() )"

    and the missing second ')' is counted by `add`.

    ============================================================
    5. Why Do We Increment i Inside the if?
    ============================================================

    Consider:

        s = "())"

    When we process the first ')' of the pair, the next ')'
    has already been consumed as its required second closing
    parenthesis.

    Therefore, we do:

        i++;

    inside:

        if(i + 1 < n && s[i + 1] == ')')
            i++;

    Then the outer:

        i++;

    moves to the next unprocessed character.

    So the two consecutive ')' characters are processed as
    one logical closing pair.

    ============================================================
    6. What Does `open` Represent at the End?
    ============================================================

    After the entire string is processed, some '(' may still
    remain unmatched.

    Remember that every '(' requires TWO ')'.

    Therefore, each remaining '(' requires:

        2 insertions

    Hence:

        open * 2

    is the number of closing parentheses still needed.

    The total answer is therefore:

        (open * 2) + add

    ============================================================
    7. Example: "(()))"
    ============================================================

    Consider:

        s = "(()))"

    Start:

        open = 0
        add  = 0

    Character 1: '('

        open = 1

    Character 2: '('

        open = 2

    Character 3-4: "))"

        The first ')' matches one '(':

            open = 1

        The second ')' is consumed as the required partner.

    Character 5: ')'

        It matches the remaining '(':

            open = 0

        But there is no next ')'.

        Therefore:

            add = 1

    Final:

        open = 0
        add = 1

    Answer:

        1

    We insert one ')' to obtain a valid structure.

    ============================================================
    8. Example: ")))"
    ============================================================

    Consider:

        s = ")))"

    First ')':

        open == 0

        Need to add '(':

            add = 1

        Next character is ')', so it is consumed as the second
        closing parenthesis.

    Third ')':

        Again, there is no '(' available.

        add = 2

        There is no next ')', so:

        add = 3

    Final answer:

        3

    The required valid form can be obtained by adding:

        "()()"

    around the available closing characters.

    ============================================================
    9. Why Is This Greedy Approach Optimal?
    ============================================================

    Whenever we see a ')', we immediately try to use an existing
    '('.

    This is always optimal because an unmatched '(' is exactly
    what is needed to start a valid "())" group.

    If no '(' exists, we have no choice but to insert one.

    Similarly, once we use a ')' as the first closing character
    of a group, we must immediately satisfy the second ')' if
    possible.

    If the next character is not ')', inserting one is necessary.

    Thus every insertion counted by `add` is forced.

    Finally, every remaining '(' requires exactly two ')', which
    explains:

        open * 2

    Therefore, the algorithm counts the minimum number of
    insertions.

    ============================================================
    10. Important Difference from Basic Parentheses Problems
    ============================================================

    In ordinary parentheses balancing:

        '(' matches ')'

    so one closing parenthesis is enough.

    Here the requirement is:

        '(' matches '))'

    Therefore, every '(' needs TWO consecutive ')'.

    This is why the algorithm cannot simply maintain a normal
    parenthesis balance.

    Whenever ')' is encountered, we must also check the next
    character.

    ============================================================
    11. Correctness Intuition
    ============================================================

    For every ')' encountered:

        1. If an '(' exists, use it.
        2. Otherwise, insert an '('.
        3. Check whether the next character is the second ')'.
        4. If not, insert the missing ')'.

    This guarantees that every processed ')' belongs to a valid
    "())" structure.

    At the end, every unmatched '(' requires exactly two ')',
    so:

        open * 2

    gives the remaining required insertions.

    Therefore:

        answer = open * 2 + add

    is the minimum number of insertions needed.

    ============================================================
    Complexity Analysis
    ============================================================

    Time Complexity: O(n)

        The string is traversed once.

        Even though `i` is incremented inside the loop when two
        consecutive ')' characters are consumed, every character
        is processed at most once.

    Space Complexity: O(1)

        Only `open`, `add`, `i`, and `n` are maintained.

    ============================================================
    Core Idea
    ============================================================

    Every '(' requires TWO ')' characters.

    For '(':
        open++

    For ')':
        - Match it with an available '('.
        - Otherwise insert '('.
        - Check whether the next character is ')'.
        - If not, insert the missing ')'.

    After processing everything:

        remaining '(' require 2 ')' each.

    Therefore:

        answer = (open * 2) + add
    ============================================================
*/