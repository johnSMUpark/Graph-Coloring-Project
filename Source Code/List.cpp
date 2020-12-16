#include "Set.cpp"

struct List {
  struct Node {
    int data;
    Node *prev, *next;
    Node(int d) { data = d; prev = next = nullptr; }
  };
  Node *head, *tail;
  int length;
  List() { head = tail = nullptr; length = 0; }
  List(const List& src) { copy(src); }
  List& operator = (const List& rhs) { copy(rhs); return *this; }
  ~List() { clear(); }
  void copy(const List& src) {
    if (this == &src) return;
    clear();
    Node *curr = src.head;
    while (curr != nullptr) {
      pushBack(curr->data);
      curr = curr->next;
    }
  }
  Node *pushBack(int n) {
    Node *newNode = new Node(n);
    if (tail == nullptr) head = tail = newNode;
    else {
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
    }
    ++length;
    return newNode;
  }
  Node *pushFront(int n) {
    Node *newNode = new Node(n);
    if (head == nullptr) head = tail = newNode;
    else {
      head->prev = newNode;
      newNode->next = head;
      head = newNode;
    }
    ++length;
    return newNode;
  }
  void removeByNode(Node *nodeToDel) {
    if (length == 0) return; // if length == 0, do nothing
    if (nodeToDel == head) { // delete head
      popFront();
      return;
    }
    if (nodeToDel == tail) { // delete tail
      popBack();
      return;
    }
    Node *curr = head;             // start from head
    while (curr != nullptr) {      // until end of list
      if (curr == nodeToDel) {     // if curr's adr == nodeToDel's adr
        Node *before = curr->prev; // get curr's before
        Node *after = curr->next;  // get curr's after
        before->next = after;      // link after and
        after->prev = before;      // after
        delete curr;               // delete curr
        --length;                  // update length
        break;                     // break
      }
      curr = curr->next; // move to next node
    }
  }
  void removeByData(int n) {
    if (length == 0) return;
    if (head->data == n) {
      popFront();
      return;
    }
    if (tail->data == n) {
      popBack();
      return;
    }
    Node *curr = head;
    while (curr != nullptr) {
      if (curr->data == n) {
        Node *before = curr->prev;
        Node *after = curr->next;
        before->next = after;
        after->prev = before;
        delete curr;
        --length;
        break;
      }
      curr = curr->next;
    }
  }
  int front() { return head->data; }
  void popFront() {
    if (length == 0) return; // if length == 0, nothing to delete
    Node *nodeToDel = head;  // get node to delete
    head = head->next;       // update head
    delete nodeToDel;        // delete node to delete
    --length;                // update length
    if (length > 0) head->prev = nullptr; // if there's length, update new head's prev
    else tail = nullptr;     // if length == 0, update tail
  }
  void popBack() {
    if (length == 0) return;
    Node *nodeToDel = tail;
    tail = tail->prev;
    delete nodeToDel;
    --length;
    if (length > 0) tail->next = nullptr;
    else head = nullptr;
  }
  bool containsData(int n) { // does list contain node with certain data?
    Node *curr = head;
    while (curr != nullptr) {
      if (curr->data == n) return true;
      curr = curr->next;
    }
    return false;
  }
  bool containsNode(Node *node) {
    Node *curr = head;
    while (curr != nullptr) {
      if (curr == node) return true;
      curr = curr->next;
    }
    return false;
  }
  void clear() {
    while (head != nullptr) { // start from head and keep deleting head
      Node *headToDel = head;
      head = head->next;
      delete headToDel;
    }
    length = 0;     // update length
    tail = nullptr; // update tail
  }
  int& operator [] (int idx) {
    if (length == 0) { // corner case 1: list is empty
      cout << "List is empty so returning length" << endl;
      return length;
    }
    if (idx >= length) { // corner case 2: index out of range
      cout << "Index out of range. Returning length" << endl;
      return length;
    }
    Node *curr = head;
    for (int i = 0; i <= idx; ++i) {   // traverse nodes till node at desired index is reached
      if (i == idx) return curr->data; // return that node's data
      curr = curr->next;
    }
    cout << "Returning length" << endl; // corner case 3: for whatever reason, 
    return length;                      // data access via index didn't work
  }
  Vector toVec() {
    Vector vec(length);
    Node *curr = head;
    while (curr != nullptr) {
      vec.pushBack(curr->data);
      curr = curr->next;
    }
    return vec;
  }
};
