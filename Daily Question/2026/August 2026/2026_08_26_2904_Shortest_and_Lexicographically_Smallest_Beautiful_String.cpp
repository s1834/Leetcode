class Solution {
    public:
        string shortestBeautifulSubstring(string s, int k) {
            int left = 0, right = 0, n = s.size(), count = 0;
            string ans = "";
            while(right < n) {
                // increase count if 1
                if(s[right] == '1') count++;
    
                if(count == k) {
                    while(s[left] == '0' && left <= right) left++; // remove preceding zeros
                    
                    string curr = s.substr(left, right - left + 1);
                    if(ans == "" || curr.size() < ans.size() || (curr.size() == ans.size() && curr < ans)) ans = curr; // add if a shorter lexicographically string found
                    
                    // remove leftmost one
                    count--;
                    left++;
                }
                right++;
            }
    
            return ans;
        }
    };

/*
LeetCode 2904. Shortest and Lexicographically Smallest Beautiful String

Approach:
---------

A substring is called "beautiful" if it contains exactly k
characters equal to '1'.

We need to find the substring that:

    1. Contains exactly k ones.
    2. Has the minimum length.
    3. If multiple substrings have the same minimum length,
       return the lexicographically smallest one.

We use the Sliding Window / Two Pointer approach.

------------------------------------------------------------

Main Idea:
----------

We maintain a window:

    [left ... right]

and keep track of:

    count = number of '1's inside the current window

We expand the window using right.

Whenever:

    count == k

the current window contains exactly k ones.

Now we try to remove unnecessary leading zeros from the
window so that we get the shortest possible substring ending
at right.

Then we compare this candidate with our current answer.

------------------------------------------------------------

Variables:
----------

    int left = 0;

Left boundary of the sliding window.

    int right = 0;

Right boundary of the sliding window.

    int count = 0;

Number of '1's currently inside the window.

    string ans = "";

Best beautiful substring found so far.

------------------------------------------------------------

Expand the Window:
------------------

    while(right < n)

We move right from left to right through the string.

Whenever:

    s[right] == '1'

we increase the number of ones:

    if(s[right] == '1')
        count++;

So at every point:

    count

represents the number of ones inside:

    s[left ... right]

------------------------------------------------------------

When count == k:
----------------

    if(count == k)

Now the current window contains exactly k ones.

However, it might contain unnecessary zeros at the beginning.

For example:

    s = "001010"

Suppose our window is:

    00101

and it contains exactly 2 ones.

The leading zeros:

    00

do not contribute anything to the number of ones.

So they can be removed without changing the number of ones.

------------------------------------------------------------

Remove Leading Zeros:
----------------------

    while(s[left] == '0' && left <= right)
        left++;

This moves left forward while the current left character is
zero.

For example:

    00101
    ^^
    ||

After removing the unnecessary zeros:

    101

Now the substring still contains exactly k ones, but it is
shorter.

This is important because we want the shortest beautiful
substring.

------------------------------------------------------------

Why Only Remove Zeros?
----------------------

We cannot remove a '1'.

If we remove a '1', then:

    count < k

and the substring is no longer beautiful.

Therefore, once we have exactly k ones, the only characters
we can safely remove from the left are zeros.

------------------------------------------------------------

Create Current Candidate:
--------------------------

    string curr = s.substr(left, right - left + 1);

Now:

    curr

is the shortest valid substring ending at right that contains
exactly k ones.

We compare it with our current answer.

------------------------------------------------------------

Choosing the Best Answer:
--------------------------

    if(ans == "" ||
       curr.size() < ans.size() ||
       (curr.size() == ans.size() && curr < ans))

There are three cases.

------------------------------------------------------------

Case 1: No Answer Yet
---------------------

    ans == ""

If this is the first valid beautiful substring we found,
simply store it:

    ans = curr

------------------------------------------------------------

Case 2: Current String Is Shorter
---------------------------------

    curr.size() < ans.size()

The problem asks for the shortest beautiful substring.

Therefore, a shorter valid substring is always better.

Example:

    ans  = "10101"  -> length 5
    curr = "101"    -> length 3

So:

    ans = curr

------------------------------------------------------------

Case 3: Same Length
-------------------

If:

    curr.size() == ans.size()

then length cannot decide which one is better.

The problem says to choose the lexicographically smallest
substring.

So we compare:

    curr < ans

For strings of the same length, normal C++ string comparison
gives lexicographical ordering.

For example:

    "10101" < "10110"

because the first different character is:

    0 < 1

Therefore, we choose:

    "10101"

------------------------------------------------------------

Why Lexicographical Comparison Works:
--------------------------------------

C++ compares strings lexicographically, character by character.

For binary strings:

    '0' < '1'

So if two candidate substrings have the same length, the one
with a '0' earlier at the first differing position is smaller.

Therefore:

    curr < ans

directly implements the problem's lexicographical requirement.

------------------------------------------------------------

After Recording a Candidate:
----------------------------

    count--;

    left++;

This is an important step.

We currently have a window containing exactly k ones.

To search for the next possible beautiful substring, we need
to move the left boundary past the leftmost '1'.

Why?

Because if we only move right while keeping all k ones, we
would keep considering the same group of k ones.

By removing the leftmost one:

    count--

we allow the next '1' to enter the window later.

------------------------------------------------------------

Why left++ Is Safe Here:
------------------------

Before this point, we already removed all leading zeros.

Therefore:

    s[left] == '1'

So:

    count--;

    left++;

means:

    "Remove the leftmost 1 from the current window."

This changes the window from:

    exactly k ones

to:

    k - 1 ones

Then we continue moving right.

When the next '1' arrives, count becomes k again and we
evaluate another candidate.

------------------------------------------------------------

Example:
--------

Consider:

    s = "110001110"
    k = 3

We move right and count ones.

When we reach the third '1', we have a window containing:

    11000111

There are exactly 5? No — after trimming and depending on the
current left boundary, we keep only the necessary prefix.

The important process is:

    1. Expand right until count == k.
    2. Remove leading zeros.
    3. Evaluate the candidate.
    4. Remove the leftmost 1.
    5. Continue searching.

This allows us to examine the best substring for each group of
k consecutive ones.

------------------------------------------------------------

Important Observation:
-----------------------

A beautiful substring must contain exactly k ones.

Suppose the ones are positioned at:

    p1, p2, p3, ..., pk

For any substring containing exactly these k ones, the shortest
possible substring must start at:

    p1

and end at:

    pk

There is no reason to keep a zero before p1 or after pk if it
can be removed while maintaining exactly k ones.

The sliding window effectively finds these minimal windows.

------------------------------------------------------------

Why Does the Algorithm Find the Shortest Window?
-------------------------------------------------

When:

    count == k

we already know there are exactly k ones in the window.

Then:

    while(s[left] == '0')

removes every unnecessary zero from the beginning.

We cannot remove the first '1', because that would make:

    count = k - 1

Therefore, the resulting window is the shortest possible
window for the current right boundary.

As right continues moving, we consider other groups of k ones.

The global shortest one is stored in:

    ans

------------------------------------------------------------

Why Do We Need to Move Past the Leftmost 1?
---------------------------------------------

Suppose:

    s = "10101"
    k = 2

First candidate:

    "101"

contains the first two ones.

After recording it:

    count--

    left++

Now the first '1' is removed.

As right continues, the next candidate can become:

    "101"

using the second and third ones.

This is how the sliding window moves from one group of k ones
to the next.

------------------------------------------------------------

Overall Flow:
-------------

            right moves →
    
    [ left ................ right ]
             |
             ↓
       count number of 1s
             |
        count == k ?
             |
       +-----+-----+
       |           |
      NO          YES
       |           |
   continue     remove leading
                zeros
                    |
                    ↓
              create curr
                    |
                    ↓
           compare with ans
                    |
                    ↓
          remove leftmost 1
                    |
                    ↓
               continue

------------------------------------------------------------

Why This Is Better Than Checking Every Substring:
-------------------------------------------------

There are O(n²) possible substrings.

Checking every substring would be too expensive.

Instead, the sliding window maintains the number of ones while
moving:

    left
    right

forward through the string.

Each pointer only moves forward.

Therefore, the main scanning work is linear.

------------------------------------------------------------

Complexity:
-----------

The left and right pointers each move at most n positions.

So the sliding-window traversal is:

    O(n)

However, this implementation creates:

    string curr = s.substr(...)

for every candidate.

Copying a substring can take O(n) in the worst case.

Therefore, strictly for this implementation, the worst-case
time complexity can be:

    O(n²)

In practice, the number of candidates is limited by the number
of groups of k ones.

The auxiliary sliding-window state itself uses:

    O(1)

space, excluding the temporary candidate strings and answer.

------------------------------------------------------------

Main Idea to Remember:
----------------------

This is a:

    Sliding Window + Greedy Trimming

problem.

The pattern is:

    1. Expand right.
    2. Count the number of 1s.
    3. When count == k:
           remove unnecessary leading zeros.
    4. The remaining window is the shortest candidate for
       this right boundary.
    5. Compare it with the current answer:
           shorter -> better
           same length -> lexicographically smaller
    6. Remove the leftmost 1 and continue.

The key condition is:

    count == k

because that tells us we currently have a valid beautiful
substring.

And the key comparison is:

    curr.size() < ans.size()

or, when lengths are equal:

    curr < ans

So the overall priority is:

    shortest length
          ↓
    lexicographically smallest
*/