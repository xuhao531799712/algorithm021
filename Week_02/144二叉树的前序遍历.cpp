// 144二叉树的前序遍历
 // 递归解法
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        helper(root, res);
        return res;
    }
    void helper(TreeNode* node, vector<int> &res) {
        if (!node) return ;
        res.push_back(node->val);
        helper(node->left, res);
        helper(node->right, res);
    }
};

//迭代解法
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*> stc;
        vector<int> res;
        while (root || !stc.empty()) {
            while (root) {
                res.push_back(root->val);
                stc.push(root);
                root = root->left;
            }
            root = stc.top();
            stc.pop();
            root = root->right;
        }
        return res;
    }
};