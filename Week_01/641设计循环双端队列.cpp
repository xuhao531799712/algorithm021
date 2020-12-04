// 641设计循环双端队列
// 方法一：双栈实现
class MyCircularDeque {
 public:
  /** Initialize your data structure here. Set the size of the deque to be k. */
  MyCircularDeque(int k) {
    size = k;
    while (!fro.empty()) fro.pop();
    while (!las.empty()) las.pop();
  }

  /** Adds an item at the front of Deque. Return true if the operation is
   * successful. */
  bool insertFront(int value) {
    if (fro.size() + las.size() >= size) return false;
    fro.push(value);
    return true;
  }

  /** Adds an item at the rear of Deque. Return true if the operation is
   * successful. */
  bool insertLast(int value) {
    if (fro.size() + las.size() >= size) return false;
    las.push(value);
    return true;
  }

  /** Deletes an item from the front of Deque. Return true if the operation is
   * successful. */
  bool deleteFront() {
    if (fro.size()) {
      fro.pop();
      return true;
    } else {
      while (!las.empty()) {
        fro.push(las.top());
        las.pop();
      }
      if (fro.size()) {
        fro.pop();
        return true;
      } else
        return false;
    }
  }

  /** Deletes an item from the rear of Deque. Return true if the operation is
   * successful. */
  bool deleteLast() {
    if (las.size()) {
      las.pop();
      return true;
    } else {
      while (!fro.empty()) {
        las.push(fro.top());
        fro.pop();
      }
      if (las.size()) {
        las.pop();
        return true;
      } else
        return false;
    }
  }

  /** Get the front item from the deque. */
  int getFront() {
    if (isEmpty()) return -1;
    if (fro.size())
      return fro.top();
    else {
      while (!las.empty()) {
        fro.push(las.top());
        las.pop();
      }
      return fro.top();
    }
  }

  /** Get the last item from the deque. */
  int getRear() {
    if (isEmpty()) return -1;
    if (las.size())
      return las.top();
    else {
      while (!fro.empty()) {
        las.push(fro.top());
        fro.pop();
      }
      return las.top();
    }
  }

  /** Checks whether the circular deque is empty or not. */
  bool isEmpty() { return fro.empty() && las.empty(); }

  /** Checks whether the circular deque is full or not. */
  bool isFull() { return fro.size() + las.size() == size; }

 private:
  stack<int> fro;
  stack<int> las;
  int size;
};

// 方法二：环状数组实现
class MyCircularDeque {
 public:
  /** Initialize your data structure here. Set the size of the deque to be k. */
  MyCircularDeque(int k) {
    capacity = k + 1;
    data.resize(capacity, 0);
    front = 0;
    last = 0;
    // 判定条件： front == last 则对列为空， last + 1 == front 则对列满
  }

  /** Adds an item at the front of Deque. Return true if the operation is
   * successful. */
  bool insertFront(int value) {
    if (isFull()) return false;
    front = (front - 1 + capacity) % capacity;
    data[front] = value;
    return true;
  }

  /** Adds an item at the rear of Deque. Return true if the operation is
   * successful. */
  bool insertLast(int value) {
    if (isFull()) return false;
    data[last] = value;
    last = (last + 1) % capacity;
    return true;
  }

  /** Deletes an item from the front of Deque. Return true if the operation is
   * successful. */
  bool deleteFront() {
    if (isEmpty()) return false;
    front = (front + 1) % capacity;
    return true;
  }

  /** Deletes an item from the rear of Deque. Return true if the operation is
   * successful. */
  bool deleteLast() {
    if (isEmpty()) return false;
    last = (last - 1 + capacity) % capacity;
    return true;
  }

  /** Get the front item from the deque. */
  int getFront() {
    if (isEmpty()) return -1;
    return data[front];
  }

  /** Get the last item from the deque. */
  int getRear() {
    if (isEmpty()) return -1;
    return data[(last - 1 + capacity) % capacity];
  }

  /** Checks whether the circular deque is empty or not. */
  bool isEmpty() { return last == front; }

  /** Checks whether the circular deque is full or not. */
  bool isFull() { return (last + 1) % capacity == front; }

 private:
  int front, last;
  vector<int> data;
  int capacity;
};

// 方法三：双向链表实现
struct _listnode {
  _listnode* pre;
  _listnode* next;
  int value;
  _listnode() : pre(nullptr), next(nullptr), value(0) {}
  _listnode(int _value) : pre(nullptr), next(nullptr), value(_value) {}
  _listnode(int _value, _listnode* _pre, _listnode* _next)
      : pre(_pre), next(_next), value(_value) {}
};

class MyCircularDeque {
 public:
  /** Initialize your data structure here. Set the size of the deque to be k. */
  MyCircularDeque(int k) : cap(k), used(0) {
    head.next = &tail;
    tail.pre = &head;
    // 判定条件： front == last 则对列为空， last + 1 == front 则对列满
  }

  /** Adds an item at the front of Deque. Return true if the operation is
   * successful. */
  bool insertFront(int value) {
    if (isFull()) return false;
    _listnode* tmp = head.next;
    head.next = new _listnode(value, &head, tmp);
    tmp->pre = head.next;
    used++;
    return true;
  }

  /** Adds an item at the rear of Deque. Return true if the operation is
   * successful. */
  bool insertLast(int value) {
    if (isFull()) return false;
    _listnode* tmp = tail.pre;
    tail.pre = new _listnode(value, tmp, &tail);
    tmp->next = tail.pre;
    used++;
    return true;
  }

  /** Deletes an item from the front of Deque. Return true if the operation is
   * successful. */
  bool deleteFront() {
    if (isEmpty()) return false;
    _listnode* tmp = head.next;
    head.next = tmp->next;
    tmp->next->pre = &head;
    delete tmp;
    used--;
    return true;
  }

  /** Deletes an item from the rear of Deque. Return true if the operation is
   * successful. */
  bool deleteLast() {
    if (isEmpty()) return false;
    _listnode* tmp = tail.pre;
    tail.pre = tmp->pre;
    tmp->pre->next = &tail;
    delete tmp;
    used--;
    return true;
  }

  /** Get the front item from the deque. */
  int getFront() {
    if (isEmpty()) return -1;
    return head.next->value;
  }

  /** Get the last item from the deque. */
  int getRear() {
    if (isEmpty()) return -1;
    return tail.pre->value;
  }

  /** Checks whether the circular deque is empty or not. */
  bool isEmpty() { return used == 0; }

  /** Checks whether the circular deque is full or not. */
  bool isFull() { return used == cap; }

 private:
  int cap, used;
  // 此处使用两个实体对像来代表头尾，这样更好操作
  _listnode head, tail;
};
