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
        int search(vector<int>& inorder, int rootVal, int start, int end) {
            for(int i = start; i <= end; i++) if(inorder[i] == rootVal) return i;
            return 0;
        }
    
        TreeNode* build(vector<int>& preorder, vector<int>& inorder, int& idx, int start, int end) {
            if(start > end) return NULL;
    
            int rootVal = preorder[idx];
            int i = search(inorder, rootVal, start, end);
    
            idx++;
    
            TreeNode* root = new TreeNode(rootVal);
            root->left = build(preorder, inorder, idx, start, i - 1);
            root->right = build(preorder, inorder, idx, i + 1, end);
    
            return root;
        }
    
    public:
        TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
            int idx = 0;
            return build(preorder, inorder, idx, 0, preorder.size() - 1);
        }
    };

/*

Idea:
------
A binary tree can be uniquely reconstructed using its

Preorder Traversal

and

Inorder Traversal.

The key observations are:

• In Preorder, the first element is always the root of
  the current subtree.

• In Inorder, all nodes to the left of the root belong to
  the left subtree, while all nodes to the right belong
  to the right subtree.

Using these properties,

we recursively construct the entire tree.

------------------------------------------------------------

Traversal Properties:
---------------------

Preorder

Root → Left → Right

The first unprocessed element is always the root.

--------------------------------

Inorder

Left → Root → Right

The position of the root divides the tree into

Left Subtree

and

Right Subtree.

------------------------------------------------------------

Algorithm:
----------

Maintain an index

idx

in the preorder array.

Initially,

idx = 0.

------------------------------------------------------------

Step 1:

The current preorder element

preorder[idx]

is the root of the current subtree.

Create a new node.

------------------------------------------------------------

Step 2:

Search for this root value in the inorder array.

Suppose its position is

i.

Then,

inorder[start ... i-1]

represents the left subtree.

inorder[i+1 ... end]

represents the right subtree.

------------------------------------------------------------

Step 3:

Increment

idx

because the current root has been processed.

------------------------------------------------------------

Step 4:

Recursively construct

Left Subtree

using

[start, i-1]

------------------------------------------------------------

Step 5:

Recursively construct

Right Subtree

using

[i+1, end]

------------------------------------------------------------

Step 6:

Return the constructed root.

------------------------------------------------------------

Why Does This Work?
-------------------

Every recursive call constructs exactly one subtree.

The preorder traversal always provides the next root.

The inorder traversal tells us exactly where that root
belongs and how to divide the remaining nodes into left
and right subtrees.

Since every node is processed exactly once in preorder,

and every recursive call works on a smaller inorder
range,

the complete tree is reconstructed correctly.

------------------------------------------------------------

Example:
--------

Preorder

[3,9,20,15,7]

Inorder

[9,3,15,20,7]

--------------------------------

idx = 0

Root = 3

Find

3

in inorder.

          3
         / \
Left    /   \ Right

Left Inorder

[9]

Right Inorder

[15,20,7]

--------------------------------

Recursive Left

idx = 1

Root = 9

No children.

--------------------------------

Recursive Right

idx = 2

Root = 20

Find

20

in inorder.

Left

[15]

Right

[7]

--------------------------------

Construct

15

and

7

Return

        3
       / \
      9  20
         / \
        15  7

------------------------------------------------------------

Role of idx:
------------

The preorder array is processed exactly once.

Instead of passing separate preorder ranges,

the variable

idx

always points to the next root that needs to be created.

Since preorder visits nodes in

Root → Left → Right

order,

the recursive construction naturally consumes preorder in
the correct sequence.

Passing

idx

by reference ensures all recursive calls share the same
current position.

------------------------------------------------------------

Time Complexity:
----------------

Searching for the root in the inorder array takes

O(n)

for each recursive call.

Since this is done for every node,

Total Complexity:

O(n²)

------------------------------------------------------------

Space Complexity:
-----------------

Recursive call stack:

O(h)

where

h

is the height of the tree.

Worst case:

O(n)

(skewed tree)

Best case:

O(log n)

(balanced tree)

No additional data structures are used apart from the
recursion stack.

------------------------------------------------------------

Note:
-----

This implementation performs a linear search in the
inorder array for every node.

An optimized solution stores the inorder indices in a
hash map, reducing the overall time complexity to

O(n).

*/