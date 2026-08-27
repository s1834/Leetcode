class Solution {
    private:
        string result = "";
    
        bool solve(string& curr, vector<int>& count, string& target, int idx, bool greater) {
            // end of string
            if(idx == target.size()) {
                // if greater found
                if(greater) {
                    result = curr;
                    return true;
                }
                return false;
            }
    
            for(char ch = 'a'; ch <= 'z'; ch++) {
                if(count[ch - 'a'] == 0) continue; // if curr char didnt exist in 's' (i.e. count(char) = 0)
                if(greater == false && ch < target[idx]) continue; // if char is less than desired target[idx]
    
    
                curr.push_back(ch);
                count[ch - 'a']--;
                
                bool isGreater = greater || ch > target[idx];  // mark greater if already greater or current char is greater than target
    
                if(solve(curr, count, target, idx + 1, isGreater)) return true;  // recursively build remaining string; return true if a valid greater permutation is found
    
                // backtrack
                curr.pop_back();
                count[ch - 'a']++;
            }
            return false;
        }
    
    public:
        string lexGreaterPermutation(string s, string target) {
            vector<int> count(26, 0); // count of char of all 26 alphabets
            for(auto &x : s) count[x - 'a']++; // add count of each char
    
            string curr = "";
            solve(curr, count, target, 0, false);
    
            return result;
        }
    };

