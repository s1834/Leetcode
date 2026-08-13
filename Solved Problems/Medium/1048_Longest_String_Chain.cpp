class Solution {
    private:
        int dp[1000][1000];
    
        bool isPredecessor(string s1, string s2) {
            int n = s1.size(), m = s2.size();
            if(m != n + 1) return false; // if size difference is greater than 1
    
            int i = 0, j = 0;
            while(i < n && j < m) {
                if(s1[i] == s2[j]) {
                    i++;
                    j++;
                } else j++;
            }
    
            return i == n; // if all chars of i were successfully matched
        }
    
        int solve(vector<string>& words, int idx, int prevIdx) {
            if(idx >= words.size()) return 0;
    
            if(prevIdx != -1 && dp[idx][prevIdx] != -1) return dp[idx][prevIdx]; // already calculated
    
            int take = 0;
            if(prevIdx == -1 || isPredecessor(words[prevIdx], words[idx])) take = 1 + solve(words, idx + 1, idx);
            int skip = solve(words, idx + 1, prevIdx);
    
            if(prevIdx != -1) return dp[idx][prevIdx] = max(take, skip); // save ans in dp
            return max(take, skip);
        }
    
    public:
        int longestStrChain(vector<string>& words) {
            memset(dp, -1, sizeof(dp));
    
            auto lambda = [](const string& s1, const string& s2) {
                return s1.size() < s2.size();
            };
            sort(words.begin(), words.end(), lambda);
            
            return solve(words, 0, -1);
        }
    };

