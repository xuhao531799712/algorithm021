class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        pair<int, int> dir = make_pair(0, 1);
        pair<int, int> pos = make_pair(0, 0);
        int res = 0;

        set<pair<int, int>> obstaclesSet;
        for (vector<int> obstacle: obstacles)
            obstaclesSet.insert(make_pair(obstacle[0], obstacle[1]));

        for (auto command :commands) {
            if (command < 0) getNextDircetion(dir, command);
            else {
                for (int i = 0; i < command; ++i) {
                    int new_i = dir.first + pos.first, new_j = dir.second + pos.second;
                    if (obstaclesSet.count(make_pair(new_i, new_j))) break;
                    pos.first = new_i;
                    pos.second = new_j;
                    res = max(res, new_i * new_i + new_j * new_j);
                }
            }
        }

        return res;
    }


    void getNextDircetion(pair<int, int>& dir, int change) {
    // 获取下一个方向，通过引用传递
        if (dir == make_pair(0, 1)) {
            if (change == -1) dir = make_pair(1, 0);
            else dir = make_pair(-1, 0);
        } else if (dir == make_pair(0, -1)) {
            if (change == -1) dir = make_pair(-1, 0);
            else dir = make_pair(1, 0);
        } else if (dir == make_pair(1, 0)) {
            if (change == -1) dir = make_pair(0, -1);
            else dir = make_pair(0, 1);
        } else {
            if (change == -1) dir = make_pair(0, 1);
            else dir = make_pair(0, -1);
        }
    }
};