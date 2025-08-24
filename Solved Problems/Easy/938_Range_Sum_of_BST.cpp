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
    int rangeSumBST(TreeNode* root, int low, int high) {
        if(!root) return 0;
        if(root->val < low) return rangeSumBST(root->right, low, high);
        if(root->val > high) return rangeSumBST(root->left, low, high);
        if(root->val >= low && root->val <= high) {
            sum += root->val;
            rangeSumBST(root->left, low, high);
            rangeSumBST(root->right, low, high);
        }
        return sum;
    }
};

/*
1) The rangeSumBST function checks if the current node's value is within the range [low, high].
2) If the current node is null, it means we've reached a leaf node, and we return 0.
3) If the current node's value is less than the lower bound, we search the right subtree.
4) If the current node's value is greater than the upper bound, we search the left subtree.
5) If the current node's value is within the range, we add it to the sum and continue searching both subtrees.
*/