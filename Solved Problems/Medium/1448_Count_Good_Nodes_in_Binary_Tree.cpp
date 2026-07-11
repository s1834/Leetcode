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
    int good = 0;

    void dfs(TreeNode* root, int val) {
        if(!root) return;
        if(root->val >= val) {
            good++;
            val = root->val;
        }
        dfs(root->right, val);
        dfs(root->left, val);
    }

public:
    int goodNodes(TreeNode* root) {
        dfs(root, root->val);
        return good;
    }
};

/*

Idea:
------
A node is considered "good" if there is no node with a
greater value on the path from the root to that node.

Instead of checking every ancestor individually, maintain
the maximum value seen so far along the current root-to-node
path.

If the current node's value is greater than or equal to this
maximum, it is a good node.

Update the maximum value (if needed) before recursively
exploring its children.

------------------------------------------------------------

Traversal Order:
----------------

Current Node
      ↓
Right Subtree
      ↓
Left Subtree

(The traversal order does not matter for this problem.
Right-first or left-first both produce the same answer.)

------------------------------------------------------------

Example:
--------

        3
       / \
      1   4
     /   / \
    3   1   5

Initially:

maxSeen = 3

Visit 3:

3 >= 3

Good Nodes = 1

------------------------------------------------------------

Visit 1:

maxSeen = 3

1 < 3

Not Good

------------------------------------------------------------

Visit 3:

maxSeen = 3

3 >= 3

Good Nodes = 2

------------------------------------------------------------

Visit 4:

maxSeen = max(3,4) = 4

4 >= 3

Good Nodes = 3

------------------------------------------------------------

Visit 1:

maxSeen = 4

1 < 4

Not Good

------------------------------------------------------------

Visit 5:

maxSeen = max(4,5) = 5

5 >= 4

Good Nodes = 4

Final Answer:

4

------------------------------------------------------------

Time Complexity:
----------------

O(n)

Every node is visited exactly once.

------------------------------------------------------------

Space Complexity:
-----------------

O(h)

where h is the height of the tree due to the recursive
call stack.

*/
