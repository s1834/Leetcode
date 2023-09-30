class BrowserHistory {
private: 
    struct ListNode {
        string val;
        ListNode *next;
        ListNode(string x) : val(x), next(NULL) {}
    };
    ListNode* head, *ptr, *cur;
    int x = 1, x1 = x, flag = 1;
public:
    BrowserHistory(string homepage) {
        head = new ListNode(homepage);
        ptr = head;
    }
    
    void visit(string url) {
        ListNode* newURL = new ListNode(url);
        if (!flag) {
            ptr = cur;
        }
        ptr->next = newURL;
        ptr = newURL;
        x++;
        if (flag) {
            x1 = x;
            
        } else {
            cur = ptr;
        }
    }
    
    string back(int steps) {
        // int temp;
        // flag = 0;
        // if (x1 > steps && x1 - steps <= x) {
        //     temp = x1 - steps - 1;
        //     x1 -= steps;
        // } else {
        //     temp = 0;
        //     x1 = 1;
        // }
        ListNode* move = cur;
        flag = 0; 
        int count = 0;
        while(move) {
            count++;
            move = move->next;
        }
        int temp = x - count - steps;
        move = head;
        while (temp && move->next) {
            move = move->next;
            temp--;
        }
        cur = move;
        return move->val;
    }
    
    string forward(int steps) {
        // int temp;
        // flag = 0;
        // if (x1 > steps && x1 + steps <= x) {
        //     temp = x1 - steps - 1;
        //     x1 += steps;
        // } else {
        //     temp = x1 - 1;
        //     x1 = x;
        // }
        x1 += steps;
        flag = 0;
        ListNode* move = cur;
        while (steps && move->next) {
            move = move->next;
            steps--;
        }
        cur = move;
        return move->val;
    }
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */