class Solution {
    public:
        bool isAnagram(string s, string t) {
            if(s.size() != t.size()) return false;
            
            unordered_map<char, int> mp1, mp2;
            for(auto &ch : s) mp1[ch]++;
            for(auto &ch : t) mp2[ch]++;
    
            if(mp1.size() != mp2.size()) return false;
    
            for(auto &x : mp1) {
                if(x.second != mp2[x.first]) return false;
            }
    
            return true;
        }
    };

/*
    LeetCode 242: Valid Anagram

    Approach: Frequency Counting Using Two Hash Maps

    Intuition:
    Two strings are anagrams if they contain exactly the same characters
    with exactly the same frequencies, regardless of their order.

    For example:
        s = "anagram"
        t = "nagaram"

    Both strings contain:
        a -> 3 times
        n -> 1 time
        g -> 1 time
        r -> 1 time
        m -> 1 time

    Since their character frequencies are identical, they are anagrams.

    Step-by-Step Explanation:

    1. Check string lengths:
        if(s.size() != t.size()) return false;

       If the strings have different lengths, they cannot be anagrams
       because anagrams must contain exactly the same characters.

    2. Create two frequency maps:
        unordered_map<char, int> mp1, mp2;

       - `mp1` stores the frequency of each character in string `s`.
       - `mp2` stores the frequency of each character in string `t`.

    3. Count character frequencies:
        for(auto &ch : s) mp1[ch]++;
        for(auto &ch : t) mp2[ch]++;

       Traverse both strings and increment the frequency of every
       encountered character in its respective map.

    4. Compare the number of distinct characters:
        if(mp1.size() != mp2.size()) return false;

       If the maps contain different numbers of distinct characters,
       the strings cannot have identical character frequencies.

    5. Compare character frequencies:
        for(auto &x : mp1) {
            if(x.second != mp2[x.first]) return false;
        }

       Traverse every entry in `mp1`:
           - `x.first` represents a character.
           - `x.second` represents its frequency in string `s`.
           - `mp2[x.first]` gives its frequency in string `t`.

       If any character has a different frequency in the two strings,
       return false.

       Since the map sizes are already equal, matching the frequency
       of every character in `mp1` guarantees that both maps contain
       exactly the same characters with identical frequencies.

    6. If all frequencies match:
        return true;

       Both strings contain the same characters with the same
       frequencies, so they are valid anagrams.

    Example:
        s = "anagram"
        t = "nagaram"

        After frequency counting:

        mp1 = {
            a: 3,
            n: 1,
            g: 1,
            r: 1,
            m: 1
        }

        mp2 = {
            n: 1,
            a: 3,
            g: 1,
            r: 1,
            m: 1
        }

        Map sizes are equal.
        Every character has the same frequency in both maps.

        Output: true

    Complexity Analysis:

    Let n be the length of each string and k be the number of distinct
    characters.

    - Time Complexity: O(n) on average
      Building both frequency maps takes O(n) expected time.
      Comparing the map sizes and frequencies takes O(k) expected time.
      Since k <= n, the overall expected time complexity is O(n).

      In the worst case, unordered_map operations can degrade due to
      hash collisions.

    - Space Complexity: O(k)
      We maintain two hash maps, each storing at most k distinct
      characters.
      Therefore, auxiliary space is O(k).

    Core Idea:
    Anagrams must have identical character frequencies.

    Count the frequency of every character in both strings using
    hash maps, then compare the maps to determine whether the
    strings are anagrams.
*/