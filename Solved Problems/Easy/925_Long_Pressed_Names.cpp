class Solution {
    public:
        bool isLongPressedName(string name, string typed) {
            int i = 0, j = 0, n = name.size(), m = typed.size();
            if(m < n) return false;
            while (i < n && j < m) {
                if(name[i] == typed[j]) {
                    if(i + 1 < n && j + 1 < m && name[i + 1] == typed[j + 1]) i++;
                    j++;
                }
                else return false;
            }
            if(i != n - 1) return false;
            return true;
        }
    };