/*
LeetCode 3720. Lexicographically Smallest Permutation Greater Than Target

Approach:
---------

We are given a string s and a target string.

We need to rearrange all characters of s to create a permutation
which is:

    1. Strictly greater than target.
    2. Among all such permutations, lexicographically smallest.

We use:

    Frequency Array + Backtracking

The frequency array tells us which characters are still available,
and backtracking tries to build the answer from left to right.

------------------------------------------------------------

Frequency Array:
---------------

    vector<int> count(26, 0);

We store how many times each character occurs in s.

For example:

    s = "aabc"

then:

    count['a'] = 2
    count['b'] = 1
    count['c'] = 1

This allows us to use duplicate characters correctly.

------------------------------------------------------------

Backtracking State:
-------------------

    solve(curr, count, target, idx, greater)

where:

    curr
        = permutation constructed so far

    count
        = remaining frequency of every character

    target
        = target string we need to beat

    idx
        = current position we are filling

    greater
        = whether curr is already strictly greater than target
          in some previous position

The most important variable here is:

    greater

It tells us whether we have already become larger than target.

------------------------------------------------------------

Why Do We Need greater?
-----------------------

Consider:

    target = "abcd"

Suppose we build:

    curr = "ab..."

So far, curr and target are equal.

At this point, we cannot choose a character smaller than the
corresponding target character.

For example:

    target = "abcd"
    curr   = "ab..."

At index 2, choosing:

    'b'

would make:

    "abb..."

which is smaller than:

    "abc..."

So it can never become a valid answer later.

Therefore, while:

    greater == false

we must make sure:

    ch >= target[idx]

But if we have already chosen a larger character:

    target = "abcd"
    curr   = "abe..."

then the entire permutation is already greater than target.

After that point, we can choose ANY remaining character because
the prefix already guarantees:

    curr > target

------------------------------------------------------------

Base Case:
----------

    if(idx == target.size())

We have constructed a complete permutation.

Now there are two possibilities.

------------------------------------------------------------

Case 1: greater == true
------------------------

The complete permutation is strictly greater than target.

Therefore:

    result = curr;

and return true.

------------------------------------------------------------

Case 2: greater == false
-------------------------

The complete permutation is exactly equal to target.

But the problem requires:

    permutation > target

not:

    permutation >= target

Therefore, an equal permutation is invalid.

Return:

    false

------------------------------------------------------------

Try Characters in Alphabetical Order:
--------------------------------------

    for(char ch = 'a'; ch <= 'z'; ch++)

We always try characters from:

    'a' -> 'z'

This is extremely important.

We want the lexicographically smallest permutation that is
greater than target.

So at every position, we try the smallest possible character
first.

If a valid answer can be constructed using that character,
we immediately return it.

Because we try characters in increasing order, the first valid
complete permutation is the lexicographically smallest valid
one.

------------------------------------------------------------

Skip Unavailable Characters:
----------------------------

    if(count[ch - 'a'] == 0)
        continue;

If we don't have this character available in s, we cannot use it.

For example:

    s = "aabc"

If:

    count['d'] == 0

we simply skip 'd'.

------------------------------------------------------------

Don't Choose a Smaller Character While Equal:
----------------------------------------------

    if(greater == false && ch < target[idx])
        continue;

This is one of the most important conditions.

If we have not become greater yet, then choosing a smaller
character would immediately make the whole permutation smaller
than target.

For example:

    target = "abcd"
    idx = 1
    target[idx] = 'b'

If we choose:

    'a'

then:

    curr < target

and no future characters can fix it.

Therefore, we skip it.

------------------------------------------------------------

Three Possible Character Choices:
----------------------------------

When:

    greater == false

we have three possibilities.

    ch < target[idx]
        -> invalid
        -> skip

    ch == target[idx]
        -> remain equal
        -> continue with greater = false

    ch > target[idx]
        -> become greater
        -> continue with greater = true

When:

    greater == true

we can choose ANY available character because the prefix is
already larger than target.

------------------------------------------------------------

Choose the Character:
---------------------

    curr.push_back(ch);
    count[ch - 'a']--;

We add the selected character to our current permutation and
decrease its frequency because that copy has now been used.

For example:

    s = "aabc"

If we choose:

    'a'

then:

    curr = "a"
    count['a']--

------------------------------------------------------------

Update greater:
---------------

    bool isGreater = greater || ch > target[idx];

There are two ways for the new state to be greater.

1. We were already greater:

       greater == true

   Once we become greater, we ALWAYS remain greater.

2. We were equal so far, but the current character is greater:

       ch > target[idx]

Therefore:

    isGreater = greater || ch > target[idx];

Examples:

    greater = true
    ch = 'a'
    target = 'z'

Even though:

    'a' < 'z'

the result is still:

    isGreater = true

because an earlier character had already made the permutation
greater.

------------------------------------------------------------

Recursive Call:
----------------

    if(solve(curr, count, target, idx + 1, isGreater))
        return true;

Now recursively construct the next character.

If the recursive call finds a valid answer, immediately return
true.

We don't need to search for another answer because characters
are tried in alphabetical order.

Therefore, the first valid answer is the lexicographically
smallest one.

------------------------------------------------------------

Backtracking:
-------------

If the recursive call fails, we undo our choice:

    curr.pop_back();
    count[ch - 'a']++;

This restores the state so we can try another character.

For example:

    curr = "ab"
    count['c'] = 0

We try:

    'c'

and recursion fails.

We then undo:

    curr = "a"
    count['c'] = 1

and try the next available character.

This is the standard:

    Choose
       ↓
    Explore
       ↓
    Undo

backtracking pattern.

------------------------------------------------------------

Why Does Returning the First Valid Answer Work?
-----------------------------------------------

Suppose we have:

    target = "abcd"

At some position we can choose:

    'd'
    'e'
    'f'

Since we try:

    'd' first,

any valid permutation beginning with 'd' is lexicographically
smaller than every valid permutation beginning with 'e' or 'f'.

If no valid answer can be created with 'd', we backtrack and
try 'e'.

Therefore, the first complete valid permutation we find is the
lexicographically smallest possible answer.

------------------------------------------------------------

Example:
--------

Suppose:

    s = "aabc"
    target = "aabb"

Available characters:

    a -> 2
    b -> 1
    c -> 1

We build from left to right.

At index 0:

    target[0] = 'a'

We try:

    'a'

They are equal.

So:

    greater = false

At index 1:

    target[1] = 'a'

Again choose:

    'a'

Still:

    greater = false

At index 2:

    target[2] = 'b'

Available characters are:

    b
    c

Try:

    'b'

Still equal.

At index 3:

    target[3] = 'b'

Only:

    'c'

can be used.

Since:

    'c' > 'b'

we get:

    greater = true

So the permutation:

    "aabc"

is greater than:

    "aabb"

and is returned.

------------------------------------------------------------

Another Important Example:
--------------------------

Suppose:

    s = "abc"
    target = "abc"

We first try:

    a
    b
    c

The permutation becomes exactly:

    "abc"

At the end:

    greater == false

so it is rejected.

We backtrack.

Eventually we try:

    "acb"

At index 1:

    'c' > 'b'

so:

    greater = true

and:

    "acb" > "abc"

Therefore:

    "acb"

is returned.

------------------------------------------------------------

What Happens When We Choose a Larger Character?
-----------------------------------------------

This is the key idea behind the greedy + backtracking approach.

Suppose:

    target = "abcd"

and we are at:

    idx = 2

Target character:

    'c'

If we choose:

    'd'

then our prefix becomes:

    "abd..."

Since:

    "abd" > "abc"

the final permutation is guaranteed to be greater than target,
regardless of what characters we place afterward.

Therefore, after becoming greater, we no longer need to compare
future characters with target.

We can simply construct the remaining characters in the smallest
possible order.

Because our loop tries characters from 'a' to 'z', the remaining
characters will also be chosen as lexicographically small as
possible.

------------------------------------------------------------

Why We Don't Sort s:
--------------------

We could sort the characters, but the frequency array already
gives us the characters in alphabetical order.

Instead of:

    sort(s.begin(), s.end());

we maintain:

    count[26]

and try:

    'a' -> 'z'

at every position.

This also makes handling duplicate characters straightforward.

------------------------------------------------------------

Role of result:
---------------

    string result = "";

The result is stored as a class variable.

Once a valid permutation is found:

    result = curr;

and recursion returns true all the way back.

Finally:

    return result;

If no permutation is strictly greater than target, result remains:

    ""

and the function returns an empty string.

------------------------------------------------------------

Overall Flow:
-------------

                    Start
                      |
                      ↓
             Count characters
                      |
                      ↓
              idx = 0
                      |
                      ↓
          Try 'a' -> 'z'
                      |
              +-------+-------+
              |               |
          unavailable       available
              |               |
            skip          compare with target
                              |
                    +---------+---------+
                    |                   |
                  smaller           >= target
                    |                   |
                  skip              choose
                                        |
                                        ↓
                              update greater
                                        |
                                        ↓
                                  recurse
                                        |
                              +---------+---------+
                              |                   |
                            success              fail
                              |                   |
                           return             backtrack
                                                  |
                                                  ↓
                                             try next char

------------------------------------------------------------

The Important Invariant:
-------------------------

At every recursive call:

    curr

contains the characters chosen so far, and:

    count

contains exactly the characters that are still unused.

Also:

    greater == false

means:

    curr is still equal to the corresponding prefix of target.

While:

    greater == true

means:

    curr is already lexicographically greater than target.

This invariant is what allows us to safely prune smaller
characters.

------------------------------------------------------------

Why Can We Skip ch < target[idx]?
---------------------------------

Suppose the prefix is still equal.

For example:

    target = "abcde"
    curr   = "ab"

At idx = 2:

    target[idx] = 'c'

If we choose:

    'b'

then:

    curr = "abb..."

Since the first differing position is:

    'b' < 'c'

we know:

    curr < target

No matter what characters come afterward, the result can NEVER
become greater than target.

Therefore, this entire branch can be skipped.

This pruning is what makes the backtracking much more efficient
than blindly generating every permutation.

------------------------------------------------------------

Complexity:
-----------

There can be many possible permutations of s.

In the worst case, with all distinct characters, there can be:

    O(n!)

permutations.

The frequency array reduces duplicate work when characters
repeat, but the worst-case backtracking complexity is still
factorial.

For each recursive state, we try at most 26 characters.

So the worst-case complexity is approximately:

    O(26 * n!)

which is generally described as:

    O(n!)

for the permutation search.

Space complexity:

    O(n)

for:

    curr
    recursion stack

plus:

    O(26)

for the frequency array.

------------------------------------------------------------

Main Idea to Remember:
----------------------

This is a:

    Frequency Array + Backtracking + Greedy Ordering

problem.

The key logic is:

    greater == false
        ↓
    We are still equal to target.
        ↓
    Cannot choose a smaller character.

    ch == target[idx]
        ↓
    Stay equal.

    ch > target[idx]
        ↓
    We become greater permanently.

    greater == true
        ↓
    We can choose any remaining character.

And because we always try:

    'a' -> 'z'

the first valid complete permutation is the
lexicographically smallest permutation greater than target.

The core condition to remember is:

    if(!greater && ch < target[idx])
        continue;

and:

    bool isGreater = greater || ch > target[idx];

Finally:

    choose
    -> recurse
    -> if failed, undo
    -> try next character

This gives us the smallest permutation that is strictly greater
than the target.
*/