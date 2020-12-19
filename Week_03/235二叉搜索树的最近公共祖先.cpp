// 递归解法
class Solution {
 public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (p->val > q->val) swap(p, q);
    if (!root || root == p || root == q) return root;
    if (root->val > p->val && root->val < q->val) return root;
    if (root->val < p->val)
      return lowestCommonAncestor(root->right, p, q);
    else
      return lowestCommonAncestor(root->left, p, q);
  }
};

// 迭代解法
class Solution {
 public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (p->val > q->val) swap(p, q);
    TreeNode* fa = root;
    while (true) {
      if (fa->val > q->val)
        fa = fa->left;
      else if (fa->val < p->val)
        fa = fa->right;
      else
        return fa;
    }
    return nullptr;
  }
};