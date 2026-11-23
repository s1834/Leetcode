class ProductOfNumbers {
    private:
        vector<int> nums;
        int n;
    
    public:
        ProductOfNumbers() {
            nums.clear();
            n = 0;
        }
        
        void add(int num) {
            if(num == 0) {
                nums = {};
                n = 0;
            } else {
                if(nums.empty()) nums.push_back(num);
                else nums.push_back(nums[n - 1] * num);
                n++;
            }
        }
        
        int getProduct(int k) {
            if(k > n) return 0;
            else if(k == n) return nums[n - 1];
            else return nums[n - 1] / nums[n - k - 1];
        }
    };
    
    /**
     * Your ProductOfNumbers object will be instantiated and called as such:
     * ProductOfNumbers* obj = new ProductOfNumbers();
     * obj->add(num);
     * int param_2 = obj->getProduct(k);
     */

/*
    LeetCode 1352: Product of the Last K Numbers

    Approach: Prefix Product + Zero Handling

    Intuition:
    We need to design a data structure that supports two operations:

    1. add(num): Add a number to the sequence.
    2. getProduct(k): Return the product of the last k numbers.

    Instead of multiplying the last k elements every time, we maintain
    prefix products.

    The prefix product at index i represents the product of all
    non-zero numbers added since the most recent zero, up to index i.

    Using prefix products, we can calculate the product of the last
    k elements in O(1) time through division.

    The important observation is that multiplication by zero makes
    the entire product zero. Therefore, whenever we encounter zero,
    we clear the prefix product array and start tracking products
    again from the next number.

    Variables:
    - nums: Stores cumulative products of non-zero numbers since the
            most recent zero.
    - n: Number of non-zero elements currently stored in `nums`.
    - num: Number being added.
    - k: Number of last elements whose product is requested.

    Step-by-Step Explanation:

    1. Constructor:

           ProductOfNumbers() {
               nums.clear();
               n = 0;
           }

       Initially, there are no elements, so the prefix product array
       is empty and its size counter is zero.

    2. add(int num):

       This function adds a new number to the sequence.

       Case 1: The incoming number is zero.

           if(num == 0) {
               nums = {};
               n = 0;
           }

       A zero makes the product of any sequence containing it equal
       to zero.

       Therefore, we clear all previously stored prefix products.

       We also reset `n` because we are starting a new sequence
       after the most recent zero.

       Case 2: The incoming number is non-zero.

       If the prefix product array is empty:

           if(nums.empty()) nums.push_back(num);

       The current number becomes the first prefix product.

       Otherwise:

           nums.push_back(nums[n - 1] * num);

       Multiply the previous cumulative product by the new number
       and store the result.

       Finally:

           n++;

       Increment the number of stored prefix products.

       Example:

       Operations:
           add(3)
           add(4)
           add(2)

       Prefix products:
           nums = [3, 12, 24]

       Explanation:
           3
           3 * 4 = 12
           3 * 4 * 2 = 24

    3. getProduct(int k):

       This function returns the product of the last k numbers.

       Case 1: k > n

           if(k > n) return 0;

       If k is greater than the number of stored prefix products,
       the requested range must contain a zero.

       Since any product containing zero is zero, return 0.

       Case 2: k == n

           else if(k == n) return nums[n - 1];

       If we need the product of all currently stored numbers,
       the answer is simply the last prefix product.

       Case 3: k < n

           else return nums[n - 1] / nums[n - k - 1];

       This is where prefix product division is used.

       Let:
           prefix[i] = product of elements from index 0 to i.

       We know:

           prefix[n - 1]
           = product of all stored elements.

           prefix[n - k - 1]
           = product of elements before the last k elements.

       Therefore:

           Product of last k elements
           = prefix[n - 1] / prefix[n - k - 1]

       Dividing removes the contribution of all elements before
       the required range.

    Example Walkthrough:

    Operations:

        add(3)
        add(0)
        add(2)
        add(5)
        add(4)

    After add(3):
        nums = [3]
        n = 1

    After add(0):
        nums = []
        n = 0

        Previous prefix products are cleared because of zero.

    After add(2):
        nums = [2]
        n = 1

    After add(5):
        nums = [2, 10]
        n = 2

    After add(4):
        nums = [2, 10, 40]
        n = 3

    Query 1:
        getProduct(2)

        k = 2, n = 3

        nums[n - 1] / nums[n - k - 1]

        = nums[2] / nums[0]
        = 40 / 2
        = 20

        Product of last two numbers:
            5 * 4 = 20

    Query 2:
        getProduct(3)

        k == n

        Return nums[n - 1] = 40.

        Product:
            2 * 5 * 4 = 40

    Query 3:
        getProduct(4)

        k > n

        Return 0 because the last four numbers include zero.

    Why It Works:
    Prefix products allow us to calculate the product of any suffix
    within the current zero-free sequence using division.

    Clearing the prefix array whenever zero is added ensures that
    every stored prefix product is non-zero.

    Therefore, division is always valid, and if the requested range
    extends beyond the stored sequence, it must contain a zero.

    Complexity Analysis:

    - add():
      O(1) time
      Appending a prefix product or clearing the vector takes O(1)
      amortized time.

    - getProduct():
      O(1) time
      The answer is calculated using at most one division.

    - Space Complexity:
      O(n)
      We store prefix products for all non-zero elements added
      since the most recent zero.

    Core Idea:
    Maintain cumulative products instead of storing and multiplying
    every number in a query. Use prefix product division to answer
    queries in O(1), and reset the prefix products whenever zero
    is encountered.
*/