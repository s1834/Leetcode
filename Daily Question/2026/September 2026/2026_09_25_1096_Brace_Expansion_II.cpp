class Solution {
    private:
        int n;
        int idx;
        string s;
        
        set<string> getUnit() {
            set<string> result;
    
            if(s[idx] == '{') {
                idx++;
                result = performUnion();
            } else result = {string(1, s[idx])};
    
            idx++;
            return result;
        }
    
        set<string> performConcat() {
            set<string> result = {""};
    
            while(idx < n && (s[idx] == '{' || isalpha(s[idx]))) {
                set<string> temp = getUnit();
    
                set<string> concatResult;
                for(const string& left: result) {
                    for(const string& right : temp) {
                        concatResult.insert(left + right);
                    }
                }
                result = concatResult;
            }
    
            return result;
        }
    
        set<string> performUnion() {
            set<string> result;
    
            while(true) {
                set<string> temp = performConcat();
                result.insert(temp.begin(), temp.end());
    
                if(idx < n && s[idx] == ',') idx++;
                else break;
            }
    
            return result;
        }
    
    public:
        vector<string> braceExpansionII(string expression) {
            n = expression.size();
            s = expression;
            idx = 0;
    
            set<string> st = performUnion();
            vector<string> result(st.begin(), st.end());
    
            return result;
        }
    };

