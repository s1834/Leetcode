class DSU {
    public:
        vector<int> parent;
        vector<int> sizes;
    
        DSU(int n) {
            parent.resize(n);
            sizes.resize(n);
    
            for(int i = 0; i < n; i++) {
                parent[i] = i;
                sizes[i] = 1;
            }
        }
    
        int find(int x) {
            if(parent[x] == x) return x;
            return parent[x] = find(parent[x]);
        }
    
        void Union(int x, int y) {
            int xParent = find(x);
            int yParent = find(y);
    
            if(xParent == yParent) return;
    
            if(sizes[xParent] >= sizes[yParent]) {
                parent[yParent] = xParent;
                sizes[xParent] += sizes[yParent];
            } else {
                parent[xParent] = yParent;
                sizes[yParent] += sizes[xParent];
            }
        }
    };
    
    class Solution {
    public:
        vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        // 1. Assign ids to emails
        unordered_map<string,int> emailToId; // convert each unique id into a unique integer
        unordered_map<string,string> emailToName; // assign each email to a owner/name
        int id = 0;
        for(auto &account : accounts) {
            int n = account.size();
            string name = account[0];
            for(int i = 1; i < n; i++) {
                string email = account[i];
                // if email doesnt already exist assign new id
                if(emailToId.find(email) == emailToId.end()) emailToId[email] = id++;
                emailToName[email] = name; // store owner of each id
            }
        }
    
    
        // 2. Union emails inside each account
        DSU dsu(id);
        for(auto &account : accounts) {
            int firstMail = emailToId[account[1]], n = account.size(); // take first mail as parent
            for(int i = 2; i < n; i++) dsu.Union(firstMail, emailToId[account[i]]);
        }
    
        // 3. Group emails by DSU parent
        unordered_map<int, vector<string>> groups; // unordered_map<parentId, childrenIds> groups
        for(auto &emails: emailToId) {
            string email = emails.first; // current email ID
            int emailId = emails.second; /// current integer email ID
    
            int parent = dsu.find(emailId); // parent of current integer email ID
    
            groups[parent].push_back(email); // in parent's integer email ID push all its string email IDs
        }
    
        // 4. Create answer
        vector<vector<string>> ans;
        for(auto &x : groups) {
            vector<string> emails = x.second; // get all emails related to a parent id
    
            sort(emails.begin(), emails.end()); // sort them in ascending order
    
            vector<string> temp;
            temp.push_back(emailToName[emails[0]]); // get parent email Id owner and push that name
            for(auto &email : emails) temp.push_back(email); // after name push all the email ids
    
            ans.push_back(temp); // finally push name + email IDs to ans
        }
    
        return ans;
        }
    };

/*

Idea:
------

Each account contains a person's name followed by one or
more email addresses.

Two accounts belong to the same person if they share

at least one common email.

This naturally forms a graph where

• Every unique email is treated as a node.

• Emails belonging to the same account are connected.

Instead of explicitly building the graph,

we use

Disjoint Set Union (DSU)

to group all connected emails together.

Finally,

every connected component represents one merged account.

------------------------------------------------------------

Key Observation:
----------------

If two emails appear in the same account,

they belong to the same person.

Moreover,

this relationship is

transitive.

Example

John

↓

a@gmail.com

b@gmail.com

--------------------------------

Another Account

John

↓

b@gmail.com

c@gmail.com

Since

b@gmail.com

is common,

all three emails belong to the same person.

Therefore,

a@gmail.com

↓

b@gmail.com

↓

c@gmail.com

must belong to one connected component.

DSU efficiently maintains these connected components.

------------------------------------------------------------

Approach:
---------

Step 1

Assign every unique email a unique integer ID.

Why?

DSU works with integer indices instead of strings.

We also maintain

email → owner name

so that we can reconstruct the final answer.

------------------------------------------------------------

Step 2

Union all emails inside the same account.

Take the first email as the representative.

For every remaining email in that account,

perform

Union(firstEmail, currentEmail).

This guarantees that every email in the account belongs to
the same connected component.

------------------------------------------------------------

Step 3

Group emails by their DSU parent.

For every email,

find its ultimate parent using

find().

All emails having the same parent belong to the same merged
account.

------------------------------------------------------------

Step 4

Construct the final answer.

For every group,

• Sort the emails lexicographically.

• Add the owner's name.

• Append all sorted emails.

------------------------------------------------------------

Example:
--------

Accounts

John

a@gmail.com

b@gmail.com

--------------------------------

John

b@gmail.com

c@gmail.com

--------------------------------

Mary

x@gmail.com

------------------------------------------------------------

Step 1

Assign IDs

a → 0

b → 1

c → 2

x → 3

------------------------------------------------------------

Step 2

Union Operations

Union(a,b)

↓

{a,b}

--------------------------------

Union(b,c)

↓

{a,b,c}

------------------------------------------------------------

Step 3

Connected Components

Parent 0

↓

a

b

c

--------------------------------

Parent 3

↓

x

------------------------------------------------------------

Step 4

Output

John

a@gmail.com

b@gmail.com

c@gmail.com

--------------------------------

Mary

x@gmail.com

------------------------------------------------------------

Visualization:
--------------

Accounts

John

↓

a ----- b

        |

        |

        c

Mary

↓

x

--------------------------------

DSU Components

{a,b,c}

{x}

Each connected component becomes one merged account.

------------------------------------------------------------

Why Does This Work?
-------------------

Every account connects all of its emails together.

DSU merges these emails into one connected component.

If another account shares even one email,

its emails are merged into the same component.

Since DSU satisfies the transitive property,

all indirectly connected emails also become part of the same
group.

After all union operations,

each connected component represents exactly one person.

Grouping emails by their DSU parent therefore produces the
correct merged accounts.

------------------------------------------------------------

Why Use Email IDs?
------------------

Emails are strings,

whereas DSU is most efficient when operating on integers.

Therefore,

every unique email is first mapped to a unique integer ID.

Example

john@gmail.com

↓

0

alice@gmail.com

↓

1

bob@gmail.com

↓

2

All union and find operations are performed on these integer
IDs,

while the original email strings are used only when
constructing the final answer.

------------------------------------------------------------

DSU Optimizations:
------------------

Path Compression

During

find(),

every visited node directly points to the ultimate parent.

This makes future

find()

operations much faster.

--------------------------------

Union by Size

Whenever two components are merged,

the smaller component is attached under the larger one.

This keeps the DSU tree shallow and improves performance.

------------------------------------------------------------

Time Complexity:
----------------

Let

N = total number of accounts

M = total number of unique emails

Building Email Maps

O(M)

--------------------------------

Union Operations

Nearly

O(M · α(M))

--------------------------------

Grouping Emails

O(M · α(M))

--------------------------------

Sorting Emails

If a component contains

k

emails,

sorting costs

O(k log k).

Across all groups,

Worst Case

O(M log M)

--------------------------------

Overall Time Complexity

O(M log M)

------------------------------------------------------------

Space Complexity:
-----------------

Email → ID Map

O(M)

Email → Name Map

O(M)

DSU

O(M)

Grouping Map

O(M)

Overall Space Complexity

O(M)

------------------------------------------------------------

Note:
-----

The key insight is to think of

emails

instead of

accounts

as the graph nodes.

Accounts simply provide edges connecting those email nodes.

Once all connected emails are merged using DSU,

every connected component corresponds to one unique person,
making reconstruction of the merged accounts straightforward.

*/