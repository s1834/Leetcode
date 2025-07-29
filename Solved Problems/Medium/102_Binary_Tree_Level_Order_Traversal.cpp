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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if(!root) return ans;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            int n = q.size();
            vector<int> level;
            for(int i = 0; i < n; i++) {
                if(q.front()->left) q.push(q.front()->left);
                if(q.front()->right) q.push(q.front()->right);
                level.push_back(q.front()->val);
                q.pop();
            }
            ans.push_back(level);
        }
        return ans;
    }
};

/*
Level Order Traversal = Breadth-First Search (BFS)
There are two common approaches to implement level order traversal:
1) Using a queue:
- Start with the root node in the queue.
- While the queue is not empty:
  - Get the size of the queue (number of nodes at the current level).
  - For each node at the current level:
  - If it has a left child, add it to the queue.
  - If it has a right child, add it to the queue.
  
2) Using recursion
*/