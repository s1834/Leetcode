/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 class Codec {
    private:
        void preorder(TreeNode* root, string &serialized) {
            if(!root) {
                serialized += "n,";
                return;
            }
    
            serialized += to_string(root->val) + ",";
    
            preorder(root->left, serialized);
            preorder(root->right, serialized);
        }
    
        TreeNode* build(vector<string>& v, int& i) {
            if(v[i] == "n") {
                i++;
                return nullptr;
            }
    
            TreeNode* newNode = new TreeNode(stoi(v[i]));
            i++;
    
            newNode->left = build(v, i);
            newNode->right = build(v, i);
    
            return newNode;
        }
        
    public:
    
        // Encodes a tree to a single string.
        string serialize(TreeNode* root) {
            string serialized = "";
            preorder(root, serialized);
            return serialized;
        }
    
        // Decodes your encoded data to tree.
        TreeNode* deserialize(string data) {
            vector<string> v;
            string temp = "";
            for(auto x : data) {
                if(x == ',') {
                    v.push_back(temp);
                    temp = "";
                } else temp += x;
            }
            
            int i = 0;
            return build(v, i);
        }
    };
    
    // Your Codec object will be instantiated and called as such:
    // Codec ser, deser;
    // TreeNode* ans = deser.deserialize(ser.serialize(root));

/*

Idea:
------
The goal is to convert a binary tree into a string
(Serialization)

and later reconstruct the exact same tree from that string
(Deserialization).

This solution uses

Preorder Traversal

along with a special marker

"n"

to represent NULL nodes.

Recording NULL nodes is essential because without them,
different tree structures could produce the same traversal.

------------------------------------------------------------

Serialization:
--------------

Perform a preorder traversal.

Preorder Order:

Root → Left → Right

--------------------------------

For every node:

If the node exists,

append

node->value + ","

to the serialized string.

--------------------------------

If the node is NULL,

append

"n,"

to indicate an empty child.

Thus every node and every NULL child is explicitly stored.

------------------------------------------------------------

Deserialization:
----------------

First,

split the serialized string using ','

to obtain a vector of tokens.

Example:

Serialized String

"1,2,n,n,3,4,n,n,5,n,n,"

↓

Vector

["1","2","n","n","3","4","n","n","5","n","n"]

------------------------------------------------------------

Now recursively rebuild the tree using the same preorder
order.

Maintain an index

i

that always points to the current token.

--------------------------------

If

v[i] == "n"

this represents a NULL node.

Increment

i

and return

nullptr.

--------------------------------

Otherwise,

create a new node using

stoi(v[i])

Increment

i

Recursively build

Left Subtree

Recursively build

Right Subtree

Return the constructed node.

------------------------------------------------------------

Why Does This Work?
-------------------

Serialization records nodes in

Root → Left → Right

order.

During deserialization,

we read the values in exactly the same order.

Whenever a value is encountered,

we create a node.

Whenever

"n"

is encountered,

we know that the corresponding child does not exist.

Since NULL children are explicitly stored,

the exact tree structure is preserved.

Thus,

serialization and deserialization are perfect inverses of
each other.

------------------------------------------------------------

Example:
--------

Original Tree

        1
       / \
      2   3
         / \
        4   5

--------------------------------

Preorder Traversal

1

2

NULL

NULL

3

4

NULL

NULL

5

NULL

NULL

--------------------------------

Serialized String

1,2,n,n,3,4,n,n,5,n,n,

--------------------------------

Deserialization

Read

1

↓

Create Root

        1

--------------------------------

Read

2

↓

Create Left Child

        1
       /
      2

Next two tokens are

n

n

So

2

has no children.

--------------------------------

Read

3

↓

Create Right Child

        1
       / \
      2   3

--------------------------------

Read

4

↓

Attach as left child of

3

--------------------------------

Read

5

↓

Attach as right child of

3

Final Tree

        1
       / \
      2   3
         / \
        4   5

Exactly the original tree.

------------------------------------------------------------

Why Are NULL Markers Necessary?
-------------------------------

Consider these two trees.

Tree 1

    1
   /
  2

--------------------------------

Tree 2

    1
     \
      2

Without NULL markers,

both preorder traversals become

1 2

making them indistinguishable.

Using

"n"

preserves the exact position of missing children,
allowing unique reconstruction.

------------------------------------------------------------

Time Complexity:
----------------

Serialization:

Each node is visited exactly once.

O(n)

--------------------------------

Deserialization:

Each token is processed exactly once.

O(n)

Overall:

O(n)

------------------------------------------------------------

Space Complexity:
-----------------

Serialization String:

O(n)

--------------------------------

Vector of Tokens:

O(n)

--------------------------------

Recursive Call Stack:

Worst Case (Skewed Tree):

O(n)

Balanced Tree:

O(log n)

Overall Auxiliary Space:

O(n)

*/