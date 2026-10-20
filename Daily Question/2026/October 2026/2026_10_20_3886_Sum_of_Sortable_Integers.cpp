class Solution {
    private:
        //KMP Start
        void computeLPS(vector<int>& pattern, vector<int>& lps) {
            int M = pattern.size();
            int len = 0;
            lps[0] = 0;
    
            int i = 1;
            while (i < M) {
                if (pattern[i] == pattern[len]) {
                    len++;
                    lps[i] = len;
                    i++;
                } else {
                    if (len != 0) len = lps[len - 1];
                    else {
                        lps[i] = 0;
                        i++;
                    }
                }
            }
        }
    
        bool KMPSearch(vector<int>& pat, vector<int>& txt) {
            int N = txt.size();
            int M = pat.size();
    
            vector<int> lps(M, 0);
            computeLPS(pat, lps);
    
            int i = 0; // index for text
            int j = 0; // index for pattern
    
            while (i < N) {
                if (pat[j] == txt[i]) {
                    i++;
                    j++;
                }
    
                if (j == M) {
                    return true; // pattern found , return true
                } else if (i < N && pat[j] != txt[i]) {
                    if (j != 0) j = lps[j - 1];
                    else i++;
                }
            }
    
            return false;
        }
        //KMP End
    
        // Is vec1 a cyclic rotation of vec2 ,  then, vec1 occurs in vec2+vec2
        bool isRotationPossible(vector<int>& v1, vector<int>& v2) {
            vector<int> text = v2;
            text.insert(text.end(), v2.begin(), v2.end());
            return KMPSearch(v1, text);
        }
    
    public:
        int sortableIntegers(vector<int>& nums) {
            int n = nums.size();
    
            vector<int> sorted = nums;
            sort(nums.begin(), nums.end());
    
            int result = 0;
            for(int k = 1; k <= n; k++) {
                if(n % k != 0) continue;
    
                bool valid = true;
                for(int start = 0; start < n; start += k) { // check k block sizes
                    vector<int> v1(nums.begin() + start, nums.begin() + start + k);
                    vector<int> v2(sorted.begin() + start, sorted.begin() + start + k);
    
                    if(!isRotationPossible(v1, v2)) {
                        valid = false;
                        break;
                    }
                }
    
                if(valid) result += k;
            }
    
            return result;
        }
    };