/*
    ============================================================
    LeetCode 1096 - Brace Expansion II
    ============================================================

    Approach:
    ------------------------------------------------------------
    The expression contains three important operations:

        1. Union:
           {a,b}  -> {"a", "b"}

        2. Concatenation:
           {a,b}{c,d} -> {"ac", "ad", "bc", "bd"}

        3. Single characters:
           a -> {"a"}

    The main challenge is that union and concatenation have
    different priorities.

    For example:

        {a,b}c

    first expands {a,b} into {"a","b"} and then concatenates
    "c" with every result:

        {"a","b"} + {"c"}
        = {"ac","bc"}

    Similarly:

        {a,b}{c,d}

    becomes the Cartesian product:

        {"a","b"} × {"c","d"}

        = {"ac","ad","bc","bd"}

    ------------------------------------------------------------
    Instead of building an explicit parse tree, the expression
    is parsed recursively using three functions:

        getUnit()
        performConcat()
        performUnion()

    These functions represent the grammar of the expression.
    ------------------------------------------------------------


    ============================================================
    1. Important Variables
    ============================================================

        int n;
        int idx;
        string s;

    ------------------------------------------------------------

        n
        ---
        Length of the expression.

        idx
        ---
        Current position while parsing the expression.

        s
        ---
        The input expression.

    ------------------------------------------------------------

    `idx` is shared by all parsing functions.

    Whenever a character or a complete brace expression is
    consumed, `idx` is advanced.

    This allows the recursive functions to parse the expression
    from left to right without repeatedly passing the current
    position as an argument.


    ============================================================
    2. Why `set<string>`?
    ============================================================

    All generated strings must be:

        - unique
        - sorted lexicographically

    `set<string>` provides both automatically.

    Therefore, instead of manually removing duplicates and
    sorting at the end, every intermediate result is stored in
    a set.

    Example:

        {a,a,b}

    produces:

        {"a", "b"}

    automatically.

    At the end:

        vector<string> result(st.begin(), st.end());

    converts the sorted set into the required vector.


    ============================================================
    3. Parsing Structure
    ============================================================

    The parser can be viewed as:

        expression
            |
            v
        performUnion()
            |
            v
        performConcat()
            |
            v
        getUnit()

    In other words:

        Union
          |
          +-- Concatenation
                 |
                 +-- Unit
                 +-- Unit
                 +-- Unit

    This structure naturally handles operator precedence.

    ------------------------------------------------------------

    `performUnion()` is the outermost operation.

    Each part separated by ',' is parsed using
    `performConcat()`.

    Inside each concatenation, individual units are parsed using
    `getUnit()`.

    Therefore:

        {a,b}c

    is interpreted as:

        Union
          |
          +-- Concatenation -> {a,b} + c

    rather than incorrectly treating `c` as another union item.


    ============================================================
    4. getUnit()
    ============================================================

        set<string> getUnit()

    A unit is either:

        1. A single alphabetic character
        2. A complete brace expression

    ------------------------------------------------------------

    Case 1:
    --------

        s[idx] == '{'

    Then we are starting a nested expression.

    The function does:

        idx++;

    to skip the opening `{`.

    Then:

        result = performUnion();

    parses everything inside the braces.

    For example:

        {a,b}

    after skipping `{`, `performUnion()` parses:

        a,b

    and returns:

        {"a","b"}

    Finally:

        idx++;

    skips the closing `}`.

    ------------------------------------------------------------

    Case 2:
    --------

    If the current character is alphabetic, then the unit is
    simply that character.

        result = {string(1, s[idx])};

    For example:

        a

    becomes:

        {"a"}

    Then `idx++` consumes that character.

    ------------------------------------------------------------

    Therefore `getUnit()` always returns a set of strings
    representing exactly one atomic component of the expression.


    ============================================================
    5. performConcat()
    ============================================================

        set<string> performConcat()

    This function handles concatenation.

    Example:

        {a,b}c

    The first unit produces:

        {"a","b"}

    The second unit produces:

        {"c"}

    Concatenating them means taking every string from the first
    set and every string from the second set.

    ------------------------------------------------------------

    The function starts with:

        set<string> result = {""};

    Why the empty string?

    Because concatenation has to start from an identity value.

    The empty string behaves like:

        "" + x = x

    Therefore, after reading the first unit:

        {""} × {"a","b"}

    produces:

        {"a","b"}

    ------------------------------------------------------------

    Then the function repeatedly reads units:

        while(idx < n &&
              (s[idx] == '{' || isalpha(s[idx])))

    This means concatenation continues while the next thing is
    either:

        - another `{...}` expression
        - an alphabetic character

    A comma or `}` means that the current concatenation has ended.

    ------------------------------------------------------------

    For every unit:

        set<string> temp = getUnit();

    `temp` contains all possible strings generated by that unit.

    We then calculate:

        result × temp

    using:

        for(const string& left: result) {
            for(const string& right: temp) {
                concatResult.insert(left + right);
            }
        }

    This is a Cartesian product.

    ------------------------------------------------------------

    Example:

        result = {"a","b"}
        temp   = {"c","d"}

    We generate:

        "a" + "c" = "ac"
        "a" + "d" = "ad"
        "b" + "c" = "bc"
        "b" + "d" = "bd"

    Therefore:

        concatResult =
        {
            "ac",
            "ad",
            "bc",
            "bd"
        }

    Then:

        result = concatResult;

    and parsing continues with the next unit.


    ============================================================
    6. performUnion()
    ============================================================

        set<string> performUnion()

    This function handles comma-separated alternatives.

    Example:

        a,b,c

    The function repeatedly calls:

        performConcat()

    for each part.

    ------------------------------------------------------------

    First:

        temp = performConcat();

    Suppose it returns:

        {"a"}

    Then:

        result.insert(temp.begin(), temp.end());

    adds those strings to the union.

    If the next character is a comma:

        if(idx < n && s[idx] == ',')
            idx++;

    we skip the comma and parse the next alternative.

    Otherwise, the union is complete.

    ------------------------------------------------------------

    Example:

        {a,b,c}

    performs:

        performConcat() -> {"a"}
        comma
        performConcat() -> {"b"}
        comma
        performConcat() -> {"c"}

    and finally:

        result = {"a","b","c"}


    ============================================================
    7. Nested Expressions
    ============================================================

    The recursive nature of `getUnit()` allows nested braces to
    be handled naturally.

    Example:

        {a,{b,c}}

    When `getUnit()` encounters the inner `{`, it calls:

        performUnion()

    recursively.

    The recursive call finishes parsing the inner expression
    before the outer expression continues.

    Therefore, arbitrarily nested brace expressions are handled
    without needing a separate stack.


    ============================================================
    8. Example 1
    ============================================================

    Expression:

        "{a,b}{c,d}"

    ------------------------------------------------------------

    First unit:

        {a,b}

    gives:

        {"a","b"}

    Second unit:

        {c,d}

    gives:

        {"c","d"}

    Since these units are adjacent, they are concatenated.

        {"a","b"} × {"c","d"}

    gives:

        "ac"
        "ad"
        "bc"
        "bd"

    Final result:

        ["ac","ad","bc","bd"]


    ============================================================
    9. Example 2
    ============================================================

    Expression:

        "{a,b}c"

    ------------------------------------------------------------

    First unit:

        {a,b}

    gives:

        {"a","b"}

    Second unit:

        c

    gives:

        {"c"}

    Concatenation produces:

        "a" + "c" = "ac"
        "b" + "c" = "bc"

    Final result:

        ["ac","bc"]


    ============================================================
    10. Example 3
    ============================================================

    Expression:

        "a{b,c}"

    ------------------------------------------------------------

    First unit:

        a

    gives:

        {"a"}

    Second unit:

        {b,c}

    gives:

        {"b","c"}

    Concatenation gives:

        "a" + "b" = "ab"
        "a" + "c" = "ac"

    Final result:

        ["ab","ac"]


    ============================================================
    11. Example 4 - Union and Concatenation Together
    ============================================================

    Expression:

        "{a,b}c{d,e}"

    ------------------------------------------------------------

    First:

        {a,b}
        -> {"a","b"}

    Then concatenate with:

        c
        -> {"c"}

    We get:

        {"ac","bc"}

    Then concatenate with:

        {d,e}
        -> {"d","e"}

    Cartesian product:

        "ac" + "d" = "acd"
        "ac" + "e" = "ace"
        "bc" + "d" = "bcd"
        "bc" + "e" = "bce"

    Final:

        {"acd","ace","bcd","bce"}


    ============================================================
    12. Example 5 - Why the Empty String Is Important
    ============================================================

    Suppose the expression is:

        {a,b}

    `performConcat()` starts with:

        result = {""}

    Then `getUnit()` returns:

        {"a","b"}

    Cartesian product:

        "" + "a" = "a"
        "" + "b" = "b"

    Therefore:

        result = {"a","b"}

    Without the empty string as the initial value, the first
    concatenation would have no existing left-hand side to
    combine with.


    ============================================================
    13. How `idx` Moves
    ============================================================

    Consider:

        {a,b}c

    Parsing roughly progresses as:

        idx
         |
         v
        { a , b } c

        0 1 2 3 4 5

    `getUnit()` sees `{`.

    It consumes `{` and recursively parses:

        a,b

    The recursive `performUnion()` stops when it reaches `}`.

    Then the outer `getUnit()` consumes `}`.

    `performConcat()` continues because the next character is:

        c

    It consumes `c`.

    Finally, `idx == n`.

    This shared pointer is what allows the parser to know exactly
    where each recursive expression ends.


    ============================================================
    14. Why the Parsing Is Correct
    ============================================================

    The key idea is that each function is responsible for exactly
    one grammatical operation.

    ------------------------------------------------------------

    `getUnit()`
    ------------

    Parses one atomic expression:

        character
        OR
        {...}

    ------------------------------------------------------------

    `performConcat()`
    ------------------

    Parses consecutive units.

    Example:

        A B C

    becomes:

        A × B × C

    ------------------------------------------------------------

    `performUnion()`
    -----------------

    Parses comma-separated concatenations.

    Example:

        A,B,C

    becomes:

        A ∪ B ∪ C

    ------------------------------------------------------------

    Because `performUnion()` calls `performConcat()`, and
    `performConcat()` calls `getUnit()`, nested expressions are
    evaluated in the correct structural order.


    ============================================================
    15. Correctness Intuition
    ============================================================

    We can reason about each level independently.

    ------------------------------------------------------------

    For `getUnit()`:

    It returns every possible expansion of exactly one unit.

    If the unit is a character, there is only one result.

    If the unit is `{...}`, recursive `performUnion()` returns
    every possible expansion inside the braces.

    Therefore `getUnit()` is correct.

    ------------------------------------------------------------

    For `performConcat()`:

    Suppose the current accumulated results are:

        A

    and the next unit can produce:

        B

    Every possible concatenation must be:

        a + b

    for some:

        a ∈ A
        b ∈ B

    The nested loops enumerate exactly these combinations.

    Therefore no valid concatenation is missed.

    ------------------------------------------------------------

    For `performUnion()`:

    Every comma-separated part is parsed independently using
    `performConcat()`.

    The results of all parts are inserted into the same set.

    Therefore the final set is exactly the union of all possible
    expansions.

    ------------------------------------------------------------

    Since these three functions recursively compose, the complete
    expression is expanded correctly.


    ============================================================
    16. Why `set` Automatically Handles Duplicates
    ============================================================

    Different expansion paths can sometimes generate the same
    string.

    For example:

        {a,a}

    has two alternatives, but both produce:

        "a"

    `set<string>` stores it only once.

    The same applies during concatenation.

    Therefore:

        concatResult.insert(left + right);

    automatically removes duplicate generated strings.

    It also keeps them lexicographically sorted.


    ============================================================
    17. Complexity
    ============================================================

    Let:

        R = number of distinct strings generated
        L = maximum length of a generated string

    ------------------------------------------------------------

    The parser itself processes the expression from left to
    right, so parsing overhead is roughly linear in the size of
    the expression.

    However, the expensive part is generating all possible
    strings.

    Concatenation may perform Cartesian products such as:

        A × B

    which can produce:

        |A| × |B|

    strings.

    Therefore the total complexity is dominated by the number of
    generated results and the cost of storing/inserting strings
    into the set.

    A useful high-level bound is approximately:

        O(R * L * log R)

    for the set operations, ignoring the additional intermediate
    Cartesian-product work.

    ------------------------------------------------------------

    Space Complexity:

        O(R * L)

    for storing the generated strings in the sets.

    The recursion depth is proportional to the nesting depth of
    braces.


    ============================================================
    18. Core Idea
    ============================================================

    The entire solution can be remembered as:

        Union
          |
          +------ concatenate alternatives
                       |
                       +------ parse each unit
                                  |
                                  +------ character
                                  |
                                  +------ nested {...}

    And the two fundamental set operations are:

        UNION:
            A ∪ B

        CONCATENATION:
            A × B
            = {x + y | x ∈ A, y ∈ B}

    The parser recursively applies these two operations while
    `idx` moves through the expression.

    `set<string>` simultaneously guarantees:

        - uniqueness
        - lexicographical ordering

    ------------------------------------------------------------
    Main Takeaway:

    This is essentially a recursive-descent parser where:

        performUnion()
            handles commas,

        performConcat()
            handles adjacent expressions,

        getUnit()
            handles characters and nested braces.

    Once the expression is viewed as a combination of UNION and
    CARTESIAN-PRODUCT CONCATENATION, the implementation becomes
    a direct translation of the expression's grammar.
    ============================================================
*/