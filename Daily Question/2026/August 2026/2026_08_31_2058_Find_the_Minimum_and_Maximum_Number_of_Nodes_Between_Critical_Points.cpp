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
        vector<int> nodesBetweenCriticalPoints(ListNode* head) {
            if(!head || !head->next || !head->next->next) return {-1, -1};
    
            ListNode *prev = head, *curr = head->next, *nxt = curr->next;
            int idx = 1;
            vector<int> ans;
            while(nxt) {
                if((curr->val > prev->val && curr->val > nxt->val) || (curr->val < prev->val && curr->val < nxt->val)) ans.push_back(idx);
                prev = curr;
                curr = nxt;
                nxt = nxt->next;
                idx++;
            }
    
            int mn = INT_MAX, n = ans.size(); 
            if(n < 2) return {-1, -1};
    
            for(int i = 0; i < n - 1; i++) mn = min(mn, ans[i + 1] - ans[i]);
            
            return {mn, ans[n - 1] - ans[0]};
    
    
        }
    };

/*
LeetCode 2058. Find the Minimum and Maximum Number of Nodes Between Critical Points

Approach:
---------

A critical point is a node that is either:

    1. A local maximum:
           curr->val > prev->val
        && curr->val > next->val

    2. A local minimum:
           curr->val < prev->val
        && curr->val < next->val

The first and last nodes can never be critical points because a
critical point needs both:

    - a previous node
    - a next node

So we traverse the linked list while keeping track of:

    prev -> previous node
    curr -> current node
    nxt  -> next node

Whenever curr is a critical point, we store its index.

After finding all critical points:

    - Minimum distance = minimum distance between consecutive
      critical points.

    - Maximum distance = distance between the first and last
      critical points.

------------------------------------------------------------

Example:
--------

Linked List:

    5 -> 3 -> 1 -> 2 -> 5 -> 1 -> 2

Indexes:

    0    1    2    3    4    5    6

Critical points:

    index 2 -> 1 is smaller than both 3 and 2
               local minimum

    index 4 -> 5 is greater than both 2 and 1
               local maximum

    index 5 -> 1 is smaller than both 5 and 2
               local minimum

Critical point indexes:

    [2, 4, 5]

Minimum distance:

    min(4 - 2, 5 - 4)
    = min(2, 1)
    = 1

Maximum distance:

    5 - 2
    = 3

Answer:

    [1, 3]

------------------------------------------------------------

Important Observation:
----------------------

If the critical point indexes are:

    [a, b, c, d]

The minimum distance will always occur between two consecutive
critical points.

We do not need to compare every pair.

Why?

For example:

    d - a

can always be broken into:

    (b - a) + (c - b) + (d - c)

Therefore, a non-consecutive pair can never have a smaller
distance than all consecutive pairs.

So for minimum distance, checking consecutive critical points
is sufficient.

For maximum distance, the largest possible distance is always:

    lastCriticalPoint - firstCriticalPoint

------------------------------------------------------------

1. Check Minimum Number of Nodes
--------------------------------

A critical point requires:

    prev <- curr -> nxt

Therefore, we need at least three nodes.

    if(!head || !head->next || !head->next->next)
        return {-1, -1};

If fewer than three nodes exist, no critical point is possible.

------------------------------------------------------------

2. Initialize Three Pointers
----------------------------

    ListNode *prev = head;
    ListNode *curr = head->next;
    ListNode *nxt = curr->next;

We start curr at the second node because:

    - head has no previous node.
    - The last node will have no next node.

The first possible critical point is therefore at index 1.

    int idx = 1;

------------------------------------------------------------

3. Traverse the Linked List
---------------------------

    while(nxt)

As long as nxt exists, curr has both:

    prev
    nxt

Therefore, curr can potentially be a critical point.

------------------------------------------------------------

4. Check for a Critical Point
-----------------------------

A local maximum:

    curr->val > prev->val
    &&
    curr->val > nxt->val

Example:

        3 -> 5 -> 2
             ↑

            curr

Since:

        5 > 3
        5 > 2

5 is a critical point.

A local minimum:

    curr->val < prev->val
    &&
    curr->val < nxt->val

Example:

        5 -> 2 -> 4
             ↑

            curr

Since:

        2 < 5
        2 < 4

2 is a critical point.

So:

    if(
        (curr->val > prev->val && curr->val > nxt->val)
        ||
        (curr->val < prev->val && curr->val < nxt->val)
    )
        ans.push_back(idx);

We store the index of every critical point.

------------------------------------------------------------

5. Move All Pointers Forward
----------------------------

After processing the current node:

    prev = curr;
    curr = nxt;
    nxt = nxt->next;

This moves our three-node window:

Before:

    prev -> curr -> nxt

After:

           prev -> curr -> nxt

We also increase the current index:

    idx++;

------------------------------------------------------------

6. Check Whether At Least Two Critical Points Exist
---------------------------------------------------

The question asks for distances between critical points.

With:

    0 critical points -> impossible

or:

    1 critical point -> no pair exists

Therefore:

    if(n < 2)
        return {-1, -1};

------------------------------------------------------------

7. Find the Minimum Distance
----------------------------

Suppose:

    ans = [2, 4, 5]

We compare consecutive critical points:

    4 - 2 = 2

    5 - 4 = 1

Therefore:

    mn = 1

The code:

    for(int i = 0; i < n - 1; i++)
        mn = min(mn, ans[i + 1] - ans[i]);

Since the linked list is traversed from left to right, critical
point indexes are already stored in sorted order.

------------------------------------------------------------

8. Find the Maximum Distance
----------------------------

The maximum distance is always between:

    first critical point
    and
    last critical point

Therefore:

    ans[n - 1] - ans[0]

For:

    ans = [2, 4, 5]

Maximum distance:

    5 - 2
    = 3

------------------------------------------------------------

Time Complexity:
----------------

We traverse the linked list once:

    O(n)

Then we iterate through the critical point indexes:

    O(n) in the worst case

Overall:

    O(n)

------------------------------------------------------------

Space Complexity:
-----------------

The vector ans stores all critical point indexes.

In the worst case, there can be O(n) critical points.

Therefore:

    O(n)

------------------------------------------------------------

Core Idea:
----------

Use a sliding three-node window:

    prev -> curr -> nxt

For every curr:

    Local Maximum:

        curr > prev
        &&
        curr > nxt

    Local Minimum:

        curr < prev
        &&
        curr < nxt

Store every critical point index.

Then:

    Minimum Distance:
        minimum difference between consecutive critical points

    Maximum Distance:
        last critical point - first critical point

Finally return:

    {minimumDistance, maximumDistance}
*/