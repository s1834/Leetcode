class MyHashMap {
private:
    struct ListNode {
        int key;
        int val;
        ListNode *next;
        ListNode(int x, int y): key(x), val(y), next(nullptr) {}
    };
    ListNode* head;
public:
    MyHashMap() {
        head = NULL;
    }
    
    void put(int key, int value) {
        ListNode* newNode = new ListNode(key, value);
        if (!head) {
            head = newNode;
            return;
        }

        ListNode* ptr = head, *ptr1 = head;
        while(ptr)  {
            if (ptr->key == key) {
                ptr->val = value;
                return;
            }
            ptr1 = ptr;
            ptr = ptr->next;
        }
        ptr1->next = newNode;
    }
    
    int get(int key) {
        if (!head) {
            return -1;
        }
        ListNode* ptr = head;
        while(ptr) {
            if (ptr->key == key) {
                return ptr->val;
            }
            ptr = ptr->next;
        }
        return -1;
    }
    
    void remove(int key) {
        if (!head) {
            return;
        }
        ListNode* ptr = head, *ptr1 = head;
        if (ptr->key == key) {
            head = head->next;
            return;
        }
        while(ptr) {
            if (ptr->key == key) {
                ptr1->next = ptr->next;
            }
            ptr1 = ptr;
            ptr = ptr->next;
        }
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */