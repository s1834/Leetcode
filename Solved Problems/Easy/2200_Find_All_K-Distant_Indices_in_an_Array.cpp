// APPROACH 1

// class Solution {
// public:
//     vector<int> findKDistantIndices(vector<int>& nums, int key, int k) {
//         set<int> s;
//         int n = nums.size(), i = 0, j = 0;
//         while(j < n && i < n) {
//             if(abs(i - j) <= k) {
//                 if(i > j && nums[i] == key) {
//                      s.insert(i);
//                      s.insert(j);
//                      j++;
//                 } else if(nums[j] == key) {
//                      s.insert(i);
//                      s.insert(j);
//                      i++;
//                 } else j++;
//             } else i < j ? i++ : j++;
//         }
//         return vector<int>(s.begin(), s.end());
//     }
// };

// APPROACH 2
class Solution {
    public:
        vector<int> findKDistantIndices(vector<int>& nums, int key, int k) {
            set<int> s;
            int n = nums.size();
            for(int i = 0; i < n; i++) {
                if(nums[i] == key) {
                    for(int j = max(i - k , 0); j < min(i + k + 1, n); j++) {
                        s.insert(j);
                    }
                }
            }
            return vector<int>(s.begin(), s.end());
        }
    };