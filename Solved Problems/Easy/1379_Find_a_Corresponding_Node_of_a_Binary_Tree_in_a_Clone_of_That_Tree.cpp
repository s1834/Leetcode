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
private:
    TreeNode* ans;
public:
    TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target) {
        if(!original || !cloned || !target) return NULL;
        if(target->val == cloned->val) ans = cloned;
        getTargetCopy(original, cloned->left, target);
        getTargetCopy(original, cloned->right, target);
        return ans;
    }
};

/*
1) The getTargetCopy function checks if the current nodes in the original and cloned trees are null.
2) If the target node is found in the cloned tree, it is stored in the ans variable.
3) The function recursively searches the left and right subtrees of both trees.
4) Finally, it returns the corresponding node in the cloned tree.
*/