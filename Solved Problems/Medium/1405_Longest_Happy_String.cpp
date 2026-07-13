class Solution {
    public:
        string longestDiverseString(int a, int b, int c) {
    
            priority_queue<pair<int, char>> pq;
            
            // if characters are not 0, push in queue
            if(a) pq.push({a,'a'});
            if(b) pq.push({b,'b'});
            if(c) pq.push({c,'c'});
    
            string ans = "";
    
            while(!pq.empty()) {
                
                auto temp = pq.top();
                pq.pop();
    
                int n = ans.size();
                // check we are forming 3 consecutive chars
                if(n > 1 && ans[n - 1] == temp.second && ans[n - 2] == temp.second) {
                    // if adding temp forms 3 consecutive, append topmost element of pq
                    if(pq.empty()) break;
                    auto p = pq.top();
                    pq.pop();
    
                    ans += p.second;
                    p.first--;
    
                    // push p and temp again for next iteration
                    if(p.first > 0) pq.push(p);
    
                    pq.push(temp);
                }
                else {
                    // if we are not forming 3 consecutive then simply append the temp char
                    ans += temp.second;
                    temp.first--;
                    if(temp.first > 0) pq.push(temp);
                }
            }
    
            return ans;
        }
    };

/*

Idea:
------
Always try to use the character with the highest remaining
frequency.

However, before appending it, check whether it would create
three consecutive identical characters.

If it does, temporarily use the second most frequent
character instead.

A Max Heap is used to always retrieve the character with
the highest remaining frequency.

------------------------------------------------------------

Algorithm:
----------

1.

Push all characters with non-zero frequencies into the
Max Heap as

(frequency, character).

------------------------------------------------------------

2.

While the heap is not empty,

remove the character with the highest remaining frequency.

------------------------------------------------------------

3.

Check whether appending this character would create

xxx

(i.e., the last two characters of the answer are already
the same character).

------------------------------------------------------------

4.

If it creates three consecutive characters,

• If no other character is available,

  no more valid characters can be added.

  Stop building the answer.

• Otherwise,

  use the second most frequent character.

  Decrease its frequency.

  Push it back into the heap if occurrences remain.

  Also push the first character back since it was not used.

------------------------------------------------------------

5.

Otherwise,

append the most frequent character.

Decrease its frequency.

If occurrences remain,

push it back into the Max Heap.

------------------------------------------------------------

Example:
--------

a = 5

b = 2

c = 1

Heap:

(5,a)

(2,b)

(1,c)

------------------------------------------------------------

Take:

a

Answer:

a

------------------------------------------------------------

Take:

a

Answer:

aa

------------------------------------------------------------

Top is still 'a',

but appending it would create

aaa.

So use the second most frequent character.

Answer:

aab

Push 'a' back into the heap.

------------------------------------------------------------

Continue until no valid character can be appended.

Possible answer:

aabaaca

------------------------------------------------------------

Time Complexity:
----------------

O((a + b + c) log 3)

Since there are at most three different characters,

this is effectively

O(a + b + c).

------------------------------------------------------------

Space Complexity:
-----------------

O(1)

The Max Heap stores at most three characters.

*/