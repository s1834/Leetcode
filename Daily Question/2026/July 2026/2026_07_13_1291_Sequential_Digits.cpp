class Solution {
    public:
        vector<int> sequentialDigits(int low, int high) {
            vector<int> ans;
            for(int i = 1; i <= 9; i++) {
                int num = i;
                for(int j = i + 1; j <= 9; j++) {
                    num = num * 10 + j;
                    if(num >= low && num <= high) ans.push_back(num);
                }
            }
            
            sort(ans.begin(), ans.end());
            return ans;
        }
    };

/*

Idea:
------
Generate every possible sequential digit number.

Start with every digit from 1 to 9 and continuously
append the next consecutive digit to build larger
sequential numbers.

If the generated number lies within the given range,
store it in the answer.

------------------------------------------------------------

Algorithm:
----------

1.

Choose every starting digit from

1 to 9.

------------------------------------------------------------

2.

Initialize

num = starting digit.

------------------------------------------------------------

3.

Append the next consecutive digit one by one.

Example:

Start = 2

2

↓

23

↓

234

↓

2345

↓

23456

...

This is done using

num = num * 10 + next_digit

------------------------------------------------------------

4.

After generating each new number,

check whether

low <= num <= high.

If yes,

store it in the answer.

------------------------------------------------------------

5.

Since numbers are generated from different starting
digits, they are not guaranteed to be in sorted order.

Sort the final answer before returning it.

------------------------------------------------------------

Example:
--------

low = 100

high = 300

Start = 1

12

123   ✓

1234  > high

------------------------------------------------------------

Start = 2

23

234   ✓

2345  > high

------------------------------------------------------------

Start = 3

34

345  > high

------------------------------------------------------------

Answer after sorting:

123

234

------------------------------------------------------------

Time Complexity:
----------------

There are at most

9 + 8 + 7 + ... + 1 = 45

possible sequential numbers.

Generating each number takes constant time.

Overall:

O(1)

Sorting at most 45 numbers is also O(1).

------------------------------------------------------------

Space Complexity:
-----------------

O(1)

At most 45 sequential numbers are generated.

*/