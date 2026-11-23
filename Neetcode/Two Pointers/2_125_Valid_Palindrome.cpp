class Solution {
    public:
        bool isPalindrome(string s) {
            string converted = "";
            for(auto &ch : s) {
                if(isalnum(ch)) converted += tolower(ch);
            }
    
            string reversed = converted;
            reverse(reversed.begin(), reversed.end());
    
            return converted == reversed;
        }
    };

/*
    LeetCode 125: Valid Palindrome

    Approach: String Filtering + Reversal

    Intuition:
    We need to check whether a string is a palindrome after:
    1. Removing all non-alphanumeric characters.
    2. Converting all remaining uppercase letters to lowercase.

    A palindrome reads the same forward and backward.

    Instead of comparing characters directly in the original string,
    we first create a cleaned version containing only lowercase
    alphanumeric characters.

    Then we reverse the cleaned string and compare both strings.

    Step-by-Step Explanation:

    1. Create an empty string:

           string converted = "";

       This will store the processed version of the original string.

    2. Traverse the original string:

           for(auto &ch : s)

       We examine every character one by one.

    3. Check whether the character is alphanumeric:

           if(isalnum(ch))

       `isalnum()` returns true if the character is:
       - An uppercase English letter (A-Z).
       - A lowercase English letter (a-z).
       - A digit (0-9).

       Spaces, punctuation marks, and other non-alphanumeric
       characters are ignored.

    4. Convert the character to lowercase and append it:

           converted += tolower(ch);

       `tolower()` converts uppercase letters into lowercase.
       Digits and lowercase letters remain unchanged.

       This ensures that the comparison is case-insensitive.

    5. Create a reversed copy:

           string reversed = converted;

       We copy the cleaned string so that the original processed
       string remains unchanged.

    6. Reverse the copied string:

           reverse(reversed.begin(), reversed.end());

       This reverses all characters in the copied string.

    7. Compare both strings:

           return converted == reversed;

       If both strings are identical, the cleaned string reads
       the same forward and backward, so it is a palindrome.

       Otherwise, return false.

    Example Walkthrough 1:

    s = "A man, a plan, a canal: Panama"

    Step 1: Remove non-alphanumeric characters and convert to lowercase.

        converted = "amanaplanacanalpanama"

    Step 2: Reverse the cleaned string.

        reversed = "amanaplanacanalpanama"

    Step 3: Compare:

        converted == reversed

        true

    Return true.

    Example Walkthrough 2:

    s = "race a car"

    After filtering and lowercase conversion:

        converted = "raceacar"

    Reversed string:

        reversed = "raceacar"

    In this case, the reversed string is actually:

        "racaecar"

    Comparison:

        "raceacar" != "racaecar"

    Return false.

    Why It Works:
    Removing non-alphanumeric characters and converting everything
    to lowercase produces exactly the normalized string required
    by the problem.

    A string is a palindrome if and only if it is equal to its reverse.

    Therefore, comparing the cleaned string with its reversed copy
    correctly determines whether the input is a valid palindrome.

    Complexity Analysis:
    Let n be the length of the original string.

    - Time Complexity: O(n)
      Filtering and lowercase conversion take O(n).
      Reversing the cleaned string takes O(n).
      Comparing the two strings takes O(n).

    - Space Complexity: O(n)
      We create a cleaned string and a reversed copy, both of which
      can contain up to n characters.

    Core Idea:
    Normalize the string by removing non-alphanumeric characters
    and converting letters to lowercase. Reverse the normalized
    string and check whether both versions are equal.
*/