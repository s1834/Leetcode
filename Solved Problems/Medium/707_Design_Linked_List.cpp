class MyLinkedList {
private:
    struct ListNode {
        int val;
        ListNode* next;
        ListNode* prev;
        ListNode(): val(0), next(nullptr), prev(nullptr) {}
        ListNode(int x) : val(x), next(nullptr), prev(nullptr) {}
        ListNode(int x, ListNode *next, ListNode* prev) : val(x), next(next), prev(prev) {}
    };
    ListNode* head = nullptr;

public:
    MyLinkedList() {}
    
    int get(int index) {
        ListNode* ptr = head;
        while(ptr && index--) ptr = ptr->next;
        if(index == -1) return ptr->val;
        return -1;
    }
    
    void addAtHead(int val) {
        ListNode* newNode = new ListNode(val);
        newNode->next = head;
        if(head) head->prev = newNode;
        head = newNode;
    }
    
    void addAtTail(int val) {
        if(!head) {
            addAtHead(val);
            return;
        }

        ListNode* newNode = new ListNode(val);
        ListNode* ptr = head;
        while(ptr->next) ptr = ptr->next;
        ptr->next = newNode;
        newNode->prev = ptr;
    }
    
    void addAtIndex(int index, int val) {
        if(!head || index == 0) {
            addAtHead(val);
            return;
        }
        ListNode* newNode = new ListNode(val);
        ListNode* ptr = head;
        while(ptr && index--) ptr = ptr->next;
        if(index == -1) {
            newNode->next = ptr;
            newNode->prev = ptr->prev;
            ptr->prev->next = newNode;
            ptr->prev = newNode;
        }
        if(index == 0) addAtTail(val);
    }
    
    void deleteAtIndex(int index) {
        if (index == 0) {
            head = head->next;
            return;
        }
        ListNode* ptr = head;
        while(ptr && index--) ptr = ptr->next;
        if(index == -1) ptr->prev->next = ptr->next;
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */