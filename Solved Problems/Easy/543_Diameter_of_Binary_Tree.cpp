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
    int diameter(TreeNode* root, int& ans) {
        if(!root) return 0;

        int sumLeft, sumRight;
        sumLeft = diameter(root->left, ans);
        sumRight = diameter(root->right, ans);

        ans = max(ans, sumLeft + sumRight);

        return 1 + max(sumLeft, sumRight);
    }

public:
    int diameterOfBinaryTree(TreeNode* root) {
        int ans = 0;
        diameter(root, ans);
        return ans;
    }
};