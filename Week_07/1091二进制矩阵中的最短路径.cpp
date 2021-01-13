// 当可以用bfs和dfs且题目是求最小值时，bfs要好于dfs
// 首先实现常规 bfs 算法
class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        // 异常条件判断
        if (grid[0][0] == 1 ||grid[n - 1][n - 1] == 1) return -1;

        queue<pair<int, int>> que;
        unordered_set<int> visited; // pos = i * n + j ;
        que.push(make_pair(0, 0));
        visited.insert(0);
        int count = 0;

        while(!que.empty()) {
            count++;
            queue<pair<int, int>> tmp;
            while(!que.empty()) {
                int i = que.front().first, j = que.front().second;
                que.pop();
                if (i == n - 1 && j == n - 1) return count;
                for (auto dir : dirs) {
                    int new_i = i + dir.first, new_j = j + dir.second;
                    if (new_i < 0 || new_i >= n || new_j < 0 || new_j >= n || grid[new_i][new_j] == 1 || visited.count(new_i * n + new_j)) continue;
                    tmp.push(make_pair(new_i, new_j));
                    visited.insert(new_i * n + new_j);
                }
            }
            que = tmp;
        }
        return -1;
    }

    vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
};


// A* 搜索
struct node {
    int i;
    int j;
    int steps;
    node (int _i, int _j, int _s) : i(_i), j(_j), steps(_s) {}
};

struct cmp{
    bool operator()(node &a, node &b) {
        return min(a.i, a.j) + 4 * a.steps > min(b.i, b.j) + 4 * b.steps;
        // 点坐标x,y距终点的较大值+4*step
    }
};

class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        // 异常条件判断
        if (grid[0][0] == 1 ||grid[n - 1][n - 1] == 1) return -1;

        priority_queue<node, vector<node>, cmp> pq;

        unordered_set<int> visited; // pos = i * n + j ;
        pq.push(node(0, 0, 1));
        visited.insert(0);

        while(!pq.empty()) {
            int i = pq.top().i, j = pq.top().j, steps = pq.top().steps;
            pq.pop();
            if (i == n - 1 && j == n - 1) return steps;
            for (auto dir : dirs) {
                int new_i = i + dir.first, new_j = j + dir.second;
                if (new_i < 0 || new_i >= n || new_j < 0 || new_j >= n || grid[new_i][new_j] == 1 || visited.count(new_i * n + new_j)) continue;
                pq.push(node(new_i, new_j, steps + 1));
                visited.insert(new_i * n + new_j);
            }
        }
        return -1;
    }

    vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
};