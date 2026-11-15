class Solution {
    private:
        vector<vector<int>> adj; // adjacency list
        vector<long long> dp; // maximum score
        vector<long long> subtreeSum; // original sum
    
        void dfs(vector<int>&op, vector<int>& score, int u) {
            long long totalDP = score[u];
            subtreeSum[u] = score[u];
            long long minSubtree = INT_MAX; // minimum subtree sum
    
            for(int v : adj[u]) {
                dfs(op, score, v);
    
                totalDP += dp[v];
                subtreeSum[u] += subtreeSum[v];
    
                minSubtree = min(minSubtree, dp[v]);
            }
    
            if(adj[u].empty()) {
                dp[u] = score[u];
                return;
            }
    
            if(op[u] == 0) dp[u] = totalDP - min(0LL, (long long)minSubtree);
            else dp[u] = totalDP - minSubtree;
        }
        
    public:
        int maxScore(vector<int>& parent, vector<int>& op, vector<int>& score) {
            int n = parent.size();
            adj.resize(n);
            for(int i = 1; i < n; i++) adj[parent[i]].push_back(i);
    
            dp.assign(n, 0);
            subtreeSum.assign(n, 0);
    
            dfs(op, score, 0);
            return dp[0];
        }
    };

/*
    LeetCode 4112: Maximize Score After Zeroing Subtrees

    Approach: Tree DP (DFS + Postorder Traversal)

    Intuition:
    We are given a rooted tree where every node has:
        - `op[i]`: Determines whether selecting a child subtree is optional
                    or mandatory.
        - `score[i]`: The original score of the node.

    We need to maximize the sum of all remaining node scores after
    processing every non-leaf node exactly once.

    When processing a non-leaf node:
        - If op[u] == 0, we can choose at most one child subtree to zero,
          or choose no child.
        - If op[u] == 1, we must choose exactly one child subtree to zero.

    Zeroing a child subtree means that the scores of that child and
    all its descendants become zero.

    The key observation is that if we zero a child subtree, we lose
    the score that would otherwise be obtained from that entire subtree.

    Therefore, we should choose the child subtree that causes the
    minimum loss.

    We use Tree DP to calculate the maximum score obtainable from
    every subtree.

    DP State:
        dp[u] = Maximum score obtainable from the subtree rooted at u,
                considering all operations performed inside this subtree
                and the operation at node u.

    Additional State:
        subtreeSum[u] = Original sum of all node scores in the subtree
                        rooted at u.

    Note:
        `subtreeSum` is calculated and maintained in this implementation,
        but it is not used in the final DP transition.

    Step-by-Step Explanation:

    1. Build the adjacency list:

        vector<vector<int>> adj;

       We convert the parent array into a tree representation.

        for(int i = 1; i < n; i++)
            adj[parent[i]].push_back(i);

       For every node i:
           - parent[i] is its parent.
           - Add i to the list of children of parent[i].

       Since node 0 is the root, DFS starts from node 0.

    2. Initialize DP arrays:

        dp.assign(n, 0);
        subtreeSum.assign(n, 0);

       `dp[u]` will store the maximum achievable score for subtree u.

       `subtreeSum[u]` will store the original sum of scores in
       subtree u.

    3. Start DFS:

        dfs(op, score, 0);

       We perform DFS starting from the root.

       The DFS processes children before calculating the answer
       for the current node.

       This is a postorder traversal, which is necessary because
       the DP value of a node depends on the DP values of its children.

    4. Initialize the current node's values:

        long long totalDP = score[u];
        subtreeSum[u] = score[u];

       `totalDP` initially contains the current node's own score.

       As we process its children, we add their optimal DP values.

       `subtreeSum[u]` initially contains the original score of u.
       We later add the original subtree sums of its children.

    5. Initialize the minimum child DP value:

        long long minSubtree = INT_MAX;

       This variable stores the minimum DP value among all children.

       Since we may need to zero exactly one child subtree, this
       identifies the child whose removal causes the smallest
       reduction in the achievable score.

    6. Process every child:

        for(int v : adj[u]) {

            dfs(op, score, v);

            totalDP += dp[v];

            subtreeSum[u] += subtreeSum[v];

            minSubtree = min(minSubtree, dp[v]);
        }

       For every child v:

       a. Recursively calculate its optimal score:

            dfs(op, score, v);

          This ensures dp[v] is available before calculating dp[u].

       b. Add the child's optimal score:

            totalDP += dp[v];

          Before processing the current node's operation, the total
          achievable score is the current node's score plus the
          optimal scores of all its children.

       c. Calculate the original subtree sum:

            subtreeSum[u] += subtreeSum[v];

          This combines the original scores of the current node
          and all its descendants.

       d. Find the minimum child DP value:

            minSubtree = min(minSubtree, dp[v]);

          We need to identify the child subtree with the smallest
          achievable score because zeroing that subtree causes
          the least loss.

    7. Handle leaf nodes:

        if(adj[u].empty()) {
            dp[u] = score[u];
            return;
        }

       A leaf has no children, so no operation is performed on it.

       Its score remains unchanged.

       Therefore:

            dp[u] = score[u];

       We return immediately because there are no child subtrees
       to process.

    8. Handle nodes where operation is optional:

        if(op[u] == 0)
            dp[u] = totalDP - min(0LL, (long long)minSubtree);

       When op[u] == 0, we can either:
           - Choose no child subtree.
           - Choose exactly one child subtree to zero.

       The current `totalDP` represents the score obtained when
       we preserve the optimal contribution of every child.

       There are two possibilities:

       Case 1: Do not zero any child.

           Score = totalDP

       Case 2: Zero the child with the minimum DP value.

           Score = totalDP - minSubtree

       We choose whichever gives the larger result.

       This is equivalent to:

           totalDP - min(0LL, minSubtree)

       Why?

           If minSubtree is positive:
               min(0, minSubtree) = 0

               We lose nothing by choosing no child.

               dp[u] = totalDP

           If minSubtree is negative:
               min(0, minSubtree) = minSubtree

               Removing that negative contribution increases
               the total score.

               dp[u] = totalDP - minSubtree

       Therefore, this transition handles both possibilities.

    9. Handle nodes where operation is mandatory:

        else dp[u] = totalDP - minSubtree;

       When op[u] == 1, we must choose exactly one child subtree
       and set all its scores to zero.

       We cannot choose to do nothing.

       To maximize the remaining score, we should remove the child
       subtree with the smallest DP value.

       Therefore:

           dp[u] = totalDP - minSubtree;

       This works even if the minimum child DP value is negative:
       removing a negative contribution increases the total score.

    10. Return the root's answer:

        return dp[0];

       Since node 0 is the root, its subtree contains the entire tree.

       Therefore, dp[0] represents the maximum possible score
       remaining after all required operations.

    ------------------------------------------------------------
    Example Walkthrough:
    ------------------------------------------------------------

        parent = [-1, 0, 0, 0, 1, 2, 3, 3]

        op = [1, 1, 0, 0, 1, 1, 0, 1]

        score = [5, 6, 1, 2, 3, 2, 3, -3]

        Tree structure:

                    0 (5)
                  /   |   \
               1(6)  2(1)  3(2)
                |      |    / \
               4(3)  5(2) 6(3) 7(-3)

        DFS processes the leaves first.

        Leaf nodes:

            dp[4] = 3
            dp[5] = 2
            dp[6] = 3
            dp[7] = -3

        Node 1:
            score[1] = 6
            child DP = [3]
            totalDP = 6 + 3 = 9
            minSubtree = 3

            op[1] = 1

            Must zero exactly one child.

            dp[1] = 9 - 3 = 6

        Node 2:
            score[2] = 1
            child DP = [2]
            totalDP = 1 + 2 = 3
            minSubtree = 2

            op[2] = 0

            Optional operation.

            dp[2] = 3 - min(0, 2)
                  = 3

            We choose not to zero its child.

        Node 3:
            score[3] = 2
            child DP = [3, -3]

            totalDP = 2 + 3 + (-3) = 2
            minSubtree = -3

            op[3] = 0

            Optional operation.

            dp[3] = 2 - min(0, -3)
                  = 2 - (-3)
                  = 5

            We zero the subtree rooted at node 7 because its
            achievable score is negative.

        Root node 0:
            score[0] = 5
            child DP = [6, 3, 5]

            totalDP = 5 + 6 + 3 + 5 = 19
            minSubtree = 3

            op[0] = 1

            Mandatory operation.

            We must zero exactly one child subtree.

            The minimum child DP value is 3, belonging to node 2.

            dp[0] = 19 - 3
                  = 16

        Final Answer: 16

    ------------------------------------------------------------
    Why This DP Works:
    ------------------------------------------------------------

    1. Independent Child Subtrees:

       Before processing node u, the optimal contribution of each
       child subtree can be calculated independently using DFS.

       Their combined contribution is:

           totalDP = score[u] + sum(dp[v])

    2. Only One Child Can Be Zeroed:

       The operation at node u affects exactly one child subtree.

       Therefore, we only need to consider the child with the
       minimum DP value.

       Zeroing any other child would remove an equal or larger
       contribution and cannot produce a better result.

    3. Optional Operation:

       If op[u] == 0, we compare:
           - Keeping every child subtree.
           - Removing the minimum-valued child subtree.

       This gives:

           dp[u] = totalDP - min(0, minSubtree)

    4. Mandatory Operation:

       If op[u] == 1, we must remove one child subtree.

       Removing the minimum-valued child gives:

           dp[u] = totalDP - minSubtree

    5. Postorder Dependency:

       Since dp[u] depends on dp[v] for every child v, DFS must
       calculate the children before calculating the parent.

       This is exactly what the recursive postorder traversal does.

    ------------------------------------------------------------
    Complexity Analysis:
    ------------------------------------------------------------

    Let n be the number of nodes.

    - Time Complexity: O(n)

      Building the adjacency list takes O(n).

      DFS visits every node exactly once.

      Every parent-child edge is processed once, and each DP
      transition takes constant time per child.

      Therefore, total time complexity is O(n).

    - Space Complexity: O(n)

      Adjacency list stores n - 1 edges: O(n).

      DP and subtreeSum arrays each use O(n) space.

      The recursive DFS stack can use O(n) space in the worst
      case when the tree is a chain.

      Overall space complexity is O(n).

    Core Idea:
    Use postorder Tree DP to calculate the maximum achievable score
    for every subtree.

    For each non-leaf node:
        - Sum its own score and the optimal scores of all children.
        - Find the child with the minimum DP value.
        - If the operation is optional, remove that child only
          when its DP value is negative.
        - If the operation is mandatory, always remove that child.

    The DP value at the root gives the maximum possible final score.
*/