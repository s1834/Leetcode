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
    void inOrder(TreeNode* root, vector<int> &v) {
        if(!root) return;
        inOrder(root->left, v);
        v.push_back(root->val);
        inOrder(root->right, v);
    }
    
public:
    int kthSmallest(TreeNode* root, int k) {
       vector<int> v;
       inOrder(root, v);
       return v[k - 1];
    }
};

/*
1) The inOrder function performs an in-order traversal of the BST and stores the values in a vector.
    - inorder traversal ensures that the values are stored in sorted order.
2) The kthSmallest function calls inOrder to fill the vector and then returns the k-1 th element (0-indexed) as the result.
*/