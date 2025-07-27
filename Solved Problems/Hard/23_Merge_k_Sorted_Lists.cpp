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
 
struct CompareListNode {
    bool operator()(const ListNode* a, const ListNode* b) const {
        return a->val > b->val;
    }
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, CompareListNode> pq;
        int n = lists.size();
        if(n == 0) return NULL;
        for(int i = 0; i < n; i++) {
            ListNode* ptr = lists[i];
            while(ptr) {
                pq.push(ptr);
                ptr = ptr->next;
            }
        }

        if(pq.size() == 0) return NULL;

        ListNode* ans = new ListNode(pq.top()->val);
        ListNode* head = ans;
        pq.pop();
        while(!pq.empty()) {
            ListNode* temp = new ListNode(pq.top()->val);
            ans->next = temp;
            ans = temp;
            pq.pop();
        }
        
        return head;
    }
};

/*
We are given k sorted linked lists, we can use a priority queue to merge them into one sorted linked list.
1) We first push all the nodes of all the linked lists into a priority queue.
2) Then we pop the top element of the priority queue and add it to the new linked list.
3) We repeat this process until the priority queue is empty.
4) Finally, we return the head of the new linked list.

ans as priority queue greater<ListNode*> dosent directly give us the minimum value, so we have to use a custom comparator to compare the values of the nodes.
we use const to prevent us from modifying the nodes, we are just comparing their values.
*/