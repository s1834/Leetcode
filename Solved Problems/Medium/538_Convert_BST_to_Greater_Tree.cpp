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
    int sum = 0;
public:
    TreeNode* convertBST(TreeNode* root) {
        if(!root) return NULL;
        convertBST(root->right);
        sum += root->val;
        root->val = sum;
        convertBST(root->left);
        return root;
    }
};

/*
Here we use a reverse in-order traversal (Right → Node → Left) to convert the BST to a Greater Tree.
1) Store the sum of all nodes visited so far in a variable `sum`.
2) Visit right subtree (greater values first)
3) Update sum and node value
4) Visit left subtree (smaller values)

Given BST:
        4
       / \
      1   6
     / \ / \
    0  2 5  7
          \
           8

Greater Sum Tree:
        30
       /  \
     36    21
    / \   /  \
  36 35 26   15
          \
          8

How it works:
Visit 8 → sum = 8 → node.val = 8

Visit 7 → sum = 8+7 = 15 → node.val = 15

Visit 6 → sum = 15+6 = 21 → node.val = 21

Visit 5 → sum = 21+5 = 26 → node.val = 26

....

Visit 0 → sum = total of all greater or equal values → node.val updated
*/