// John Park (446 88 167)

Graph cycle(Vector& vertices) {
  Set set(vertices);
  Vector uniqueVertices = set.toVec();
  int len = uniqueVertices.length;
  Graph g(len);
  for (int i = 0; i < len; ++i) g.addEdge(uniqueVertices[i], uniqueVertices[(i + 1) % len]);
  return g;
}

Graph complete(Vector& vertices) {
  Set set(vertices);
  Vector uniqueVertices = set.toVec();
  int len = uniqueVertices.length;
  Graph g(len);
  for (int i = 0; i < len; ++i)
    for (int j = 0; j < len; ++j)
      if (i != j) g.addEdge(uniqueVertices[i], uniqueVertices[j]);
  return g;
}

int randIndex(int maxIdx, int minIdx = 0) { // random index 0 ~ maxIdx; uniform random distr
  random_device rand_dev;
  mt19937 generator(rand_dev());
  uniform_int_distribution<int> distribution(minIdx, maxIdx);
  return distribution(generator);
}

Graph random(Vector& vertices, int numEdges) {
  Graph g = cycle(vertices);
  while(g.getNumEdges() < numEdges) {
    int u, v;
    do {
      u = vertices[randIndex(vertices.length - 1)];
      v = vertices[randIndex(vertices.length - 1)];
    } while (u == v);
    g.addEdge(u, v);
  }
  return g;
}

Graph initGraph(int graphType, Vector& vertices, int numEdges = -1) {
  if (graphType == Random && numEdges == -1) { 
    cout << "For random graph, need to supply number of edges" << endl; 
    exit(0); 
  }
  switch (graphType) {
    case Complete: return complete(vertices);
    case Cycle: return cycle(vertices);
    default: return random(vertices, numEdges);
  }
}