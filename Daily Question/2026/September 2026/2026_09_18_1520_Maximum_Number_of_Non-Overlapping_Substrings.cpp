class Solution {
    public:
        vector<string> maxNumOfSubstrings(string s) {
            int n = s.size();
            vector<int> start(26, -1);
            vector<int> end(26, 0);
            vector<bool> isValid(26, true);
            vector<string> result;
    
            for(int i = 0; i < n; i++) {
                int idx = s[i] - 'a';
                if(start[idx] == -1) start[idx] = i;
                end[idx] = i;
            }
    
            // checking all characters
            for(int c = 0; c < 26; c++) {
                if(start[c] == -1) continue;
                for(int i = start[c]; i <= end[c]; i++) {
                    if(start[s[i] - 'a'] < start[c]) {
                        isValid[c] =false;
                        break;
                    }
                    end[c] = max(end[c], end[s[i] - 'a']);
                }
            }
    
            int lastTakenStart = INT_MAX;
            for(int i = n - 1; i >= 0; i--) {
                int c = s[i] - 'a';
                if(!isValid[c]) continue;
                if(i == start[c] && end[c] < lastTakenStart) {
                    result.push_back(s.substr(i, end[c] - i + 1));
                    lastTakenStart = i;
                }
            }
    
            return result;
        }
    };

