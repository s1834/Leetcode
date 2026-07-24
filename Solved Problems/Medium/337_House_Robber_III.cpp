/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
 class Solution {
    private: 
        pair<int, int> dfs(TreeNode* root) {
            if(!root) return {0, 0};
    
            pair<int, int> left = dfs(root->left);
            pair<int, int> right = dfs(root->right);
    
            int withRoot = root->val + left.second + right.second;
            int withoutRoot = max(left.first, left.second) + max(right.first, right.second);
    
            return {withRoot, withoutRoot};
        }
    
    public:
        int rob(TreeNode* root) {
            pair<int, int> ans = dfs(root);
            return max(ans.first, ans.second);
        }
    };

/*

Idea:
------
For every house (tree node), there are only two possible
choices:

1.

Rob the current house.

In this case,

its immediate children cannot be robbed.

------------------------------------------------------------

2.

Do not rob the current house.

Then,

each child can independently choose whether to rob itself
or not, whichever gives a larger profit.

This naturally leads to Dynamic Programming on Trees.

Instead of returning a single value for every subtree,

we return two values representing both possible states.

------------------------------------------------------------

DP State:
---------

For every node,

dfs(node)

returns a pair

{withRoot, withoutRoot}

--------------------------------

withRoot

Maximum money obtainable from this subtree

when the current node IS robbed.

--------------------------------

withoutRoot

Maximum money obtainable from this subtree

when the current node is NOT robbed.

------------------------------------------------------------

Transition:
-----------

Suppose

Left = {leftWith, leftWithout}

Right = {rightWith, rightWithout}

have already been computed.

--------------------------------

Case 1

Rob Current Node

If we rob the current node,

its children cannot be robbed.

Therefore,

withRoot

=

root->val

+

leftWithout

+

rightWithout

--------------------------------

Case 2

Do NOT Rob Current Node

Since the current node is skipped,

each child is free to either rob itself or not.

So we choose the better option independently for each
child.

withoutRoot

=

max(leftWith, leftWithout)

+

max(rightWith, rightWithout)

------------------------------------------------------------

Base Case:
----------

If the node is

NULL,

there is nothing to rob.

Return

{0, 0}

------------------------------------------------------------

Algorithm:
----------

1.

Recursively solve the left subtree.

------------------------------------------------------------

2.

Recursively solve the right subtree.

------------------------------------------------------------

3.

Compute

withRoot

using only the

withoutRoot

values of the children.

------------------------------------------------------------

4.

Compute

withoutRoot

using the best value from each child.

------------------------------------------------------------

5.

Return the pair

{withRoot, withoutRoot}.

------------------------------------------------------------

6.

For the overall answer,

the root may either be robbed or skipped.

Return

max(withRoot, withoutRoot).

------------------------------------------------------------

Why Does This Work?
-------------------

For every node,

all valid possibilities are represented by exactly two
states:

• Rob the node.

• Skip the node.

These two states completely describe every possible
configuration of the subtree.

Since every node computes its answer using already solved
subtrees,

the recursion follows a postorder traversal,

ensuring all required information is available before
processing the current node.

------------------------------------------------------------

Example:
--------

        3
       / \
      2   3
       \   \
        3   1

--------------------------------

Leaf

3

returns

{3,0}

--------------------------------

Leaf

1

returns

{1,0}

--------------------------------

Node

2

withRoot

=

2 + 0

=

2

withoutRoot

=

max(0,3)

=

3

Returns

{2,3}

--------------------------------

Right Node

3

withRoot

=

3 + 0

=

3

withoutRoot

=

max(0,1)

=

1

Returns

{3,1}

--------------------------------

Root

3

withRoot

=

3 + 3 + 1

=

7

withoutRoot

=

max(2,3)

+

max(3,1)

=

3 + 3

=

6

Answer

=

max(7,6)

=

7

------------------------------------------------------------

Time Complexity:
----------------

Each node is visited exactly once.

Time Complexity:

O(n)

where

n

is the number of nodes in the tree.

------------------------------------------------------------

Space Complexity:
-----------------

The recursion stack stores one call per tree level.

Worst Case (Skewed Tree):

O(n)

Balanced Tree:

O(log n)

No additional data structures are used apart from the
recursion stack.

*/