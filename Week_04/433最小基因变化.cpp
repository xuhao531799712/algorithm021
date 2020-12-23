// dfs 解法，几个注意要点
// 1. 为了加快查询速度，需要将 bank 做成一个哈希表
// 2. 防止遍历过程中出现环状造成无穷递归，需要做一个 visited 哈希表，用来记录每个 dfs 中访问过的位置。注意此处不可以通过限制索引值递增来达到这个效果，会得到错误的结果
// 3. 进行剪枝，当当前的深度大于已得的最小值时，直接退出 dfs，进行下一分支。同时在一开始将 minsteps 定义为 bank 的长度相关来加大限制，但这里会和 visited 表的作用有重复。
class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank) {
        if (start.size() != end.size() || !start.size() || !end.size()) return -1;

        bankset = unordered_set<string>(bank.begin(), bank.end());
        if (!bankset.count(end)) return -1;
        minsteps = bank.size() + 2;
        dfs(start, end, 0);
        return minsteps == bank.size() + 2 ? -1 : minsteps;
    }

    void dfs(string& now, string& end, int steps) {
        if (now == end) {
            minsteps = min(minsteps, steps);
            return ;
        }
        if (steps >= minsteps || visited[now]) return ;
        visited[now] = 1;
        for (int i = 0; i < now.size(); ++i) {
            char tmp = now[i];
            for (auto g : gene) {
                if (tmp == g) continue;
                now[i] = g;
                if(bankset.find(now) != bankset.end()) {
                    dfs(now, end, steps + 1);
                }
            }
            now[i] = tmp;
        }
        visited[now] = 0;
    }

private:
    vector<char> gene = {'A', 'C', 'G', 'T'};
    unordered_set<string> bankset;
    unordered_map<string, int> visited;
    int minsteps ;
};

// bfs 解法
class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank) {
        if (start.size() != end.size() || !start.size() || !end.size()) return -1;

        vector<char> gene = {'A', 'C', 'G', 'T'};
        unordered_set<string> visited;
        int steps = 0;
        queue<string> que;
        unordered_set<string> bankset(bank.begin(),bank.end());
        if (!bankset.count(end)) return -1;
        que.push(start);

        while (!que.empty()) {
            queue<string> q2;
            while (!que.empty()) {
                string now = que.front();
                que.pop();

                if (now == end) return steps;
                if (visited.count(now)) continue;
                visited.insert(now);

                for (int i = 0; i < now.size(); ++i) {
                    char tmp = now[i];
                    for (auto g : gene) {
                        if (tmp == g) continue;
                        now[i] = g;
                        if(bankset.find(now) != bankset.end()) {
                            q2.push(now);
                        }
                    }
                    now[i] = tmp;
                }
            }
            ++steps;
            que = q2;
        }
        
        return -1;
    } 
};