class BrowserHistory {
private: 
    struct ListNode {
        string val;
        ListNode *next;
        ListNode *prev;
        ListNode(string x) : val(x), next(nullptr), prev(nullptr) {}
    };
    ListNode* head, *ptr;
public:
    BrowserHistory(string homepage) {
        head = new ListNode(homepage);
        ptr = head;
    }
    
    void visit(string url) {
        ListNode* newURL = new ListNode(url);
        ptr->next = newURL;
        newURL->prev = ptr;
        ptr = newURL;
    }
    
    string back(int steps) {
        ListNode* move = ptr;
        while (steps-- && move->prev) {
            move = move->prev;
        }
        ptr = move;
        return move->val;
    }
    
    string forward(int steps) {
        ListNode* move = ptr;
        while (steps-- && move->next) {
            move = move->next;
        }
        ptr = move;
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