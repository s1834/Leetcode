class Solution {
    public:
        int numberOfAlternatingGroups(vector<int>& colors, int k) {
            int n = colors.size(), count = 0;
            for(int i = 1; i <= n; i++) {
                int flag = true;
                for(int j = i; j < i + k - 2; j++) {
                    if(j < n - 1) flag = colors[j] != colors[j - 1] && colors[j] != colors[j + 1];
                    else if(j > n) flag = colors[j - n] != colors[j - n - 1] && colors[j - n] != colors[j - n + 1];
                    else if(j == n - 1) flag = colors[j] != colors[j - 1] && colors[j] != colors[j - n + 1];
                    else flag = colors[j - n] != colors[j - 1] && colors[j - n] != colors[j - n + 1];
                    if(!flag) break;
                }
                if(flag) count++;
            }
            return count;
        }
    };