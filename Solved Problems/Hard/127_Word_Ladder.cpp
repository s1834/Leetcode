class Solution {
    public:
        int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
            unordered_set<string> st(wordList.begin(), wordList.end()); // wordList
    
            queue<pair<string, int>> q; // queue<pair<word, BFS level>> q
            q.push({beginWord, 1});
            st.erase(beginWord);
    
            while(!q.empty()) {
                string word = q.front().first;
                int level = q.front().second;
                q.pop();
    
                if(word == endWord) return level; // endWord found
    
                int n = word.size();
                // replace each char of the word with each char from 'a' to 'z'
                for(int i = 0; i < n; i++) {
                    char curr = word[i];
                    for(char j = 'a'; j <= 'z'; j++) {
                        word[i] = j;
                        if(st.find(word) != st.end()) {
                            st.erase(word);
                            q.push({word, level + 1});
                        }
                    }
                    word[i] = curr; // backtrack
                }
            }
            
            return 0;
        }
    };

/*

Idea:
------

Think of every word as a node in a graph.

Two words are connected if they differ by exactly

one character.

The problem asks for the minimum number of transformations
needed to convert

beginWord

into

endWord,

where every intermediate word must exist in the dictionary.

Since every transformation has equal cost (one word change),

Breadth First Search (BFS)

is the ideal algorithm because it always finds the shortest
path in an unweighted graph.

------------------------------------------------------------

Key Observation:
----------------

Instead of explicitly building the graph,

we generate neighboring words on the fly.

For every position in the current word,

replace that character with every letter from

'a'

to

'z'.

If the newly formed word exists in the dictionary,

it represents a valid transformation and becomes a neighbor
in the graph.

------------------------------------------------------------

Approach:
---------

1. Store all words from the dictionary in a hash set.

   This allows

   O(1)

   average lookup for checking whether a transformed word
   exists.

2. Start BFS from

beginWord.

3. For every word removed from the queue,

   generate all possible neighboring words by changing one
   character at a time.

4. If a generated word exists in the dictionary,

   • Remove it from the hash set (mark as visited).

   • Push it into the queue with

     level + 1.

5. If

endWord

is reached,

return the current BFS level.

6. If BFS finishes without reaching

endWord,

return

0.

------------------------------------------------------------

Generating Neighbors:
---------------------

Current Word

hit

Change one position at a time.

Position 0

ait

bit

cit

...

zit

--------------------------------

Position 1

hat

hbt

hct

...

hzt

--------------------------------

Position 2

hia

hib

hic

...

hiz

Only the generated words present in the dictionary are
considered valid neighbors.

------------------------------------------------------------

Example:
--------

beginWord

hit

endWord

cog

Dictionary

hot

dot

dog

lot

log

cog

--------------------------------

Level 1

hit

↓

Level 2

hot

↓

Level 3

dot

lot

↓

Level 4

dog

log

↓

Level 5

cog

Answer

5

------------------------------------------------------------

Visualization:
--------------

hit

|

hot

/   \

dot   lot

|      |

dog   log

 \    /

  cog

BFS explores the graph level by level.

The first time

cog

is reached,

the shortest transformation sequence has been found.

------------------------------------------------------------

Why Remove Words Immediately?
-----------------------------

Once a word is added to the queue,

it is immediately removed from the dictionary.

This serves as the

visited

mark.

Without removing it,

the same word could be generated multiple times through
different paths,

leading to unnecessary processing and repeated visits.

Removing it guarantees that every word is processed at most
once.

------------------------------------------------------------

Why Does This Work?
-------------------

Each valid transformation changes exactly one character,
making every graph edge have the same cost.

BFS explores all words reachable in

k

transformations before exploring words requiring

k + 1

transformations.

Therefore,

the first time

endWord

is removed from the queue,

it is guaranteed to have been reached using the minimum
number of transformations.

------------------------------------------------------------

Time Complexity:
----------------

Let

N = number of words

L = length of each word

For every visited word,

we try

L

positions,

and for each position,

26

possible characters.

Overall Time Complexity

O(N × L × 26)

≈

O(N × L)

------------------------------------------------------------

Space Complexity:
-----------------

Hash Set

O(N)

Queue

O(N)

Overall Space Complexity

O(N)

------------------------------------------------------------

Note:
-----

This solution uses standard BFS, which is optimal for the
given constraints.

A faster approach for very large dictionaries is

Bidirectional BFS,

where the search starts simultaneously from

beginWord

and

endWord,

reducing the search space significantly.

*/