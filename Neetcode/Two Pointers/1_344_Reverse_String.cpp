class Solution {
    public:
        void reverseString(vector<char>& s) {
            int n = s.size();
            for(int i = 0; i < n / 2; i++) swap(s[i], s[n - i - 1]);
        }
    };

/*
    LeetCode 344: Reverse String

    Approach: Two Pointers + In-place Swapping

    Intuition:
    We need to reverse the given character array in-place.

    Instead of creating a new reversed array, we swap characters
    from opposite ends of the array.

    - The first character is swapped with the last character.
    - The second character is swapped with the second-last character.
    - We continue moving towards the center.

    Once we reach the middle of the array, the string is reversed.

    Step-by-Step Explanation:

    1. Calculate the size of the array:

           int n = s.size();

       This gives us the total number of characters.

    2. Traverse only the first half of the array:

           for(int i = 0; i < n / 2; i++)

       We only need to process half the elements because every swap
       handles two positions simultaneously.

    3. Find the corresponding position from the end:

           n - i - 1

       For every index `i`:
       - If i = 0, the corresponding index is n - 1.
       - If i = 1, the corresponding index is n - 2.
       - If i = 2, the corresponding index is n - 3.

       This allows us to compare and swap elements from opposite ends.

    4. Swap the two characters:

           swap(s[i], s[n - i - 1]);

       This places the character from the beginning at the end
       and the character from the end at the beginning.

    5. Once the loop finishes, the entire array is reversed.

    Example Walkthrough:

    s = ['h', 'e', 'l', 'l', 'o']

    n = 5

    Iteration 1:
        i = 0
        Swap s[0] and s[4]

        ['o', 'e', 'l', 'l', 'h']

    Iteration 2:
        i = 1
        Swap s[1] and s[3]

        ['o', 'l', 'l', 'e', 'h']

    Loop terminates because i reaches n / 2.

    Final array:
        ['o', 'l', 'l', 'e', 'h']

    Why It Works:
    Every swap places two characters in their correct reversed
    positions.

    After processing the first half of the array, all corresponding
    pairs have been swapped. The middle character of an odd-length
    array does not need to move because it remains in the same position.

    Complexity Analysis:
    - Time Complexity: O(n)
      We perform approximately n / 2 swaps.

    - Space Complexity: O(1)
      Reversal happens directly in the input array using only
      a few variables.

    Core Idea:
    Swap characters from opposite ends of the array and move
    towards the center to reverse the string in-place.
*/