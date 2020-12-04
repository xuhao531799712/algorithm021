// 21合并两个有序链表
// 迭代解法
class Solution {
 public:
  ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* pt = &dummy;
    while (l1 && l2) {
      if (l1->val < l2->val) {
        pt->next = l1;
        l1 = l1->next;
      } else {
        pt->next = l2;
        l2 = l2->next;
      }
      pt = pt->next;
    }
    pt->next = l1 ? l1 : l2;
    return dummy.next;
  }
};

// 递归解法
class Solution {
 public:
  ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    if (l1 && l2) {
      if (l1->val < l2->val) {
        dummy.next = l1;
        l1->next = mergeTwoLists(l1->next, l2);
      } else {
        dummy.next = l2;
        l2->next = mergeTwoLists(l2->next, l1);
      }
    } else
      dummy.next = l1 ? l1 : l2;
    return dummy.next;
  }
};