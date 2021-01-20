struct listnode {
    int key;
    int value;
    listnode* pre;
    listnode* next;
    listnode(int k, int v) : key(k), value(v) {
        pre = next = nullptr;
    }
    listnode(int k, int v, listnode* p, listnode* n) : key(k), value(v), pre(p), next(n) {}
};

class LRUCache {
public:
    LRUCache(int capacity) : cap(capacity), count(0) {
        head->next = tail;
        tail->pre = head;
    }

    int get(int key) {
        if (!mm.count(key)) return -1;
        listnode* ptr = mm[key];
        // 移动到头部
        movetohead(ptr);

        return ptr->value;
    }

    void put(int key, int value) {
        if (mm.count(key)) {
            listnode* ptr = mm[key];
            ptr->value = value;
            movetohead(ptr);
        }
        else {
            listnode* cur = new listnode(key, value, head, head->next);
            mm[key] = cur;
            head->next = cur;
            cur->next->pre = cur;
            ++count;

            if (count <= cap) return;
            // 开始删除最后一个结点
            deletelast();
            --count;
        }
    }

private:
    void movetohead(listnode* ptr) {
        ptr->pre->next = ptr->next;
        ptr->next->pre = ptr->pre;
        ptr->next = head->next;
        ptr->next->pre = ptr;
        ptr->pre = head;
        head->next = ptr;
    }

    void deletelast() {
        listnode* last = tail->pre;
        if (last == head) return;
        tail->pre = last->pre;
        last->pre->next = tail;
        mm.erase(last->key);
        delete last;
    }


    int cap;
    int count;
    listnode *head = new listnode(-1, -1); // 存近期刚访问的元素
    listnode *tail = new listnode(-1, -1); // 存最久没访问的元素
    unordered_map<int, listnode*> mm;
};

// 核心点为使用哈希表来使 get 和 put 方法达到 O(1) 的时间复杂度