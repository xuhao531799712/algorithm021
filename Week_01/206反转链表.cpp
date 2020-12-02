// 206 反转链表
struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
 public:
  ListNode* reverseList(ListNode* head) {
    ListNode *pt = head, *pre = NULL;
    while (pt) {
      ListNode* tmp = pt->next;
      pt->next = pre;
      pre = pt;
      pt = tmp;
    }
    return pre;
  }
};