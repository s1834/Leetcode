class Twitter {
    private:
        void getUserTweets(priority_queue<pair<int, int>>& pq, int& userId) {
            for(auto x : tweets[userId]) pq.push(x);
        }
    
        void getFollowersTweets(priority_queue<pair<int, int>>& pq, int& userId) {
            for(auto x : followers[userId]) {
                for(auto y : tweets[x]) pq.push(y);
            }
        }
    
        int time;
        unordered_map<int, set<int>> followers; // unordered_map<followerId, set<followeeId>> followers;
        unordered_map<int, vector<pair<int, int>>> tweets; // unordered_map<userId, vector<pair<time, tweetId>>> tweets;
        
    public:
        Twitter() {
            time = 0;
        }
        
        void postTweet(int userId, int tweetId) {
            tweets[userId].push_back({time++, tweetId});
        }
        
        vector<int> getNewsFeed(int userId) {
            priority_queue<pair<int, int>> pq;
    
            getUserTweets(pq, userId);
            getFollowersTweets(pq, userId);
    
            int i = 0;
            vector<int> ans;
            while(!pq.empty() && i < 10) {
                auto temp = pq.top();
                pq.pop();
                ans.push_back(temp.second);
                i++;
            }
    
            return ans;
        }
        
        void follow(int followerId, int followeeId) {
            followers[followerId].insert(followeeId);
        }
        
        void unfollow(int followerId, int followeeId) { 
            followers[followerId].erase(followeeId);
        }
    };
    
    /**
     * Your Twitter object will be instantiated and called as such:
     * Twitter* obj = new Twitter();
     * obj->postTweet(userId,tweetId);
     * vector<int> param_2 = obj->getNewsFeed(userId);
     * obj->follow(followerId,followeeId);
     * obj->unfollow(followerId,followeeId);
     */

/*

Idea:
------
The Twitter system must support four operations:

1.

Post a tweet.

2.

Follow another user.

3.

Unfollow a user.

4.

Retrieve the 10 most recent tweets visible to a user.

This implementation stores every user's tweets separately
along with a global timestamp.

When generating the news feed,

all tweets from the user and the users they follow are
inserted into a

Max Heap (Priority Queue),

allowing us to retrieve the most recent tweets first.

------------------------------------------------------------

Data Structures:
----------------

1.

tweets

unordered_map<userId,
              vector<{timestamp, tweetId}>>

Stores every tweet posted by each user.

Each tweet is stored along with the time at which it was
posted.

--------------------------------

2.

followers

unordered_map<followerId,
              set<followeeId>>

Stores the users that a particular user follows.

For example,

followers[5] = {2,7}

means

User 5 follows User 2 and User 7.

--------------------------------

3.

time

A global counter.

Every new tweet receives a unique timestamp.

Since

time

is incremented after every post,

larger timestamps always represent newer tweets.

------------------------------------------------------------

Algorithm:
----------

postTweet(userId, tweetId)

1.

Store

{currentTime, tweetId}

inside the user's tweet list.

------------------------------------------------------------

2.

Increment the global timestamp.

This guarantees that every tweet has a unique posting
time.

------------------------------------------------------------

follow(followerId, followeeId)

Insert

followeeId

into the follower's follow list.

Since a

set

is used,

duplicate follow relationships are automatically ignored.

------------------------------------------------------------

unfollow(followerId, followeeId)

Remove

followeeId

from the follower's follow list.

If the user is not being followed,

erase() simply has no effect.

------------------------------------------------------------

getNewsFeed(userId)

The news feed should contain

• The user's own tweets.

• Tweets of every user they follow.

Only the

10 most recent

tweets should be returned.

------------------------------------------------------------

Step 1

Create a

Max Heap

(priority_queue).

The heap automatically keeps the tweet having the largest
timestamp at the top.

------------------------------------------------------------

Step 2

Insert all tweets posted by the user.

------------------------------------------------------------

Step 3

For every followed user,

insert all of their tweets into the same heap.

------------------------------------------------------------

Step 4

Repeatedly remove the heap's top element.

Since the heap is ordered by timestamp,

tweets are removed from newest to oldest.

Collect the first

10

tweet IDs.

------------------------------------------------------------

Step 5

Return the collected tweet IDs.

------------------------------------------------------------

Helper Functions:
-----------------

getUserTweets()

Pushes every tweet posted by the current user into the
priority queue.

--------------------------------

getFollowersTweets()

Iterates over every followed user and pushes all of their
tweets into the priority queue.

These helper functions keep the implementation modular
and avoid duplicating code.

------------------------------------------------------------

Why Does This Work?
-------------------

Every tweet is assigned a unique increasing timestamp.

Therefore,

sorting tweets by timestamp is equivalent to sorting them
by posting time.

The priority queue always keeps the newest tweet at its
top.

By inserting every visible tweet into the heap,

the first

10

elements removed are exactly the

10 most recent

tweets that should appear in the user's news feed.

------------------------------------------------------------

Example:
--------

Initially

User 1

posts

Tweet 5

Time = 0

tweets[1]

(0,5)

--------------------------------

User 2

posts

Tweet 8

Time = 1

tweets[2]

(1,8)

--------------------------------

User 1

follows

User 2

followers[1]

{2}

--------------------------------

User 2

posts

Tweet 9

Time = 2

tweets[2]

(1,8)

(2,9)

--------------------------------

getNewsFeed(1)

Insert User 1 tweets

(0,5)

Insert User 2 tweets

(1,8)

(2,9)

Priority Queue

Top

↓

(2,9)

↓

(1,8)

↓

(0,5)

Result

[9,8,5]

------------------------------------------------------------

Why Use a Priority Queue?
-------------------------

Tweets are posted at different times by different users.

After collecting all visible tweets,

they must be returned in descending order of posting
time.

A max heap automatically maintains this ordering,

allowing us to repeatedly retrieve the newest remaining
tweet.

------------------------------------------------------------

Time Complexity:
----------------

Let

F

be the number of followed users.

Let

T

be the total number of visible tweets
(user's tweets + followed users' tweets).

--------------------------------

postTweet()

O(1)

--------------------------------

follow()

O(log F)

Insertion into a set.

--------------------------------

unfollow()

O(log F)

Deletion from a set.

--------------------------------

getNewsFeed()

All visible tweets are inserted into the priority queue.

Insertion:

O(T log T)

Extracting the top 10 tweets:

O(10 log T)

Overall:

O(T log T)

------------------------------------------------------------

Space Complexity:
-----------------

tweets

stores every posted tweet.

followers

stores all follow relationships.

The priority queue temporarily stores all visible tweets
during

getNewsFeed().

Auxiliary Space for getNewsFeed():

O(T)

where

T

is the total number of visible tweets.

*/