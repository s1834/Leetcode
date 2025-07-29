/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(p->val < root->val && q->val < root->val) return lowestCommonAncestor(root->left, p, q);
        else if(p->val > root->val && q->val > root->val) return lowestCommonAncestor(root->right, p, q);
        else return root;
    }
};

/*
Since it is a Binary Search Tree (BST):
1) left subtree contains values less than the root.
2) right subtree contains values greater than the root.
So considering the above properties, we can find the lowest common ancestor (LCA) of two nodes `p` and `q` as follows:
- If both `p` and `q` are less than the root, then LCA is in the left subtree.
- If both `p` and `q` are greater than the root, then LCA is in the right subtree.
- If one of them is less than the root and the other is greater than the root, then the root is the LCA.
*/