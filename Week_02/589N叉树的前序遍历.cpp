// 589N叉树的前序遍历
class Solution {
public:
    vector<int> preorder(Node* root) {
        vector<int> res;
        stack<Node*> stc;
        if (root) stc.push(root);
        while (!stc.empty()) {
            root = stc.top();
            stc.pop();
            for (int i = root->children.size() - 1; i >= 0; --i) {
                if (root->children[i]) stc.push(root->children[i]);
            }
            res.push_back(root->val);
        }
        return res;
    }
};