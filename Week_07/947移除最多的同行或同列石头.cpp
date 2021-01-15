// 核心是建立起各个石头的连接，知道这个石头连着哪个石头
// 然后使用dfs或使用并查集来解决

// 并查集类定义
class unionfind {
public :
    unionfind(int size) {
        count = size;
        uni.resize(size);
        for (int i = 0; i < size; ++i) {
            uni[i] = i;
        }
    }

    int find(int i) {
        while (uni[i] != i) {
            uni[i] = uni[uni[i]];
            i = uni[i];
        }
        return i;
    }

    void connect(int i, int j) {
        int fi = find(i), fj = find(j);
        if (fi != fj) {
            --count;
            uni[fi] = fj;
        }
    }

    int count;
    vector<int> uni;
};

class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();
        vector<vector<int>> edge(n); // 存储连接关系的数组

        // 建立石头间的连接可以使用暴力遍历的方法 时间复杂度 O(n^2)
//        for (int i = 0; i < n; ++i) {
//            for (int j = 0; j < n; ++j) {
//                if (stones[i][0] == stones[j][0] || stones[i][1] == stones[j][1])
//                    edge[i].push_back(j);
//            }
//        }
        // 建立石头间的连接也可以使用哈希表优化 时间复杂度 O(n)
        unordered_map<int, vector<int>> mm; // 存各个行和列里的石头，其中行直接用 i 做索引，列使用 i+10001 做索引，因为行数列数最多为 10000
        for (int i = 0; i < n; ++i) {
            mm[stones[i][0]].push_back(i);
            mm[stones[i][1] + 10001].push_back(i);
        }
        for (auto& vv : mm) {
            int size = vv.second.size();
            for (int i = 1; i < size; i++) {
                edge[vv.second[i - 1]].push_back(vv.second[i]);
                edge[vv.second[i]].push_back(vv.second[i - 1]);
            }
        }

        // 然后进行 dfs 求解
//        vector<int> visited(n, 0);
//        int res = 0;
//        for (int i = 0; i < n; ++i) {
//            if (!visited[i]) {
//                dfs(visited, edge, i);
//                ++res;
//            }
//        }
//        return n - res;

        // 也可以构建并查集来求解
        unionfind stonesunion(n);
        for (int i = 0; i < n; ++i) {
            for (auto j : edge[i]) {
                stonesunion.connect(i, j);
            }
        }
        return n - stonesunion.count;

    }

    // 深度优先搜索函数定义
    void dfs(vector<int>& visited, vector<vector<int>>& edge, int i) {
        visited[i] = 1;
        for (auto j : edge[i]) {
            if (!visited[j]) {
                dfs(visited, edge, j);
            }
        }
    }
};