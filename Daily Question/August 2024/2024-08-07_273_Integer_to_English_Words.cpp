class Solution {
private:
    vector<string> ones = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine" };
    vector<string> tens = { "", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
    vector<string> twenty = { "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };

public:
    string numberToWords(int num) {
        if(num == 0) return "Zero";
        if(num < 10) return ones[num];
        if(num < 20) return twenty[num - 10];
        if(num < 100) return tens[num / 10] + (num % 10 ? " " + numberToWords(num % 10) : "");
        if(num < 1000) return numberToWords(num / 100) + " Hundred" + (num % 100 ? " " + numberToWords(num % 100) : "");
        if(num < 1000000) return numberToWords(num / 1000) + " Thousand" + (num % 1000 ? " " + numberToWords(num % 1000) : "");
        if(num < 1000000000) return numberToWords(num / 1000000) + " Million" + (num % 1000000 ? " " + numberToWords(num % 1000000) : "");
        return numberToWords(num / 1000000000) + " Billion" + (num % 1000000000 ? " " + numberToWords(num % 1000000000) : "");
    }
};