// 迭代解法
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root) {
            TreeNode* tmp = root->left;
            root->left = invertTree(root->right);
            root->right = invertTree(tmp);
        } 
        return root;
    }
};

// 迭代解法
// 遍历所有的节点，把其左右节点交换
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        queue<TreeNode*> que;
        if(root) que.push(root);
        while(!que.empty()) {
            TreeNode* node = que.front();
            que.pop();
            swap(node->left, node->right);
            if(node->left) que.push(node->left);
            if(node->right) que.push(node->right);
        }

        return root;
    }
};