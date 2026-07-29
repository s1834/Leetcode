class Solution {
    public:
        string convertToTitle(int columnNumber) {
            string ans = "";
            while(columnNumber > 0) {
                int remainder = (columnNumber - 1) % 26;
                ans += char('A' + remainder);
                columnNumber = (columnNumber - 1) / 26;
            }
    
            reverse(ans.begin(), ans.end());
            return ans;
        }
    };

/*

Idea:
------
The problem is similar to converting a decimal number into
base

26,

but there is one important difference.

Unlike the normal base-26 system,

Excel column titles do

NOT

contain the digit

0.

Instead,

the mapping is

1 → A

2 → B

...

26 → Z

27 → AA

...

Because of this,

before taking the remainder,

we subtract

1

from the current number.

This converts the numbering from

1-based

to

0-based,

making the conversion identical to a normal base-26
conversion.

------------------------------------------------------------

Key Observation:
----------------

Normal Base-26

Digits

0

to

25

Example

0 → A

25 → Z

--------------------------------

Excel Column Numbering

Digits

1

to

26

Example

1 → A

26 → Z

There is no digit representing

0.

Therefore,

we subtract

1

before computing the remainder.

------------------------------------------------------------

Why Subtract 1?
---------------

Consider

columnNumber = 26.

Without subtracting

1

26 % 26 = 0

This would incorrectly map to

'A'.

However,

26

should correspond to

'Z'.

Instead,

compute

(26 - 1) % 26

=

25

↓

'A' + 25

↓

'Z'

Similarly,

the next number

27

becomes

(27 - 1) % 26

=

0

↓

'A'

which is correct because

27 = AA.

Thus,

subtracting

1

correctly converts the numbering system.

------------------------------------------------------------

Character Mapping:
------------------

remainder = (columnNumber - 1) % 26

Character

'A' + remainder

Examples

remainder = 0

↓

A

--------------------------------

remainder = 1

↓

B

--------------------------------

remainder = 25

↓

Z

------------------------------------------------------------

Updating the Number:
--------------------

After extracting the last character,

remove it from the number.

Since we already subtracted

1,

the next value becomes

(columnNumber - 1) / 26

This moves to the next higher "digit"

exactly like normal base conversion.

------------------------------------------------------------

Why Reverse the String?
-----------------------

Characters are obtained from

right to left.

That means,

the least significant character is generated first.

Example

columnNumber = 28

Step 1

(28 - 1) % 26

=

1

↓

B

--------------------------------

Remaining Number

(28 - 1) / 26

=

1

--------------------------------

Step 2

(1 - 1) % 26

=

0

↓

A

Generated String

"BA"

Actual Answer

"AB"

Therefore,

reverse the string before returning.

------------------------------------------------------------

Algorithm:
----------

Step 1

Initialize an empty string

ans.

------------------------------------------------------------

Step 2

While

columnNumber > 0

Repeat.

------------------------------------------------------------

Step 3

Convert the current least significant Excel digit into a
character.

remainder =

(columnNumber - 1) % 26

Append

'A' + remainder

to the answer.

------------------------------------------------------------

Step 4

Remove the processed digit.

columnNumber =

(columnNumber - 1) / 26

------------------------------------------------------------

Step 5

Reverse the generated string.

------------------------------------------------------------

Step 6

Return the answer.

------------------------------------------------------------

Example 1:
----------

columnNumber = 1

Iteration

remainder

=

(1 - 1) % 26

=

0

↓

A

Remaining Number

0

Generated String

"A"

Reverse

"A"

Answer

A

------------------------------------------------------------

Example 2:
----------

columnNumber = 28

Iteration 1

(28 - 1) % 26

=

1

↓

B

Remaining

1

Generated

"B"

--------------------------------

Iteration 2

(1 - 1) % 26

=

0

↓

A

Generated

"BA"

Reverse

"AB"

Answer

AB

------------------------------------------------------------

Example 3:
----------

columnNumber = 701

Iteration 1

(701 - 1) % 26

=

24

↓

Y

Remaining

26

Generated

"Y"

--------------------------------

Iteration 2

(26 - 1) % 26

=

25

↓

Z

Remaining

0

Generated

"YZ"

Reverse

"ZY"

Answer

ZY

------------------------------------------------------------

Visualization:
--------------

Excel Columns

1  → A

2  → B

...

26 → Z

27 → AA

28 → AB

29 → AC

...

52 → AZ

53 → BA

...

701 → ZY

702 → ZZ

703 → AAA

------------------------------------------------------------

Why Does This Work?
-------------------

Subtracting

1

converts Excel's

1-based

alphabet numbering into a standard

0-based

base-26 representation.

Each iteration extracts one character from the least
significant position,

exactly like repeatedly extracting digits during base
conversion.

The extracted characters are generated from right to left,

so reversing the string restores the correct order.

Thus,

every column number is converted into its corresponding
Excel column title.

------------------------------------------------------------

Correctness Proof:
------------------

We prove that the algorithm returns the correct Excel
column title.

At every iteration,

subtracting

1

converts the current number into an equivalent
zero-indexed representation.

Taking

(columnNumber - 1) % 26

correctly determines the current least significant Excel
character,

which is mapped to

'A'

through

'Z'.

Updating

columnNumber

to

(columnNumber - 1) / 26

removes the processed character while preserving the
remaining higher-order characters.

The process continues until all characters have been
generated.

Since characters are extracted from least significant to
most significant,

reversing the string restores their proper order.

Therefore,

the returned string is exactly the Excel column title
corresponding to the given column number.

------------------------------------------------------------

Time Complexity:
----------------

Let

k

be the number of characters in the answer.

Each iteration processes one character.

Overall Time Complexity

O(k)

------------------------------------------------------------

Space Complexity:
-----------------

The output string stores

k

characters.

Ignoring the output,

the auxiliary space is

O(1).

Including the output string,

the total space is

O(k).

------------------------------------------------------------

Note:
-----

This problem is a modified

Base-26 Conversion

where the digits range from

1

to

26

instead of

0

to

25.

The subtraction of

1

before every modulo and division operation is the key idea
that correctly handles Excel's numbering system.

*/