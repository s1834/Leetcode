class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(head == NULL) {
            return head;
        }

        ListNode* ptr = head;
        int temp = k;
        while(temp && ptr != NULL) {
            ptr = ptr->next;
            temp--;
        }
        if(temp != 0) {
            return head;
        }


        ListNode* prev = NULL, *cur = head, *nxt = NULL;
        temp = 0;
        while(temp < k && cur != NULL) {
            nxt = cur->next;
            cur->next = prev;
            prev = cur;
            cur = nxt;
            temp++;
        }
     
        if(nxt != NULL) {
            head->next = reverseKGroup(nxt, k);
        }
        return prev;
    }
};