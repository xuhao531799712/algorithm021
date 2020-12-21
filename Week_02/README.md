# 二叉树的三种遍历方式

中序遍历、前序遍历、后序遍历，都是即可以用递归法进行，也可以用迭代法进行的。

其中，中序遍历和前序遍历的模板基本一样，只是在访问节点处不同。其模板如下：

```cpp
// 迭代法实现
return_type preorderTraversal(TreeNode* root) {
    stack<TreeNode*> stc;

    while (root || !stc.empty()) {
        if (root) {
            stc.push(root);
            // 此处进行节点访问为前序遍历
            root = root->left;
        } else {
            root = stc.top();
            stc.pop();
            // 此处进行节点访问为中序遍历
            root = root->right;
        }
    }
    return vec;
}
```

```cpp
// 递归法实现
return_type preorderTraversal(TreeNode* root) {
    helper(root);
    return return_value;
}

void helper(TreeNode* root) {
    if (!root) return ;
    // 此处进行节点访问为前序遍历
    helper(root->left, vec);
    // 此处进行节点访问为中序遍历
    helper(root->right, vec);
    // 此处进行节点访问为后序遍历
}
```

而后序遍历可以使用变样的前序遍历来实现，利用前序为 中-左-右，而后序为 左-右-中 的顺序。将前序访问的顺序变为 中-右-左，再将结果反转就可以。如下模板：

```cpp
// 迭代法实现
return_type preorderTraversal(TreeNode* root) {
    stack<TreeNode*> stc;

    while (root || !stc.empty()) {
        if (root) {
            stc.push(root);
            // 此处进行节点访问为前序遍历
            root = root->right;
        } else {
            root = stc.top();
            stc.pop();
            root = root->left;
        }
    }
    return reverse(return_value);
}
```

但以上模板，其实并不是真正意义上的后序遍历，没有按照后序遍历的顺序访问内存，所以属于邪门歪道。正统的后序遍历迭代模板如下：

```cpp
return_type postorderTraversal(TreeNode* root) {
    stack<TreeNode*> stc;
    TreeNode* pre = nullptr;
    while (root || !stc.empty()) {
        if (root) {
            stc.push(root);
            root = root->left;
        } else {
            root = stc.top();
            stc.pop();
            if (!root->right || root->right == pre) {
                // 此处进行节点访问
                pre = root; // 标记访问过的右节点
                root = nullptr;
            } else {
                // 发现当前节点的右节点还没访问，那么需要将本节点再次入栈，切换到右节点
                stc.push(root);
                root = root->right;
            }
        }
    }
    return res;
}
```
