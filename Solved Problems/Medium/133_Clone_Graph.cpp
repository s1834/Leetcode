/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
    private:
        unordered_map<Node*, Node*> mp;
    
    public:
        Node* cloneGraph(Node* node) {
            if(!node) return nullptr;
    
            // already exists
            if(mp.find(node) != mp.end()) return mp[node];
    
            // create clone
            Node* newNode = new Node(node->val);
            mp[node] = newNode;
    
            // clone neighbors
            for (Node* neighbor : node->neighbors) newNode->neighbors.push_back(cloneGraph(neighbor));
    
            return newNode;
        }
    };

/*

Approach:
---------

We use DFS to clone the graph.

The main challenge is that the graph may contain cycles.
If we recursively clone neighbors without keeping track of
already cloned nodes, we may revisit the same node multiple
times, leading to duplicate copies or infinite recursion.

To avoid this, we maintain a hash map:

Original Node  ->  Cloned Node

Algorithm:
----------

1. If the current node is nullptr, return nullptr.

2. If the node has already been cloned, simply return the
   cloned node from the map.

3. Otherwise, create a new node with the same value and
   store it in the map.

4. Recursively clone all neighbors and add the cloned
   neighbors to the new node.

5. Return the cloned node.

Why store the node before exploring neighbors?
----------------------------------------------

Graphs can contain cycles.

For example:

1 ----- 2
|       |
|       |
4 ----- 3

While cloning node 1, we may eventually reach node 1 again
through another path.

Since node 1 is already present in the map, we simply return
its clone instead of creating another copy.

This prevents infinite recursion and ensures every original
node is cloned exactly once.

Time Complexity:
----------------
O(V + E)

Space Complexity:
-----------------
O(V)

where V = number of vertices and E = number of edges.

*/