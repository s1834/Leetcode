// Approach 1: Counting Nodes

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
//     ListNode* middleNode(ListNode* head) {
//         ListNode* ptr = head;
//         int count = 0;
//         while(ptr) {
//             count++;
//             ptr = ptr->next;
//         }

//         int mid = count / 2;
//         ptr = head;
        
//         for (int i = 0; i < count; i++) {
//             if (i == mid) {
//                 return ptr;
//             }
//             ptr = ptr->next;
//         }
//         return head;
//     }
// };


// Approach 2: Fast and Slow Pointer

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
        ListNode* middleNode(ListNode* head) {
            ListNode *slow = head, *fast = head;
            while(fast && fast->next) {
                fast = fast->next->next;
                slow = slow->next;
            }
            return slow;
        }
    };

/*

Idea:
------
Use two pointers moving at different speeds.

- Slow pointer moves one node at a time.
- Fast pointer moves two nodes at a time.

By the time the fast pointer reaches the end of the list,
the slow pointer will have traveled exactly half the distance,
placing it at the middle node.

Algorithm:
----------
1. Initialize:
      slow = head
      fast = head

2. Traverse the list while both fast and fast->next exist.

3. In each iteration:
      slow = slow->next
      fast = fast->next->next

4. When the loop ends:
   - If the list has an odd number of nodes,
     slow points to the exact middle node.
   - If the list has an even number of nodes,
     fast becomes NULL after crossing the last node,
     and slow points to the second middle node,
     which is required by the problem.

Example 1:
----------
List:

1 -> 2 -> 3 -> 4 -> 5

Initially:
slow = 1
fast = 1

Iteration 1:
slow = 2
fast = 3

Iteration 2:
slow = 3
fast = 5

Next iteration:
fast->next == NULL

Return:
3

------------------------------------

Example 2:
----------
List:

1 -> 2 -> 3 -> 4 -> 5 -> 6

Initially:
slow = 1
fast = 1

Iteration 1:
slow = 2
fast = 3

Iteration 2:
slow = 3
fast = 5

Iteration 3:
slow = 4
fast = NULL

Return:
4 (second middle node)

Why does this work?
-------------------
The fast pointer moves twice as fast as the slow pointer.

Therefore, when the fast pointer reaches the end of the list,
the slow pointer has covered exactly half the list and is
positioned at the middle.

Time Complexity:
----------------
O(n)

Space Complexity:
-----------------
O(1)

*/