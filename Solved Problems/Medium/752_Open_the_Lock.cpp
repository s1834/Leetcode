class Solution {
    private:
        void fillNeighbours(queue<string>& q, unordered_set<string>& st, string curr) {
            // run for loop for 4 positions
            for(int i = 0; i < 4; i++) {
                char ch = curr[i]; // current version
                         
                char dec = ch == '0' ? '9' : ch - 1; // decrease curr
                char inc = ch == '9' ? '0' : ch + 1; // increase curr
    
                // check if decremented curr exists in deadend
                curr[i] = dec;
                if(st.find(curr) == st.end()) {
                    q.push(curr);
                    st.insert(curr);
                }
    
                // check if incremented curr exists in deadend
                curr[i] = inc;
                if(st.find(curr) == st.end()) {
                    q.push(curr);
                    st.insert(curr);
                }
    
                // backtrack curr char
                curr[i] = ch;
            }
        }
    
    public:
        int openLock(vector<string>& deadends, string target) {
            // add deadends in a set
            unordered_set<string> st(deadends.begin(), deadends.end());
    
            // if starting position is deadend return -1
            if(st.find("0000") != st.end()) return -1;
    
            // add starting poisition in queue and it is also a deadend now as it is already visited
            queue<string> q;
            q.push("0000");
            st.insert("0000");
    
            int level = 0;
            while(!q.empty()) {
                int n = q.size();
    
                while(n--) {
                    string curr = q.front();
                    q.pop();
    
                    if(curr == target) return level;
    
                    fillNeighbours(q, st, curr);
                }
    
                level++;
            }
    
            return -1;
        }
    };

/*

Idea:
------

Think of every lock combination as a node in a graph.

For any combination,

we can generate

8

neighboring combinations by rotating one wheel either

forward

or

backward.

Our goal is to find the minimum number of rotations required
to reach the target from

"0000".

Since every move has equal cost (1 rotation),

Breadth First Search (BFS)

is the ideal choice because it always finds the shortest
path in an unweighted graph.

------------------------------------------------------------

Key Observation:
----------------

Each lock combination can be viewed as a graph node.

For every wheel,

there are two possible moves:

• Rotate Forward

• Rotate Backward

Since there are

4

wheels,

each state has

4 × 2 = 8

possible neighboring states.

Deadends are simply blocked nodes that cannot be visited.

------------------------------------------------------------

Approach:
---------

1. Store all deadends in a hash set.

2. If the starting combination

"0000"

is a deadend, return

-1.

3. Start BFS from

"0000".

4. For every current combination,

generate all 8 neighboring combinations by rotating each
wheel one step forward and backward.

5. If a generated combination is neither a deadend nor
already visited,

push it into the queue and mark it as visited.

6. Whenever the target combination is reached,

return the current BFS level.

7. If BFS finishes without reaching the target,

return

-1.

------------------------------------------------------------

Generating Neighbors:
---------------------

For every wheel,

Current Digit

↓

d

Generate

Previous Digit

↓

(d - 1 + 10) % 10

Generate

Next Digit

↓

(d + 1) % 10

Example

Current

"1234"

Neighbors

0234

2234

1134

1334

1224

1244

1233

1235

------------------------------------------------------------

Example:
--------

Deadends

["0201","0101","0102","1212","2002"]

Target

"0202"

Start

0000

↓

1000

↓

1100

↓

1200

↓

1201

↓

1202

↓

0202

BFS explores every combination level by level until the
target is reached.

------------------------------------------------------------

Visualization:
--------------

Level 0

0000

↓

Level 1

1000

9000

0100

0900

0010

0090

0001

0009

↓

Level 2

All valid neighbors of Level 1 states

...

BFS guarantees that the first time we reach the target,
we have used the minimum number of rotations.

------------------------------------------------------------

Why Does This Work?
-------------------

Every lock combination represents a graph node and every
rotation represents an edge of equal weight.

BFS explores all combinations requiring

k

moves before exploring combinations requiring

k + 1

moves.

Therefore,

the first time the target is removed from the queue,
it is guaranteed to have been reached using the minimum
number of rotations.

The hash set also serves as the visited set, preventing us
from revisiting the same combination or entering deadends.

------------------------------------------------------------

Time Complexity:
----------------

There are at most

10⁴

possible lock combinations.

For every combination,

we generate

8

neighbors.

Overall Time Complexity

O(10⁴)

------------------------------------------------------------

Space Complexity:
-----------------

Queue

O(10⁴)

Visited/Deadend Hash Set

O(10⁴)

Overall Space Complexity

O(10⁴)

*/