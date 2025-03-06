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
    void inorderTraversal(TreeNode* root, vector<int>& inorder) {
        if(!root) return;
        inorderTraversal(root->left, inorder);
        inorder.push_back(root->val);
        inorderTraversal(root->right, inorder);
    }

    TreeNode* createBalancedBST(vector<int>& inorder, int start, int end) {
        if(start > end) return nullptr;
        int mid = start + (end - start) / 2;
        TreeNode* leftSubTree = createBalancedBST(inorder, start, mid - 1);
        TreeNode* rightSubTree = createBalancedBST(inorder, mid + 1, end);
        return new TreeNode(inorder[mid], leftSubTree, rightSubTree);
    }

public:
    TreeNode* balanceBST(TreeNode* root) {
        vector<int> inorder;
        inorderTraversal(root, inorder);
        int n = inorder.size();
        return createBalancedBST(inorder, 0, n - 1);
    }
};