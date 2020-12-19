class Solution {
 public:
  unordered_map<int, int> inorder_map;  //建立中序遍历中的索引
  TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    for (int i = 0; i < inorder.size(); ++i) {
      inorder_map[inorder[i]] = i;
    }
    return helper(preorder, inorder, 0, preorder.size() - 1, 0,
                  preorder.size() - 1);
  }

  TreeNode* helper(vector<int>& preorder, vector<int>& inorder, int preleft,
                   int preright, int inleft, int inright) {
    if (preleft > preright) return nullptr;
    TreeNode* root = new TreeNode(preorder[preleft]);
    int left_num = inorder_map[preorder[preleft]] - inleft;
    root->left = helper(preorder, inorder, preleft + 1, preleft + left_num,
                        inleft, inleft + left_num - 1);
    root->right = helper(preorder, inorder, preleft + left_num + 1, preright,
                         inleft + left_num + 1, inright);
    return root;
  }
};