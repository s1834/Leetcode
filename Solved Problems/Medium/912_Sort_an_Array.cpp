class Solution {
public:
    void merge(vector<int>& nums, int l, int mid, int r) {
        int n1 = mid - l + 1;
        int n2 = r - mid;

        vector<int> temp1(n1), temp2(n2);

        for(int i = 0; i < n1; i++) {
            temp1[i] = nums[l + i];
        }

        for(int i = 0; i < n2; i++) {
            temp2[i] = nums[mid + i + 1];
        }

        int i = 0, j = 0, k = l;
        while(i < n1 && j < n2) {
            if(temp1[i] <= temp2[j]) {
                nums[k] = temp1[i];
                i++;
            } else {
                nums[k] = temp2[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            nums[k] = temp1[i];
            i++;
            k++;
        }

         while (j < n2) {
            nums[k] = temp2[j];
            j++;
            k++;
        }
    }
    
    void mergeSort(vector<int>& nums, int l, int r) {
        if(l >= r) {
            return;
        }
        int mid = (l + r) / 2;
        mergeSort(nums, l, mid);
        mergeSort(nums, mid + 1, r);
        merge(nums, l, mid, r);
    }

    vector<int> sortArray(vector<int>& nums) {
        mergeSort(nums, 0, nums.size() - 1);
        return nums;
    }
};