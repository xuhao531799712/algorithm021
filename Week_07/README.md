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

## 2-3树

2-3树是一种绝对平衡的树，任意节点到它所有的叶子节点的深度都是相等的。

其优点为：它没有高度差也不会有平衡因子，没有平衡因子就不会调整旋转操作，所以2-3树不需要靠频繁的旋转来维持平衡，使用其它方法，调整频率大大降低，且不影响查询效率。

### 什么是2-3树

2-3树是具有以下特点的树：

    1. 对于树中每一个结点，它有 1 或者 2 个关键码。
       
    2. 当有 1 个关键码的时候，这个结点的子树会有两个。
       
    3. 当这个结点的关键码有 2 个的时候，这个结点的子树是3个。
       
    4. 它的所有叶子点都在树的同一层，所以绝对的平衡，从根结点搜索到任一叶子结点的深度都一样。

除了上面外，它还有一些类似二叉排序树的性质：

    1. 任意结点的左子树的值小于这个节点第一个关键码(或唯一关键码)的值

    2. 中间子树的值均大于第一个关键码,中间子树的所有结点的值小于第二个关键码的值

    3. 右子树的值均大于第二个关键码(或唯一关键码)的值

    4. 进行删除和添加操作的时候 要进行特殊处理

### 2-3树的搜索、插入、删除操作

#### 搜索

同二叉树排序树的查找算法，要查找的值与结点的第一个关键码对比，小于这个结点的第一个关键码则进入左子树进行查找，大于第一个关键码且小于第二个关键码（如果有）则进入中间的子树，大于第二个关键码则进入右子树。

然后递归，对每个结点都运行上面的算法。

### 插入

插入的核心概括是： 

1. 按照搜索将新增结点直接插入其应在位置，此时如果其所在位置有两个结点，则操作结束；

2. 如果其所在位置现在有三个节点，那么需要进行拆分，保留最大和最小的两个关键码，将中值关键码向上层提升
   
3. 接2，若此时上层结点为2个关键码，本结点若为上层结点的左子树就将最大的的关键码拆分出来作为上层节点的中子树；若为右子树，就将最小的关键码拆分出来作为中子树；当然，若上层原来为2个结点，且本分支已经是中子树了，就不用再改了。

4. 接2，若此时上层结点为3个关键码，则还要再上层，对本层而言还需要进行拆分，就不好描述了。

具体见网址进行复习 ： https://blog.csdn.net/qq_35794278/article/details/80316402

递归向上，最高可以成为新的根节点。

* 同时，2-3树是最简单的 B树，即 3 阶B数

## B树

英文名是 B-tree ，有的翻译成 B-树，是不对的，就应该是B树。出现“B-树”的地方都是B树，二者是一个东西。

B树属于多叉树又名平衡多路查找树（查找路径不只两个），数据库索引技术里大量使用者B树和B+树的数据结构。其是完全平衡二叉树。

### B树定义

B树是具有以下特点的树：若为 m 阶

    1. 对于树中每一个结点，它有最多 m 个子树。
       
    2. 每个结点的子树个数比结点内的关键码数量多 1。
       
    3. 树的根结点可以有最少 2 个子树，其他非叶子结点可以有最少 ┌m/2┐ 个子树，(┌┐向上取整) 。
        * 即根节点的子树数量为 [2, m], 其他非叶子结点的子树数量为 [┌m/2┐, m]。其内部关键码数量比子树数量少 1。
       
    4. 它的所有叶子点都在树的同一层，所以绝对的平衡，并且叶子结点不带信息（可以看作是外部结点或查找失败的结点，实际上这些结点不存在，指向这些结点的指针为空）。 

    5. 所有子树与父树的关键码大小关系满足搜索树的要求。即大小关系为 （P0，K1，P1，K2，…，Kn，Pn）,其中：Ki（i=1,2,…,n）为关键码，且Ki<Ki+1（注：ki是真实数据，存放在线性表当中，且从左至右升序排列）
     Pi 为指向儿子的指针(i=0,1,…,n)，且指针Pi-1 所指子树中所有结点的关键码均小于Ki (i=1,2,…,n)，Pn 所指子树中所有结点的关键码均大于Kn。（注：每个ki数据两旁各安放了一个指针，即Pi-1和Pi，左边的子树数据统统小于ki，右边子树的数据统统大于ki）（注：总体来看指针数量比数据数量多1）

### B树结点定义

```cpp
struct B_TNode{
    int numOfKey;//关键字个数
    B_TNode *parent;//指向父结点的指针
    B_TNode **childPtr;//指向子树的指针，childPtr[0]...childPtr[numOfKey]
    int *key;//指向关键字数组的指针
};
```

### B树面试题一例

问题： 一棵含有N个总关键字数的m阶的B树的最大高度是多少?

