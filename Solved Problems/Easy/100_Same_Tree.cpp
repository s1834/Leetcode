// /**
//  * Definition for a binary tree node.
//  * struct TreeNode {
//  *     int val;
//  *     TreeNode *left;
//  *     TreeNode *right;
//  *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
//  *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//  *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
//  * };
//  */
// class Solution {
// public:
//     bool isSameTree(TreeNode* p, TreeNode* q) {
//         if(!p && !q) {
//             return true;
//         }
//         if (!p || !q) {
//             return false;
//         }
//         queue<TreeNode *> que1, que2;
//         que1.push(p);
//         que2.push(q);
//         while (!que1.empty() && !que2.empty()) {
//             TreeNode* front1 = que1.front(), *front2 = que2.front();
//             que1.pop();
//             que2.pop();
//             if (front1->val != front2->val) {
//                 return false;
//             }
//             if (front1->left != NULL) {
//                 if (front2->left != NULL) {
//                     que2.push(front2->left);
//                 } else {
//                     return false;
//                 }
//                 que1.push(front1->left);
//             } else if (front2->left != NULL){
//                 return false;
//             }
            
//             if (front1->right != NULL) {
//                 if (front2->right != NULL) {
//                     que2.push(front2->right);
//                 } else {
//                     return false;
//                 }
//                 que1.push(front1->right);
//             } else if (front2->right != NULL){
//                 return false;
//             }   
//         }
//         return true;
//     }
// };

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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(!p || !q) {
            return p == q;
        }
        return (p->val == q->val) && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};