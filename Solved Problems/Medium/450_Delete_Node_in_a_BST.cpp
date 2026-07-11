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
        TreeNode* minimum(TreeNode* root) {
            while(root->left) root = root->left;
            return root;
        }
    
    public:
        TreeNode* deleteNode(TreeNode* root, int key) {
            if(!root) return NULL;
            
            else if(root->val > key) root->left = deleteNode(root->left, key);
            else if(root->val < key) root->right = deleteNode(root->right, key);
            else {
                 if(!root->left) {
                    TreeNode* ptr = root->right;
                    delete root;
                    return ptr;
                }
    
                if(!root->right) {
                    TreeNode* ptr = root->left;
                    delete root;
                    return ptr;
                }
    
                TreeNode* nxt = minimum(root->right);
                root->val = nxt->val;
                root->right = deleteNode(root->right, nxt->val);
            }
            return root;
        }
    };

/*

Idea:
------
To delete a node from a Binary Search Tree (BST), we first
search for the node exactly like a normal BST search.

Once the node is found, there are three possible cases.

------------------------------------------------------------

Case 1:
--------

The node has no left child.

Example:

    5
     \
      7

Delete 5.

The right child takes its place.

Return:

7

------------------------------------------------------------

Case 2:
--------

The node has no right child.

Example:

      5
     /
    3

Delete 5.

The left child takes its place.

Return:

3

------------------------------------------------------------

Case 3:
--------

The node has both left and right children.

Example:

        5
       / \
      3   8
         /
        6

We cannot simply delete the node because both subtrees
must remain connected while preserving the BST property.

Instead,

1. Find the inorder successor.
   (Smallest node in the right subtree.)

2. Copy the successor's value into the current node.

3. Delete the successor from the right subtree.

The successor is guaranteed to have no left child,
making its deletion fall into Case 1 or Case 2.

------------------------------------------------------------

Finding the Successor:
----------------------

The inorder successor is the leftmost node
of the right subtree.

Example:

        8
       / \
      6   9
     /
    5
   /
  4

The minimum is found by continuously moving left
until no further left child exists.

------------------------------------------------------------

Example:
--------

Delete 5 from

        5
       / \
      3   8
         /
        6

Find successor:

6

Copy its value:

        6
       / \
      3   8
         /
        6

Now there are two 6's.

Delete the duplicate successor from the right subtree.

Final Tree:

        6
       / \
      3   8

------------------------------------------------------------

Time Complexity:
----------------

Average Case:

O(log n)

Only one path from the root to a leaf is traversed
in a balanced BST.

Worst Case:

O(n)

For a skewed BST.

------------------------------------------------------------

Space Complexity:
-----------------

Average Case:

O(log n)

Worst Case:

O(n)

Due to the recursive call stack.

*/