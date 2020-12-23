// 单向 bfs
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        unordered_set<string> visited; 
        visited.insert(beginWord);
        int count = 1;

        queue<string> que;
        que.push(beginWord);
        while (!que.empty()) {
            queue<string> q2;
            while (!que.empty()) {
                string word = que.front();
                que.pop();
                if (word == endWord) return count;
                for (int i = 0; i < word.size(); ++i) {
                    char tmp = word[i];
                    for (char c = 'a'; c <= 'z'; ++c) {
                        word[i] = c;
                        if (wordSet.count(word) && !visited.count(word)) {
                            q2.push(word);
                            visited.insert(word);
                        }
                    }
                    word[i] = tmp;
                }
            }
            que = q2;
            ++count;
        }

        return 0;
    }
};

// 双向 bfs
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordDict(wordList.begin(), wordList.end());
        if (wordDict.find(endWord) == wordDict.end()){
            return 0;
        }
        unordered_set<string> beginSet{beginWord}, endSet{endWord};
        int step = 2;
        while (!beginSet.empty()) {
            unordered_set<string> tempSet;
            for (auto word : beginSet) {
                wordDict.erase(word);
            }
            for (auto word : beginSet) {
                for (int i = 0; i < word.size(); ++i){
                    char chartmp = word[i];
                    for (char c = 'a'; c <= 'z'; ++c){
                        word[i] = c;
                        if (wordDict.find(word) == wordDict.end()){
                            continue;
                        }
                        if (endSet.find(word) != endSet.end()){
                            return step;
                        }
                        tempSet.insert(word);
                    }
                    word[i] = chartmp;
                }
            }
            if (tempSet.size() < endSet.size()){
                beginSet = tempSet;
            } else {
                beginSet = endSet;
                endSet = tempSet;
            }
            ++step;
        }
        return 0;
    }
};