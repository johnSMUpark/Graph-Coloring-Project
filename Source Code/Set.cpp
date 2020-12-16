// John Park (446 88 167)

#include "Tree.cpp"

struct Set {
  Tree t;
  Set() { }
  Set(Vector& v) { for (int i = 0; i < v.length; ++i) t.insert(v[i]); }
  Set(const Set& src) { copy(src); }
  Set& operator = (const Set& rhs) { copy(rhs); return *this; }
  ~Set() { clear(); }
  void copy(const Set& src) { if (this == &src) return; t = src.t; }
  void add(int n) { t.insert(n); }
  void remove(int n) { t.remove(n); }
  void clear() { t.clear(); }
  bool empty() { return t.empty(); }
  bool contains(int n) { return t.contains(n); }
  int length() { return t.numNodes(); }
  Vector toVec() { return t.toVec(); }
};