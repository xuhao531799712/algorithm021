 // 使用两种方法做，先用最常用的 bfs, 再用递归版的和迭代版的 dfs

 // bfs 时间复杂度 O(n) 空间复杂度 O(n)
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        queue<TreeNode*> que;
        if (root) que.push(root);
        while (!que.empty()) {
            vector<int> vec;
            queue<TreeNode*> q2;

            while (!que.empty()) {
                TreeNode* node = que.front();
                que.pop();
                vec.push_back(node->val);

                if (node->left) q2.push(node->left);
                if (node->right) q2.push(node->right);
            }

            ans.push_back(vec);
            que = q2;
        }

        return ans;
    }
};

// 递归版 dfs 时间复杂度 O(n) 空间复杂度最大也是 O(n)
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        dfs(root, 0, ans);
        return ans;
    }

    void dfs(TreeNode* root, int level, vector<vector<int>>& ans) {
        if (!root) return ;
        while (ans.size() <= level) {
            ans.push_back(vector<int>());
        }

        ans[level].push_back(root->val);

        dfs(root->left, level + 1, ans);
        dfs(root->right, level + 1, ans);
    }
};

// 迭代版 dfs， 注意要将 level 值同时入栈 时间复杂度 O(n) 空间复杂度 O(n)
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        
        stack<pair<TreeNode*, int>> sta; // 把level同时存入栈中
        if (root) sta.push(make_pair(root, 0));

        while (!sta.empty()) {
            root = sta.top().first;
            int level = sta.top().second;
            sta.pop();

            while (ans.size() <= level) {
                ans.push_back(vector<int>());
            }

            ans[level].push_back(root->val);

            if (root->right) sta.push(make_pair(root->right, level + 1));
            if (root->left) sta.push(make_pair(root->left, level + 1));
        }

        return ans;
    }
};