//429N叉树的层序遍历
class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> res;
        queue<Node*> que;
        if (root) que.push(root);
        while(!que.empty()) {
            queue<Node*> q2;
            vector<int> vec;
            while (!que.empty()) {
                root = que.front();
                que.pop();
                vec.push_back(root->val);
                for (auto child : root->children) {
                    if (child) q2.push(child);
                }
            }
            res.push_back(vec);
            que = q2;
        }
        return res;
    }
};