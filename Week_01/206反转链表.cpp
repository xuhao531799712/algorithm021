// 206 反转链表
struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

// 迭代做法
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

// 递归解法
class Solution {
 public:
  ListNode* reverseList(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode* root = reverseList(head->next);

    head->next->next = head;
    head->next = nullptr;

    return root;
  }
};
