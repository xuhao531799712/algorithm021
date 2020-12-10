// 145二叉树的后序遍历
// 递归解法
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        helper(root, res);
        return res;
    }

    void helper(TreeNode* node, vector<int> &res) {
        if (!node) return ;
        helper(node->left, res);
        helper(node->right, res);
        res.push_back(node->val);
    }
};

// 迭代方法
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        stack<TreeNode*> stc;
        vector<int> res;
        TreeNode* pre = nullptr;
        while (root || !stc.empty()) {
            while (root) {
                stc.push(root);
                root = root->left;
            }
            root = stc.top();
            stc.pop();
            if (!root->right || root->right == pre) {
                res.push_back(root->val);
                pre = root;
                root = nullptr;
            } else {
                stc.push(root);
                root = root->right;
            }
        }
        return res;
    }
};

//另一种迭代，因为根节点先打印更方便，所以采用逆序打印的方式，然后反转输出数组，此种做法适合后序遍历，应用于前序遍历时不需要最后的翻转
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        stack<TreeNode*> stc;
        vector<int> res;
        if (root) stc.push(root);
        while (!stc.empty()) {
            root = stc.top();
            stc.pop();
            res.push_back(root->val);
            if (root->left) stc.push(root->left);
            if (root->right) stc.push(root->right);
        }
        reverse(res.begin(), res.end());
        return res;
    }
};