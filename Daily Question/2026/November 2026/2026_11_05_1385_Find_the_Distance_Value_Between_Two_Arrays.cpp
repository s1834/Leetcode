class Solution {
    public:
        int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
            int n = arr1.size();
            int m = arr2.size();
    
            int count = 0;
            for(int i = 0; i < n; i++) {
                bool flag = true;
                for(int j = 0; j < m; j++) {
                    if(abs(arr1[i] - arr2[j]) <= d) {
                        flag = false;
                        break;
                    }
                }
                if(flag) count++;
            }
    
            return count;
        }
    };

/*
Problem: LeetCode 1385 - Find the Distance Value Between Two Arrays

Approach: Brute Force + Nested Loops

Intuition:
----------
We need to count the number of elements in arr1 that satisfy
the following condition:

For an element arr1[i], its absolute difference with every
element in arr2 must be strictly greater than d.

In other words, arr1[i] is valid if:

    abs(arr1[i] - arr2[j]) > d

for every j in arr2.

The solution checks every element of arr1 against all elements
of arr2 and counts only those that satisfy this condition.

--------------------------------------------------
1. Get the Array Sizes
--------------------------------------------------

int n = arr1.size();
int m = arr2.size();

- n stores the number of elements in arr1.
- m stores the number of elements in arr2.

--------------------------------------------------
2. Initialize the Counter
--------------------------------------------------

int count = 0;

Stores the number of valid elements from arr1.

--------------------------------------------------
3. Traverse the First Array
--------------------------------------------------

for(int i = 0; i < n; i++) {

    bool flag = true;

    For every element in arr1, initially assume that it
    satisfies the required condition.

    flag = true means no element in arr2 has violated
    the condition so far.

}

--------------------------------------------------
4. Check Against Every Element of the Second Array
--------------------------------------------------

for(int j = 0; j < m; j++) {

    if(abs(arr1[i] - arr2[j]) <= d) {
        flag = false;
        break;
    }

}

For the current arr1[i], calculate its absolute difference
with every element of arr2.

If:

    abs(arr1[i] - arr2[j]) <= d

then the current element is NOT valid.

Why?

Because the problem requires the absolute difference to
be strictly greater than d for every element in arr2.

Once we find even one element that violates this condition:
- Set flag to false.
- Break out of the inner loop because no further checks
  are needed for this arr1[i].

--------------------------------------------------
5. Count Valid Elements
--------------------------------------------------

if(flag) count++;

If flag is still true after checking the entire second
array, it means arr1[i] has an absolute difference greater
than d from every element in arr2.

Therefore, increment count.

--------------------------------------------------
6. Return the Answer
--------------------------------------------------

return count;

After processing all elements of arr1, count contains
the total number of elements satisfying the distance
condition.

--------------------------------------------------
7. Example Walkthrough
--------------------------------------------------

Input:

    arr1 = [4, 5, 8]
    arr2 = [10, 9, 1, 8]
    d = 2

Initially:

    count = 0

Check arr1[0] = 4:

    |4 - 10| = 6
    |4 - 9|  = 5
    |4 - 1|  = 3
    |4 - 8|  = 4

All differences are greater than 2.

    flag = true
    count = 1

Check arr1[1] = 5:

    |5 - 10| = 5
    |5 - 9|  = 4
    |5 - 1|  = 4
    |5 - 8|  = 3

All differences are greater than 2.

    flag = true
    count = 2

Check arr1[2] = 8:

    |8 - 10| = 2

Since 2 <= d, the condition is violated.

    flag = false

Break immediately.

Final count:

    2

Output:
2

--------------------------------------------------
8. Complexity Analysis
--------------------------------------------------

Time Complexity: O(n * m)

- The outer loop traverses all n elements of arr1.
- For each element, the inner loop may traverse all m
  elements of arr2.
- In the worst case, every pair is checked.

Space Complexity: O(1)

Only a counter, two loop variables, and a boolean flag
are used.

Core Idea:
----------
For every element in arr1, check whether its absolute
difference from every element in arr2 is strictly greater
than d.

If even one difference is <= d, reject that element.

Otherwise, count it as valid.

The final count is the required distance value.
*/