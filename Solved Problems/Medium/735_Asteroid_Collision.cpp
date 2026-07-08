class Solution {
    public:
        vector<int> asteroidCollision(vector<int>& asteroids) {
            stack<int> st;
            int n = asteroids.size();
            for(int i = 0; i < n; i++) {
                if(st.empty()) st.push(asteroids[i]);
                else if(st.top() < 0 || asteroids[i] > 0) st.push(asteroids[i]);
                else {
                    int flag = true;
                    while(!st.empty() && st.top() > 0 && asteroids[i] < 0) {
                        if(abs(st.top()) < abs(asteroids[i])) st.pop();
                        else if(abs(st.top()) == abs(asteroids[i])) {
                            st.pop();
                            flag = false;
                            break;
                        }
                        else {
                            flag = false;
                            break;
                        }
                    }
                    if(flag) st.push(asteroids[i]);
                }
            }
    
            vector<int> ans;
            while(!st.empty()) {
                ans.push_back(st.top());
                st.pop();
            }
            reverse(ans.begin(), ans.end());
            return ans;
        }
    };

/*

Idea:
------
A collision is only possible when:

    positive asteroid ---> <--- negative asteroid

Since we process asteroids from left to right, this happens only when:

    stack.top() > 0 && current < 0

All other cases are safe because the asteroids are either moving in the
same direction or moving away from each other.

Examples:

+  +   -> never collide
-  -   -> never collide
-  +   -> moving away, never collide
+  -   -> collision possible

------------------------------------------------------------

Algorithm:
----------

1. Traverse the asteroids from left to right.

2. If there is no possibility of collision:
      • Stack is empty.
      • Top asteroid is moving left.
      • Current asteroid is moving right.

   Simply push the current asteroid.

3. Otherwise, simulate collisions while:
      • Stack is not empty.
      • Top asteroid is moving right.
      • Current asteroid is moving left.

4. During each collision:

      a) If current asteroid is larger:
            abs(top) < abs(current)

         The top asteroid explodes.
         Pop it and continue checking because the current asteroid may
         collide with more asteroids.

      b) If both have equal size:

         Both explode.
         Pop the stack and discard the current asteroid.

      c) If the top asteroid is larger:

         Current asteroid explodes.
         Stop processing.

5. If the current asteroid survives all collisions, push it into the stack.

6. The stack stores the final surviving asteroids in order.

------------------------------------------------------------

Example:
--------

Input:

[3,5,-6,2,-1,4]

Process:

3      -> [3]

5      -> [3,5]

-6

5 explodes.

[3]

3 explodes.

[]

-6 survives.

[-6]

2

[-6,2]

-1

2 destroys -1.

[-6,2]

4

[-6,2,4]

Answer:

[-6,2,4]

------------------------------------------------------------

Time Complexity:
----------------
O(n)

Each asteroid is pushed into the stack at most once and popped at most once.

------------------------------------------------------------

Space Complexity:
-----------------
O(n)

In the worst case, all asteroids survive and are stored in the stack.

*/