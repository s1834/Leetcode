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
        ListNode* ptr = head, *ptr1 = head;;
        while (ptr) {
            if(ptr->val == key) {
                return;
            }
            ptr1 = ptr;
            ptr = ptr->next;
        }
        ptr1->next = newNode;
    }
    
    void remove(int key) {
        if (!head) {
            return;
        }
        ListNode* ptr = head, *ptr1 = head;
        if (ptr->val == key) {
            head = head->next;
            return;
        }
        while (ptr) {
            if (ptr->val == key) {
                ptr1->next = ptr->next;
                break;
            }
            ptr1 = ptr;
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