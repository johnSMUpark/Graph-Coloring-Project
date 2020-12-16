#include "List.cpp"

struct Queue {
  List l;
  Queue() { }
  Queue(const Queue& src) { l = src.l; }
  Queue& operator = (const Queue& rhs) { l = rhs.l; return *this; }
  ~Queue() { }
  void push(int n) { l.pushBack(n); }
  void pop() { l.popFront(); }
  int front() { return l.front(); }
  bool empty() { return l.length == 0; }
};