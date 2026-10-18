class Solution {
    private:
        typedef long long ll;
        ll MOD = 1e9 + 7;
    
        vector<vector<int>> PascalsTriangle;
    
        int solve(vector<int>& nums) {
            int n = nums.size();
            if(n < 3) return 1; // Fewer than 3 nodes have only one possible BST insertion order
    
            vector<int> leftSubtree, rightSubtree;
            int root = nums[0];
            for(int i = 1; i < n; i++) {
                if(nums[i] < root) leftSubtree.push_back(nums[i]); // Collect nodes smaller than root
                else rightSubtree.push_back(nums[i]); // Collect nodes greater than root
            }
    
            ll x = solve(leftSubtree) % MOD; // Count valid insertion orders for the left subtree
            ll y = solve(rightSubtree) % MOD; // Count valid insertion orders for the right subtree
            ll z = PascalsTriangle[n - 1][leftSubtree.size()]; // Choose positions for left-subtree nodes among non-root nodes
    
            return (((x * y) % MOD * z)) % MOD; // Interleave left and right orders while preserving each subtree's order
        }
    
    public:
        int numOfWays(vector<int>& nums) {
            int n = nums.size();
            PascalsTriangle.resize(n + 1);
    
            // Build Pascal's Triangle to calculate binomial coefficients modulo MOD
            for(int i = 0; i <= n; i++) {
                PascalsTriangle[i] = vector<int>(i + 1, 1);
                for(int j = 1; j < i; j++) PascalsTriangle[i][j] = (PascalsTriangle[i - 1][j - 1] + PascalsTriangle[i - 1][j]) % MOD; // Compute C(i, j) = C(i-1, j-1) + C(i-1, j)
            }
    
            return (solve(nums) - 1) % MOD; // Exclude the original insertion order from the total
        }
    };

