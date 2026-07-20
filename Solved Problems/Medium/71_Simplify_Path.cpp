class Solution {
    public:
        string simplifyPath(string path) {
            stack<string> st;
            int n = path.size();
    
            for (int i = 0; i < n; ) {
                // ignore // and ///
                while (i < n && path[i] == '/') i++;
    
                // store directory name in s
                string s = "";
                while (i < n && path[i] != '/') {
                    s += path[i];
                    i++;
                }
    
                // if current folder(.) or s empty contiue
                if (s == "" || s == ".") continue;
                // if "..", go one folder back
                else if (s == "..") {
                    if (!st.empty()) st.pop();
                }
                else st.push(s);
            }
    
            // return root
            if (st.empty()) return "/";
    
            vector<string> v;
            while (!st.empty()) {
                v.push_back(st.top());
                st.pop();
            }
    
            reverse(v.begin(), v.end());
    
            // add slach before and return ans
            string ans = "";
            for (string x : v) ans += "/" + x;
    
            return ans;
        }
    };

/*

Idea:
------
A Unix file path consists of directory names separated
by

'/'

While traversing the path,

we process one directory at a time and maintain the
current valid path using a stack.

The stack represents the directories from the root to
the current location.

Special directory names are handled according to Unix
rules.

------------------------------------------------------------

Unix Path Rules:
----------------

1.

"/"

Multiple consecutive slashes are treated as a single
slash.

Example

"/home//foo///bar"

=

"/home/foo/bar"

------------------------------------------------------------

2.

"."

Represents the current directory.

It does not change the current path.

Example

"/home/./user"

=

"/home/user"

------------------------------------------------------------

3.

".."

Represents the parent directory.

If possible,

move one directory back by removing the top directory
from the stack.

If already at the root,

stay at the root.

Example

"/home/user/../docs"

=

"/home/docs"

------------------------------------------------------------

Algorithm:
----------

1.

Traverse the path string.

------------------------------------------------------------

2.

Skip every consecutive

'/'

since multiple slashes are equivalent to one.

------------------------------------------------------------

3.

Extract the next directory name until another

'/'

or the end of the string is reached.

------------------------------------------------------------

4.

Handle the extracted directory.

• If it is empty or

"."

ignore it.

• If it is

".."

remove the top directory from the stack if one exists.

• Otherwise,

it is a valid directory name.

Push it onto the stack.

------------------------------------------------------------

5.

After processing the entire path,

the stack contains the simplified directory structure.

------------------------------------------------------------

6.

If the stack is empty,

return

"/"

since the canonical path is the root directory.

------------------------------------------------------------

7.

Otherwise,

reverse the stack contents and rebuild the path by
adding

'/'

before every directory name.

------------------------------------------------------------

Why Does This Work?
-------------------

The stack always represents the current absolute path.

Whenever a valid directory is encountered,

we move into it by pushing it onto the stack.

Whenever

".."

is encountered,

we move to the parent directory by popping the stack.

Ignoring

"."

and repeated slashes ensures only meaningful directory
changes are processed.

Thus,

after processing every component,

the stack exactly represents the canonical Unix path.

------------------------------------------------------------

Example:
--------

Input

"/a/./b/../../c/"

Process

"a"

Stack

[a]

----------------

"."

Ignore.

Stack

[a]

----------------

"b"

Stack

[a, b]

----------------

".."

Go to parent.

Stack

[a]

----------------

".."

Go to parent.

Stack

[]

----------------

"c"

Stack

[c]

----------------

Final Path

"/c"

------------------------------------------------------------

Example:

Input

"/home//foo/"

Process

"home"

Stack

[home]

----------------

Extra '/'

Ignored.

----------------

"foo"

Stack

[home, foo]

Final Answer

"/home/foo"

------------------------------------------------------------

Time Complexity:
----------------

O(n)

Each character of the path is processed exactly once.

------------------------------------------------------------

Space Complexity:
-----------------

O(n)

In the worst case,

all directory names are stored in the stack.

*/