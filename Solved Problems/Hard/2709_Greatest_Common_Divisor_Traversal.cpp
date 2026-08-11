class DSU {
    public:
        vector<int> parent;
        vector<int> sizes;
        int numOfComponents;
    
        DSU(int n) {
            parent.resize(n);
            sizes.resize(n);
            numOfComponents = n;
    
            for(int i = 0; i < n; i++) {
                parent[i] = i;
                sizes[i] = 1;
            }
        }
    
        int find(int x) {
            if(parent[x] == x) return x;
            return parent[x] = find(parent[x]);
        }
    
        void Union(int x, int y) {
            int xParent = find(x);
            int yParent = find(y);
    
            if(xParent == yParent) return;
    
            if(sizes[xParent] >= sizes[yParent]) {
                parent[yParent] = xParent;
                sizes[xParent] += sizes[yParent];
            } else {
                parent[xParent] = yParent;
                sizes[yParent] += sizes[xParent];
            }
    
            numOfComponents--;
        }
    
        int countComponents() {
            return numOfComponents;
        }
    };
    
    class Solution {
    public:
        bool canTraverseAllPairs(vector<int>& nums) {
           int n = nums.size();
    
           DSU dsu(n);
    
           unordered_map<int, int> mp; // <factor, index> store only the first index where that factor is seen to make it parent
    
           for(int i = 0; i < n; i++) { // for each number find all its factors
                for(int factor = 2; factor * factor <= nums[i]; factor++) {
                    if(nums[i] % factor != 0) continue; // if not a factor
    
                    if(mp.find(factor) != mp.end()) { // if factor already exists, union current with parent index
                        int idx = mp[factor];
                        dsu.Union(idx, i);
                    } else mp[factor] = i; // if factor doesnt already exists create it
    
                    while(nums[i] % factor == 0) nums[i] /= factor; // divide current number by factor until it is no longer divisible
                }
    
                // if nums[i] is still greater than 1 / it is not prime factorized
                if(nums[i] > 1) {
                    if(mp.find(nums[i]) != mp.end()) {
                        int idx = mp[nums[i]];
                        dsu.Union(idx, i);
                    } else mp[nums[i]] = i;
                }
            }
    
            return dsu.countComponents() == 1; // if it is a single component we can traverse
        }
    };