/*
Approach: Recursion + Binary Search Tree + Pascal's Triangle DP

Intuition:
----------
LeetCode 1569 asks us to count the number of different insertion orders
that produce the same Binary Search Tree (BST) as the original array.

The first element of nums is always inserted first, so it becomes the
root of the BST.

For every remaining element:
- If it is smaller than the root, it belongs to the left subtree.
- If it is greater than the root, it belongs to the right subtree.

To obtain the same BST, the relative insertion order of the elements
within each subtree must remain unchanged. However, elements belonging
to the left and right subtrees can be interleaved in different ways.

We use recursion to count valid orders for both subtrees and Pascal's
Triangle to calculate the number of ways to interleave them.

Finally, we subtract 1 to exclude the original insertion order.

--------------------------------------------------
1. Variables and Modulo
--------------------------------------------------

typedef long long ll;
ll MOD = 1e9 + 7;

The answer can become extremely large, so all counts are calculated
modulo 10^9 + 7.

The typedef ll is used for intermediate multiplication to reduce the
risk of integer overflow.

vector<vector<int>> PascalsTriangle;

This stores binomial coefficients, where:

PascalsTriangle[n][r] = C(n, r)

It represents the number of ways to choose r positions from n positions.

--------------------------------------------------
2. Recursive Function: solve(nums)
--------------------------------------------------

int solve(vector<int>& nums)

This function returns the number of insertion orders that generate
the same BST as the sequence represented by nums, including the
original insertion order.

BASE CASE:
----------
int n = nums.size();

if(n < 3) return 1;

If there are fewer than three elements, there is only one possible
insertion order that produces the same BST.

- With 0 or 1 element, there is only one ordering.
- With 2 elements, reversing their order would change the root,
  so only the original order produces the same BST.

Therefore, return 1.

--------------------------------------------------
3. Divide Elements into Left and Right Subtrees
--------------------------------------------------

int root = nums[0];

The first element is the root of the BST.

vector<int> leftSubtree, rightSubtree;

Traverse the remaining elements:

for(int i = 1; i < n; i++) {
    if(nums[i] < root)
        leftSubtree.push_back(nums[i]);
    else
        rightSubtree.push_back(nums[i]);
}

Since this is a BST:
- Values smaller than root belong to the left subtree.
- Values greater than root belong to the right subtree.

The order of elements within each vector is preserved because we
traverse nums from left to right.

This is important: each subtree must receive its elements in an
insertion order that produces the same subtree structure.

Let:
L = leftSubtree.size()
R = rightSubtree.size()

Since the root is excluded from both subtrees:

L + R = n - 1

--------------------------------------------------
4. Count Valid Orders for Both Subtrees
--------------------------------------------------

ll x = solve(leftSubtree) % MOD;
ll y = solve(rightSubtree) % MOD;

Recursively calculate:

x = number of valid insertion orders for the left subtree
y = number of valid insertion orders for the right subtree

The choices for the two subtrees are independent.

Therefore, for every valid left-subtree order, we can combine any
valid right-subtree order with it.

The total number of combinations of subtree orders is:

x * y

We take modulo MOD to keep the intermediate result manageable.

--------------------------------------------------
5. Count Ways to Interleave the Subtrees
--------------------------------------------------

ll z = PascalsTriangle[n - 1][leftSubtree.size()];

This is the key combinatorial step.

After inserting the root first, there are n - 1 remaining positions
in the insertion sequence.

We must place:
- L elements belonging to the left subtree.
- R elements belonging to the right subtree.

The relative order of the left-subtree elements must remain fixed,
and the relative order of the right-subtree elements must also
remain fixed.

However, we can choose which L of the n - 1 positions are occupied
by left-subtree elements. The remaining R positions will be occupied
by right-subtree elements.

The number of such choices is:

z = C(n - 1, L)

For example, suppose:
L = 2
R = 2

Let the left-subtree insertion order be [L1, L2], and the
right-subtree insertion order be [R1, R2].

The valid interleavings are:

1. L1 L2 R1 R2
2. L1 R1 L2 R2
3. L1 R1 R2 L2
4. R1 L1 L2 R2
5. R1 L1 R2 L2
6. R1 R2 L1 L2

There are 6 ways, which equals:

C(4, 2) = 6

Notice that the relative order within each subtree is preserved
in every interleaving.

--------------------------------------------------
6. Combine the Results
--------------------------------------------------

return (((x * y) % MOD * z)) % MOD;

The total number of valid insertion orders for the current subtree is:

ways = x * y * C(n - 1, L)

Each factor represents a separate choice:
- x: choose a valid insertion order for the left subtree.
- y: choose a valid insertion order for the right subtree.
- z: choose how to interleave the two subtree orders.

We take modulo MOD after multiplication to avoid excessively large
intermediate values.

The recursive function includes the original insertion order
in its count.

--------------------------------------------------
7. Build Pascal's Triangle
--------------------------------------------------

int numOfWays(vector<int>& nums)

int n = nums.size();
PascalsTriangle.resize(n + 1);

We precompute binomial coefficients for all required values of n
and r before starting the recursion.

for(int i = 0; i <= n; i++) {
    PascalsTriangle[i] = vector<int>(i + 1, 1);

    for(int j = 1; j < i; j++)
        PascalsTriangle[i][j] =
            (PascalsTriangle[i - 1][j - 1] +
             PascalsTriangle[i - 1][j]) % MOD;
}

Pascal's Triangle follows the recurrence:

C(i, j) = C(i - 1, j - 1) + C(i - 1, j)

Explanation:
- Every row begins and ends with 1.
- Each internal value is the sum of the two values directly above it.
- All coefficients are computed modulo MOD.

For example, the first few rows are:

Row 0:       1
Row 1:      1 1
Row 2:     1 2 1
Row 3:    1 3 3 1
Row 4:   1 4 6 4 1

If we need C(4, 2), we retrieve PascalsTriangle[4][2] = 6.

Precomputation takes O(n^2) time and O(n^2) space.

--------------------------------------------------
8. Subtract the Original Insertion Order
--------------------------------------------------

return (solve(nums) - 1) % MOD;

The recursive function counts all insertion orders that produce
the same BST, including the original input order.

But the problem asks for the number of DIFFERENT orders, excluding
the original order.

Therefore, subtract 1.

Important implementation detail:
In C++, the remainder of a negative number can be negative.
For the usual problem constraints, solve(nums) is at least 1, so
the subtraction itself is nonnegative.

--------------------------------------------------
9. Example Walkthrough
--------------------------------------------------

Consider:
nums = [2, 1, 3]

The BST is:

        2
       / \
      1   3

The root is 2.

Left subtree:
[1]

Right subtree:
[3]

For both subtrees, solve returns 1 because each contains only one node.

Thus:
x = 1
y = 1

There are n - 1 = 2 positions after the root, and the left subtree
contains L = 1 element.

Therefore:
z = C(2, 1) = 2

The total number of insertion orders is:

1 * 1 * 2 = 2

These orders are:
1. [2, 1, 3]
2. [2, 3, 1]

Both generate the same BST.

Finally:
2 - 1 = 1

Output: 1

Only one alternative insertion order produces the same BST.

--------------------------------------------------
10. Why the Algorithm Works
--------------------------------------------------

The first element must remain the root, so every valid insertion
order begins with the same root.

All elements smaller than the root must generate the same left
subtree, and all larger elements must generate the same right subtree.

By recursively counting valid insertion orders for both subtrees,
we account for every valid internal arrangement.

For each pair of valid subtree orders, Pascal's Triangle counts
all ways to interleave their elements while preserving the relative
order inside each subtree.

These choices cover every valid insertion order exactly once.

Therefore:

solve(nums) =
    solve(leftSubtree)
    * solve(rightSubtree)
    * C(n - 1, leftSubtree.size())

Subtracting one excludes the original ordering and gives the
required answer.

--------------------------------------------------
11. Complexity Analysis
--------------------------------------------------

Let n be the number of elements.

Pascal's Triangle:
- Time: O(n^2)
- Space: O(n^2)

Recursive BST partitioning:
- Each recursive call partitions its elements around the root.
- In a balanced BST, the total partitioning work is O(n log n).
- In the worst case, such as an already sorted array, the recursion
  can become highly unbalanced and partitioning takes O(n^2) time.

Overall Time Complexity:
O(n^2)

Overall Auxiliary Space Complexity:
O(n^2), dominated by Pascal's Triangle.

The recursion and temporary subtree vectors require additional
space, up to O(n^2) in the worst case when considering all recursive
allocations together; this does not change the overall O(n^2)
space bound.

Core Idea:
----------
Recursively split the sequence into left and right BST subtrees,
count the valid insertion orders for each, and multiply those counts
by C(n - 1, leftSubtree.size()) to account for every valid interleaving.
Precompute the binomial coefficients with Pascal's Triangle, then
subtract one to exclude the original insertion order.
*/