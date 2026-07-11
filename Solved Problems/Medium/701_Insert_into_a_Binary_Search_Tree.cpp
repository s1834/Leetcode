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
        TreeNode* insertIntoBST(TreeNode* root, int val) {
            if(!root) return new TreeNode(val);
    
            if(root->val > val) root->left = insertIntoBST(root->left, val);
            else if(root->val < val) root->right = insertIntoBST(root->right, val);
            
            return root;
        }
    };

/*

Idea:
------
To insert a new value into a Binary Search Tree (BST),
we follow the BST property.

For every node:

Left Subtree  -> values smaller than the current node.

Right Subtree -> values greater than the current node.

Starting from the root, compare the value to insert with
the current node and recursively move to the correct subtree
until a NULL position is found.

The new node is inserted at that position.

------------------------------------------------------------

Algorithm:
----------

1.

If the current node is NULL,

we have reached the correct insertion position.

Create a new node and return it.

------------------------------------------------------------

2.

Compare the value with the current node.

Case 1:

val < root->val

The value belongs to the left subtree.

Recursively insert into

root->left

and reconnect the returned subtree.

------------------------------------------------------------

Case 2:

val > root->val

The value belongs to the right subtree.

Recursively insert into

root->right

and reconnect the returned subtree.

------------------------------------------------------------

3.

Return the current root.

This allows every recursive call to reconnect its child
and eventually return the original root of the BST.

------------------------------------------------------------

Example:
--------

Insert

5

into

        4
       / \
      2   7

Step 1

5 > 4

Go to the right subtree.

        4
       / \
      2   7

------------------------------------------------------------

Step 2

5 < 7

Go to the left subtree.

        7
       /
     NULL

------------------------------------------------------------

Step 3

Current node is NULL.

Create

        5

Return it.

------------------------------------------------------------

Reconnect

        7
       /
      5

Return to node 4.

------------------------------------------------------------

Final Tree

        4
       / \
      2   7
         /
        5

------------------------------------------------------------

Time Complexity:
----------------

Average Case:

O(log n)

The height of a balanced BST is logarithmic.

Worst Case:

O(n)

For a skewed BST, the height becomes n.

------------------------------------------------------------

Space Complexity:
-----------------

Average Case:

O(log n)

Worst Case:

O(n)

Due to the recursive call stack.

*/