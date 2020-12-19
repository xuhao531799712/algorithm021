// 递归解法，同时也是深度搜索
class Solution {
 public:
  int maxDepth(TreeNode* root) {
    if (!root) return 0;
    return max(maxDepth(root->left), maxDepth(root->right)) + 1;
  }
};

// 广度搜索，空间复杂度和深度搜索不是一个维度
class Solution {
 public:
  int maxDepth(TreeNode* root) {
    int res = 0;
    queue<TreeNode*> que;
    if (root) que.push(root);
    while (!que.empty()) {
      ++res;
      queue<TreeNode*> tmp;
      while (!que.empty()) {
        TreeNode* node = que.front();
        que.pop();
        if (node->left) tmp.push(node->left);
        if (node->right) tmp.push(node->right);
      }
      que = tmp;
    }
    return res;
  }
};