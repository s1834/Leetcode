class Solution {
    public:
        string evaluate(string s, vector<vector<string>>& knowledge) {
            unordered_map<string, string> mp;
            for(auto &x : knowledge) mp[x[0]] = x[1];
    
            int n = s.size();
            string ans = "";
            for(int i = 0; i < n; i++) {
                if(s[i] == '(') {
                    i++;
                    string key = "";
                    while(i < n && s[i] != ')') {
                        key += s[i];
                        i++;
                    }
                    
                    if(mp.find(key) != mp.end()) ans += mp[key];
                    else ans += "?";
                } else ans += s[i];
            }
    
            return ans;
        }
    };

/*
    ============================================================
    LeetCode 1807 - Evaluate the Bracket Pairs of a String
    ============================================================

    Approach:
    ------------------------------------------------------------
    The string contains normal characters and bracket expressions
    of the form:

        (key)

    Each key has a corresponding value in the `knowledge` list.

    We first convert `knowledge` into an unordered_map:

        key -> value

    Then we scan the string from left to right.

    Whenever we encounter:

        '('

    we extract everything until the corresponding:

        ')'

    This gives us the key.

    We then look up the key in the map:

        - If the key exists:
              append its corresponding value.

        - If the key does not exist:
              append '?'.

    Normal characters are copied directly to the answer.


    ============================================================
    1. Building the Knowledge Map
    ============================================================

        unordered_map<string, string> mp;

        for(auto &x : knowledge)
            mp[x[0]] = x[1];

    ------------------------------------------------------------

    Each element of `knowledge` contains:

        {key, value}

    For example:

        knowledge =
        {
            {"name", "bob"},
            {"age", "20"}
        }

    becomes:

        mp["name"] = "bob"
        mp["age"]  = "20"

    Therefore, once we extract a key from the string, we can find
    its value in average O(1) time using the hash map.


    ============================================================
    2. Why Use an unordered_map?
    ============================================================

    We need to repeatedly answer:

        "What value corresponds to this key?"

    Searching the entire `knowledge` vector every time would take
    O(k) for each lookup, where k is the number of knowledge
    entries.

    By storing everything in:

        unordered_map<string, string>

    the lookup is O(1) on average.

    Therefore the string can be processed efficiently in one
    left-to-right scan.


    ============================================================
    3. Main String Traversal
    ============================================================

        int n = s.size();
        string ans = "";

        for(int i = 0; i < n; i++)

    ------------------------------------------------------------

    `i` represents the current character being processed.

    There are two possibilities:

        1. s[i] is '('
        2. s[i] is a normal character

    The code handles these two cases separately.


    ============================================================
    4. Normal Characters
    ============================================================

    If:

        s[i] != '('

    then the character is not the beginning of a bracket pair.

    Therefore:

        ans += s[i];

    simply copies it to the result.

    ------------------------------------------------------------

    Example:

        Input:
            "hello"

        Every character is copied directly:

            h
            e
            l
            l
            o

        Result:

            "hello"


    ============================================================
    5. Detecting a Bracket Pair
    ============================================================

    When:

        s[i] == '('

    we know a key starts immediately after it.

    The code does:

        i++;

    This skips the opening bracket.

    Then:

        string key = "";

    stores the characters belonging to the key.


    ============================================================
    6. Extracting the Key
    ============================================================

    The key is read until the closing bracket:

        while(i < n && s[i] != ')') {
            key += s[i];
            i++;
        }

    ------------------------------------------------------------

    For example:

        s = "(name)"

    After skipping '(':

        i points to 'n'

    The loop constructs:

        key = "name"

    It stops when:

        s[i] == ')'

    At this point, `key` contains the complete lookup key.


    ============================================================
    7. Looking Up the Key
    ============================================================

    After extracting the key, the code checks:

        if(mp.find(key) != mp.end())

    ------------------------------------------------------------

    This means:

        "Does this key exist in the knowledge map?"

    If it exists:

        ans += mp[key];

    Otherwise:

        ans += "?";


    ============================================================
    8. Known Key Example
    ============================================================

    Suppose:

        knowledge =
        {
            {"name", "bob"}
        }

    and:

        s = "Hi (name)"

    ------------------------------------------------------------

    The parser sees:

        H
        i
        space

    and copies them directly.

    Then it encounters:

        (name)

    It extracts:

        key = "name"

    The map contains:

        "name" -> "bob"

    Therefore:

        ans += "bob"

    Final answer:

        "Hi bob"


    ============================================================
    9. Unknown Key Example
    ============================================================

    Suppose:

        knowledge =
        {
            {"name", "bob"}
        }

    but:

        s = "Hi (age)"

    ------------------------------------------------------------

    The extracted key is:

        "age"

    But:

        mp.find("age") == mp.end()

    Therefore the code appends:

        "?"

    Final result:

        "Hi ?"


    ============================================================
    10. Complete Example
    ============================================================

    Suppose:

        s =
        "My name is (name) and I am (age)."

        knowledge =
        {
            {"name", "bob"},
            {"age", "20"}
        }

    ------------------------------------------------------------

    The scan processes:

        "My name is "

    directly.

    Then:

        (name)

    becomes:

        bob

    Then:

        " and I am "

    is copied.

    Then:

        (age)

    becomes:

        20

    Finally:

        "."

    is copied.

    Result:

        "My name is bob and I am 20."


    ============================================================
    11. Important Role of `i`
    ============================================================

    There is a subtle but important detail in:

        for(int i = 0; i < n; i++)

    and:

        while(i < n && s[i] != ')') {
        ...
        i++;
        }

    ------------------------------------------------------------

    When a bracket pair is encountered, the inner `while` moves
    `i` across the entire key until it reaches `')'`.

    For example:

        (hello)

         ^
         i

    after the inner loop, `i` points to:

        ')'

    Then the outer `for` loop performs its normal:

        i++

    which moves past the closing bracket.

    Therefore the entire:

        (hello)

    is processed as one unit.


    ============================================================
    12. Why We Do Not Need to Explicitly Process ')'
    ============================================================

    The closing bracket is only used as the boundary of the key.

    Once the `while` loop reaches:

        ')'

    we already know the key is complete.

    The outer loop's increment then moves past the closing bracket.

    Therefore there is no separate `else if` required for `')'`.


    ============================================================
    13. Why a Single Pass Is Enough
    ============================================================

    The expression has no nested bracket structure that requires
    recursive parsing.

    Every bracket pair is simply:

        '(' + key + ')'

    and keys do not contain nested brackets.

    Therefore we can process the entire string from left to right.

    There is no need for:

        - recursion
        - stack
        - dynamic programming
        - complex parsing


    ============================================================
    14. Correctness Intuition
    ============================================================

    Every character of the input belongs to exactly one of two
    categories:

        1. A normal character
        2. A complete bracket pair

    ------------------------------------------------------------

    For a normal character:

        ans += s[i]

    copies it unchanged.

    ------------------------------------------------------------

    For a bracket pair:

        (key)

    the algorithm:

        1. skips '('
        2. extracts `key`
        3. searches for `key` in `mp`
        4. appends the corresponding value if found
        5. otherwise appends '?'

    Therefore every part of the input is transformed according
    to the problem requirements.

    Since the scan processes the input from left to right, the
    relative order of all resulting pieces is preserved.


    ============================================================
    15. Complexity
    ============================================================

    Let:

        N = length of the string `s`

        K = number of entries in `knowledge`

    ------------------------------------------------------------

    Building the map:

        O(K)

    assuming average O(1) hash-map insertion.

    ------------------------------------------------------------

    Processing the string:

        O(N)

    because every character is processed while scanning through
    the string.

    Hash-map lookups are O(1) on average.

    ------------------------------------------------------------

    Therefore overall time complexity is approximately:

        O(N + K)

    excluding the cost of hashing/string copying in the usual
    complexity simplification.

    ------------------------------------------------------------

    Space complexity:

        O(K)

    for the knowledge map, plus the output string.

    More precisely, the map stores all key-value pairs, and `ans`
    requires space proportional to the output size.


    ============================================================
    16. Core Idea
    ============================================================

    The entire solution can be summarized as:

        1. Convert knowledge into:

               key -> value

        2. Scan the string.

        3. If the current character is normal:

               copy it.

        4. If the current character is '(':

               extract the key until ')'

        5. Look up the key.

        6. Append:
               value if found
               '?' otherwise

    ------------------------------------------------------------

    The key insight is that this is fundamentally a simple
    parsing + hash-map lookup problem.

    The `unordered_map` handles fast key lookup, while the single
    left-to-right scan handles extraction of each `(key)` pair.

    ============================================================
    Main Takeaway:

        unordered_map
              +
        linear string parsing
              =
        efficient bracket-pair evaluation

    The important implementation detail is that the same `i`
    pointer is used to scan both normal characters and the entire
    contents of each bracket pair, allowing the complete string
    to be processed in one pass.
    ============================================================
*/