/*
Approach: KMP String-Matching Algorithm + Cyclic Rotation + Divisor Enumeration

Intuition:
----------
The goal is to find all values k such that:
1. k divides the array length n.
2. Every consecutive block of size k in nums is a cyclic rotation
   of the corresponding block in the sorted array.

For each valid block size k, we divide both arrays into blocks of length k
and check whether every corresponding pair of blocks satisfies the
cyclic-rotation condition.

If all blocks are valid, we add k to the answer.

The key challenge is checking whether one integer vector is a cyclic
rotation of another efficiently. This is handled using the KMP pattern-
matching algorithm.

--------------------------------------------------
1. KMP: computeLPS()
--------------------------------------------------

void computeLPS(vector<int>& pattern, vector<int>& lps)

LPS stands for Longest Proper Prefix which is also a Suffix.

For every index i, lps[i] stores the length of the longest proper prefix
of pattern[0...i] that is also a suffix of pattern[0...i].

A proper prefix cannot be equal to the entire string.

Variables:
- M: length of the pattern.
- len: length of the current matching prefix.
- i: index currently being processed.

Initialization:
int len = 0;
lps[0] = 0;
int i = 1;

A single-element prefix has no proper prefix that is also a suffix,
so lps[0] is initialized to zero.

Case 1: Characters Match
------------------------
if(pattern[i] == pattern[len])

Extend the current matching prefix:

len++;
lps[i] = len;
i++;

The LPS value at index i is the length of the extended match.

Case 2: Characters Do Not Match, but len != 0
---------------------------------------------
if(len != 0)
    len = lps[len - 1];

Instead of resetting len to zero, use the previous LPS value to find
a shorter prefix that might still match.

The current index i does not advance because the same pattern element
must be checked against this shorter prefix.

This is the main optimization that prevents repeatedly comparing
characters from the beginning.

Case 3: Characters Do Not Match and len == 0
--------------------------------------------
lps[i] = 0;
i++;

No nonempty prefix can match, so the LPS value is zero and we move on.

The completed LPS array allows KMP to skip unnecessary comparisons.

--------------------------------------------------
2. KMP: KMPSearch()
--------------------------------------------------

bool KMPSearch(vector<int>& pat, vector<int>& txt)

This function checks whether the entire pattern pat occurs as a
contiguous subarray of txt.

Variables:
- N: length of txt.
- M: length of pat.
- i: current index in the text.
- j: current index in the pattern.

First, calculate the LPS array:

vector<int> lps(M, 0);
computeLPS(pat, lps);

Then scan the text and pattern together.

Case 1: Elements Match
----------------------
if(pat[j] == txt[i])

Advance both indices:
i++;
j++;

This extends the current matching segment.

Case 2: Entire Pattern Is Matched
---------------------------------
if(j == M)
    return true;

When j reaches M, every element of pat has matched consecutive
elements in txt, so the pattern has been found.

Case 3: Mismatch with j != 0
----------------------------
if(j != 0)
    j = lps[j - 1];

Use the LPS array to retain the longest prefix that could still match.
The text index i does not move backward.

Case 4: Mismatch with j == 0
----------------------------
else
    i++;

No prefix matches the current text element, so advance to the next
text element.

If the text is exhausted without finding the entire pattern, return
false.

KMP takes O(N + M) time because neither index repeatedly moves
backward through the input.

--------------------------------------------------
3. Check Cyclic Rotation: isRotationPossible()
--------------------------------------------------

bool isRotationPossible(vector<int>& v1, vector<int>& v2)

Two equal-length sequences are cyclic rotations if one can be obtained
by moving some prefix of the other sequence to its end.

For example:

v2 = [1, 2, 3, 4]

Its doubled sequence is:

text = [1, 2, 3, 4, 1, 2, 3, 4]

Every cyclic rotation of v2 appears as a contiguous sequence of length
4 in v2 + v2.

Examples:
[1, 2, 3, 4]  -> original sequence
[2, 3, 4, 1]  -> rotate left by 1
[3, 4, 1, 2]  -> rotate left by 2
[4, 1, 2, 3]  -> rotate left by 3

The function constructs the doubled vector:

vector<int> text = v2;
text.insert(text.end(), v2.begin(), v2.end());

Then it searches for v1 in this doubled sequence:

return KMPSearch(v1, text);

If v1 occurs in v2 + v2, it is a cyclic rotation of v2.

Because KMP is used, the rotation check is efficient and does not
require explicitly generating every possible rotation.

For two blocks of length k:
- Doubled text length = 2k.
- Pattern length = k.
- Time complexity = O(k).

--------------------------------------------------
4. Main Function: sortableIntegers()
--------------------------------------------------

int sortableIntegers(vector<int>& nums)

This function checks every possible block size and sums the sizes
that satisfy the required condition.

Step 1: Prepare the arrays
--------------------------
int n = nums.size();

vector<int> sorted = nums;
sort(nums.begin(), nums.end());

The code saves a copy of the original array in sorted and then sorts
nums in ascending order.

Therefore:
- nums now contains the sorted array.
- sorted contains the original array.

The algorithm compares corresponding blocks of these two arrays.

Note that the variable names are reversed from what might initially
be expected: sorted is the original copy, while nums is sorted.

Step 2: Enumerate possible block sizes
--------------------------------------
for(int k = 1; k <= n; k++)

Every valid block size must divide n evenly. Otherwise, the array
cannot be divided into blocks of exactly k elements.

if(n % k != 0) continue;

This skips all sizes that do not divide n.

For example, if n = 6, the possible block sizes are:

k = 1, 2, 3, 6

Values such as 4 and 5 are skipped because they do not divide 6.

Step 3: Check every corresponding block
---------------------------------------
bool valid = true;

Initially, assume that k is a valid block size.

The loop:

for(int start = 0; start < n; start += k)

visits the starting index of every block of size k.

At each iteration, construct the two corresponding blocks:

vector<int> v1(nums.begin() + start,
               nums.begin() + start + k);

vector<int> v2(sorted.begin() + start,
               sorted.begin() + start + k);

Here:
- v1 is the block from the sorted array.
- v2 is the block from the original array.

The vectors are then checked for cyclic rotation:

if(!isRotationPossible(v1, v2)) {
    valid = false;
    break;
}

If even one pair of corresponding blocks is not a cyclic rotation,
the current block size k is invalid.

We immediately break because checking the remaining blocks cannot
change that result.

If every pair of blocks passes, valid remains true.

Step 4: Add valid block sizes
-----------------------------
if(valid) result += k;

If all blocks satisfy the cyclic-rotation condition, add k to result.

After checking every divisor of n, return result.

--------------------------------------------------
5. Example Walkthrough
--------------------------------------------------

Consider:

nums = [2, 1, 4, 3]

After copying and sorting:

Original copy, sorted:
[2, 1, 4, 3]

Sorted nums:
[1, 2, 3, 4]

Initially:
result = 0

Check k = 1:
----------------
Since 1 divides n = 4, process each block.

Original blocks:
[2], [1], [4], [3]

Sorted blocks:
[1], [2], [3], [4]

Every block contains one element. Two single-element vectors are
cyclic rotations only if their values are equal.

The corresponding blocks do not all match, so k = 1 is invalid.

result = 0

Check k = 2:
----------------
The blocks are:

Original:
[2, 1], [4, 3]

Sorted:
[1, 2], [3, 4]

Check the first pair:
[1, 2] and [2, 1]

These are cyclic rotations of each other.

Check the second pair:
[3, 4] and [4, 3]

These are also cyclic rotations.

Both blocks are valid, so add k = 2.

result = 2

Check k = 4:
----------------
Compare the entire arrays:

Sorted:
[1, 2, 3, 4]

Original:
[2, 1, 4, 3]

The original array is not a cyclic rotation of the sorted array,
so k = 4 is invalid.

Final result:
2

--------------------------------------------------
6. Why KMP Is Useful Here
--------------------------------------------------

A straightforward approach could generate all rotations of each block
and compare them one by one.

For a block of length k, this could require O(k^2) time.

Instead, the algorithm searches for v1 in v2 + v2 using KMP.

KMP preprocesses the pattern with the LPS array and uses that
information to avoid repeating comparisons after mismatches.

Consequently, each rotation check takes O(k) time.

This makes it practical to check all corresponding blocks for
every divisor of n.

--------------------------------------------------
7. Correctness Intuition
--------------------------------------------------

For each candidate block size k, the algorithm first ensures that
k divides n, so every block can be formed with exactly k elements.

It then partitions both arrays into corresponding blocks.

The doubled-vector property guarantees that a block v1 is a cyclic
rotation of v2 exactly when v1 occurs in v2 + v2 as a contiguous
subarray of length k. KMP correctly determines whether this occurrence
exists.

Therefore, valid remains true exactly when every corresponding block
pair satisfies the cyclic-rotation condition.

The algorithm adds k if and only if that condition holds for all
blocks. Since every divisor of n is checked, the result is the sum
of all valid block sizes.

--------------------------------------------------
8. Complexity Analysis
--------------------------------------------------

Let n be the array length.

Sorting:
O(n log n)

For a fixed block size k:
- There are n / k block pairs.
- Each rotation check takes O(k) time.

Therefore, checking one block size takes:

(n / k) * O(k) = O(n)

There are at most n candidate values of k, so the total time spent
checking block sizes is O(n^2) in the worst case.

Overall Time Complexity:
O(n^2)

Auxiliary Space Complexity:
O(n)

The original array copy requires O(n) space. The temporary blocks,
doubled vector, and LPS array use O(k) space at a time, with k <= n.

Core Idea:
----------
For every divisor k of n, divide the original and sorted arrays into
blocks of size k. Use KMP to check whether every original block is a
cyclic rotation of its corresponding sorted block. Add k to the answer
whenever all block pairs pass.
*/