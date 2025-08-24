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
    set<int> s;
    void inOrder(TreeNode* root) {
        if(!root) return;
        inOrder(root->left);
        s.insert(root->val);
        inOrder(root->right);
    }

public:
    int findSecondMinimumValue(TreeNode* root) {
        inOrder(root);
        if(s.size() == 1) return -1;
        return *next(s.begin(), 1);
    }
};

/*
1) The findSecondMinimumValue function finds the second minimum value in a binary tree.
2) It performs an in-order traversal to collect all unique values in a set.
3) If the set contains only one unique value, it means there is no second minimum, so it returns -1.
4) Otherwise, it returns the second minimum value by accessing the second element in the set.
    - next(s.begin(), 1) is a way to get the iterator to the second element in the set.

What is std::next?
- std::next is a function from the C++ Standard Library defined in <iterator>.
- It is used to get an iterator to the element that is n positions ahead of a given iterator.
- It takes an iterator and returns a new iterator advanced forward by n steps (without modifying the original iterator).
-  If you don’t provide n, it defaults to 1.
- Syntax:
    std::next(iterator it, difference_type n = 1);
        it → the starting iterator
        n → how many steps forward you want to move
*/