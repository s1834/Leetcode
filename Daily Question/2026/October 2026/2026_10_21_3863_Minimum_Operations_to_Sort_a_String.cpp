class Solution {
    public:
        int minOperations(string s) {
            int n = s.size();
    
            if(is_sorted(s.begin(), s.end())) return 0;
    
            if(n == 2) return -1;
    
            char min_char = *min_element(s.begin(), s.end());
            char max_char = *max_element(s.begin(), s.end());
    
            if(s[0] == min_char || s[n - 1] == max_char) return 1;
    
            char min_mid = *min_element(s.begin() + 1, s.end() - 1);
            char max_mid = *max_element(s.begin() + 1, s.end() - 1);
    
            if(s[0] > max_mid && s[n - 1] < min_mid) return 3;
    
            return 2;
        }
    };

/*
Approach: Greedy + Character Extremes

Intuition:
----------
We need to find the minimum number of operations required to make
the string sorted in non-decreasing order.

The code determines the answer by checking a sequence of conditions
based on the positions of the minimum and maximum characters.

The possible answers are:
- 0: The string is already sorted.
- -1: The string has length 2 and is not sorted.
- 1: The first character is the global minimum or the last character
     is the global maximum.
- 3: Neither of the above conditions holds, and the first character
     is greater than every middle character while the last character
     is smaller than every middle character.
- 2: All remaining cases.

--------------------------------------------------
1. Check Whether the String Is Already Sorted
--------------------------------------------------

int n = s.size();

if(is_sorted(s.begin(), s.end())) return 0;

is_sorted() checks whether the characters are arranged in
non-decreasing order.

For example:
s = "abcc"

Since every character is greater than or equal to the previous one,
the string is already sorted, so the answer is 0.

If this condition fails, at least one operation is required.

--------------------------------------------------
2. Handle Strings of Length 2
--------------------------------------------------

if(n == 2) return -1;

If the string contains exactly two characters and is not sorted,
the code returns -1, indicating that the required transformation
is impossible under the allowed operations.

This check comes after is_sorted(), so an already sorted string
of length 2 correctly returns 0.

--------------------------------------------------
3. Find the Global Minimum and Maximum Characters
--------------------------------------------------

char min_char = *min_element(s.begin(), s.end());
char max_char = *max_element(s.begin(), s.end());

min_element() returns an iterator to the smallest character.
max_element() returns an iterator to the largest character.

Dereferencing these iterators with * gives the actual characters.

For example:
s = "dcab"

min_char = 'a'
max_char = 'd'

These values help determine whether the string can be sorted
with one operation.

--------------------------------------------------
4. Check Whether One Operation Is Enough
--------------------------------------------------

if(s[0] == min_char || s[n - 1] == max_char) return 1;

There are two possibilities:

Case 1: The first character is the global minimum.
--------------------------------------------------
s[0] == min_char

The smallest character is already at the beginning of the string.
According to the operation-based conditions used by this solution,
this allows the string to be sorted in one operation.

Case 2: The last character is the global maximum.
------------------------------------------------
s[n - 1] == max_char

The largest character is already at the end of the string.
This also allows the answer to be 1.

If either condition is true, the function immediately returns 1.

--------------------------------------------------
5. Find the Minimum and Maximum Among Middle Characters
--------------------------------------------------

char min_mid = *min_element(s.begin() + 1, s.end() - 1);
char max_mid = *max_element(s.begin() + 1, s.end() - 1);

The middle substring excludes the first and last characters.

For a string of length n, the middle characters occupy indices
1 through n - 2.

min_mid stores the smallest middle character.
max_mid stores the largest middle character.

For example:
s = "dbca"

First character: 'd'
Middle characters: "bc"
Last character: 'a'

min_mid = 'b'
max_mid = 'c'

These values help identify the special case in which three
operations are required.

--------------------------------------------------
6. Check Whether Three Operations Are Required
--------------------------------------------------

if(s[0] > max_mid && s[n - 1] < min_mid) return 3;

This condition checks both ends of the string:

s[0] > max_mid
    The first character is greater than every middle character.

s[n - 1] < min_mid
    The last character is smaller than every middle character.

When both conditions hold, the code returns 3.

For example:
s = "dbca"

First character = 'd'
Largest middle character = 'c'
'd' > 'c' is true.

Last character = 'a'
Smallest middle character = 'b'
'a' < 'b' is true.

Therefore, this special case returns 3.

--------------------------------------------------
7. All Remaining Cases
--------------------------------------------------

return 2;

If none of the previous conditions applies, the code returns 2.

At this point:
- The string is not already sorted.
- The string does not have length 2.
- The first character is not the global minimum.
- The last character is not the global maximum.
- The special condition requiring 3 operations is false.

According to the decision logic implemented here, the answer is 2.

--------------------------------------------------
8. Example Walkthrough
--------------------------------------------------

Example 1:
s = "abc"

is_sorted() returns true.

Output: 0

Example 2:
s = "ba"

The string is not sorted, and n == 2.

Output: -1

Example 3:
s = "bac"

The string is not sorted.

min_char = 'a'
max_char = 'c'

The last character is 'c', which equals max_char.

Output: 1

Example 4:
s = "dbca"

The string is not sorted, and its length is greater than 2.

min_char = 'a'
max_char = 'd'

The first character 'd' is not the global minimum.
The last character 'a' is not the global maximum.

Middle substring = "bc"
min_mid = 'b'
max_mid = 'c'

Check:
'd' > 'c' is true.
'a' < 'b' is true.

Output: 3

--------------------------------------------------
9. Complexity Analysis
--------------------------------------------------

Time Complexity: O(n)

- is_sorted() takes O(n) time in the worst case.
- min_element() and max_element() each take O(n).
- The middle-substring minimum and maximum each take O(n).
- All remaining comparisons take O(1).

These operations execute sequentially, so the total time complexity
is O(n).

Space Complexity: O(1)

The algorithm uses only a constant number of variables and does not
create any additional string or array proportional to n.

Core Idea:
----------
Check the string in increasing order of operation count:
first test whether it is already sorted, then handle length 2,
then check the global minimum and maximum at the boundaries,
and finally use the middle characters to distinguish between
the 3-operation case and the remaining 2-operation cases.
*/