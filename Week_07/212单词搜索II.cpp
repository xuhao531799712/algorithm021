class Solution {
public:
    struct TrieNode {
        bool is_end;
        TrieNode* child[26];
        TrieNode () {
            is_end = false;
            memset(child, 0, sizeof(child));
        }
    };
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        int m = board.size(), n = board[0].size();
        vector<string> ans;

        // 构建字典树
        TrieNode *root = new TrieNode(), *cur;
        for (auto word : words) {
            cur = root;
            for (auto c : word) {
                if (!cur->child[c - 'a']) cur->child[c - 'a'] = new TrieNode();
                cur = cur->child[c - 'a'];
            }
            cur->is_end = true;
        }

        // dfs遍历网格
        int maxnums = words.size(); // 最大能找到的单词数，达到就停止 // 一部分剪枝
        int count = 0;
        string tmp = "";
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                boarddfs(board, i, j, tmp, ans, root, count, maxnums);
            }
        }

        return ans;
    }

    void boarddfs(vector<vector<char>>& board, int i, int j, string &tmp, vector<string> &ans, TrieNode* cur, int& count, int& maxnums) {
        // cur表示从节点开始搜索 board[i][j] 的字符
        if (count >= maxnums || i < 0 || i >= board.size() || j < 0 || j >= board[0].size() || board[i][j] == '#') return;

        char c = board[i][j];
        if (cur->child[c - 'a']) {
            tmp.push_back(c);
            board[i][j] = '#';
            cur = cur->child[c - 'a']; // 位置要在这里，不然每次进下面for循环里的dfs，都会判断一次并加ans
            if (cur->is_end) {
                ans.push_back(tmp);
                cur->is_end = false; // 每个单词只加一次，在这里判重更快 还可以通过将叶子节点删除的做法
                ++count;
            }
            for (int k = 0; k < action.size(); ++k) {
                boarddfs(board, i + action[k].first, j + action[k].second, tmp, ans, cur, count, maxnums);
            }
            tmp.pop_back();
            board[i][j] = c;
        }
    }

    vector<pair<int, int>> action = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
};

// 本题所做优化：
// 1. 在dfs过程中，不会每次对string tmp 在字典树中进行从头开始的查找，因为过去这个单词过去查过的字符都已经查过一遍了，只需要对最新的字符进行查找
//    所以在递归过程中还会传递一个 TrieNode* cur 指针，直接在当前位置继续向下查找
// 2. 为了避免最后的结果数组中含有相同的单词，在将一个单词加入结果数组后，会同时将它在字典树中删除，采用的方法是将 is_end 标记为 false
//    而不是采用先用 set 存储结果再转为 vector
// 3. 一开始记录一个 maxnums 值来表示最多可以在 board 中找到的单词数，达到之后就停止搜索，算是一种剪枝方式