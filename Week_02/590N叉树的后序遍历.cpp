// 590N叉树的后序遍历
// 递归解法
class Solution {
public:
    vector<int> postorder(Node* root) {
        vector<int> res;
        helper(root, res);
        return res;
    }

    void helper(Node* root, vector<int> &res) {
        if (!root) return ;
        for (auto child : root->children) {
            helper(child, res);
        }
        res.push_back(root->val);
    }
};

// 迭代方法
class Solution {
public:
    vector<int> postorder(Node* root) {
        stack<Node*> stc;
        vector<int> res;
        if (root) stc.push(root);
        while (!stc.empty()) {
            root = stc.top();
            stc.pop();
            res.push_back(root->val);
            for (auto child : root->children) {
                if (child) stc.push(child);
            }
        }
        reverse(res.begin(), res.end());
        return res;
    }
};