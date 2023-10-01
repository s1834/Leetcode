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
    ListNode *head;
    int totalNodes = 0;
public:
    MyLinkedList() {
        head = new ListNode();
        totalNodes++;
    }
    
    int get(int index) {
        if (index > totalNodes) {
            return -1;
        }
        ListNode* ptr = head;
        while (index && ptr->next) {
            ptr = ptr->next;
            index--;
        }
        return ptr->val;
    }
    
    void addAtHead(int val) {
        ListNode* ptr = new ListNode(val);
        if (!head) {
            head = ptr;
            totalNodes++;
            cout<<head->val<<"addathead\n";
            return;
        }
        ptr->next = head;
        head = ptr;
        totalNodes++;
    }
    
    void addAtTail(int val) {
        ListNode* ptr = head;
        while (ptr->next) {
            ptr = ptr->next;
        }
        ListNode* newNode = new ListNode(val);
        ptr->next = newNode;
        newNode->prev = ptr;
        totalNodes++;
    }
    
    void addAtIndex(int index, int val) {
        if (index > totalNodes) {
            return;
        }
        ListNode* ptr = head;
        while (index-- && ptr->next) {
            ptr = ptr->next;
        } 
        ListNode* newNode = new ListNode(val);
        newNode->next = ptr->next;
        ptr->next = newNode;
        newNode->prev = ptr;
        totalNodes++;
    }
    
    void deleteAtIndex(int index) {
        if (index > totalNodes) {
            return;
        }
        ListNode* ptr = head;
        while (index-- && ptr->next) {
            ptr = ptr->next;
        } 
        ptr->next = ptr->next->next;
        if (!ptr->next->next) {
            ptr->next->next = NULL;
        } else {
            ptr->next->next->prev = ptr;
        }
        totalNodes--;
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