/*
LeetCode 2709. Greatest Common Divisor Traversal

Idea:
------

We have an array nums.

We can move between two indices i and j if:

    gcd(nums[i], nums[j]) > 1

The question asks whether we can traverse between

ALL

elements.

Instead of explicitly checking every pair of numbers, we can
build connected components using their

PRIME FACTORS.

Key observation:

If two numbers share any prime factor,

    gcd(a, b) > 1

so they belong to the same connected component.

Therefore, we can connect numbers through their common prime
factors using DSU.

------------------------------------------------------------

Example:
--------

nums = [6, 10, 15]

Prime factors:

    6  -> 2, 3
    10 -> 2, 5
    15 -> 3, 5

6 and 10 share factor 2:

    6 <-> 10

6 and 15 share factor 3:

    6 <-> 15

10 and 15 share factor 5:

    10 <-> 15

Therefore, all three numbers belong to one component.

Answer:

    true

------------------------------------------------------------

Why DSU?
--------

We need to repeatedly connect numbers that share a factor.

DSU is perfect for this because it efficiently supports:

    find(x)
        -> find which component x belongs to

    Union(x, y)
        -> merge the components of x and y

At the end:

    if all numbers belong to one component

then we can traverse between every pair through some sequence
of valid gcd connections.

------------------------------------------------------------

DSU Initialization:
-------------------

Initially, every number is its own component.

For:

    nums = [6, 10, 15]

we have:

    {0}
    {1}
    {2}

So:

    numOfComponents = 3

The DSU constructor:

    numOfComponents = n;

keeps track of how many connected components currently exist.

------------------------------------------------------------

Union:
-------

When we find that two indices share a prime factor,

we call:

    dsu.Union(idx, i);

If they are already in the same component,

nothing changes:

    if(xParent == yParent) return;

Otherwise, their components are merged and:

    numOfComponents--;

This is important because at the end we only need to know
whether there is exactly one component.

------------------------------------------------------------

Path Compression:
-----------------

In:

    find(int x)

we recursively find the root of x.

This line:

    parent[x] = find(parent[x]);

performs path compression.

After finding the root,

x is directly connected to that root.

This makes future DSU operations very fast.

------------------------------------------------------------

Union by Size:
--------------

When merging two components, your code attaches the smaller
component under the larger component:

    if(sizes[xParent] >= sizes[yParent])

This prevents the DSU tree from becoming unnecessarily deep.

After merging:

    sizes[xParent] += sizes[yParent];

and:

    numOfComponents--;

------------------------------------------------------------

Main Trick: Factor -> Index
---------------------------

The important data structure is:

    unordered_map<int, int> mp;

It stores:

    <primeFactor, index>

For example:

    mp[2] = 0

means:

    index 0 is the first number we encountered containing
    prime factor 2.

Suppose later we encounter another number containing factor 2.

We do:

    dsu.Union(mp[2], i);

This connects the current number to the first number that
contained the same factor.

We do NOT need to connect the current number to every previous
number containing that factor.

Connecting it to just one representative is enough to merge
the entire component.

------------------------------------------------------------

Example:
--------

nums:

    [6, 10]

Process 6:

    factors = 2, 3

Store:

    mp[2] = 0
    mp[3] = 0

So index 0 represents both factors.

--------------------------------

Process 10:

    factor = 2

We already have:

    mp[2] = 0

Therefore:

    Union(0, 1)

Now:

    6 and 10

belong to the same component.

------------------------------------------------------------

Why Only Store the First Index?
--------------------------------

Suppose:

    nums = [6, 10, 14]

All three contain factor 2.

We store:

    mp[2] = 0

When processing 10:

    Union(0,1)

When processing 14:

    Union(0,2)

Now all three are connected.

There is no need to do:

    Union(1,2)

because they are already connected through index 0.

So storing one representative index for every factor is enough.

------------------------------------------------------------

Finding Prime Factors:
-----------------------

For every number:

    nums[i]

we try possible factors:

    for(int factor = 2;
        factor * factor <= nums[i];
        factor++)

If:

    nums[i] % factor != 0

then factor is not a divisor,

so we continue.

If it is a factor,

we process it.

------------------------------------------------------------

Why Divide Repeatedly?
-----------------------

This part:

    while(nums[i] % factor == 0)
        nums[i] /= factor;

removes all occurrences of the same factor.

For example:

    nums[i] = 12

12 = 2 × 2 × 3

When factor = 2:

    12 -> 6 -> 3

Now factor 2 has been completely removed.

We only need to know that

    2

is a prime factor.

We do not need to process it again.

------------------------------------------------------------

Example:

    nums[i] = 72

Prime factorization:

    72 = 2 × 2 × 2 × 3 × 3

When factor = 2:

    72 -> 36 -> 18 -> 9

Then factor 2 is completely removed.

Later:

    factor = 3

and:

    9 -> 3 -> 1

So the unique prime factors are:

    2, 3

------------------------------------------------------------

Why factor * factor <= nums[i]?
--------------------------------

If a number has a factor greater than its square root,

then it must have another factor smaller than its square root.

For example:

    30 = 5 × 6

Since:

    5 <= sqrt(30)

we can discover the factor 5 while checking up to sqrt(n).

After removing all smaller factors,

if:

    nums[i] > 1

then the remaining value must itself be a prime factor.

------------------------------------------------------------

Handling the Remaining Prime:
------------------------------

After the loop:

    if(nums[i] > 1)

the remaining value is a prime factor that has not yet been
processed.

For example:

    nums[i] = 35

We find:

    factor = 5

and remove it:

    35 -> 7

Now the loop ends because:

    7

does not have any factor <= sqrt(7).

Therefore:

    7

is the remaining prime factor.

Your code processes it:

    if(mp.find(nums[i]) != mp.end()) {
        int idx = mp[nums[i]];
        dsu.Union(idx, i);
    } else {
        mp[nums[i]] = i;
    }

------------------------------------------------------------

Complete Example:
-----------------

nums:

    [6, 10, 15]

Initially:

    components = 3

--------------------------------

Process index 0:

    nums[0] = 6

Factors:

    2, 3

Store:

    mp[2] = 0
    mp[3] = 0

Components:

    {0}, {1}, {2}

--------------------------------

Process index 1:

    nums[1] = 10

Factor:

    2

Already exists:

    mp[2] = 0

So:

    Union(0,1)

Components:

    {0,1}, {2}

Then remaining factor:

    5

Store:

    mp[5] = 1

--------------------------------

Process index 2:

    nums[2] = 15

Factor:

    3

Already exists:

    mp[3] = 0

So:

    Union(0,2)

Components:

    {0,1,2}

Then factor:

    5

Already exists:

    mp[5] = 1

So:

    Union(1,2)

They are already connected, so nothing changes.

Finally:

    numOfComponents = 1

Therefore:

    return true

------------------------------------------------------------

Why Does One Component Mean We Can Traverse All Pairs?
------------------------------------------------------------

We create a graph where:

    each index = a node

and two nodes are connected whenever their numbers have a
common prime factor.

That is exactly equivalent to:

    gcd(nums[i], nums[j]) > 1

A connected component means there is some sequence of valid
moves connecting those indices.

Therefore:

    one connected component

means:

    every index can reach every other index.

So:

    dsu.countComponents() == 1

is the final condition.

------------------------------------------------------------

Important Edge Case:
--------------------

If:

    nums = [1, 1]

then neither number has any prime factor.

There is no valid gcd connection because:

    gcd(1,1) = 1

Initially:

    numOfComponents = 2

No Union happens.

Therefore:

    numOfComponents != 1

and the answer is:

    false

Similarly, if nums contains a 1 along with other numbers,
that 1 cannot share a gcd > 1 with anything, so it forms an
isolated component.

------------------------------------------------------------

Why We Modify nums:
-------------------

Inside the factorization loop you do:

    nums[i] /= factor;

This modifies the input array.

That is okay for this solution because after processing a number,
we only need its remaining prime factors.

The original values are not needed later.

If preserving the input were required,

we could use a temporary variable instead:

    int x = nums[i];

and factorize x instead.

------------------------------------------------------------

Overall Flow:
-------------

For every number:

        nums[i]
           |
           ↓
    Find prime factors
           |
           ↓
    Have we seen this factor?
        /          \
      Yes           No
       |             |
       ↓             ↓
    Union(i,       Store i
    previous)      as owner
       |
       ↓
 Merge components

After processing every number:

        DSU
         |
         ↓
  Count components
         |
     +---+---+
     |       |
     1      >1
     |       |
   true    false

------------------------------------------------------------

Main Concept to Remember:
--------------------------

The important trick in this problem is:

    Do NOT compare every pair of numbers.

Instead:

    Number
      ↓
    Prime factors
      ↓
    Common factor
      ↓
    Union their indices
      ↓
    DSU connected components

So the problem changes from:

    "Can every pair of numbers be connected?"

into:

    "Do all indices belong to one connected component?"

That is why DSU + prime factorization is the key pattern here.

------------------------------------------------------------

Time Complexity:
----------------

Let:

    n = number of elements
    M = maximum value in nums

We factorize each number using trial division up to its
square root, with repeated division removing duplicate factors.

The practical complexity is roughly:

    O(n * sqrt(M) * α(n))

where α(n) is the inverse Ackermann function from DSU.

Since α(n) grows extremely slowly, DSU operations are
effectively almost constant time.

------------------------------------------------------------

Space Complexity:
-----------------

DSU arrays:

    O(n)

Map of prime factors:

    O(number of distinct prime factors)

Therefore:

    O(n + number of distinct factors)

which is effectively:

    O(n)

for the constraints.

*/