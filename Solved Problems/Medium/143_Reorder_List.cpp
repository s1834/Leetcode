/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    void reorderList(ListNode* head) {
        stack<ListNode*> st;
        ListNode* ptr1 = head;
        int count = 0;
        while(ptr1) {
            st.push(ptr1);
            ptr1 = ptr1->next;
            count++;
        }

        ptr1 = head;
        ListNode* ptr2 = head->next;
        
        while(st.size() > count / 2) {
            ptr1->next = st.top();
            st.top()->next = ptr2;
            st.pop();
            ptr1 = ptr2;
            ptr2 = ptr1->next;
        }
        if(count % 2) {
            ptr1 = ptr2;   
        } 
        ptr1->next = NULL;
    }
};