class Solution {
    public:
        string reorganizeString(string s) {
            unordered_map<char, int> mp;
            for(char x : s) mp[x]++;
    
            priority_queue<pair<int, char>> pq;
            for(auto x : mp) pq.push({x.second, x.first});
    
            string ans = "";
            while(!pq.empty()) {
                if(pq.size() == 1) {
                    if(pq.top().first > 1) return "";
                    else {
                        ans += pq.top().second;
                        return ans;
                    }
                }
                else {
                    pair<int, char> temp = pq.top();
                    pq.pop();
                    ans += temp.second;
                    temp.first--;
    
                    pair<int, char> p = pq.top();
                    pq.pop();
                    ans += p.second;
                    p.first--;
                    if(p.first != 0) pq.push(p);
                    if(temp.first != 0) pq.push(temp);
                }
            }
    
            return ans;
        }
    };

/*

Idea:
------
Always place the two most frequent remaining characters
next to each other.

Since they are different characters, no two adjacent
characters in the answer will be the same.

A Max Heap is used to always retrieve the two characters
with the highest remaining frequencies.

------------------------------------------------------------

Algorithm:
----------

1.

Count the frequency of every character.

------------------------------------------------------------

2.

Push

(frequency, character)

into a Max Heap.

The heap always keeps the character with the highest
remaining frequency at the top.

------------------------------------------------------------

3.

While the heap is not empty,

if only one character remains,

• If its frequency is greater than 1,

  it is impossible to reorganize the string.

  Return an empty string.

• Otherwise,

  append the final character and return the answer.

------------------------------------------------------------

4.

Otherwise,

remove the two most frequent characters.

Append both to the answer.

Decrease their remaining frequencies.

If either character still has occurrences left,

push it back into the Max Heap.

------------------------------------------------------------

Example:
--------

Input:

aaabbc

Frequencies:

a -> 3

b -> 2

c -> 1

------------------------------------------------------------

Heap:

(3,a)

(2,b)

(1,c)

Take:

a

b

Answer:

ab

Remaining:

a -> 2

b -> 1

c -> 1

------------------------------------------------------------

Heap:

(2,a)

(1,c)

(1,b)

Take:

a

c

Answer:

abac

Remaining:

a -> 1

b -> 1

------------------------------------------------------------

Heap:

(1,b)

(1,a)

Take:

b

a

Answer:

abacba

All characters are used.

------------------------------------------------------------

Impossible Case:
----------------

Input:

aaab

Heap:

(3,a)

(1,b)

Take:

a

b

Remaining:

a -> 2

Heap:

(2,a)

Only one character remains with frequency > 1.

Since another character is not available to separate
the remaining 'a's,

reorganization is impossible.

Return:

""

------------------------------------------------------------

Time Complexity:
----------------

O(n log k)

where

n = length of the string

k = number of distinct characters.

Since lowercase English letters contain at most
26 distinct characters,

this is effectively

O(n).

------------------------------------------------------------

Space Complexity:
-----------------

O(k)

The heap and frequency map together store at most
one entry for each distinct character.

*/