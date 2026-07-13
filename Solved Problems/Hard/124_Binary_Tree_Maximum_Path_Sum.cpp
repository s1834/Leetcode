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
        int sum = INT_MIN;
    
        int dfs(TreeNode* root) {
            if(!root) return 0;
    
            int leftSum = max(0, dfs(root->left));
            int rightSum = max(0, dfs(root->right));
    
            sum = max(sum, root->val + leftSum + rightSum);
            return root->val + max(leftSum, rightSum);
        }
    public:
        int maxPathSum(TreeNode* root) {
            dfs(root);
            return sum;
        }
    };

/*

Idea:
------
A maximum path can pass through any node.

For every node,

there are two possible values to compute:

1.

The maximum path sum that can be extended to its parent.

2.

The maximum path sum passing through the current node,
which may include both its left and right subtrees.

A DFS is used to compute both values simultaneously.

------------------------------------------------------------

Algorithm:
----------

1.

Recursively compute the maximum path sum from the left
and right subtrees.

------------------------------------------------------------

2.

If a subtree contributes a negative sum,

ignore it.

Using a negative path would only decrease the total path
sum.

This is done using

max(0, subtree_sum)

------------------------------------------------------------

3.

Compute the maximum path passing through the current node.

currentPath =
root->val + leftSum + rightSum

Update the global answer if this path is larger.

------------------------------------------------------------

4.

Return only one branch to the parent.

A parent can continue the path through only one child,
otherwise the path would split into two directions.

Return

root->val + max(leftSum, rightSum)

------------------------------------------------------------

Example:
--------

        -10
       /   \
      9     20
           /  \
         15    7

------------------------------------------------------------

At node 15

left = 0

right = 0

Global Answer:

15

Return:

15

------------------------------------------------------------

At node 7

Global Answer:

15

Return:

7

------------------------------------------------------------

At node 20

left = 15

right = 7

Current Path:

20 + 15 + 7 = 42

Global Answer:

42

Return:

20 + max(15,7) = 35

------------------------------------------------------------

At node -10

left = 9

right = 35

Current Path:

-10 + 9 + 35 = 34

Global Answer remains:

42

Final Answer:

42

------------------------------------------------------------

Time Complexity:
----------------

O(n)

Each node is visited exactly once.

------------------------------------------------------------

Space Complexity:
-----------------

O(h)

where h is the height of the tree due to the
recursive call stack.

Worst Case:

O(n)

Balanced Tree:

O(log n)

*/