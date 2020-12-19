// 递归，深度优先
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root) return 0;
        else if (!root->left && !root->right) return 1;
        else if (!root->left) return minDepth(root->right) + 1;
        else if (!root->right) return minDepth(root->left) + 1;
        else return min(minDepth(root->right), minDepth(root->left)) + 1;
    }
};

// 迭代，广度优先
class Solution {
public:
    int minDepth(TreeNode* root) {
        int depth=0;
        queue<TreeNode*> que;
        if(root) que.push(root);
        while(!que.empty())
        {
            depth++;
            queue<TreeNode*> que_tmp;
            while(!que.empty())
            {
                TreeNode* point=que.front();
                que.pop();
                if((!point->left)&&(!point->right)) return depth;
                if(point->left) que_tmp.push(point->left);
                if(point->right) que_tmp.push(point->right);
            }
            que=que_tmp;
        }
        return depth;
    }
};