/*
    LeetCode 1520 - Maximum Number of Non-Overlapping Substrings
    ------------------------------------------------------------

    Approach:
    ------------------------------------------------------------

    The main idea is to find, for every character, the smallest possible
    substring that contains ALL occurrences of that character and also
    contains all occurrences of every other character that appears inside it.

    Once we find all such valid substrings, we greedily select the maximum
    number of non-overlapping ones.

    Since there are only 26 lowercase English letters, we can process
    every character directly.


    ------------------------------------------------------------
    Key Observation:
    ------------------------------------------------------------

    For a character c, let:

        start[c] = first occurrence of c
        end[c]   = last occurrence of c

    Any substring containing ALL occurrences of c must contain at least:

        s[start[c] ... end[c]]

    However, this interval may contain some other character x.

    If x appears somewhere before start[c], then it is impossible for the
    substring starting at start[c] to contain ALL occurrences of x.

    Therefore, the interval for c is invalid.

    Otherwise, if x is completely contained inside the interval, we need
    to extend the right boundary so that it also contains the LAST
    occurrence of x.

    This process can continue recursively through other characters.


    Example:

        s = "adefaddaccc"

    Suppose we start with character 'a':

        a: first = 0, last = 6

    Initial interval:

        [0 ... 6] = "adefadd"

    Inside this interval we encounter:

        d, e, f

    Their last occurrences may extend the interval.

    We keep extending end[a] until every character inside the interval
    has all of its occurrences included.

    This gives the smallest valid substring associated with 'a'.


    ------------------------------------------------------------
    Step 1: Find first and last occurrence of every character
    ------------------------------------------------------------

    We maintain:

        vector<int> start(26, -1);
        vector<int> end(26, 0);

    For every character s[i]:

        idx = s[i] - 'a'

    If this is the first time we see the character:

        start[idx] = i

    Every occurrence updates:

        end[idx] = i

    After this pass:

        start[c] = first position of character c
        end[c]   = last position of character c


    Example:

        s = "abbc"

        a -> start = 0, end = 0
        b -> start = 1, end = 2
        c -> start = 3, end = 3


    ------------------------------------------------------------
    Step 2: Determine which character intervals are valid
    ------------------------------------------------------------

    We use:

        vector<bool> isValid(26, true);

    Initially every character is considered valid.

    For each character c, we start from:

        i = start[c]

    and scan until:

        i <= end[c]

    While scanning the interval, suppose we encounter character x.

    We check:

        if(start[x] < start[c])

    If this happens, x has an occurrence before the beginning of c's
    interval.

    Therefore, any substring containing all occurrences of c would need
    to start before start[c].

    So the substring associated with c cannot be a valid minimal
    substring starting at start[c].

    We mark:

        isValid[c] = false


    Otherwise, x is completely compatible with the current interval.

    We extend the right boundary using:

        end[c] = max(end[c], end[x]);

    This is important because the current interval must contain ALL
    occurrences of x, not just the occurrence currently being scanned.


    ------------------------------------------------------------
    Why can end[c] keep increasing?
    ------------------------------------------------------------

    Consider:

        s = "abacb"

    For 'a':

        start[a] = 0
        end[a]   = 2

    Initial interval:

        [0 ... 2] = "aba"

    While scanning it, we only see 'a' and 'b'.

    But:

        end[b] = 3

    Therefore we extend:

        end[a] = 3

    Now the interval is:

        [0 ... 3] = "abac"

    The newly included character 'c' has:

        end[c] = 3

    So the interval remains valid.

    The important idea is that a valid interval must be closed under
    character occurrences: every character appearing inside it must have
    all of its occurrences inside it.


    ------------------------------------------------------------
    Step 3: Select the maximum number of non-overlapping substrings
    ------------------------------------------------------------

    After finding valid intervals, we scan the string from RIGHT to LEFT.

    We maintain:

        int lastTakenStart = INT_MAX;

    This represents the start position of the most recently selected
    substring in the right-to-left greedy process.

    For every position i:

        c = s[i] - 'a'

    We only consider c if:

        isValid[c] == true


    We additionally require:

        i == start[c]

    This ensures that we consider the substring exactly once, at its
    starting position.


    The candidate substring is:

        [i ... end[c]]

    We select it when:

        end[c] < lastTakenStart


    This guarantees that the newly selected substring ends before the
    previously selected substring starts.

    Therefore, the two substrings do not overlap.


    ------------------------------------------------------------
    Why scan from right to left?
    ------------------------------------------------------------

    The goal is to maximize the NUMBER of substrings.

    Among possible valid intervals, selecting a substring that finishes
    earlier leaves more room for other substrings.

    The structure of the problem allows us to process the valid intervals
    from right to left and greedily take a valid interval whenever it fits.

    When scanning from right to left:

        - We encounter intervals according to their starting positions.
        - A selected interval becomes the boundary for what can be chosen
          before it.
        - Taking the valid interval whenever it does not overlap allows us
          to maximize the number of selected intervals.

    The condition:

        end[c] < lastTakenStart

    is exactly the non-overlap condition.


    ------------------------------------------------------------
    Example:
    ------------------------------------------------------------

    Consider:

        s = "adefaddaccc"

    The valid minimal substrings can include intervals such as:

        "e"
        "f"
        "ccc"
        "ad...a"

    The important property is that we want as many non-overlapping
    substrings as possible.

    Single-character substrings such as "e" and "f" are especially useful
    because they occupy very little space.

    The right-to-left greedy selection finds the compatible collection.


    ------------------------------------------------------------
    Another Example:
    ------------------------------------------------------------

    s = "abbaccd"

    Character ranges:

        a -> [0,3]
        b -> [1,2]
        c -> [4,5]
        d -> [6,6]

    For 'a':

        initial interval = [0,3]

    It contains 'b', whose complete range is [1,2].

    Since b's entire range lies inside [0,3], 'a' remains valid.

    So:

        "abba"

    is a valid substring.

    For 'c':

        range = [4,5]

    Therefore:

        "cc"

    is valid.

    For 'd':

        range = [6,6]

    Therefore:

        "d"

    is valid.

    We can choose:

        "abba"
        "cc"
        "d"

    These substrings do not overlap.


    ------------------------------------------------------------
    Important Condition:
    ------------------------------------------------------------

        start[s[i] - 'a'] < start[c]

    means that the character currently inside c's interval has an
    occurrence before c begins.

    Example:

        c starts at position 5

        x appears at position 2 and position 7

    If x appears inside c's interval at position 7, then selecting a
    substring starting at position 5 would not contain x's occurrence
    at position 2.

    Therefore c's interval cannot be valid.

    This is why:

        isValid[c] = false;

    is necessary.


    ------------------------------------------------------------
    Why do we update end[c]?
    ------------------------------------------------------------

    Suppose:

        c's current interval = [start[c], end[c]]

    and inside this interval we find character x.

    If:

        end[x] > end[c]

    then c's interval currently does not contain all occurrences of x.

    We therefore extend it:

        end[c] = max(end[c], end[x]);

    This guarantees that the final interval contains every occurrence
    of every character appearing inside it.


    ------------------------------------------------------------
    Why does this produce a valid substring?
    ------------------------------------------------------------

    For a character c to be valid:

        1. The substring starts at the first occurrence of c.
        2. It initially ends at the last occurrence of c.
        3. Every character encountered inside the interval must have
           its first occurrence at or after start[c].
        4. The right boundary is extended to include the last occurrence
           of every encountered character.

    Therefore, when the scan finishes, every character appearing in:

        s[start[c] ... end[c]]

    has ALL of its occurrences inside the same interval.

    Hence the substring is self-contained with respect to its characters.


    ------------------------------------------------------------
    Why does the greedy selection maximize the number?
    ------------------------------------------------------------

    After constructing all valid minimal intervals, the remaining
    problem is essentially an interval-selection problem:

        Select as many non-overlapping intervals as possible.

    The intervals are processed from right to left.

    When an interval:

        [i, end[c]]

    satisfies:

        end[c] < lastTakenStart

    it can safely be selected because it does not overlap the interval
    already selected on its right.

    Selecting it updates:

        lastTakenStart = i;

    so future intervals must finish before i.

    Because we are selecting compatible intervals while moving from
    right to left, we obtain the maximum possible number of
    non-overlapping valid substrings.


    ------------------------------------------------------------
    Why do we store strings in result?
    ------------------------------------------------------------

    Once a valid interval is selected:

        result.push_back(s.substr(i, end[c] - i + 1));

    The substring starts at i and has length:

        end[c] - i + 1


    ------------------------------------------------------------
    Time Complexity:
    ------------------------------------------------------------

    Let n = length of s.

    First pass to find first/last occurrences:

        O(n)

    There are only 26 characters.

    For each character, we scan its interval.

    Because the alphabet contains only 26 distinct characters, the
    interval construction is bounded by a small constant factor relative
    to n.

    The overall complexity is effectively:

        O(n)

    with respect to the input length, since the alphabet size is fixed
    at 26.


    ------------------------------------------------------------
    Space Complexity:
    ------------------------------------------------------------

    We use:

        start       -> 26 integers
        end         -> 26 integers
        isValid     -> 26 booleans
        result      -> output strings

    Apart from the output, the auxiliary space is:

        O(26) = O(1)

    The returned substrings themselves require space proportional to the
    output size.


    ------------------------------------------------------------
    Core Idea:
    ------------------------------------------------------------

    1. Find the first and last occurrence of every character.

    2. For every character, build the smallest interval containing all
       occurrences of that character.

    3. While building the interval:
           - If a character inside it started before the interval,
             the interval is invalid.
           - Otherwise extend the interval to include that character's
             last occurrence.

    4. Scan from right to left and greedily select valid intervals that
       do not overlap with the previously selected interval.

    5. Return the selected substrings.


    ------------------------------------------------------------
    Main Takeaway:
    ------------------------------------------------------------

    The problem has two important parts:

        Character closure
            +
        Greedy interval selection

    First, every candidate substring must be "closed" with respect to
    all character occurrences.

    Then, once valid intervals are known, we select the maximum number
    of mutually non-overlapping intervals using the right-to-left
    greedy scan.

    The key condition is:

        start[s[i] - 'a'] < start[c]

    to reject invalid intervals, and:

        end[c] < lastTakenStart

    to guarantee that selected substrings do not overlap.
*/