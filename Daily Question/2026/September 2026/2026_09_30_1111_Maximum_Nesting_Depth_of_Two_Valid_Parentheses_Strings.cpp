class Solution {
    public:
        vector<int> maxDepthAfterSplit(string seq) {
            int n = seq.size();
            vector<int> ans(n);
    
            int depth = 0;
            for(int i = 0; i < n; i++) {
                if(seq[i] == '(') {
                    depth++;
                    ans[i] = (depth % 2 == 0) ? 0 : 1;
                } else {
                    ans[i] = (depth % 2 == 0) ? 0 : 1;
                    depth--;
                }
            }
    
            return ans;
        }
    };

/*
    ============================================================
    LeetCode 1111 - Maximum Nesting Depth of Two Valid
    Parentheses Strings
    ============================================================

    Approach:
    ------------------------------------------------------------
    We need to split the given valid parentheses sequence into
    two valid subsequences while minimizing the maximum nesting
    depth between them.

    The key idea is to alternate parentheses between the two
    groups based on the current nesting depth.

    We maintain:

        depth
            -> current nesting depth

        ans[i]
            -> which group character i belongs to
               (0 or 1)

    We assign:

        odd depth  -> group 1
        even depth -> group 0

    This effectively distributes nested parentheses between the
    two groups and keeps their maximum depths balanced.


    ============================================================
    How the Algorithm Works
    ============================================================

    For an opening parenthesis:

        depth++;

        ans[i] = (depth % 2 == 0) ? 0 : 1;

    We first increase the depth because this '(' creates a new
    nesting level.

    Then we assign the parenthesis according to whether the new
    depth is odd or even.

    ------------------------------------------------------------

    For a closing parenthesis:

        ans[i] = (depth % 2 == 0) ? 0 : 1;

        depth--;

    Here we assign the closing parenthesis using the CURRENT
    depth, before decreasing it.

    This matches the nesting level of the corresponding opening
    parenthesis.

    Therefore an opening and its matching closing parenthesis are
    assigned to the same group.


    ============================================================
    Example
    ============================================================

    Consider:

        seq = "((()))"

    Track `depth`:

        char     depth       group

         (         1           1
         (         2           0
         (         3           1
         )         3           1
         )         2           0
         )         1           1

    Therefore:

        ans = [1, 0, 1, 1, 0, 1]

    The parentheses are distributed between the two groups so
    that the nesting depth is divided between them.


    ============================================================
    Why Alternating Depth Works
    ============================================================

    Suppose the original sequence has nesting depth:

        D

    Consecutive nesting levels are assigned alternately:

        depth 1 -> group 1
        depth 2 -> group 0
        depth 3 -> group 1
        depth 4 -> group 0
        ...

    Therefore each group receives roughly every other nesting
    level.

    So instead of one group containing the entire nesting depth,
    the maximum depth is divided approximately in half.


    ============================================================
    Why Closing Parentheses Use the Current Depth
    ============================================================

    Consider:

        "(())"

    Before processing the first closing parenthesis:

        depth = 2

    That ')' closes the parenthesis opened at depth 2.

    Therefore it must use the assignment corresponding to:

        depth = 2

    After assigning it, we do:

        depth--;

    and return to depth 1.

    This is why the code performs:

        ans[i] = ...
        depth--;

    rather than decreasing first.


    ============================================================
    Complexity
    ============================================================

    Let:

        n = seq.size()

    ------------------------------------------------------------

    Time:

        O(n)

    Every character is processed exactly once.

    Space:

        O(n)

    for the answer array.

    Apart from the required output, the algorithm uses only
    O(1) extra space.


    ============================================================
    Core Idea
    ============================================================

    Track the current nesting depth and alternate the assignment
    between the two groups based on its parity:

        odd depth  -> 1
        even depth -> 0

    This distributes the nested levels between the two
    subsequences and minimizes the maximum nesting depth.
    ============================================================
*/