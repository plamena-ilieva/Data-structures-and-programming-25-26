class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

size_t heightByVertex(const Node* root) {
    if (root == nullptr) return 0;
    size_t depth = 0;
    for (const Node* child : root->children) 
      depth = max(depth, heightByVertex(child));
    return 1 + depth;
}

size_t heightByEdges(const Node* root) {
  return heightByVertex(root) - 1;
}

