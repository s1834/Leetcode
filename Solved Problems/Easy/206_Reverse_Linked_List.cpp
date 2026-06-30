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
        ListNode* reverseList(ListNode* head) {
            if(!head || !head->next) return head;
            
            ListNode* ptr = reverseList(head->next);
            
            ListNode* newHead = head->next;
            newHead->next = head;
            head->next = NULL;
            
            return ptr;
        }
    };

/*
Backtracking:
-------------
The actual reversal happens while the recursive calls return.

Initially, recursion reaches the last node:

1 -> 2 -> 3 -> 4 -> 5

Node 5 becomes the new head and is returned.

Now the recursion starts returning one call at a time.

------------------------------------

Returning to node 4:

Current:
4 -> 5

Execute:

5 -> 4
4 -> NULL

List becomes:

5 -> 4

------------------------------------

Returning to node 3:

Current reversed part:

5 -> 4

Original link:

3 -> 4

Execute:

4 -> 3
3 -> NULL

List becomes:

5 -> 4 -> 3

------------------------------------

Returning to node 2:

Current reversed part:

5 -> 4 -> 3

Original link:

2 -> 3

Execute:

3 -> 2
2 -> NULL

List becomes:

5 -> 4 -> 3 -> 2

------------------------------------

Returning to node 1:

Current reversed part:

5 -> 4 -> 3 -> 2

Original link:

1 -> 2

Execute:

2 -> 1
1 -> NULL

List becomes:

5 -> 4 -> 3 -> 2 -> 1

Final reversed list:

5 -> 4 -> 3 -> 2 -> 1

Key Observation:
----------------
While going down the recursion, no links are changed.

The reversal happens only while returning (backtracking).

At each return:
1. Make the next node point back to the current node.
2. Remove the original forward link.
3. Return the same new head (the original last node).
*/