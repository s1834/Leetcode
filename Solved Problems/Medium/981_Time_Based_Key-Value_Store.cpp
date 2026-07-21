class TimeMap {
    private:
        unordered_map<string, vector<pair<int,string>>> mp;
    
    public:
        TimeMap() {
            
        }
        
        void set(string key, string value, int timestamp) {
            mp[key].push_back({timestamp, value});
        }
        
        string get(string key, int timestamp) {
            if(mp.find(key) == mp.end()) return "";
    
            vector<pair<int, string>> &v = mp[key];
    
            int left = 0, right = v.size() - 1;
            string ans = "";
    
            while(left <= right) {
                int mid = left + (right - left) / 2;
    
                if(v[mid].first <= timestamp) {
                    ans = v[mid].second;
                    left = mid + 1;
                }
                else right = mid - 1;
            }
    
            return ans;
        }
    };
    
    /**
     * Your TimeMap object will be instantiated and called as such:
     * TimeMap* obj = new TimeMap();
     * obj->set(key,value,timestamp);
     * string param_2 = obj->get(key,timestamp);
     */

/*

Idea:
------
For every key,

multiple values can be stored at different timestamps.

The timestamps for a particular key are inserted in
strictly increasing order.

Therefore,

instead of searching linearly,

we can store all

(timestamp, value)

pairs in a vector and use Binary Search to quickly find
the latest value whose timestamp is less than or equal to
the given timestamp.

------------------------------------------------------------

Key Observation:
----------------

For each key,

the timestamps are always inserted in increasing order
(as guaranteed by the problem).

Therefore,

the vector corresponding to a key is already sorted by
timestamp.

This allows us to perform Binary Search without any
additional sorting.

------------------------------------------------------------

Data Structure:
---------------

unordered_map<
    string,
    vector<pair<int, string>>
>

Each key maps to a sorted list of

(timestamp, value)

pairs.

Example

set("foo", "bar", 1)

set("foo", "bar2", 4)

Stored as

foo →

[(1, "bar"), (4, "bar2")]

------------------------------------------------------------

Algorithm:
----------

set(key, value, timestamp)

1.

Append

(timestamp, value)

to the vector corresponding to

key.

Since timestamps are inserted in increasing order,

the vector remains sorted.

Time:

O(1)

------------------------------------------------------------

get(key, timestamp)

1.

If the key does not exist,

return an empty string.

------------------------------------------------------------

2.

Retrieve the sorted vector of

(timestamp, value)

pairs.

------------------------------------------------------------

3.

Perform Binary Search to find the largest timestamp that
is less than or equal to the given timestamp.

During Binary Search,

if

v[mid].timestamp ≤ timestamp

then

v[mid]

is a valid answer.

Store its value and continue searching toward the right
to see if there exists an even larger valid timestamp.

Otherwise,

search in the left half.

------------------------------------------------------------

4.

Return the stored answer.

If no valid timestamp exists,

the answer remains an empty string.

------------------------------------------------------------

Mathematical Explanation:
-------------------------

We need to find

max(timestamp_i)

such that

timestamp_i ≤ queryTimestamp

This is known as the

Floor

of the query timestamp.

Suppose the stored timestamps are

[1, 3, 6, 9]

Query

timestamp = 7

The largest timestamp satisfying

timestamp ≤ 7

is

6.

Therefore,

return the value stored at timestamp

6.

Binary Search efficiently finds this floor in

O(log n)

time.

------------------------------------------------------------

Example:
--------

set("foo", "bar", 1)

set("foo", "bar2", 4)

set("foo", "bar3", 8)

Stored Vector

[(1, bar), (4, bar2), (8, bar3)]

--------------------------------

Query

get("foo", 5)

Binary Search

mid = 4

4 ≤ 5

Possible answer = "bar2"

Search right.

--------------------------------

Next timestamp

8

8 > 5

Search left.

--------------------------------

Search ends.

Largest valid timestamp = 4

Return

"bar2"

------------------------------------------------------------

Another Example:
----------------

Stored timestamps

[2, 5, 9]

Query

timestamp = 1

No timestamp satisfies

timestamp ≤ 1

Therefore,

return

""

(empty string).

------------------------------------------------------------

Why Does This Work?
-------------------

Since timestamps are stored in sorted order,

all timestamps before the answer are also valid, while
all timestamps after the answer are invalid.

Binary Search repeatedly eliminates half of the search
space.

Whenever a valid timestamp is found,

we continue searching toward the right because there may
exist a larger timestamp that is still valid.

Thus,

the final stored answer is the latest value available at
or before the requested timestamp.

------------------------------------------------------------

Time Complexity:
----------------

set()

O(1)

Appending to the vector.

--------------------------------

get()

Binary Search over the timestamps of one key.

O(log n)

where

n

is the number of timestamps stored for that key.

------------------------------------------------------------

Space Complexity:
-----------------

O(total entries)

Every

(timestamp, value)

pair is stored exactly once.

*/