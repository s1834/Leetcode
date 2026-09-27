class Solution {
    public:
        string reverseParentheses(string s) {
            stack<vector<char>> st;
            vector<char> v;
            for (auto c : s) {
                if(c == '(') {
                    st.push(v);
                    v.clear();
                } else if (c == ')') {
                    reverse(v.begin(), v.end());
                    vector<char> top = st.top();
                    st.pop();
                    top.insert(top.end(), v.begin(), v.end());
                    v = top;
                    for(auto x : v) cout << x << " ";
                    cout << endl;
                } else v.push_back(c);
            }
            return string(v.begin(), v.end());;
        }
    };

/*
    ============================================================
    LeetCode 1190 - Reverse Substrings Between Each Pair of
    Parentheses
    ============================================================

    Approach:
    ------------------------------------------------------------
    The main idea is to process the string from left to right
    while keeping track of the characters belonging to the
    currently active parenthesis level.

    The key operation is:

        When we encounter '(':
            save the current characters and start a new
            temporary vector for the contents inside the
            parentheses.

        When we encounter ')':
            reverse the characters inside the current
            parentheses, then append them to the characters
            that existed before '('.

    A stack is used to remember the characters that existed
    before every opening parenthesis.

    ------------------------------------------------------------

    The state is represented using:

        stack<vector<char>> st;
        vector<char> v;

    `v` contains the characters currently being constructed at
    the current parenthesis level.

    `st` contains previously completed outer levels.

    This naturally handles nested parentheses.


    ============================================================
    1. Why a Stack?
    ============================================================

    Parentheses can be nested.

    For example:

        abc(def(ghi)jkl)mno

    When we enter:

        (def(ghi)jkl)

    we temporarily leave the outer string and start constructing
    the inner part.

    When the inner `)` is encountered, we must return to the
    previous level.

    This is exactly the behavior of a stack:

        last opened parenthesis
        =
        first closed parenthesis

    Therefore parentheses naturally follow the LIFO property of
    a stack.


    ============================================================
    2. Meaning of `v`
    ============================================================

        vector<char> v;

    ------------------------------------------------------------

    `v` stores the characters currently being processed at the
    current nesting level.

    For example, while processing:

        abc(def)

    before encountering '(':

        v = ['a','b','c']

    When '(' is encountered, these characters are saved on the
    stack and `v` is cleared.

    Now:

        v = []

    As we process:

        def

    we get:

        v = ['d','e','f']

    When ')' is encountered, this vector is reversed and then
    attached to the saved outer part.


    ============================================================
    3. Meaning of `st`
    ============================================================

        stack<vector<char>> st;

    ------------------------------------------------------------

    The stack stores the contents that existed immediately before
    each opening parenthesis.

    For example:

        abc(def)

    when '(' is encountered:

        st.push(v);

    so:

        st.top() = ['a','b','c']

    and:

        v = []

    This allows us to restore the outer context when ')' is
    encountered.


    ============================================================
    4. Processing an Opening Parenthesis
    ============================================================

    When:

        c == '('

    the code executes:

        st.push(v);
        v.clear();

    ------------------------------------------------------------

    Suppose we currently have:

        v = "abc"

    and encounter:

        '('

    We save:

        st = ["abc"]

    and reset:

        v = ""

    Now `v` will contain only the substring inside the newly
    opened parentheses.


    ============================================================
    5. Processing Characters
    ============================================================

    For a normal character:

        else
            v.push_back(c);

    ------------------------------------------------------------

    The character is simply added to the current level.

    Example:

        input:
            abc

        v evolves as:

            []
            [a]
            [a,b]
            [a,b,c]

    No special processing is required until a parenthesis is
    encountered.


    ============================================================
    6. Processing a Closing Parenthesis
    ============================================================

    When:

        c == ')'

    the code performs three important operations.

        1. Reverse the current substring.

        2. Restore the previous outer level.

        3. Append the reversed substring to that outer level.


    ------------------------------------------------------------
    Step 1:
    --------

        reverse(v.begin(), v.end());

    If:

        v = "abc"

    it becomes:

        v = "cba"

    This implements the required reversal for the current pair
    of parentheses.


    ------------------------------------------------------------
    Step 2:
    --------

        vector<char> top = st.top();
        st.pop();

    `top` represents everything that existed before the matching
    opening parenthesis.

    For example:

        top = "xyz"

        v = "cba"

    after reversing the inner contents.


    ------------------------------------------------------------
    Step 3:
    --------

        top.insert(top.end(), v.begin(), v.end());

    This concatenates:

        top + reversed(v)

    Therefore:

        "xyz" + "cba"

    becomes:

        "xyzcba"

    Finally:

        v = top;

    makes this the current string at the outer level.


    ============================================================
    7. Example - Simple Parentheses
    ============================================================

    Input:

        "(abcd)"

    ------------------------------------------------------------

    Start:

        v = ""

    Encounter '(':

        st.push("")
        v = ""

    Read:

        a b c d

    Therefore:

        v = "abcd"

    Encounter ')':

        reverse(v)

        v = "dcba"

    Restore stack:

        top = ""

    Append:

        top + v
        = ""
        + "dcba"
        = "dcba"

    Therefore:

        v = "dcba"

    Final answer:

        "dcba"


    ============================================================
    8. Example - Characters Outside Parentheses
    ============================================================

    Input:

        "a(bc)d"

    ------------------------------------------------------------

    Process:

        a

        v = "a"

    Encounter '(':

        stack = ["a"]
        v = ""

    Process:

        b
        c

        v = "bc"

    Encounter ')':

        reverse("bc")
        -> "cb"

    Restore:

        top = "a"

    Append:

        "a" + "cb"
        = "acb"

    Then process:

        d

    giving:

        "acbd"


    ============================================================
    9. Example - Nested Parentheses
    ============================================================

    Consider:

        "(u(love)i)"

    ------------------------------------------------------------

    Start:

        v = ""

    First '(':

        st = [""]
        v = ""

    Read:

        u

    So:

        v = "u"

    Second '(':

        st.push(v)

    Therefore:

        st = ["", "u"]

        v = ""

    Read:

        love

    So:

        v = "love"

    Encounter inner ')':

        reverse("love")
        -> "evol"

    Restore:

        top = "u"

    Append:

        "u" + "evol"
        = "uevol"

    Therefore:

        v = "uevol"

    Now the outer ')' is encountered.

    Reverse:

        reverse("uevol")
        = "loveu"

    Restore:

        top = ""

    Append:

        "" + "loveu"

    Final result:

        "loveu"


    ============================================================
    10. Why Nested Parentheses Work
    ============================================================

    Consider:

        A(B(CD)E)F

    ------------------------------------------------------------

    The stack keeps one vector for every currently active
    parenthesis level.

    After entering:

        (B...

    the previous content:

        A

    is stored.

    After entering:

        (C...

    the current content:

        B

    is stored.

    Therefore:

        stack:

            [A, B]

    while `v` contains:

        CD

    ------------------------------------------------------------

    When `)` closes the inner pair:

        CD -> DC

    and it is attached to:

        B

    giving:

        BDC

    ------------------------------------------------------------

    When the outer `)` closes:

        BDC -> CDB

    and it is attached to:

        A

    giving:

        ACDB

    Finally:

        F

    is appended.

    Result:

        ACDBF

    ------------------------------------------------------------

    Thus the stack ensures that every closing parenthesis
    reverses exactly the substring belonging to its matching
    opening parenthesis.


    ============================================================
    11. Important Observation About Reversal
    ============================================================

    The reversal is performed immediately when the closing
    parenthesis is encountered:

        reverse(v.begin(), v.end());

    This works because a closing parenthesis tells us that the
    complete contents of the corresponding pair have now been
    constructed.

    Therefore we do not need to know the matching parenthesis
    beforehand.


    ============================================================
    12. Why We Save `v` Before Clearing It
    ============================================================

    Consider:

        abc(def)

    Before '(':

        v = "abc"

    If we simply cleared `v` without saving it, we would lose:

        "abc"

    Therefore:

        st.push(v);

    is performed first.

    Only then:

        v.clear();

    is called.

    The stack preserves the outer context while we construct the
    inner substring.


    ============================================================
    13. Why We Restore the Stack After `)`
    ============================================================

    When ')' is encountered, the current parenthesis level has
    finished.

    Therefore:

        st.top()

    gives the immediately enclosing level.

    After retrieving it:

        st.pop();

    removes that level because we are returning to it.

    This is exactly the standard stack behavior for nested
    structures.


    ============================================================
    14. Full Processing Example
    ============================================================

    Input:

        "a(bc(def)g)h"

    ------------------------------------------------------------

    Start:

        v = ""

    Read `a`:

        v = "a"

    Read `(`:

        stack = ["a"]
        v = ""

    Read `b`, `c`:

        v = "bc"

    Read `(`:

        stack = ["a", "bc"]
        v = ""

    Read `d`, `e`, `f`:

        v = "def"

    Read `)`:

        reverse("def")
        -> "fed"

    Restore:

        top = "bc"

    Append:

        "bc" + "fed"
        = "bcfed"

    So:

        v = "bcfed"

    Read `g`:

        v = "bcfedg"

    Read outer `)`:

        reverse("bcfedg")
        -> "gdefcb"

    Restore:

        top = "a"

    Append:

        "a" + "gdefcb"
        = "agdefcb"

    Finally read `h`:

        "agdefcbh"

    Final answer:

        "agdefcbh"


    ============================================================
    15. Correctness Intuition
    ============================================================

    At every point, `v` represents the string being constructed
    at the current parenthesis nesting level.

    ------------------------------------------------------------

    When we encounter '(':

        - the current outer string is saved
        - a new empty string is started

    Therefore all following characters belong to the new inner
    level.

    ------------------------------------------------------------

    When we encounter ')' :

        - all characters of the current inner level are complete
        - reversing `v` performs the required operation
        - the saved outer string is restored
        - the reversed inner string is appended

    Therefore the result of the completed parenthesis pair is
    correctly incorporated into its surrounding expression.

    ------------------------------------------------------------

    Since every parenthesis pair is processed exactly when its
    closing parenthesis is encountered, and nested pairs are
    resolved from the inside outward, every required reversal is
    applied in the correct order.


    ============================================================
    16. Why BFS / DP Is Not Needed
    ============================================================

    This is not a shortest-path or optimization problem.

    There is only one deterministic transformation:

        reverse the contents of every parenthesis pair.

    Therefore we only need:

        - one scan of the string
        - a stack for nesting
        - a vector for the current level


    ============================================================
    17. Complexity
    ============================================================

    Let:

        n = length of the input string.

    ------------------------------------------------------------

    Every character is read once during the main loop.

    However, `reverse()` and `insert()` can move multiple
    characters.

    In the worst case, nested parentheses can cause characters to
    participate in multiple reversals/copies.

    Therefore the worst-case time complexity of this direct
    implementation can be:

        O(n²)

    ------------------------------------------------------------

    Space Complexity:

        O(n)

    because the stack can store characters from multiple nesting
    levels, and the current vector also contains characters from
    the string.


    ============================================================
    18. Core Idea
    ============================================================

    The solution can be remembered using three operations:

        '('
        ----
        Save the current string on the stack and start a new
        inner string.

        normal character
        ----------------
        Add it to the current string.

        ')'
        ----
        Reverse the current string, restore the previous string,
        and append the reversed part.


    ------------------------------------------------------------

    In short:

        '('
            -> push outer context

        inside parentheses
            -> build inner string

        ')'
            -> reverse inner string
            -> pop outer context
            -> append reversed string


    ============================================================
    Main Takeaway
    ============================================================

    The key insight is that nested parentheses are naturally
    handled using a stack.

    The stack remembers:

        "What string existed before I entered this pair?"

    The vector `v` represents:

        "What am I currently building inside this level?"

    When the pair closes:

        current content
              |
              v
          reverse it
              |
              v
        attach to outer content

    Therefore the complete problem becomes a simple stack-based
    simulation of nested parentheses.

    The most important pattern to remember is:

        OPEN PARENTHESIS
            -> SAVE CURRENT STATE

        CLOSE PARENTHESIS
            -> TRANSFORM CURRENT STATE
            -> RESTORE PREVIOUS STATE
            -> MERGE

    This same stack pattern is useful for many problems involving
    nested expressions, parentheses, and recursive-looking
    structures.
    ============================================================
*/