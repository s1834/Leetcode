class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int size = flowerbed.size();
        for (int i = 0; i < size; i++) {
            if (flowerbed[i] != 1 && flowerbed[i + 1] != 1 && flowerbed[i - 1] != 1) {
                n--;
                flowerbed[i] = 1;
            }
        }

        if (n) {
            return false;
        }
        return true;
    }
};