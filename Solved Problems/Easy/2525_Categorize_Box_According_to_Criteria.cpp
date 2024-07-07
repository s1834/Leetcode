class Solution {
public:
    string categorizeBox(int length, int width, int height, int mass) {
        bool bulky = (length >= 1e4 || width >= 1e4 || height >= 1e4 || (long long int) length * width * height >= 1e9) ? true : false, heavy = mass >= 100 ? true : false;
        if(bulky && heavy) return "Both";
        if(!bulky && !heavy) return "Neither";
        if(bulky && !heavy) return "Bulky";
        cout << (long long int) length * width * height;
        return "Heavy";
    }
};