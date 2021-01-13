class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode* node = root;
        for (auto c : word) {
            if (!node->next[c - 'a']) node->next[c - 'a'] = new TrieNode();
            node = node->next[c - 'a'];
        }
        node->is_end = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode* node = root;
        for (auto c : word) {
            if (!node->next[c - 'a']) return false;
            node = node->next[c - 'a'];
        }
        return node->is_end;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (auto c : prefix) {
            if (!node->next[c - 'a']) return false;
            node = node->next[c - 'a'];
        }
        return true;
    }

private:
    struct TrieNode {
        bool is_end;
        TrieNode* next[26];
        TrieNode() {
            is_end = false;
            memset(next, 0, sizeof(next));
        }
    };
    TrieNode* root;
};