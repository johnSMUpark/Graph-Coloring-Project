// John Park (446 88 167)

#include "Vector.cpp"

struct Tree { // AVL Tree for fast read & write
  struct Node {
    int data, height;
    Node *left, *right;
    Node(const int& d, Node *l = nullptr, Node *r = nullptr, int h = 0) {
      data = d; left = l; right = r; height = h;
    }
    Node(int&& d, Node *l = nullptr, Node *r = nullptr, int h = 0) {
      data = move(d); left = l; right = r; height = h;
    }
  };
  Node *root;
  Tree() { root = nullptr; }
  Tree(const Tree& t) { root = copy(t.root); }
  Tree& operator = (const Tree& rhs) {
    Tree copy = rhs;
    std::swap(*this, copy);
    return *this;
  }
  ~Tree() { clear(); }
  void insert(int& d) { if (!contains(d)) insertHelper(d, root); }
  int& retrieve(int& d) { return contains(d) ? getNode(d)->data : d; }
  void update(int& d) { getNode(d)->data = d; }
  void remove(const int& d) { if (contains(d)) removeHelper(d, root); }
  void clear() { clearHelper(root); }
  bool empty() const { return root == nullptr; }
  bool contains(const int& d) { return containsHelper(d, root); }
  int numNodes() { return empty() ? 0 : numNodesHelper(root); }
  Vector toVec() { Vector v; toVecHelper(root, v); return v; }
private:
  Node *getNode(int& d) { return getNodeHelper(d, root); } // get node by val
  void insertHelper(const int& d, Node*& t) {
    if (t == nullptr) t = new Node(d);
    else if (t->data > d) insertHelper(d, t->left);
    else if (t->data < d) insertHelper(d, t->right);
    balance(t);
  }
  void insertHelper(int&& d, Node*& t) {
    if (t == nullptr) t = new Node(move(d));
    else if (d < t->data) insertHelper(move(d), t->left);
    else if (t->data < d) insertHelper(move(d), t->right);
    balance(t);
  }
  void removeHelper(const int& d, Node*& t) {
    if (t == nullptr) return;
    if (t->data > d) removeHelper(d, t->left);
    else if (t->data < d) removeHelper(d, t->right);
    else if (t->left != nullptr && t->right != nullptr) {
      t->data = privFindMin(t->right)->data;
      removeHelper(t->data, t->right);
    }
    else {
      Node *oldNode = t;
      t = t->left != nullptr ? t->left : t->right;
      delete oldNode;
    }
    balance(t);
  }
  void balance(Node*& t) {
    if (t == nullptr) return;
    else if (height(t->left) - height(t->right) == 2) {
      if (height(t->left->left) >= height(t->left->right)) rotateWithLeftChild(t);
      else doubleWithLeftChild(t);
    }
    else if (height(t->right) - height(t->left) == 2) {
      if (height(t->right->right) >= height(t->right->left)) rotateWithRightChild(t);
      else doubleWithRightChild(t);
    }
    t->height = max(height(t->left), height(t->right)) + 1;
  }
  bool containsHelper(const int& d, Node *t) {
    if (t == nullptr) return false;
    else if (t->data > d) return containsHelper(d, t->left);
    else if (t->data < d) return containsHelper(d, t->right);
    else return true;
  }
  void clearHelper(Node*& t) {
    if (t != nullptr) {
      clearHelper(t->left);
      clearHelper(t->right);
      delete t;
    }
    t = nullptr;
  }
  int height(Node *t) const { return t == nullptr ? -1 : t->height; }
  int max(int lhs, int rhs) const { return lhs > rhs ? lhs : rhs; }
  void rotateWithLeftChild(Node*& k2) {
    Node *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;  // update
    k1->height = max(height(k1->left), k2->height) + 1;         // height
    k2 = k1;                                                    // root
  }
  void rotateWithRightChild(Node*& k1) {
    Node *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;  // update
    k2->height = max(height(k2->right), k1->height) + 1;        // height &
    k1 = k2;                                                    // root
  }
  void doubleWithLeftChild(Node*& k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
  }
  void doubleWithRightChild(Node*& k1) {
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
  }
  Node *privFindMin(Node *t) const { // return node w/ min data
    if (t == nullptr) return nullptr;
    else if (t->left == nullptr) return t;
    else return privFindMin(t->left);
  }
  Node *privFindMax(Node *t) const { // return node w/ max data
    if (t != nullptr) while (t->right != nullptr) t = t->right;
    return t;
  }
  Node *copy(Node *t) const {
    return t == nullptr ? nullptr : new Node(t->data, copy(t->left), copy(t->right), t->height);
  }
  Node *getNodeHelper(int& d, Node*& t) {
    if (t->data == d) return t;
    return t->data > d ? getNodeHelper(d, t->left) : getNodeHelper(d, t->right);
  }
  int numNodesHelper(Node*& t) {
    int nodeCount = 1;
    if (t->left!=nullptr) nodeCount += numNodesHelper(t->left);
    if (t->right!=nullptr) nodeCount += numNodesHelper(t->right);
    return nodeCount;
  }
  void toVecHelper(Node *t, Vector& v) {
    if (t == nullptr) return;
    toVecHelper(t->left, v);
    v.pushBack(t->data);
    toVecHelper(t->right, v);
  }
};
