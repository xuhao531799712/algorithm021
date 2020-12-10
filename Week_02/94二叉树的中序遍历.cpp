// 94二叉树的中序遍历
// 迭代方法
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> stc;
        vector<int> res;
        while (root || !stc.empty()) {
            while (root) {
                stc.push(root);
                root = root->left;
            }
            root = stc.top();
            stc.pop();
            res.push_back(root->val);
            root = root->right;
        }
        return res;
    }
};
// 递归方法
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        helper(root, res);
        return res;
    }

    void helper(TreeNode* node, vector<int> &res) {
        if (!node) return ;
        helper(node->left, res);
        res.push_back(node->val);
        helper(node->right, res);
    }
};