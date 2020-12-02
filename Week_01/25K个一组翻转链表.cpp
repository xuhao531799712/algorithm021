// 25.K个1组翻转链表
class Solution {
 public:
  ListNode* reverseKGroup(ListNode* head, int k) {
    if (k <= 1) return head;
    ListNode dummy(0);
    dummy.next = head;
    ListNode* pre = &dummy;
    ListNode* pt = head;

    // 判断当前后k个结点满足要求
    while (regular(pt, k)) {
      ListNode* first = pt;  //保留第一个结点,用来指向最后一个结点的next
      int times = k - 1;
      ListNode* ne = pt->next;
      // while (times--) {
      //   ListNode* nene = ne->next;
      //   ne->next = pt;
      //   pt = ne;
      //   ne = nene;
      // }
      // 优化循环为for
      for (int i = 1; i < k; i++) {
        ListNode* nene = ne->next;
        ne->next = pt;
        pt = ne;
        ne = nene;
      }
      pre->next = pt;
      first->next = ne;
      pre = first;
      pt = ne;
    }
    return dummy.next;
  }

  bool regular(ListNode* head, int k) {
    bool res = (head != nullptr);
    for (int i = 0; res && i < k - 1; i++) {
      head = head->next;
      if (!head) res = false;
    }
    return res;
  }
};