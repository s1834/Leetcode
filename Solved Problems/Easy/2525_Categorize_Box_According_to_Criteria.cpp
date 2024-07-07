class Solution {
public:
    string categorizeBox(int length, int width, int height, int mass) {
        bool bulky = (length >= 10e4 || width >= 10e4 || height >= 10e4 || (long long int) length * width * height >= 10e9) ? true : false, heavy = mass >= 100 ? true : false;
        if(bulky && heavy) return "Both";
        if(!bulky && !heavy) return "Neither";
        if(bulky && !heavy) return "Bulky";
        return "Heavy";
    }
};