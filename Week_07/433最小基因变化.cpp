// class Solution {
// public:
//     int minMutation(string start, string end, vector<string>& bank) {
//         // 首先简单的 bfs 实现，因为本题是求最小，所以 bfs 好于 dfs
//         unordered_set<string> mm(bank.begin(), bank.end());
//         if (!mm.count(end)) return -1;
//         unordered_set<string> visited;
//         visited.insert(start);

//         queue<string> que;
//         que.push(start);
//         int count = 0;

//         while (!que.empty()) {
//             queue<string> tmp;
//             while (!que.empty()) {
//                 string str = que.front();
//                 que.pop();
//                 if (str == end) return count;
//                 for (int i = 0; i < 8; ++i) {
//                     char t = str[i];
//                     for (auto b : bb) {
//                         if (b == t) continue;
//                         str[i] = b;
//                         if (!visited.count(str) && mm.count(str)) {
//                             tmp.push(str);
//                             visited.insert(str);
//                         }
//                     }
//                     str[i] = t;
//                 }
//             }
//             que = tmp;
//             ++count;
//         }

//         return -1;
//     }

//     vector<char> bb = {'A', 'C', 'G', 'T'};
// };


class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank) {
        // 然后是双向 bfs 实现，
        unordered_set<string> mm(bank.begin(), bank.end());
        if (!mm.count(end)) return -1;

        if (mm.count(start)) mm.erase(start);
        mm.erase(end);

        unordered_set<string> frovisited, bacvisited, *hpset, *tpset;
        frovisited.insert(start);
        bacvisited.insert(end);

        int count = 0;

        while (!frovisited.empty() && !bacvisited.empty() ) {
            if (frovisited.size() <= bacvisited.size()) {
                hpset = &frovisited;
                tpset = &bacvisited;
            } else {
                tpset = &frovisited;
                hpset = &bacvisited;
            }
            ++count;
            unordered_set<string> tmp;
            for (auto str : *hpset) {
                // if (tpset->count(str)) return count;
                for (int i = 0; i < 8; ++i) {
                    char t = str[i];
                    for (auto b : bb) {
                        if (b == t) continue;
                        str[i] = b;

                        // 注意，判断是否首尾搜索相接应该和 mm.erase 在一个域内
                        // 因为，接触的情况下，mm 肯定已经删除掉了，因为它被 insert 到了 bacvisited 里
                        if (tpset->count(str)) return count;
                        if (mm.count(str)) {
                            tmp.insert(str);
                            mm.erase(str);
                        }
                    }
                    str[i] = t;
                }
            }

            hpset->swap(tmp);
        }

        return -1;
    }

    vector<char> bb = {'A', 'C', 'G', 'T'};
};