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

同时，前序遍历还有更简介的写法，这在N叉树中就尤为重要，而且N叉树不存在迭代版的中序遍历，只有前序遍历和后序遍历，且迭代版后序遍历也无法写出，迭代版只可以通过对前序遍历进行修改来得到。

以下代码当然也可以用在二叉树前序遍历，注意入栈的顺序，是左右相反的。

```cpp
vector<int> preorder(Node* root) {
    vector<int> res;
    stack<Node*> stc;
    if (root) stc.push(root);
    while (!stc.empty()) {
        root = stc.top();
        stc.pop();
        res.push_back(root->val);
        for (int i = root->children.size() - 1; i >= 0; --i) { // 注意此处遍历顺序
            if (root->children[i]) stc.push(root->children[i]);
        }
    }
    return res;
}
```

## 层序遍历

各个树的层序遍历都要用到队列queue，不可以用栈，也就不能使用递归来实现了。

## 堆或者优先队列

注意，使用c++创建堆的时候：```priority_queue<int, vector<int>, greater<int>>```创建的是小顶堆，而```priority_queue<int, vector<int>, less<int>>```创建的是大顶堆。

且，底层使用的是 vector 容器的时候，使用 pop() 操作，会把 top() 元素与队尾元素交换，然后再进行队列的维护，也就是采用不断的 pop() 操作，可以得到一个升序或者降序的 vector。

## topK 问题

两种解法：优先队列、快速排序变形--快速选择

优先队列分析：
由于使用了一个大小为 k 的堆，空间复杂度为 O(k)；
入堆和出堆操作的时间复杂度均为 O(logk)，每个元素都需要进行一次入堆操作，故算法的时间复杂度为 O(nlogk)。

快速排序分析：
空间复杂度 O(1)，不需要额外空间。
时间复杂度的分析方法和快速排序类似。由于快速选择只需要递归一边的数组，时间复杂度小于快速排序，期望时间复杂度为 O(n)，最坏情况下的时间复杂度为 O(n^2)。

两种方法的优劣性比较
在面试中，另一个常常问的问题就是这两种方法有何优劣。看起来分治法的快速选择算法的时间、空间复杂度都优于使用堆的方法，但是要注意到快速选择算法的几点局限性：

第一，算法需要修改原数组，如果原数组不能修改的话，还需要拷贝一份数组，空间复杂度就上去了。

第二，算法需要保存所有的数据。如果把数据看成输入流的话，使用堆的方法是来一个处理一个，不需要保存数据，只需要保存 k 个元素的最大堆。而快速选择的方法需要先保存下来所有的数据，再运行算法。当数据量非常大的时候，甚至内存都放不下的时候，就麻烦了。所以当数据量大的时候还是用基于堆的方法比较好。
