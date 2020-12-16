#include "Stack.cpp"

struct AdjList {
  int length;
  List *arr; // len = # of vertices; vertices = 0 ~ (# of vertices - 1)
  AdjList(int len) { length = len; arr = new List[length]; } 
  AdjList(const AdjList& src) { copy(src); }
  AdjList& operator = (const AdjList& src) { copy(src); return *this; }
  ~AdjList() { clear(); }
  void copy(const AdjList& src) {
    if (this == &src) return;
    clear();
    length = src.length;
    arr = new List[length];
    for (int i = 0; i < length; ++i) arr[i] = src.arr[i];
  }
  void clear() { delete [] arr; length = 0; }
  void add(int u, int v) { if (!arr[u].containsData(v)) arr[u].pushBack(v); }
  void remove(int u, int v) { if (arr[u].containsData(v)) arr[u].removeByData(v); }
  int getNumEl() { int tot = 0; for (int i = 0; i < length; ++i) tot += arr[i].length; return tot; }
};