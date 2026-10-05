class Solution {
    public:
        int scoreOfParentheses(string s) {
            stack<int> st;
            int n = s.size(), score = 0;
    
            for(int i = 0; i < n; i++) {
                if(s[i] == '(')  {
                    st.push(score);
                    score = 0;
                } else {
                    if(s[i - 1] == '(') score = st.top() + 1;
                    else score = st.top() + (2 * score);
                    st.pop();
                }
            }
    
            return score;
        }
    };

/*
    ============================================================
    LeetCode 856 - Score of Parentheses
    ============================================================

    Approach: Stack
    ------------------------------------------------------------

    Every balanced parentheses string has a score defined by:

        "()"     -> 1
        AB       -> score(A) + score(B)
        (A)      -> 2 * score(A)

    The main difficulty is keeping track of the score belonging
    to each currently open pair of parentheses.

    We use a stack where each element stores the score that had
    already been accumulated BEFORE entering the current '('.

    `score` represents the score being built inside the current
    innermost pair of parentheses.

    ============================================================
    1. What Does the Stack Store?
    ============================================================

    When we encounter '(':

        st.push(score);
        score = 0;

    The current `score` belongs to the parent level.

    We save it on the stack and reset `score` because we are
    now starting to calculate the score inside this new pair.

    Example:

        "(())"

    When the first '(' is encountered:

        stack = [0]
        score = 0

    When the second '(' is encountered:

        stack = [0, 0]
        score = 0

    We are now calculating the innermost pair separately.

    ============================================================
    2. Handling ')'
    ============================================================

    When ')' is encountered, the current inner score has been
    completely calculated.

    There are two cases.

    ------------------------------------------------------------
    Case 1: "()"
    ------------------------------------------------------------

    If:

        s[i - 1] == '('

    then the current pair is directly "()".

    According to the scoring rules:

        "()" -> 1

    Therefore:

        score = st.top() + 1;

    The previous score stored on the stack is restored and
    the score of this new pair is added to it.

    ------------------------------------------------------------
    Case 2: "(A)"
    ------------------------------------------------------------

    Otherwise, the current pair contains another balanced
    parentheses expression.

    According to the scoring rule:

        (A) -> 2 * score(A)

    Therefore:

        score = st.top() + (2 * score);

    Here `score` is the score of A.

    We multiply it by 2 because A is enclosed inside a pair
    of parentheses.

    ============================================================
    3. Why Do We Pop the Stack?
    ============================================================

    After processing ')', the current pair is completely
    evaluated.

    Therefore, its corresponding '(' is no longer active:

        st.pop();

    The resulting `score` now belongs to the parent level.

    This allows nested expressions to naturally propagate
    their scores outward.

    ============================================================
    4. Example: "()()"
    ============================================================

    Start:

        score = 0
        stack = []

    First '(':

        stack = [0]
        score = 0

    First ')':

        Previous character is '('.

        score = 0 + 1 = 1

        stack = []

    Second '(':

        stack = [1]
        score = 0

    Second ')':

        Again, "()":

        score = 1 + 1 = 2

        stack = []

    Final answer:

        2

    This follows:

        score("()" + "()")
        = score("()") + score("()")
        = 1 + 1
        = 2

    ============================================================
    5. Example: "(())"
    ============================================================

    First '(':

        stack = [0]
        score = 0

    Second '(':

        stack = [0, 0]
        score = 0

    Second ')':

        Previous character is '('.

        Inner "()" has score 1.

        score = 0 + 1 = 1

        stack = [0]

    Final ')':

        Previous character is ')', so this is "(A)"
        where A has score 1.

        score = 0 + (2 * 1)
              = 2

        stack = []

    Final answer:

        2

    This follows:

        score("(())")
        = 2 * score("()")
        = 2 * 1
        = 2

    ============================================================
    6. Example: "(()())"
    ============================================================

    The inner content is:

        "()()"

    Its score is:

        1 + 1 = 2

    Therefore:

        "(()())"
        = 2 * 2
        = 4

    The stack allows the inner score 2 to be calculated first,
    then doubled when the outer ')' is encountered.

    ============================================================
    7. Why Check s[i - 1] == '('?
    ============================================================

    This condition identifies whether the current closing
    parenthesis directly closes an empty pair:

        "()"

    If the previous character is '(':

        score = 1

    Otherwise, the parentheses contain some already-calculated
    expression:

        "(A)"

    so:

        score = 2 * score(A)

    This avoids needing to explicitly store individual
    expressions or recursively parse the string.

    ============================================================
    8. Correctness Intuition
    ============================================================

    At every '(':

        - Save the score of the outer level.
        - Start a fresh score for the new inner level.

    At every ')':

        - If it closes "()", add 1.
        - Otherwise, double the score of the inner expression.
        - Add the resulting value to the outer score.
        - Remove the completed level from the stack.

    Therefore, nested expressions are evaluated from the
    inside outward, while consecutive expressions are added
    together.

    This exactly follows the three scoring rules.

    ============================================================
    Complexity Analysis
    ============================================================

    Time:  O(n)

        Every character is processed exactly once.

    Space: O(n)

        In the worst case, the stack contains one entry for
        every nested '('.

    ============================================================
    Core Idea
    ============================================================

    `score` stores the score of the current innermost level.

    On '(':
        Save the outer score and reset the current score.

    On ')':
        "()" -> add 1
        "(A)" -> add 2 * A

    The stack lets each completed inner expression return
    its score to the surrounding parentheses level.
    ============================================================
*/