// bfs 层序遍历
class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        vector<int> ans;
        queue<TreeNode*> que;
        if (root) que.push(root);
        while (!que.empty()) {
            int maxval = INT_MIN;
            queue<TreeNode*> q2;
            while (!que.empty()) {
                root = que.front();
                que.pop();
                maxval = max(maxval, root->val);
                if (root->left) q2.push(root->left);
                if (root->right) q2.push(root->right);
            }
            ans.push_back(maxval);
            que = q2;
        }
        return ans;
    }
};

// 递归版 dfs
class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        vector<int> ans;
        dfs(root, 0, ans);
        return ans;
    }

    void dfs(TreeNode* root, int level, vector<int>& ans) {
        if (!root) return;
        if (ans.size() <= level) ans.push_back(root->val);
        else ans[level] = max(root->val, ans[level]);
        dfs (root->left, level + 1, ans);
        dfs (root->right, level + 1, ans);
    }
};

// 迭代版 dfs
class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        vector<int> ans;
        stack<pair<TreeNode*, int>> stc;
        if (root) stc.push(make_pair(root, 0));
        while (!stc.empty()) {
            root = stc.top().first;
            int level = stc.top().second;
            stc.pop();

            if (ans.size() <= level) ans.push_back(root->val);
            else ans[level] = max(root->val, ans[level]);

            if (root->right) stc.push(make_pair(root->right, level + 1));
            if (root->left) stc.push(make_pair(root->left, level + 1));
        }
    
        return ans;
    }
};
