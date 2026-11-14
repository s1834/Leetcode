class Solution {
    public:
        vector<vector<string>> groupAnagrams(vector<string>& strs) {
            unordered_map<string, vector<string>> mp;
            for(auto &x : strs) {
                string s = x;
                sort(s.begin(), s.end());
                mp[s].push_back(x);
            }
    
            vector<vector<string>> result;
            for(auto &x : mp) result.push_back(x.second);
    
            return result;
        }
    };

/*
    LeetCode 49: Group Anagrams

    Approach: Sorting + Hash Map

    Intuition:
    We are given an array of strings and need to group together all
    strings that are anagrams of each other.

    Two strings are anagrams if they contain exactly the same characters
    with the same frequencies, regardless of their order.

    The key observation is that if we sort the characters of two
    anagrams, both strings will produce the same sorted string.

    For example:
        "eat" -> "aet"
        "tea" -> "aet"
        "ate" -> "aet"

    Since all three strings produce the same sorted representation,
    we can use that sorted string as a common key in a hash map.

    Step-by-Step Explanation:

    1. Create a hash map:
        unordered_map<string, vector<string>> mp;

       The map stores:
           Key   -> Sorted version of a string.
           Value -> All original strings having that sorted version.

       This allows us to group anagrams together.

    2. Traverse the input strings:
        for(auto &x : strs)

       Process each string one by one.

    3. Create a sorted copy:
        string s = x;
        sort(s.begin(), s.end());

       We create a copy of the original string so that sorting does
       not modify the input string.

       After sorting, all anagrams produce the same string.

       Example:
           x = "eat"
           s = "aet"

    4. Group strings using the sorted key:
        mp[s].push_back(x);

       Use the sorted string `s` as the key.

       Append the original string `x` to the vector associated
       with that key.

       If the key already exists, the string is added to its
       existing anagram group.

       Otherwise, a new group is automatically created.

    5. Construct the final result:
        vector<vector<string>> result;

       This vector will contain all the anagram groups.

    6. Traverse the hash map:
        for(auto &x : mp)
            result.push_back(x.second);

       Each map entry represents one complete group of anagrams.

       Since `x.second` contains the original strings belonging
       to that sorted key, we directly append it to the result.

    7. Return the grouped anagrams:
        return result;

    Example:
        strs = ["eat", "tea", "tan", "ate", "nat", "bat"]

        Processing each string:

        1. "eat"
           Sorted key = "aet"
           mp["aet"] = ["eat"]

        2. "tea"
           Sorted key = "aet"
           mp["aet"] = ["eat", "tea"]

        3. "tan"
           Sorted key = "ant"
           mp["ant"] = ["tan"]

        4. "ate"
           Sorted key = "aet"
           mp["aet"] = ["eat", "tea", "ate"]

        5. "nat"
           Sorted key = "ant"
           mp["ant"] = ["tan", "nat"]

        6. "bat"
           Sorted key = "abt"
           mp["abt"] = ["bat"]

        Final groups:

            ["eat", "tea", "ate"]
            ["tan", "nat"]
            ["bat"]

        Output:
            [["eat", "tea", "ate"],
             ["tan", "nat"],
             ["bat"]]

        Note:
        Since unordered_map does not maintain insertion order,
        the order of the groups in the final result is not guaranteed.
        However, any ordering of the groups is accepted.

    Complexity Analysis:

    Let:
        n = Number of strings.
        m = Maximum length of a string.

    - Time Complexity: O(n * m log m) on average.

      For every string:
          - Copying the string takes O(m).
          - Sorting its characters takes O(m log m).
          - Inserting it into the hash map takes O(m) expected time
            for hashing and insertion.

      Therefore, processing all n strings takes
      O(n * m log m) expected time.

      Constructing the result takes O(n) vector insertions.

    - Space Complexity: O(n * m).

      The hash map stores all original strings along with their
      sorted keys.

      The result vector also stores all original strings grouped
      together.

      Therefore, the overall auxiliary space complexity is O(n * m).

    Core Idea:
    Sort every string to generate a canonical representation.

    All anagrams produce the same sorted string, so use that string
    as a hash map key and group the original strings under it.

    Finally, collect all map values to build the answer.
*/