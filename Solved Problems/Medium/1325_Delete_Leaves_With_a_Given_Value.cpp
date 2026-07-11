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
    public:
        TreeNode* removeLeafNodes(TreeNode* root, int target) {
            if(!root) return NULL;
            
            root->left = removeLeafNodes(root->left, target);
            root->right = removeLeafNodes(root->right, target);
            
            if(!root->left && !root->right && root->val == target) return NULL;
            
            return root;
        }
    };

/*

Idea:
------
Use Postorder Traversal (Left → Right → Root).

A node can only be removed after both of its children have
already been processed, because removing children may turn
the current node into a new leaf.

Therefore, recursively process the left and right subtrees
first, then decide whether to remove the current node.

------------------------------------------------------------

Algorithm:
----------

1.

Recursively remove target leaf nodes from the left subtree.

Store the updated subtree by assigning it back to
root->left.

------------------------------------------------------------

2.

Recursively remove target leaf nodes from the right subtree.

Store the updated subtree by assigning it back to
root->right.

------------------------------------------------------------

3.

After both children have been processed,

if the current node

- has no left child,
- has no right child,
- and its value equals the target,

remove it by returning NULL.

Otherwise, return the current node.

------------------------------------------------------------

Example:
--------

Target = 2

        1
       / \
      2   3
     /
    2

Process bottom-up.

First remove the leaf:

        1
       / \
      2   3

Now node 2 has become a leaf.

Since its value also equals the target,
remove it as well.

Final Tree:

      1
       \
        3

------------------------------------------------------------

Why Postorder?
--------------

If we checked the current node before processing its
children, we could miss newly formed leaf nodes.

By processing children first, every node is checked only
after its subtree has been updated.

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