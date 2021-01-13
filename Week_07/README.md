# 第七周笔记

## 字典树模板

```cpp
class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode* cur = root;
        for (auto c : word) {
            if (!cur->next[c - 'a']) cur->next[c - 'a'] = new TrieNode(); 
            cur = cur->next[c - 'a'];
        }
        cur->is_end = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode* cur = root;
        for (auto c : word) {
            if (!cur->next[c - 'a']) return false; 
            cur = cur->next[c - 'a'];
        }
        return cur->is_end;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode* cur = root;
        for (auto c : prefix) {
            if (!cur->next[c - 'a']) return false; 
            cur = cur->next[c - 'a'];
        }
        return true;
    }

private:
    struct TrieNode {
        TrieNode* next[26]; // 26 个小写字母所以用 26 大小的数组，如果还有其他值就扩充，最大为 128 的所有char
        bool is_end; // 标记以本结点结尾的字符串是否存在
        TrieNode () : is_end(false) {
            memset(next, 0, sizeof(next));
        }
    };
    TrieNode* root;
};
```

注意，类内定义一下结点类，更加清晰和合理。每个结点类有两个数据成员：指向下一个字符的指针、字符串存在标识符。

字典树适合单词数庞大的情况下，一次性建立所有单词的集合。有些类似于哈希表的作用，但字典树还可以查询前缀也就是“start with”功能，这一点要优于哈希表。

## 并查集

代码模板

```cpp
class UnionFind {
public:
    UnionFind (int _size) {
        parent.resize(_size);
        count = _size;
        for (int i = 0; i < _size; ++i)
            parent[i] = i;
    }

    int find(int i) {
        while (parent[i] != i) {
            parent[i] = parent[pro[i]]; // 进行一定的路径压缩
            i = parent[i];
        }
        return i;
    }

    void connect(int i, int j) {
        int fa_i = find(pro, i);
        int fa_j = find(pro, j);
        if (fa_i == fa_j) return;
        parent[fa_j] = fa_i;
        --count;
    }
private:
    vector<int> parent;
    int count;
};
```

其中 count 成员用来记录并查集中不相连的组的数量。

并查集的空间复杂度是 O(n)， 带路径压缩后，均摊下来，find() 的时间复杂度接近于 O(1), 而 connect() 里面进行两次 find() 操作，所以其时间复杂度也接近于 O(1)。

实际，严谨的数学推理上，当前实现的并查集时间复杂度是 O(log* n)， 比 O(log n) 要快，但比 O(1) 要慢一些，但是接近于 O(1)。

## 搜索进阶

之前练习过的暴力遍历、bfs 和 dfs 还算是比较朴素的搜索方法，在此之上还可以进行优化。优化方式有3种：

    1. 不重复。即尽可能把过程中会重复计算的值保存下来，使得程序不尽兴重复计算。

    2. 剪枝。即尽可能早得进行剪枝，进行提前判断当前的分支是否含有结果值，通过判断来剪掉多余的支路，来提高效率。

    3. * 双向 BFS。通过从首尾同时向彼此进行 BFS，来降低搜索空间，提高效率
       * 启发式搜索，即 A* 搜索。对 BFS 中的队列改为优先队列，优先遍历最可能是最优解的结点。

比较速度的话： 双向A* > 单向A*(曼哈顿距离) > 双向BFS > 单向A*(汉明距离) > BFS。

注意，A* 中的估价函数计算简单更好，但是要考虑其估价的参考度有多高*。A* 算法在导航应用中是用来高效地计算出次优解的，而在算法题当中是要计算最优解，所以估价函数的设计尤为重要。

在做题的过程中发现：

    1. 在优先队列中进行排序时，一定要用加上当前的 steps 到优先级计算函数中，不然不会得到最优解。
    
    2. 但是即使加入了当前的 steps，也可能不是最优解，但一定比不加入更优，可以尝试加大 steps 的比重来变得更优，但是会减慢遍历速度
    
    3. 例如 rank = steps * n + heuristic(now) 加大 n 的数值

当当前 steps 的比重在估价函数中越大时，优先队列就越接近于原来的普通队列，正确性就会提高，但是遍历效率就会降低，在这之间要取一个平衡才可以。

## 平衡二叉树相关

二叉搜索树的操作当中，删除节点操作过程算稍微复杂，代码可能不会写得特别容易，但是逻辑要知道。 在平衡二叉树中要删除节点时有四种情况：

    1.无左子树，无右子树。直接删除即可
    
    2.无左子树，有右子树。删除后把右子树连接在当前位置
    
    3.有左子树，无右子树。删除后把左子树连接在当前位置
    
    4.既有左子树，也有右子树。最复杂——把左子树的最大节点或者右子树的最小节点替换到此处。如果抽掉的节点依然不是叶子节点，那么要递归再调用（此时递归调用就只会有1、2、3三种情况，而不会再有4这种情况了）。

删除时分情况讨论即可。

## 要掌握的树

    ### 2-3树
    
    ### AVL树
    
    ### B树
    
    ### 红黑树

## AVL 树

AVL树的核心是带有平衡因子，且平衡因子的范围只能是 -1、0、1 三种，代表左右子树的深度差。

因为二叉搜索树的搜索效率只和深度有关，所以平衡因子只用深度来算，而不包括结点数。

为了保持平衡，有四种基础操作：左旋、右旋、左右旋、右左旋。后面两种即前两种的搭配，先后旋转两次。四种分别对应右右子树、左左子树、左右子树、右左子树。理解原理，并且知道在旋转过程中，各个节点的左右子树怎么进行转移。

AVL树的缺点：
    
    1.需要记录平衡因子，为 int 型，多花内存；

    2.调整次数频繁，因为它的要求很严格。

## 红黑树

那么为了取一个平衡，保证一定的平衡性又不要调整过于频繁，出现了其他的树。

读操作非常多，写操作非常少的情况下，用AVL树，比如数据库，微博等，此时可以保证最好的查询效率；
写操作非常多或者插入和查询操作一半一半用红黑树比如map，set等，可以不那么耗费时间，又保证一定的平衡性能。

然后红黑树是一种近似平衡二叉树，其有五条条件，而这五条条件可以保证任何一个结点的左右子树的高度差小于两倍：

    1. 每个结点要么是红色要么是黑丝。

    2. 根结点是黑色。

    3. 每个叶子结点是黑色。注意此处的叶子结点是指在最下面且为Null的结点，并不是之前的那种叶子结点。

    4. 不能有相邻接的两个红色结点。

    5. 从任一一结点到其他叶子的所有路径都包含相同数据的黑色结点。

前三条记住就行了，4、5两条就可以保证“任何一个结点的左右子树的高度差小于两倍”这个性质，因为黑色数量相同了，而红色不能连续，那么两个子树差距最大的情况就是一方全是黑结点，另一方有相同数目的黑结点，再加上和黑色结点数目相同的红色结点，此时相差两倍。