答曰：log_ceil(m/2) (N+1)/2 + 1 

    要求最大高度，那么就要令每个结点的关键字个数最少才可以令高度最大。要注意叶子结点的个数不算在 N 内。

    除了根结点和叶子结点外，其他内部结点的关键字个数最少为 ┌m/2┐-1，而后各个层的具体数字为：

    根至少有两个孩子，因此第 2 层至少有两个节点；

    除根和叶子外，其它结点至少有 ┌m/2┐ 个孩子；

    在第 3 层至少有 2 *（┌m/2┐）个结点；

    在第 4 层至少有 2 *（┌m/2┐^2）个结点。

    在第 l 层至少有 2 *（┌m/2┐（l-2））个结点。

    以上除了第一层只有一个关键字外，其他层的关键字个数都为 (结点数 * (┌m/2┐-1))，假设第 l 层为树的最后一层(非叶子结点层）
    
    可得 N = 1 + (┌m/2┐-1) * ( 2 + 2 * (┌m/2┐-1) + 2 * (┌m/2┐-1)^2 + ... + 2 * (┌m/2┐-2)^(l-2) )

    根据求和公式可以解得 l = log┌m/2┐((N+1)/2 )+1。
    
    所以当B树包含 N 个关键字时，B树的最大高度为 l =  log┌m/2┐((N+1)/2 )+1。

## B+树

### B+树定义

B+-tree：是应文件系统所需而产生的一种B-tree的变形树。

一棵m阶的B+树和m阶的B树的异同点在于：

    1.有n棵子树的结点中含有n个关键字； (此处颇有争议，B+树到底是与B树n棵子树有n-1个关键字保持一致，还是不一致。就目前查的资料来看，两种实现都可以，mySQL使用的是 n 对应 n 的方式实现)

    2.所有数据地址必须要到叶子节点才能获取到。所以每次数据查询的次数都一样； (而B 树的叶子节点并没有包括全部需要查找的信息)

    3.所有的叶子结点中包含了全部关键字的信息，及指向含有这些关键字记录的指针，且叶子结点本身依关键字的大小自小而大的顺序链接，且左边结尾数据都会保存右边节点开始数据的指针，叶子结点层表现为一个链表。

    4.所有的非终端结点可以看成是索引部分，结点中仅含有其子树根结点中最大（或最小）关键字。这使得B+树每个非叶子节点所能保存的关键字大大增加。 (而B树的非终结点也包含需要查找的有效信息)

### B+树的搜索方式

    1.可以循着叶子结点链进行顺序搜索，方便查询区间数据。

    2.另一种搜索是从根结点开始，进行自顶向下，直至叶结点，适合数据的随机搜索。

    3.先根据2查询到区间的最小值叶子结点，再进行叶子结点链的顺序搜索来获取区间数据。(实际1应该是这么做的)

### 与B树比较

B+树的优点为：

    1.B+树的层级更少：相较于B树B+每个非叶子节点存储的关键字数更多，树的层级更少所以查询数据更快；
    
    2.B+树查询速度更稳定：B+所有关键字数据地址都存在叶子节点上，所以每次查找的次数都相同所以查询速度要比B树更稳定;
    
    3.B+树天然具备排序功能：B+树所有的叶子节点数据构成了一个有序链表，在查询大小区间的数据时候更方便，数据紧密性很高，缓存的命中率也会比B树高。
    
    4.B+树全节点遍历更快：B+树遍历整棵树只需要遍历所有的叶子节点即可，而不需要像B树一样需要对每一层进行遍历，这有利于数据库做全表扫描。

B树相对于B+树的优点是：
    
    如果经常访问的数据离根节点很近，而B树的非叶子节点本身存有关键字其数据的地址，所以这种数据检索的时候会要比B+树快。

## 查找树总结

动态查找树主要有：二叉查找树（Binary Search Tree），平衡二叉查找树（Balanced Binary Search Tree），红黑树(Red-Black Tree )，B-tree/B+-tree/ B*-tree (B~Tree)。

前三者是典型的二叉查找树结构，其查找的时间复杂度O(log2N)与树的深度相关，那么降低树的深度自然会提高查找效率。所以 B-tree/B+-tree/ B*-tree (B~Tree) 就比前三者搜索效率要高。

实际场景中，因为磁盘的操作费时费资源，如果过于频繁的多次查找势必效率低下。那么如何提高效率，即如何避免磁盘过于频繁的多次查找呢？根据磁盘查找存取的次数往往由树的高度所决定，所以，通过某种较好的树结构减少树的结构尽量减少树的高度，那么便能有效减少磁盘查找存取的次数。

几种树的应用场景如下：

    AVL树: 最早的平衡二叉树之一。应用相对其他数据结构比较少。windows 对进程地址空间的管理用到了 AVL 树。
    
    红黑树: 平衡二叉树，工业界应用广泛的平衡搜索树，C++ 的 STL 中的如 map、set、multimap 都是用红黑树实现的，还有 Java 的 TreeMap。
    
    B/B+树: 用在磁盘文件组织，数据索引和数据库索引，需要大量查询和插入操作的应用。
    
    Trie树(字典树): 用在统计和排序大量字符串，如自动机。

##待补充

对各个树的查询、插入、删除操作原理要理解记住