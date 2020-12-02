// 24.两两交换链表中的结点
//迭代解法
class Solution {
 public:
  ListNode* swapPairs(ListNode* head) {
    ListNode dummy(0);
    dummy.next = head;
    ListNode* pre = &dummy;
    ListNode* pt = head;
    while (pt && pt->next) {
      ListNode* tmp = pt->next;
      pt->next = tmp->next;
      tmp->next = pt;
      pre->next = tmp;
      pre = pt;
      pt = pt->next;
    }
    return dummy.next;
  }
};
//递归解法
class Solution {
 public:
  ListNode* swapPairs(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode* tmp = head->next;
    head->next = tmp->next;
    tmp->next = head;
    head->next = swapPairs(head->next);

    return tmp;
  }
};