/*
LeetCode 1048. Longest String Chain

Approach:
---------

We are given a list of words.

A word s1 is a predecessor of s2 if:

    1. s2 has exactly one more character than s1
    2. We can insert exactly one character into s1 and obtain s2

For example:

    "abc" -> "abdc"

is valid because inserting 'd' gives "abdc".

We need to find the longest possible chain:

    word1 -> word2 -> word3 -> ...

where every word is a valid predecessor of the next word.

This solution uses:

    Sorting + Take/Skip DP + Memoization

------------------------------------------------------------

Why Sort the Words?
-------------------

We first sort the words by their length:

    sort(words.begin(), words.end(), lambda);

where:

    return s1.size() < s2.size();

This means shorter words appear before longer words.

For example:

    ["bdca", "a", "bda", "ba"]

becomes:

    ["a", "ba", "bda", "bdca"]

This is useful because a predecessor must always have exactly
one fewer character than the current word.

So after sorting, when we are at words[idx], any possible
predecessor must appear before it.

This lets us process the words from left to right using the
same Take/Skip DP pattern used in LIS.

------------------------------------------------------------

isPredecessor(s1, s2):
----------------------

    bool isPredecessor(string s1, string s2)

This function checks whether s1 can be a predecessor of s2.

For example:

    s1 = "abc"
    s2 = "abdc"

We need to determine whether adding exactly one character to
s1 can produce s2.

------------------------------------------------------------

Length Condition:
-----------------

    int n = s1.size(), m = s2.size();

    if(m != n + 1) return false;

A valid predecessor must have exactly one fewer character.

So:

    s1 = "abc"
    s2 = "abdc"

has:

    n = 3
    m = 4

which is valid.

But:

    "abc"
    "abcdef"

cannot be a predecessor relationship because the length
difference is greater than 1.

Therefore, we immediately return false.

------------------------------------------------------------

Two Pointers:
-------------

We use:

    int i = 0, j = 0;

where:

    i -> current character in s1
    j -> current character in s2

We want to check whether every character of s1 can be matched
in order inside s2 after skipping exactly one character.

------------------------------------------------------------

Matching Characters:
---------------------

If:

    s1[i] == s2[j]

then the characters match.

So we move both pointers:

    i++;
    j++;

For example:

    s1 = "abc"
    s2 = "abdc"

Start:

    i = 0 -> 'a'
    j = 0 -> 'a'

They match:

    i = 1
    j = 1

Then:

    'b' == 'b'

so:

    i = 2
    j = 2

------------------------------------------------------------

When Characters Don't Match:
----------------------------

If:

    s1[i] != s2[j]

we move only j:

    j++;

Why?

Because s2 has exactly one extra character.

So the mismatching character in s2 is the character that was
inserted.

For:

    s1 = "abc"
    s2 = "abdc"

At:

    i = 2 -> 'c'
    j = 2 -> 'd'

we have:

    'c' != 'd'

So we skip 'd':

    j++;

Now:

    i = 2 -> 'c'
    j = 3 -> 'c'

They match.

Therefore:

    i++;

    j++;

At the end:

    i == 3

which means all characters of s1 were successfully matched.

------------------------------------------------------------

Why Don't We Move i on a Mismatch?
-----------------------------------

This is an important part of the logic.

If:

    s1[i] != s2[j]

we assume s2[j] is the one extra character.

So we skip only s2[j]:

    j++;

We do NOT skip s1[i], because every character in s1 must
eventually be matched.

Since we already verified that s2 has exactly one extra
character, there can only be one such mismatch.

------------------------------------------------------------

Final Check:
------------

    return i == n;

At the end, if:

    i == n

then every character of s1 was successfully matched in s2.

Therefore, s1 is a valid predecessor of s2.

------------------------------------------------------------

Example:
--------

s1 = "abc"
s2 = "abdc"

Pointers:

    i -> s1
    j -> s2

Initially:

    a == a
    i++, j++

Then:

    b == b
    i++, j++

Then:

    c != d

Skip d:

    j++

Then:

    c == c
    i++, j++

Now:

    i == n

Therefore:

    true

------------------------------------------------------------

Example Where It Fails:
-----------------------

s1 = "abc"
s2 = "abd"

Both have the same length.

Immediately:

    m != n + 1

so:

    false

Another example:

    s1 = "abc"
    s2 = "abde"

Lengths differ by 1.

Compare:

    a == a
    b == b
    c != d -> skip d
    c != e -> no more matching

At the end:

    i != n

so:

    false

------------------------------------------------------------

Recursive DP:
-------------

The main function is:

    solve(words, idx, prevIdx)

The meaning of the state is:

    "What is the longest string chain we can create from
     words[idx] onward, assuming words[prevIdx] is the
     previously selected word?"

This is the same Take/Skip structure as:

    LeetCode 300 - Longest Increasing Subsequence
    LeetCode 646 - Maximum Length of Pair Chain

The only thing that changes is the condition for taking the
current element.

------------------------------------------------------------

Why prevIdx?
------------

To decide whether:

    words[idx]

can be added to the current chain, we need to know the previous
word:

    words[prevIdx]

Then we check:

    isPredecessor(words[prevIdx], words[idx])

For example:

    previous = "abc"
    current  = "abdc"

Since "abc" is a predecessor of "abdc", we can take the
current word.

------------------------------------------------------------

Initial State:
--------------

    solve(words, 0, -1)

At the beginning, there is no previous word.

So:

    prevIdx = -1

means:

    "We haven't selected any word yet."

Therefore, the first word can always be taken:

    if(prevIdx == -1 || ...)

------------------------------------------------------------

Base Case:
----------

    if(idx >= words.size()) return 0;

Once idx reaches the end of the array, there are no more words
to consider.

So the maximum additional chain length is:

    0

------------------------------------------------------------

Take Choice:
------------

    int take = 0;

We can take the current word if:

    prevIdx == -1

or:

    isPredecessor(words[prevIdx], words[idx])

If it is valid:

    take = 1 + solve(words, idx + 1, idx);

The +1 represents adding words[idx] to the chain.

After taking it, the current word becomes the new previous
word:

    prevIdx = idx

------------------------------------------------------------

Skip Choice:
------------

    int skip = solve(words, idx + 1, prevIdx);

We can always skip the current word.

When we skip it:

    idx -> idx + 1

but the previous selected word remains unchanged:

    prevIdx stays the same

------------------------------------------------------------

Choose the Maximum:
--------------------

    max(take, skip)

We want the longest chain.

Therefore:

    dp[idx][prevIdx] =
        max(take, skip)

------------------------------------------------------------

Memoization:
------------

The same state can be reached through different choices.

For example, we might reach:

    solve(5, 2)

through different chains.

But once we calculate the answer for:

    idx = 5
    prevIdx = 2

the result will always be the same.

So we store it:

    dp[5][2]

Your code checks:

    if(prevIdx != -1 && dp[idx][prevIdx] != -1)
        return dp[idx][prevIdx];

This prevents recalculating the same state.

------------------------------------------------------------

Why prevIdx == -1 Is Not Stored:
---------------------------------

The DP table uses:

    dp[idx][prevIdx]

but -1 cannot be used as an array index.

So your code only stores states where:

    prevIdx != -1

For the initial state:

    solve(0, -1)

we simply calculate and return the answer.

This is fine because that initial state is called only once.

------------------------------------------------------------

DP State:
---------

The most important thing to remember is:

    dp[idx][prevIdx]

means:

    "Longest string chain possible from idx onward,
     when words[prevIdx] is the last word already selected."

There are two changing pieces of information:

    idx
    prevIdx

which is why this is a 2D DP problem.

------------------------------------------------------------

Example of the Complete Chain:
-------------------------------

Suppose:

    words = ["a", "ba", "bda", "bdca"]

After sorting, they are already in the correct order.

Start:

    solve(0, -1)

Take:

    "a"

Then:

    "ba"

Check:

    "a" -> "ba"

Valid.

Then:

    "bda"

Check:

    "ba" -> "bda"

Valid.

Then:

    "bdca"

Check:

    "bda" -> "bdca"

Valid.

So the chain is:

    "a"
      ↓
    "ba"
      ↓
    "bda"
      ↓
    "bdca"

Length:

    4

------------------------------------------------------------

Why This Is Similar to LIS:
----------------------------

In LIS (LeetCode 300), we check:

    nums[prevIdx] < nums[idx]

Here, we check:

    isPredecessor(words[prevIdx], words[idx])

So the structure is the same:

    Current element
          |
       +--+--+
       |     |
      TAKE  SKIP
       |     |
       ↓     ↓
    valid   move forward
       |
       ↓
    1 + next state

The difference is simply the definition of "valid."

For LIS:

    previous < current

For String Chain:

    previous is a predecessor of current

------------------------------------------------------------

Why Sorting by Length Is Necessary:
------------------------------------

Suppose:

    "bdca"

and:

    "bda"

appear in arbitrary order.

If we process "bdca" before "bda", we would not yet have the
smaller predecessor available in our left-to-right DP order.

Sorting by length guarantees:

    shorter words
          ↓
    longer words

So a possible predecessor always comes before the word it can
lead to.

------------------------------------------------------------

Overall Flow:
-------------

        Sort by length
              |
              ↓
      solve(0, -1)
              |
              ↓
        Current word
              |
        +-----+-----+
        |           |
       TAKE        SKIP
        |           |
   predecessor?   idx + 1
        |
        ↓
  1 + solve(idx+1, idx)
        |
        +------+
               ↓
        max(take, skip)
               |
               ↓
          store in dp

------------------------------------------------------------

Complexity:
-----------

Let:

    n = number of words
    L = maximum word length

There are approximately:

    O(n²)

DP states because both:

    idx
    prevIdx

can vary.

For every state, checking whether one word is a predecessor
takes:

    O(L)

because of the two-pointer comparison.

Therefore, the DP portion is approximately:

    O(n² * L)

Sorting takes:

    O(n log n)

so the dominant complexity is:

    O(n² * L)

------------------------------------------------------------

Space Complexity:
-----------------

The DP table stores:

    O(n²)

states.

The recursion depth can be:

    O(n)

So overall:

    Space Complexity: O(n²)

with O(n) additional recursion-stack space.

------------------------------------------------------------

Main Pattern to Remember:
--------------------------

This is another:

    Sort + Take/Skip + Memoization

problem.

The state is:

    solve(idx, prevIdx)

At every word:

    TAKE:
        if previous word can be a predecessor

        1 + solve(idx + 1, idx)

    SKIP:
        solve(idx + 1, prevIdx)

Then:

    dp[idx][prevIdx] = max(take, skip)

The key new part compared with LIS is the
"isPredecessor()" function.

Remember the predecessor check as:

    1. Current word must be exactly one character longer.
    2. Match characters using two pointers.
    3. When characters differ, skip the extra character in
       the longer word.
    4. All characters of the shorter word must be matched.

*/