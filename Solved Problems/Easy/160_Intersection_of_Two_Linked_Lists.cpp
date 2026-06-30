/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *a = headA;
        ListNode *b = headB;
        while(a != b) {
            a = (a == NULL) ? headB : a->next;
            b = (b == NULL) ? headA : b->next;
        }
        return a;
    }
};

/*

Idea:
------
Use two pointers to traverse both linked lists.

Instead of computing the lengths of the lists, let each pointer
traverse both lists. This automatically compensates for any
difference in lengths.

If the lists intersect, both pointers will eventually reach the
same intersection node.

If they do not intersect, both pointers will eventually become
NULL at the same time.

Algorithm:
----------
1. Initialize:
      a = headA
      b = headB

2. Traverse both lists simultaneously.

3. If a reaches the end of List A,
      redirect it to headB.

   Otherwise,
      move to the next node.

4. Similarly, if b reaches the end of List B,
      redirect it to headA.

5. Continue until:
      a == b

   They will either:
   - Meet at the intersection node, or
   - Both become NULL (no intersection).

Why does this work?
-------------------
Suppose:

Length of List A = m
Length of List B = n

Pointer a travels:

    List A -> List B

Pointer b travels:

    List B -> List A

Both pointers therefore travel exactly:

    m + n

nodes.

Initially, one pointer may reach the shared part earlier because
its list is shorter.

After switching lists, the other pointer traverses the extra nodes
of the longer list, automatically canceling the difference in
lengths.

As a result, both pointers reach the intersection node at the
same time.

If no intersection exists, both pointers finish traversing both
lists and become NULL simultaneously.

Example:
--------
List A:

4 -> 1
      \
       8 -> 4 -> 5
      /
List B:

5 -> 6 -> 1

Pointer a:
A -> B

Pointer b:
B -> A

After both have traversed the same total distance,
they meet at node 8.

Time Complexity:
----------------
O(m + n)

Space Complexity:
-----------------
O(1)

*/