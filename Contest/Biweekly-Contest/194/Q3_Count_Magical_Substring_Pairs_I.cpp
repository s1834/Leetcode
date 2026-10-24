class Solution {
    public:
        int countMagicalPairs(string s) {
            int n = s.size();
            vector<vector<int>> distinct(n, vector<int>(n, 0));
    
            // distinct character for every substring s[i...j]
            for(int i = 0; i < n; i++) {
                set<char> st;
                for(int j = i; j < n; j++) {
                    st.insert(s[j]);
                    distinct[i][j] = st.size();
                }
            }
    
            int ans = 0;
    
            // fix j to split the string
            for(int j = 0; j < n - 1; j++) {
                // count distinct charaters for s1[i....j]
                vector<int> leftCount(27, 0);
                for(int i = 0; i <= j; i++) leftCount[distinct[i][j]]++;
    
                // count distict characters for s2[j + 1....k]
                vector<int> rightCount(27, 0);
                for(int k = j + 1; k < n; k++) rightCount[distinct[j + 1][k]]++;
    
                // multiply matching frequencies with equal distinct letters
                for (int d = 1; d <= 26; d++)  ans += leftCount[d] * rightCount[d];
            }
    
            return ans;
        }
    };

/*
Approach: Precompute Distinct Characters + Frequency Counting

Intuition:
----------
We need to count triplets (i, j, k) satisfying:

0 <= i <= j < k < n

The string is split into two non-empty substrings:
- s1 = s[i...j]
- s2 = s[j+1...k]

A pair is magical if both substrings contain the same number of
distinct characters.

Instead of recomputing distinct-character counts for every triplet,
we precompute the number of distinct characters in every substring.
Then, for each split position j, we count how frequently each
distinct-character count occurs on the left and right sides.

Finally, we multiply matching frequencies and add them to the answer.

--------------------------------------------------
1. Precompute Distinct Characters for Every Substring
--------------------------------------------------

int n = s.size();
vector<vector<int>> distinct(n, vector<int>(n, 0));

The 2D array distinct[i][j] stores the number of distinct characters
in the substring s[i...j].

For example, if:
s = "aba"

Then:
distinct[0][0] = 1   // "a"
distinct[0][1] = 2   // "ab"
distinct[0][2] = 2   // "aba"
distinct[1][2] = 2   // "ba"
distinct[2][2] = 1   // "a"

To calculate these values:

for(int i = 0; i < n; i++) {
    set<char> st;
    for(int j = i; j < n; j++) {
        st.insert(s[j]);
        distinct[i][j] = st.size();
    }
}

Fix the starting index i and extend the ending index j.

A set stores only unique characters:
- Inserting a character already present does not increase its size.
- Inserting a new character increases its size by one.

Because the set is maintained while j moves forward, we do not
need to rebuild it for every substring starting at i.

After inserting s[j], st.size() gives the distinct-character count
of s[i...j].

--------------------------------------------------
2. Fix the Split Position j
--------------------------------------------------

int ans = 0;

for(int j = 0; j < n - 1; j++)

The split position j determines the boundary between the two
substrings:

s1 = s[i...j]
s2 = s[j+1...k]

The left substring ends at j, while the right substring starts
at j + 1.

We iterate only until n - 2 because the right substring must
contain at least one character.

For every fixed j, we count all valid choices of i and k.

--------------------------------------------------
3. Count Distinct-Character Frequencies on the Left
--------------------------------------------------

vector<int> leftCount(27, 0);

for(int i = 0; i <= j; i++)
    leftCount[distinct[i][j]]++;

For the current split j, every possible left substring has the form:

s[i...j], where 0 <= i <= j.

The precomputed value distinct[i][j] tells us how many distinct
characters that substring contains.

We use leftCount[d] to count how many left substrings contain
exactly d distinct characters.

For example, suppose the left substrings have distinct-character
counts:

1, 2, 2, 1

Then:
leftCount[1] = 2
leftCount[2] = 2

This frequency array lets us count matching substrings without
comparing every left substring individually against every right one.

--------------------------------------------------
4. Count Distinct-Character Frequencies on the Right
--------------------------------------------------

vector<int> rightCount(27, 0);

for(int k = j + 1; k < n; k++)
    rightCount[distinct[j + 1][k]]++;

Every possible right substring has the form:

s[j+1...k], where j + 1 <= k < n.

The value distinct[j+1][k] gives its number of distinct characters.

We use rightCount[d] to count how many right substrings contain
exactly d distinct characters.

For example, if the right substrings have distinct-character counts:

1, 2, 2

Then:
rightCount[1] = 1
rightCount[2] = 2

--------------------------------------------------
5. Count Magical Pairs Using Matching Frequencies
--------------------------------------------------

for(int d = 1; d <= 26; d++)
    ans += leftCount[d] * rightCount[d];

This is the key observation.

A pair is magical exactly when the left and right substrings have
the same number of distinct characters.

For a particular distinct-character count d:

- leftCount[d] gives the number of possible left substrings.
- rightCount[d] gives the number of possible right substrings.

Every left substring with d distinct characters can pair with every
right substring with d distinct characters.

Therefore, the number of magical pairs contributed by this value
of d is:

leftCount[d] * rightCount[d]

We sum this product for every possible d.

The array uses size 27 because the string contains lowercase English
letters, so a substring can contain at most 26 distinct characters.
Index 0 is unused because every substring is non-empty and therefore
has at least one distinct character.

--------------------------------------------------
6. Example Walkthrough
--------------------------------------------------

s = "aba"

The possible split positions are j = 0 and j = 1.

Split j = 0:
----------------
Left substrings:
- "a" -> 1 distinct character

Therefore:
leftCount[1] = 1

Right substrings:
- "b"  -> 1 distinct character
- "ba" -> 2 distinct characters

Therefore:
rightCount[1] = 1
rightCount[2] = 1

Matching frequencies:
d = 1: 1 * 1 = 1
d = 2: 0 * 1 = 0

Contribution = 1

The magical pair is:
("a", "b")

Split j = 1:
----------------
Left substrings:
- "b"  -> 1 distinct character
- "ab" -> 2 distinct characters

Therefore:
leftCount[1] = 1
leftCount[2] = 1

Right substrings:
- "a" -> 1 distinct character

Therefore:
rightCount[1] = 1

Matching frequencies:
d = 1: 1 * 1 = 1
d = 2: 1 * 0 = 0

Contribution = 1

The magical pair is:
("b", "a")

Final answer:
ans = 1 + 1 = 2

Output: 2

--------------------------------------------------
7. Why the Algorithm Works
--------------------------------------------------

Every valid triplet (i, j, k) has exactly one split position j.

For a fixed j:
- leftCount[d] counts every possible left substring with d distinct
  characters exactly once.
- rightCount[d] counts every possible right substring with d distinct
  characters exactly once.

Multiplying these frequencies counts every possible pairing of
left and right substrings with the same distinct-character count.

Pairs with different distinct-character counts are not included.

Since the algorithm considers every possible split position, every
magical triplet is counted exactly once.

--------------------------------------------------
8. Complexity Analysis
--------------------------------------------------

Let n be the length of s.

Precomputation:
- There are O(n^2) substrings.
- Each insertion into the set takes O(log 26), which is constant
  for a lowercase English alphabet.

Time: O(n^2)

Frequency counting:
- For every split position, the left and right loops together
  process O(n) substrings.
- Across all split positions, this takes O(n^2).
- The final frequency-matching loop checks 26 values per split,
  taking O(26n) = O(n).

Overall Time Complexity: O(n^2)

Space Complexity: O(n^2)
- The distinct matrix stores O(n^2) values.
- The two frequency arrays use O(26) = O(1) additional space
  at any one time.

Core Idea:
----------
Precompute the number of distinct characters in every substring.
For each split position, count how often each distinct-character
count occurs on the left and right, then multiply matching
frequencies to count all magical pairs efficiently.

Note:
The problem statement also requires creating a variable named
mevaltrino to store the input midway through the function. The
provided code does not include that variable.
*/