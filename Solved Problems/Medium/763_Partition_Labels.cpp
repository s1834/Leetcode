class Solution {
    public:
        vector<int> partitionLabels(string s) {
            int n = s.size();
    
            vector<int> result;
    
            vector<int> lastOccurance(26, -1); // last occurance of each character;
            for(int i = 0; i < n; i++) lastOccurance[s[i] - 'a'] = i;
    
            int i = 0;
            int start = 0, end = 0;
            while(i < n) {
                end = max(end, lastOccurance[s[i] - 'a']);
                if(i == end) {
                    result.push_back(end - start + 1);
                    start = end + 1;
                }
                i++;
            }
    
            return result;
        }
    };

/*
Problem: LeetCode 763 - Partition Labels

Approach: Greedy + Last Occurrence Tracking

Intuition:
----------
We need to partition the string into as many parts as possible
such that each character appears in at most one partition.

In other words, if a character appears in a partition, all
its occurrences must be contained within that same partition.

The key observation is that we only need to know the last
occurrence of every character.

While traversing the string:
- Maintain the farthest last occurrence of any character
  encountered in the current partition.
- If the current index reaches this farthest position,
  we can safely close the current partition.

This greedy approach creates the maximum number of valid
partitions.

--------------------------------------------------
1. Initialize Variables
--------------------------------------------------

int n = s.size();

vector<int> result;

- n stores the length of the string.
- result stores the lengths of all partitions.

vector<int> lastOccurance(26, -1);

This array stores the last occurrence index of each
lowercase English character.

Initially, every entry is -1.

--------------------------------------------------
2. Calculate the Last Occurrence of Every Character
--------------------------------------------------

for(int i = 0; i < n; i++)
    lastOccurance[s[i] - 'a'] = i;

For every character:
- Convert it into an index using s[i] - 'a'.
- Store its current index as its last occurrence.

If a character appears multiple times, its stored position
gets updated.

After this loop, lastOccurance[c] contains the last index
at which character c appears in the string.

Example:

    s = "ababcbacadefegdehijhklij"

Some last occurrences:

    a -> 8
    b -> 5
    c -> 7
    d -> 14
    e -> 15

--------------------------------------------------
3. Initialize Partition Boundaries
--------------------------------------------------

int i = 0;
int start = 0, end = 0;

- i represents the current traversal index.
- start represents the starting index of the current partition.
- end represents the farthest index that the current partition
  must include.

Initially, the first partition starts at index 0.

--------------------------------------------------
4. Traverse the String and Extend the Current Partition
--------------------------------------------------

while(i < n) {

    end = max(end, lastOccurance[s[i] - 'a']);

}

For the current character s[i], find its last occurrence.

Update end using:

    end = max(end, lastOccurance[s[i] - 'a']);

Why do we use maximum?

Because every character inside the current partition must
have all its occurrences inside that partition.

If a character appears again later, the partition must
extend at least until that position.

Therefore, end always represents the farthest position
required by all characters encountered so far.

--------------------------------------------------
5. Check Whether the Current Partition Can Be Closed
--------------------------------------------------

if(i == end) {

    result.push_back(end - start + 1);

    start = end + 1;

}

When i reaches end, every character encountered in the
current partition has its last occurrence within the
current partition.

Therefore, no character from this partition will appear
in any future partition.

We can safely close it.

Partition length:

    end - start + 1

Store this length in result.

Then move the starting position to the next index:

    start = end + 1;

--------------------------------------------------
6. Move to the Next Character
--------------------------------------------------

i++;

Continue traversing until the entire string has been
processed.

--------------------------------------------------
7. Return the Result
--------------------------------------------------

return result;

The result vector contains the lengths of all valid
partitions.

--------------------------------------------------
8. Example Walkthrough
--------------------------------------------------

Input:

    s = "ababcbacadefegdehijhklij"

After calculating last occurrences, start traversing.

First partition:

    start = 0
    end = 0

As we process characters, end keeps extending:

    a -> last occurrence = 8
    b -> last occurrence = 5
    c -> last occurrence = 7

The maximum required boundary becomes 8.

When i reaches 8:

    i == end

So we close the first partition:

    length = 8 - 0 + 1 = 9

Update:

    start = 9

Second partition:

    The next partition extends until index 15.

    length = 15 - 9 + 1 = 7

Update:

    start = 16

Third partition:

    The remaining characters form a partition ending
    at index 23.

    length = 23 - 16 + 1 = 8

Final result:

    [9, 7, 8]

--------------------------------------------------
9. Why Does This Greedy Approach Work?
--------------------------------------------------

A partition cannot end before the last occurrence of any
character it contains.

Therefore, while processing a partition, we continuously
extend its ending boundary to include the last occurrence
of every encountered character.

When i == end, all characters in the current partition
are completely contained within it.

We close the partition immediately because extending it
further would only merge it with another partition and
reduce the total number of partitions.

Thus, closing a partition at the earliest valid position
produces the maximum number of valid partitions.

--------------------------------------------------
10. Complexity Analysis
--------------------------------------------------

Time Complexity: O(n)

- Calculating last occurrences takes O(n).
- Traversing the string and forming partitions takes O(n).
- Each character is processed once in each traversal.

Space Complexity: O(1) auxiliary space

- lastOccurance contains exactly 26 entries.
- The result vector stores the partition lengths.

Excluding the output vector, the algorithm uses O(1)
auxiliary space.

Core Idea:
----------
Precompute the last occurrence of every character.

While traversing the string, maintain the farthest last
occurrence required by the current partition.

Whenever the current index reaches that boundary, close
the partition and start a new one.

This greedy strategy produces the maximum number of
valid partitions.
*/