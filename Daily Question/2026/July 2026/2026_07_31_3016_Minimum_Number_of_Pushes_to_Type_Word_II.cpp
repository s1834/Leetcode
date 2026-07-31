class Solution {
    public:
        int minimumPushes(string word) {
            // count how many times each character appears
            map<char, int> mp;
            for (auto x : word) mp[x]++;
    
            // get and sort the counts in descending order
            // to give the minimum presses to most occured char
            vector<int> count;
            for(auto x : mp) count.push_back(x.second);
            sort(count.begin(), count.end(), greater<int>());
    
    
            int pressTimes = 1, n = count.size(), ans = 0;
            for(int i = 0; i < n; i++) {
                // multiply the current count with the number of presses
                ans += count[i] * pressTimes;
    
                // if 8 keys are consumed, increase number of presses by 1
                if(!((i + 1) % 8)) pressTimes++;
            }
    
            return ans;
        }
    };

/*

Idea:
------

We are free to remap the characters to any of the 8 keys.

Unlike Part I, characters may appear multiple times.

To minimize the total number of key presses,

the characters that appear more frequently should be placed
at positions requiring fewer presses.

This is a classic greedy strategy.

------------------------------------------------------------

Key Observation:
----------------

Each key provides positions requiring

1 push

2 pushes

3 pushes

...

Across all 8 keys,

there are exactly

8 positions

requiring 1 push,

8 positions

requiring 2 pushes,

and so on.

Therefore,

the characters with the highest frequencies should occupy
the cheapest available positions.

------------------------------------------------------------

Greedy Strategy:
----------------

Suppose two characters have frequencies

10

and

2.

If

10

is assigned to

2 pushes

and

2

is assigned to

1 push,

Total Cost

=

10 × 2 + 2 × 1

=

22

--------------------------------

Swapping their positions

10 × 1 + 2 × 2

=

14

which is always smaller.

Hence,

placing higher frequency characters at smaller press counts
always minimizes the answer.

------------------------------------------------------------

Algorithm:
----------

1. Count the frequency of every character.

2. Store all frequencies in a vector.

3. Sort the frequencies in decreasing order.

4. Assign the first 8 frequencies to

1 push.

5. Assign the next 8 frequencies to

2 pushes.

6. Continue similarly until all characters are assigned.

7. Add

frequency × pressCount

for every character.

------------------------------------------------------------

Example:
--------

word =

"abcabcabcd"

Frequencies

a → 3

b → 3

c → 3

d → 1

--------------------------------

Sorted Frequencies

3 3 3 1

--------------------------------

Assignments

3 × 1

+

3 × 1

+

3 × 1

+

1 × 1

=

10

Since there are fewer than 8 distinct characters,

every character gets a one-push position.

------------------------------------------------------------

Example:
--------

Suppose the sorted frequencies are

15 12 10 9 8 7 5 4 3 2

Assignments

First 8

↓

1 push

15×1 + 12×1 + ... + 4×1

--------------------------------

Remaining

↓

2 pushes

3×2 + 2×2

------------------------------------------------------------

Visualization:
--------------

Sorted Frequencies

f1 ≥ f2 ≥ f3 ≥ ...

↓

Press Count

1 1 1 1 1 1 1 1

2 2 2 2 2 2 2 2

3 3 3 3 ...

Multiply

Frequency × Press Count

and sum all contributions.

------------------------------------------------------------

Why Does This Work?
-------------------

Every occurrence of a character contributes the same number
of key presses.

Therefore,

saving one key press for a highly frequent character reduces
the total cost much more than saving one press for a rarely
used character.

Sorting the frequencies ensures that the most frequent
characters always receive the cheapest available positions,
which minimizes the overall number of key presses.

------------------------------------------------------------

Time Complexity:
----------------

Let

n = length of the word.

Counting frequencies

O(n)

Sorting at most 26 frequencies

O(26 log 26)

Overall Time Complexity

O(n)

------------------------------------------------------------

Space Complexity:
-----------------

Frequency Map

O(26)

Frequency Vector

O(26)

Overall Space Complexity

O(1)

since the alphabet size is fixed (26 lowercase letters).

*/