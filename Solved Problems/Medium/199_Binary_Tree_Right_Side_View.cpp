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
        vector<int> ans;
        int maxDepth = -1;
    
        void dfs(TreeNode* root, int depth) {
            if(!root) return;
    
            if(maxDepth < depth) {
                ans.push_back(root->val);
                maxDepth = depth;
            }
    
            dfs(root->right, depth + 1);
            dfs(root->left, depth + 1);
        }
    public:
        vector<int> rightSideView(TreeNode* root) {
            dfs(root, 0);
            return ans;
        }
    };

/*

Idea:
------
Perform a Depth First Search (DFS), always visiting the
right subtree before the left subtree.

Since the right subtree is explored first, the first node
encountered at every depth is the node visible from the
right side of the tree.

Maintain the maximum depth that has already been visited.

If the current depth is greater than maxDepth, it means
this is the first node encountered at this level, so add
it to the answer and update maxDepth.

------------------------------------------------------------

Traversal Order:
----------------

Current Node
      ↓
Right Subtree
      ↓
Left Subtree

Visiting the right subtree first guarantees that the
rightmost node of each level is processed before any
other node at that level.

------------------------------------------------------------

Example:
--------

        1
       / \
      2   3
       \   \
        5   4

DFS Traversal:

1 → 3 → 4 → 2 → 5

Depths:

1 -> 0
3 -> 1
4 -> 2
2 -> 1
5 -> 2

First node visited at each depth:

Depth 0 -> 1
Depth 1 -> 3
Depth 2 -> 4

Answer:

[1, 3, 4]

------------------------------------------------------------

Time Complexity:
----------------

O(n)

Every node is visited exactly once.

------------------------------------------------------------

Space Complexity:
-----------------

O(h)

where h is the height of the tree due to the recursive
call stack.

*/