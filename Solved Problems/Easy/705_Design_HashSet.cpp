class MyHashSet {
private:
    struct ListNode {
        int val;
        ListNode *next;
    };
    ListNode* head;
public:
    MyHashSet() {
        head = NULL;
    }
    
    void add(int key) {
        ListNode* newNode = new ListNode;
        newNode->val = key;
        newNode->next = NULL;
        if (!head) {
            head = newNode;
            return;
        }
        ListNode* ptr = head;
        while (ptr->next) {
            if(ptr->val == key) {
                return;
            }
            ptr = ptr->next;
        }
        if(ptr->val == key) {
                return;
        }
        ptr->next = newNode;
    }
    
    void remove(int key) {
        if (!head) {
            return;
        }
        ListNode* ptr = head;
        while (ptr->next) {
            if (ptr->next->val == key) {
                ptr->next = ptr->next->next;
                break;
            }
            ptr = ptr->next;
        }
    }
    
    bool contains(int key) {
        if (!head) {
            return false;
        }
        ListNode* ptr = head;
        while (ptr) {
            if (ptr->val == key) {
                return true;
            }
            ptr = ptr->next;
        }
        return false;
    }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */