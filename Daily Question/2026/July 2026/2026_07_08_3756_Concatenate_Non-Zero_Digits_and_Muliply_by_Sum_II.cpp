class Solution {
    public:
        static const int MOD = 1e9 + 7;
        typedef long long ll;
    
        vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
            int n = s.size();
    
            vector<ll> pow10(n + 1, 0);      // pow10[i] = 10^i % MOD (n+1 because k can be n)
            vector<int> nonZeroCount(n, 0);  // Prefix count of non-zero digits
            vector<ll> numberUpto(n, 0);     // Number formed by all non-zero digits seen so far
            vector<ll> digitSum(n, 0);       // Prefix sum of digits
    
            // Calculate powers of 10
            pow10[0] = 1;
            for(int i = 1; i < n + 1; i++) pow10[i] = (pow10[i - 1] * 10) % MOD;
    
            // Calculate non zero count upto a particular index
            nonZeroCount[0] = (s[0] != '0') ? 1 : 0;
            for(int i = 1; i < n; i++) {
                int digit = s[i] - '0';
                nonZeroCount[i] = nonZeroCount[i - 1] + (digit ? 1 : 0);
            }
    
            // Calculate the number without zero upto a particular index
            numberUpto[0] = s[0] - '0';
            for(int i = 1; i < n; i++) {
                int digit = s[i] - '0';
                if(digit) numberUpto[i] = ((numberUpto[i - 1] * 10) + digit) % MOD;
                else numberUpto[i] = numberUpto[i - 1];
            }
    
            // Calculate the digit sum upto a particular index
            digitSum[0] = s[0] - '0';
            for(int i = 1; i < n; i++) {
                int digit = s[i] - '0';
                digitSum[i] = digitSum[i - 1] + digit;
            }
    
            int q = queries.size();
            vector<int> ans(q);
            for(int i = 0; i < q; i++) {
                int l = queries[i][0], r = queries[i][1];
    
                ll sum = digitSum[r] - (l ? digitSum[l - 1] : 0);
    
                int numBefore = l ? numberUpto[l - 1] : 0; // Number formed by non-zero digits before index l.
                int k = nonZeroCount[r] - (l ? nonZeroCount[l - 1] : 0); // power used
                ll x = (numberUpto[r] - (numBefore * pow10[k] % MOD) + MOD) % MOD; // final number between l and r
    
                ans[i] = (int) ((x * sum) % MOD); // x * sum
            }
            return ans;
        }
    };

/*

/*

Idea:
------
For every query [l, r], we need two values:

1. Sum of all digits in s[l...r].

2. Number formed by concatenating only the non-zero digits
   in s[l...r].

Answer = Number × Digit Sum.

------------------------------------------------------------

Observation:
------------

A brute-force solution would process every query independently.

For each query:

    • Traverse s[l...r].
    • Compute the digit sum.
    • Build the number by skipping zeros.

Time Complexity:

    O(length of substring)

Since both

    |s| <= 1e5
    queries <= 1e5

Worst case becomes

    O(n × q)

which is too slow.

------------------------------------------------------------

How can we answer each query in O(1)?
-------------------------------------

Instead of recomputing everything for every query,
precompute useful prefix information.

We maintain four prefix arrays.

------------------------------------------------------------

1) digitSum[i]
--------------

digitSum[i] stores

    Sum of digits from index 0 to i.

Example

s = "10203004"

digitSum

index

0 1 2 3 4 5 6 7

1 1 3 3 6 6 6 10

Then

Sum(l,r)

=

digitSum[r]

-

digitSum[l-1]

------------------------------------------------------------

2) nonZeroCount[i]
------------------

Stores

Number of non-zero digits in s[0...i].

Example

s = "10203004"

nonZeroCount

1 1 2 2 3 3 3 4

This allows us to know how many digits are present
inside any query after removing zeros.

------------------------------------------------------------

3) numberUpto[i]
----------------

Stores the number formed by concatenating every non-zero
digit from s[0...i].

Example

s = "10203004"

numberUpto

1
1
12
12
123
123
123
1234

Zeros simply keep the previous value.

------------------------------------------------------------

4) pow10[i]
-----------

pow10[i]

=

10^i % MOD

Precomputed so that powers of ten are available in O(1).

------------------------------------------------------------

How do we extract the number for a query?
-----------------------------------------

Suppose

numberUpto[r]

=

ABCDE

where

AB

belongs before l

and

CDE

belongs inside the query.

Then

ABCDE

=

AB × 10^(length of CDE)

+

CDE

Therefore

CDE

=

ABCDE

-

AB × 10^(length of CDE)

where

length(CDE)

=

number of non-zero digits inside the query

=

nonZeroCount[r] - nonZeroCount[l-1]

Hence

number

=

numberUpto[r]

-

numberBefore × 10^k

------------------------------------------------------------

Modulo subtraction
------------------

Subtraction may become negative.

Instead of

    a - b

we compute

    (a - b + MOD) % MOD

Adding one MOD keeps the value equivalent under modulo
while ensuring it never becomes negative.

------------------------------------------------------------

Algorithm
---------

Preprocessing

1. Compute powers of 10.

2. Compute prefix digit sums.

3. Compute prefix non-zero counts.

4. Compute the number formed by non-zero digits up to every index.

For every query

1. Compute digit sum using prefix sums.

2. Compute k = number of non-zero digits.

3. Remove the prefix contribution from numberUpto
   using powers of ten.

4. Multiply both values modulo MOD.

------------------------------------------------------------

Time Complexity
---------------

Preprocessing

    O(n)

Each query

    O(1)

Overall

    O(n + q)

------------------------------------------------------------

Space Complexity
----------------

O(n)

for the four prefix arrays.

*/