class Solution {
public:
    char kthCharacter(long long k, vector<int>& operations) {
        int ops = 0;
        long long int val = k;
        while(val > 1) {
            int jumps = ceil(log2(val));
            val -= pow(2, jumps - 1);
            ops += operations[jumps - 1];
        }
        return char('a' + (ops % 26));
    }
};

/*

------------------------------------------------------------------------------------------------------------------------

word = "a"
k = 15
operations = [1, 1, 0, 1]

------------------------------------------------------------------------------------------------------------------------

1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16
a  b  b  c  a  b  b  c  b  c  c  d  b  c  c  d

------------------------------------------------------------------------------------------------------------------------
NOTE: we are calculating it in thepower of 2 as at each operation we are doubling the string length
------------------------------------------------------------------------------------------------------------------------

val = 15 {value of k}

jump = (log2 val) = 4 {this means the length og the string is going to be 2^4 = 16} {also 4 is the value that we are going to choose which operation we will perform }

2^(jump - 1) = 8 {the jump - 1 is used to get the previous power of 2 where the string should be devided into two halves recursively to get all the operations that we need to perform}

val - 2^(jump - 1) = 15 - 8 = 7 {this we to find how far 15/val is from the middle so we can figure out which character from beginning will affetct val/15 character}

ops= = 0 + 1 = 1 {this we selected frrom [1, 1, 0, 1] as 1 is on 4th position or index 3}

------------------------------------------------------------------------------------------------------------------------

val = 7
jump = (log2 val) = 3 
2^(jump - 1) = 4
val - 2^(jump - 1) = 7 - 4 = 3
ops = 0 + 1 + 0 = 1 {this we selected frrom [1, 1, 0, 1] as 0 is on 3rd position or index 2 as what character is at 3rd position will be at 7th poition too}

------------------------------------------------------------------------------------------------------------------------

val = 3
jump = (log2 val) = 2
2^(jump - 1) = 2
val - 2^(jump - 1) = 3 - 2 = 1
ops = 0 + 1 + 0 + 1 = 2 {this we selected frrom [1, 1, 0, 1] as 1 is on 2nd position or index 1}

------------------------------------------------------------------------------------------------------------------------

val = 1
as we reached to the base case we will stop now and return the 
'a' + (ops % 26)
as this will give us the final character after all the operations

------------------------------------------------------------------------------------------------------------------------

*/