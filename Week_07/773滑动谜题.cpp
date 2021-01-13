class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        string end = "123450";
        string start = "";
        for (auto line : board) {
            for (auto x : line) {
                start += to_string(x);
            }
        }

        unordered_set<string> visited;
        visited.insert(start);
        queue<string> que;
        que.push(start);
        int count = 0;

        while (!que.empty()) {
            queue<string> tmp;
            while (!que.empty()) {
                string str = que.front();
                que.pop();
                if (str == end) return count;
                int pos = get_zero_pos(str);
                for (auto p : change[pos]) {
                    swap(str[pos], str[p]);
                    if (!visited.count(str)) {
                        tmp.push(str);
                        visited.insert(str);
                    }
                    swap(str[pos], str[p]);
                }
            }
            que = tmp;
            ++count;
        }
        return -1;
    }

    int get_zero_pos(string& str) {
        for (int i = 0; i < 6; ++i) {
            if (str[i] == '0') return i;
        }
        return 0;
    }

    // 交换位置数组
    vector<vector<int>> change = {
            {1, 3},
            {0, 2, 4},
            {1, 5},
            {0, 4},
            {1, 3, 5},
            {2, 4}
    };
};



// 接下来是 A* 算法
// 在做题的过程中发现这个要点：
//  在优先队列中进行排序时，一定要用加上当前的 steps 到优先级计算函数中，不然不会得到最优解，
//  但是即使加入了，也可能不是最优解，但一定足够优，可以尝试加大 steps 的比重来变得更优，但是会减慢速度
// 例如 rank = steps * n + heuristic(now) 加大 n 的数值

// 估价函数
int f_distance(string& str)
{
    int res = 0;
    for (int i = 0; i < 6; ++i) {
        if (str[i] == '0') continue;
        int val = str[i] - '1';
        res += abs(i / 3 - val / 3) + abs(i % 3 - val % 3);
    }
    return res;
}

struct node {
    string str;
    int pos;
    int rank;
    int steps;
    node (string s, int p, int ste) : str(s), pos(p), steps(ste) {
        rank = f_distance(str) + steps;
    }

    // 此处运算符重载必须是const函数
    bool operator<(const node& b) const {
        return this->rank < b.rank;
    }
    bool operator>(const node& b) const {
        return this->rank > b.rank;
    }
    bool operator==(const node& b) const {
        return this->str == b.str;
    }
};

class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        string end = "123450";
        string start = "";
        int pp;
        for (auto line : board) {
            for (auto x : line) {
                if (x == 0) pp = start.size();
                start += to_string(x);
            }
        }
        node begin = node(start, pp, 0);

        unordered_set<string> visited;
        visited.insert(start);

        // 因为优先队列的底层是数组，数组的排布是按 greater 来的，然而队首在尾部，队尾在头部
        priority_queue<node, vector<node>, greater<node> > que;
        que.push(begin);

        while (!que.empty()) {
            string str = que.top().str;
            int pos = que.top().pos;
            int steps = que.top().steps;
            que.pop();
            if (str == end) return steps;
            for (auto p : change[pos]) {
                swap(str[pos], str[p]);
                if (!visited.count(str) ) {
                    que.push(node(str, p, steps + 1));
                    visited.insert(str);
                }
                swap(str[pos], str[p]);
            }
        }
        return -1;
    }

    // 交换位置数组
    vector<vector<int>> change = {
            {1, 3},
            {0, 2, 4},
            {1, 5},
            {0, 4},
            {1, 3, 5},
            {2, 4}
    };
};