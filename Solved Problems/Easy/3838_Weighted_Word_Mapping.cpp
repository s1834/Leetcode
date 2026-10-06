class Solution {
    public:
        string mapWordWeights(vector<string>& words, vector<int>& weights) {
            int n = words.size();
            string ans = "";
            for(int i = 0; i < n; i++) {
                int m = words[i].size();
                int sum = 0;
                for(int j = 0; j < m; j++) sum += weights[words[i][j] - 'a'];
                ans += char('z' - (sum % 26));
            }
            return ans;
        }
    };

/*
    ============================================================
    LeetCode 3838 - Map Word Weights
    ============================================================

    Approach:
    ------------------------------------------------------------

    Each character from 'a' to 'z' has a corresponding weight
    stored in the `weights` array.

    For every word:

        1. Convert each character into its corresponding weight.
        2. Add all weights of the characters in the word.
        3. Take the sum modulo 26 to get a value from 0 to 25.
        4. Map that value to a character using:

               'z' - (sum % 26)

    Append the resulting character to `ans`.

    ============================================================
    1. Mapping a Character to Its Weight
    ============================================================

    For a character:

        words[i][j]

    we use:

        words[i][j] - 'a'

    to convert the character into an index from 0 to 25.

    For example:

        'a' - 'a' = 0
        'b' - 'a' = 1
        'c' - 'a' = 2
        ...
        'z' - 'a' = 25

    Therefore:

        weights[words[i][j] - 'a']

    gives the weight assigned to that character.

    ============================================================
    2. Calculate the Weight of Each Word
    ============================================================

    For every word, we initialize:

        int sum = 0;

    Then traverse all its characters:

        for(int j = 0; j < m; j++)
            sum += weights[words[i][j] - 'a'];

    So `sum` represents the total weight of the current word.

    Example:

        word = "abc"

        weights['a'] = 2
        weights['b'] = 4
        weights['c'] = 5

        sum = 2 + 4 + 5
            = 11

    ============================================================
    3. Why Use sum % 26?
    ============================================================

    We need to map the total weight back to one of the
    26 lowercase English letters.

    Therefore, we reduce the sum to the range [0, 25]:

        sum % 26

    For example:

        sum = 37

        37 % 26 = 11

    So only the value 11 is used for the final character.

    ============================================================
    4. Convert the Value to a Character
    ============================================================

    The code uses:

        char('z' - (sum % 26))

    Unlike the usual mapping:

        'a' + value

    this problem maps the value in reverse order.

    The mapping is:

        value = 0  -> 'z'
        value = 1  -> 'y'
        value = 2  -> 'x'
        ...
        value = 25 -> 'a'

    Therefore, if:

        sum % 26 = 2

    then:

        'z' - 2 = 'x'

    The resulting character is appended to `ans`.

    ============================================================
    5. Example
    ============================================================

    Suppose a word has character weights whose sum is:

        sum = 28

    First:

        sum % 26 = 2

    Then:

        'z' - 2 = 'x'

    So this word contributes:

        'x'

    to the final answer.

    If there are multiple words, each word contributes exactly
    one character.

    ============================================================
    6. Building the Final Answer
    ============================================================

    `ans` starts as an empty string:

        string ans = "";

    After calculating the mapped character for each word:

        ans += char('z' - (sum % 26));

    Therefore, if there are `n` words, the final answer
    contains exactly `n` characters.

    ============================================================
    7. Why Does the Algorithm Work?
    ============================================================

    Every character has exactly one weight, obtained through
    its position in the alphabet.

    For each word, summing these weights gives its total weight.

    Taking modulo 26 converts that total into one of the
    26 possible alphabet positions.

    Finally, the expression:

        'z' - (sum % 26)

    performs the required reverse alphabetical mapping.

    Since every word is processed independently, appending
    one mapped character per word produces the required result.

    ============================================================
    Complexity Analysis
    ============================================================

    Let:

        n = number of words
        L = total number of characters across all words

    Time Complexity: O(L)

        Every character in every word is visited exactly once.

    Space Complexity: O(n)

        The output string contains one character per word.

        Apart from the output, only O(1) extra space is used.

    ============================================================
    Core Idea
    ============================================================

    For every word:

        1. Add the weights of all its characters.
        2. Compute sum % 26.
        3. Map it in reverse alphabetical order:

               'z' - (sum % 26)

        4. Append the resulting character to the answer.

    Thus, each word contributes exactly one character to `ans`.
    ============================================================
*/