class Solution {
 public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    // 最近公共祖先，满足就是两者分别在其左右子树上，如果在一边，那么就去另一边，如果自己是两者之一，就是自己
    if (root == nullptr || root == p || root == q) return root;
    TreeNode *left = lowestCommonAncestor(root->left, p, q),
             *right = lowestCommonAncestor(root->right, p, q);
    if (left && right) return root;
    if (left)
      return left;
    else if (right)
      return right;
    else
      return nullptr;
  }
};