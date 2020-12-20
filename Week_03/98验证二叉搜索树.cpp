// 原始解法
class Solution {
 public:
  bool isValidBST(TreeNode* root) {
    if (!root) return true;

    if (root->left && root->val <= getbig(root->left) ||
        root->right && root->val >= getsmall(root->right))
      return false;

    return isValidBST(root->left) && isValidBST(root->right);
  }

  int getbig(TreeNode* root) {
    while (root->right) root = root->right;
    return root->val;
  }

  int getsmall(TreeNode* root) {
    while (root->left) root = root->left;
    return root->val;
  }
};

// 为了缩短时间，引入一个全局变量，在某处不符合二叉搜索树规则时，停掉所有递归
class Solution {
 public:
  bool isValidBST(TreeNode* root) {
    if (!root) return true;

    if (root->left && root->val <= getbig(root->left) ||
        root->right && root->val >= getsmall(root->right)) {
      flag = false;  // 此处赋值，令其他分支的递归也结束
      return false;
    }
    return flag && isValidBST(root->left) && isValidBST(root->right);
  }

  int getbig(TreeNode* root) {
    while (root->right) root = root->right;
    return root->val;
  }

  int getsmall(TreeNode* root) {
    while (root->left) root = root->left;
    return root->val;
  }

 private:
  bool flag = true;
};

// 以上的解法，在向下找寻最大最小值时明显是会有很多重复步骤的，这就像斐波那契数列题目中的递归方法
// 那么要化简这些重复步骤，要么是用缓存（用空间换时间，这种方法用的空间较大），要么是用动态规范的方法
// 那么动态规划的方法，就是不去找当前节点的左最大和右最小值，而将自己作为限制值往下传，这样遍历一遍就可以
class Solution {
 public:
  bool helper(long lower_bound, long bigger_bound, TreeNode* root) {
    if (!root) return true;
    if (root->val >= bigger_bound || root->val <= lower_bound) {
      return false;
    }
    return helper(lower_bound, root->val, root->left) &&
           helper(root->val, bigger_bound, root->right);
  }

  bool isValidBST(TreeNode* root) { return helper(LONG_MIN, LONG_MAX, root); }
};

// 二叉搜索树的一个特性就是中序遍历是递增序列
// 以下使用递归实现中序遍历
class Solution {
 public:
  long left = LONG_MIN;
  bool isValidBST(TreeNode* root) {
    // 写一个中序遍历
    if (!root) return true;
    if (!isValidBST(root->left)) return false;
    if (root->val <= left) return false;
    left = root->val;
    return isValidBST(root->right);
  }
};
// 以下使用迭代实现中序遍历
class Solution {
 public:
  bool isValidBST(TreeNode* root) {
    stack<TreeNode*> stc;
    long minline = LONG_MIN;

    while (!stc.empty() || root) {
      while (root) {
        stc.push(root);
        root = root->left;
      }
      root = stc.top();
      stc.pop();

      //处理本节点
      if (root->val <= minline) return false;
      minline = root->val;
      //继续后续
      root = root->right;
    }
    return true;
  }
};
