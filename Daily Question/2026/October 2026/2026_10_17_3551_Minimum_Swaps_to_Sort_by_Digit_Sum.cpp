class Solution {
    private:
        int digitSum(int x) {
            int sum = 0;
            while(x) {
                sum += x % 10;
                x /= 10;
            }
            return sum;
        }
    
    public:
        int minSwaps(vector<int>& nums) {
             int n = nums.size();
            vector<int> afterSort(nums);
    
            auto lambda = [&](int num1, int num2) {
                int digitSum1 = digitSum(num1);
                int digitSum2 = digitSum(num2);
    
                if(digitSum1 != digitSum2) return digitSum1 < digitSum2;
                return num1 < num2;
            };
    
            sort(afterSort.begin(), afterSort.end(), lambda);
    
            unordered_map<int, int> originalIdx;
            for(int i = 0; i < n; i++) originalIdx[nums[i]] = i;
            
            int swaps = 0;
            for(int i = 0; i < n; i++) {
                int expectedVal = afterSort[i];
                int currVal = nums[i];
    
                if(expectedVal == currVal) continue;
    
                int idx = originalIdx[expectedVal];
                nums[i] = expectedVal;
                nums[idx] = currVal;
    
                originalIdx[expectedVal] = i;
                originalIdx[currVal] = idx; 
    
                swaps++;
            }
    
            return swaps;
        }
    };

/*
Approach: Greedy Sorting + Index Mapping

Intuition:
----------
We need to transform nums into the order obtained by sorting its elements
according to the following rules:

1. Elements with a smaller digit sum come first.
2. If two elements have the same digit sum, the smaller element comes first.

After constructing this target order, we find the minimum number of swaps
needed to transform the original array into that order.

The key idea is to place the correct element at each index using swaps.
An unordered_map stores the current index of each element, allowing us to
locate the element that belongs at the current position in O(1) expected
time.

1. Helper Function: digitSum()
------------------------------
int digitSum(int x)

This function calculates the sum of the digits of a number.

For each iteration:
- x % 10 extracts the last digit.
- Add that digit to sum.
- x /= 10 removes the last digit.

Example:
x = 432

Iteration 1: sum = 2, x = 43
Iteration 2: sum = 5, x = 4
Iteration 3: sum = 9, x = 0

Therefore, digitSum(432) = 9.

Time Complexity: O(log x)
Space Complexity: O(1)

2. Create the Target Sorted Array
---------------------------------
vector<int> afterSort(nums);

Create a copy of nums so that the original array remains available for
comparison while afterSort stores the desired sorted order.

The custom comparator lambda defines the sorting rules:

auto lambda = [&](int num1, int num2)

First, calculate the digit sums of both numbers.

if(digitSum1 != digitSum2)
    return digitSum1 < digitSum2;

If their digit sums differ, the number with the smaller digit sum comes
first.

Otherwise:
return num1 < num2;

If the digit sums are equal, the smaller numerical value comes first.

Example:
nums = [21, 12, 3, 11]

Digit sums:
21 -> 3
12 -> 3
3  -> 3
11 -> 2

The sorted order is:
afterSort = [11, 3, 12, 21]

The element 11 comes first because its digit sum is 2. The remaining
elements all have digit sum 3, so they are ordered numerically.

3. Build the Original Index Map
-------------------------------
unordered_map<int, int> originalIdx;

for(int i = 0; i < n; i++)
    originalIdx[nums[i]] = i;

This map stores the current index of each element.

For example:
nums = [21, 12, 3, 11]

originalIdx:
21 -> 0
12 -> 1
3  -> 2
11 -> 3

Whenever two elements are swapped, their entries in the map are updated
so that originalIdx always reflects their current positions.

This is essential because the next element we need to place may have
moved during a previous swap.

4. Greedily Place the Correct Element
-------------------------------------
Initialize:
int swaps = 0;

Traverse the array from left to right.

At every index i:

int expectedVal = afterSort[i];
int currVal = nums[i];

- expectedVal is the element that should occupy index i.
- currVal is the element currently occupying index i.

Case 1: The element is already correct
--------------------------------------
if(expectedVal == currVal) continue;

If the current element already matches the target element, no swap is
required. Move to the next index.

Case 2: The element is incorrect
--------------------------------
int idx = originalIdx[expectedVal];

Find the current position of expectedVal using the index map.

Because expectedVal belongs at index i, swap it with the element
currently at index i.

The code performs this swap manually:

nums[i] = expectedVal;
nums[idx] = currVal;

After these assignments:
- The correct element occupies index i.
- The element previously at index i moves to index idx.

Now update the index map:

originalIdx[expectedVal] = i;
originalIdx[currVal] = idx;

These updates ensure that both elements' recorded positions match
their new positions in nums.

Finally:
swaps++;

One swap has placed the correct element at the current index.

5. Why the Greedy Strategy Works
--------------------------------
We process the array from left to right and never disturb an index that
already contains its correct element.

Whenever nums[i] differs from afterSort[i], we bring the required
element directly to index i using one swap.

This fixes the current position while leaving all previously fixed
positions unchanged.

For distinct elements, this direct-placement strategy minimizes the
number of swaps needed to obtain the target permutation.

Important assumption:
The map originalIdx stores only one index per value. Therefore, this
implementation relies on nums having distinct values. If duplicates are
allowed, the map may not correctly track every occurrence.

6. Complete Walkthrough
-----------------------
Consider:
nums = [21, 12, 3, 11]

Target sorted array:
afterSort = [11, 3, 12, 21]

Initial index map:
21 -> 0
12 -> 1
3  -> 2
11 -> 3

Initially:
swaps = 0

Index i = 0:
expectedVal = 11
currVal = 21

They differ, so find:
idx = originalIdx[11] = 3

Swap 21 and 11:
nums = [11, 12, 3, 21]

Update the map:
11 -> 0
21 -> 3

swaps = 1

Index i = 1:
expectedVal = 3
currVal = 12

They differ, so find:
idx = originalIdx[3] = 2

Swap 12 and 3:
nums = [11, 3, 12, 21]

Update the map:
3  -> 1
12 -> 2

swaps = 2

Index i = 2:
expectedVal = 12
currVal = 12

Already correct, so continue.

Index i = 3:
expectedVal = 21
currVal = 21

Already correct, so continue.

Final array:
[11, 3, 12, 21]

Minimum swaps counted by the algorithm:
2

7. Complexity Analysis
----------------------
Let n be the number of elements and D be the maximum number of digits
in an element.

Time Complexity:
- Copying nums: O(n)
- Sorting afterSort: O(n log n * D), because the comparator calculates
  digit sums while comparing elements.
- Building originalIdx: O(n) expected.
- Greedy placement: O(n) expected, since each map lookup and update
  takes O(1) expected time.

Overall: O(n log n * D) expected.

Space Complexity:
- afterSort stores n elements: O(n).
- originalIdx stores up to n elements: O(n).

Overall: O(n) auxiliary space.

Core Idea:
----------
Sort a copy using digit sum and numerical value, then scan the original
array from left to right. Whenever an element is misplaced, swap in the
required element using an index map, update both affected indices, and
increment the swap count.
*/