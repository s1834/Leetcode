class Solution {
private:
    int josephusProblem(int n, int k) {
        return n == 1 ? 0 : (josephusProblem(n - 1, k) + k) % n;
    }  
    
public:
    int findTheWinner(int n, int k) {
        return josephusProblem(n, k) + 1;
    }
};