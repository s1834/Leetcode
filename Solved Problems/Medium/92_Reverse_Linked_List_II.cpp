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
    private:
        ListNode* reverse(ListNode* head, int remove) {
            if(!head || !head->next) return head;
            ListNode *prev = NULL, *curr = head, *nxt = head->next;
            while(remove > 1 && nxt != NULL) {
                curr->next = prev;
                prev = curr;
                curr = nxt;
                nxt = curr->next;
                remove--;
            }
            curr->next = prev;
            head->next = nxt;
            return curr;
        }
    
    public:
        ListNode* reverseBetween(ListNode* head, int left, int right) {
            ListNode* ptr = head;
            for(int i = 1; i < left - 1; i++) ptr = ptr->next;
            if(left == 1) head = reverse(ptr, right - left + 1);
            else ptr->next = reverse(ptr->next, right - left + 1);
            return head;
        }
    };

/*

Idea:
------
Reverse only the portion of the linked list from position
left to right.

Instead of reversing the entire list, we:

1. Traverse to the node just before the left position.
2. Reverse only (right - left + 1) nodes.
3. Reconnect the reversed portion with the remaining list.

------------------------------------------------------------

Step 1:
-------

Find the starting point of reversal.

If

left == 1

the reversal starts from the head itself.

Otherwise,

move a pointer to the node immediately before
the left position.

Example:

1 -> 2 -> 3 -> 4 -> 5

left = 3

ptr

     ↓
1 -> 2 -> 3 -> 4 -> 5

The nodes after ptr will be reversed.

------------------------------------------------------------

Step 2:
-------

Reverse exactly

(right - left + 1)

nodes.

The helper function receives

head

=

the first node of the sublist to reverse.

During reversal:

prev

Stores the already reversed portion.

curr

Represents the current node being reversed.

nxt

Stores the next node so we do not lose the
remaining list after changing pointers.

------------------------------------------------------------

Reversal Process:
-----------------

Suppose we need to reverse

3 nodes

1 -> 2 -> 3 -> 4

Initially

prev = NULL
curr = 1
nxt  = 2

----------------

Iteration 1

1 -> NULL

prev = 1
curr = 2
nxt  = 3

----------------

Iteration 2

2 -> 1

prev = 2
curr = 3
nxt  = 4

The loop stops because only one node
is left to reverse.

Outside the loop,

3 -> 2 -> 1

Now

curr

becomes the new head of the reversed sublist.

The original

head

becomes the tail of the reversed sublist.

Connect

head->next = nxt

Result

3 -> 2 -> 1 -> 4

------------------------------------------------------------

Step 3:
-------

Reconnect the reversed sublist.

If

left == 1

the new head of the entire linked list is simply
the head returned by the helper function.

Otherwise,

connect

ptr->next

to the new head returned by the helper.

------------------------------------------------------------

Example:
--------

Input

1 -> 2 -> 3 -> 4 -> 5

left = 2
right = 4

Sublist to reverse

2 -> 3 -> 4

After reversal

4 -> 3 -> 2

Reconnect

1 -> 4 -> 3 -> 2 -> 5

------------------------------------------------------------

Time Complexity:
----------------

O(n)

The list is traversed only once.

------------------------------------------------------------

Space Complexity:
-----------------

O(1)

Only a few pointers are used.

*/