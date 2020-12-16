#include "Queue.cpp"

struct Stack {
  List l;
  Stack() { }
  Stack(const Stack& src) { l = src.l; }
  Stack& operator = (const Stack& rhs) { l = rhs.l; return *this; }
  ~Stack() { }
  List::Node *push(int n) { return l.pushFront(n); }
  void pop() { l.popFront(); }
  int front() { return l.front(); }
  bool empty() { return l.length == 0; }
  int length() { return l.length; }
  Vector toVec() { return l.toVec(); }
};