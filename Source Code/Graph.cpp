#include "AdjList.cpp"

struct Graph {
  AdjList *adj;
  Graph(int len) { adj = new AdjList(len); }
  Graph(const Graph& src) { copy(src); } 
  Graph& operator = (const Graph& rhs) { copy(rhs); return *this; }
  ~Graph() { delete adj; }
  void copy(const Graph& src) { if (this != &src) *adj = *src.adj; }
  void addEdge(int u, int v) { adj->add(u, v); adj->add(v, u); }
  void removeEdge(int u, int v) { adj->remove(u, v); adj->remove(v, u); }
  int getNumVertices() { return adj->length; }
  int getNumEdges() { return adj->getNumEl() / 2; }
};