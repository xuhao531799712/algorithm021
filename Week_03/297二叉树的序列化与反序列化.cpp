class Codec {
 public:
  // Encodes a tree to a single string.
  string serialize(TreeNode* root) {
    queue<TreeNode*> que;
    que.push(root);
    string res = "";
    while (!que.empty()) {
      queue<TreeNode*> tmp;
      while (!que.empty()) {
        TreeNode* node = que.front();
        que.pop();
        if (node) {
          tmp.push(node->left);
          tmp.push(node->right);
          res += to_string(node->val) + "_";
        } else {
          res += "n_";
        }
      }
      que = tmp;
    }
    return res;
  }

  // Decodes your encoded data to tree.
  TreeNode* deserialize(string data) {
    stringstream s(data);
    string str_node;
    queue<TreeNode*> que;
    getline(s, str_node, '_');
    TreeNode* root;
    if (str_node == "n")
      return nullptr;
    else
      root = new TreeNode(stoi(str_node));
    que.push(root);

    while (!que.empty()) {
      queue<TreeNode*> tmp;
      while (!que.empty()) {
        TreeNode* node = que.front();
        que.pop();
        if (node) {
          getline(s, str_node, '_');
          if (str_node == "n")
            node->left = nullptr;
          else {
            node->left = new TreeNode(stoi(str_node));
            tmp.push(node->left);
          }
          getline(s, str_node, '_');
          if (str_node == "n")
            node->right = nullptr;
          else {
            node->right = new TreeNode(stoi(str_node));
            tmp.push(node->right);
          }
        }
      }
      que = tmp;
    }
    return root;
  }
};