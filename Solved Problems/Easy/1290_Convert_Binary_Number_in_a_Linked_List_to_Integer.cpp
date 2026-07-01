// Approach 1: Stack

// /**
//  * Definition for singly-linked list.
//  * struct ListNode {
//  *     int val;
//  *     ListNode *next;
//  *     ListNode() : val(0), next(nullptr) {}
//  *     ListNode(int x) : val(x), next(nullptr) {}
//  *     ListNode(int x, ListNode *next) : val(x), next(next) {}
//  * };
//  */
// class Solution {
// public:
//     int getDecimalValue(ListNode* head) {
//         stack<int> st;
//         while (head != NULL) {
//             st.push(head->val);
//             head = head->next;
//         }
//         int n = st.size(), ans = 0, mul = 1;
//         for (int i = 0; i < n; i++) {
//             ans += st.top() * mul;
//             mul *= 2;
//             st.pop();
//         } 

//         return ans;
//     }
// };

// Approach 2: Bit Manipulation

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
 class Solution {
    public:
        int getDecimalValue(ListNode* head) {
            int ans = 0;
            while(head) {
                ans = ans * 2 + head->val;
                head = head->next;
            }
            return ans;
        }
    };

/*

Idea:
------
The linked list stores the binary representation of a number
from the Most Significant Bit (MSB) to the Least Significant Bit (LSB).

Traverse the list from left to right and construct the decimal
number one bit at a time.

For every new bit:
1. Multiply the current answer by 2.
   - This shifts the binary number one position to the left,
     creating space for the new bit.
2. Add the current bit (0 or 1).

Formula:
--------
    ans = ans * 2 + currentBit

This is similar to building a decimal number:

Decimal:
    ans = ans * 10 + digit

Binary:
    ans = ans * 2 + bit

Algorithm:
----------
1. Initialize:
      ans = 0

2. Traverse the linked list.

3. For each node:
      ans = ans * 2 + head->val

4. Return ans.

Example:
--------
Linked List:

1 -> 0 -> 1 -> 1

Initially:
ans = 0

Read 1:
ans = 0 * 2 + 1 = 1

Binary built:
1

-----------------------

Read 0:
ans = 1 * 2 + 0 = 2

Binary built:
10₂

-----------------------

Read 1:
ans = 2 * 2 + 1 = 5

Binary built:
101₂

-----------------------

Read 1:
ans = 5 * 2 + 1 = 11

Binary built:
1011₂

Final Answer:
11

Why does multiplying by 2 work?
--------------------------------
Multiplying by 2 shifts the current binary number one position
to the left.

Example:

101₂

↓

1010₂   (101₂ × 2)

Now the last position becomes empty, so we simply add the new bit.

Example:

1010₂ + 1 = 1011₂

Time Complexity:
----------------
O(n)

Space Complexity:
-----------------
O(1)

*/