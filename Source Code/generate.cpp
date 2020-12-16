// distributionType Uniform, Skewed, Normal
// graphType Complete, Cycle, Random
// orderType SL, SODL, RAND, INC, BFS, DFS
// density = 1, 2, 3, 4, 5, 6, 7, 8, 9 (only needed when graphType is Random)
void graphColorOrderWrite(int distributionType, int graphType, int orderType, int density = -1, int numVertices = NUM_VERTICES) {
  // generate vertices
  Vector vertices = initVertices(distributionType, numVertices);
  
  // generate graph
  int numEdges = density * getMaxNumEdges(numVertices) / 10;
  if (density == -1 && graphType == Random) {
    cout << "Need to specify density (1 ~ 10) for Random graph type." << endl;
    return;
  }
  Graph g = initGraph(graphType, vertices, numEdges); // numEdges only used for random graph

  // init params
  VertexEntry *vertexTracker = new VertexEntry[numVertices];
  List *degreeTracker = new List[numVertices];
  for (int i = 0; i < numVertices; ++i) {
    vertexTracker[i].vertices = g.adj->arr[i];
    vertexTracker[i].degree = vertexTracker[i].vertices.length;
    vertexTracker[i].nodeInDegreeTracker = degreeTracker[vertexTracker[i].degree].pushFront(i);
  }
  int terminalCliqueSize = 0;
  int maxDegreeWhenDeleted = 0;
  Vector degreesWhenDeleted(numVertices);

  // order & color
  Stack orderedVertices = order(orderType, numVertices, vertexTracker, degreeTracker, terminalCliqueSize, maxDegreeWhenDeleted);
  int colorsNeeded = color(numVertices, orderedVertices, vertexTracker, degreesWhenDeleted);

  // init file name
  string fileName = "Vertex, Color, Original Degree, Degree When Deleted (";
  fileName += distributionToStr(distributionType) + ") (";
  fileName += graphTypeToStr(graphType) + ") (";
  if (graphType == Random) fileName += densityToStr(density) + ") (";
  fileName += "V = " + to_string(numVertices) + ") (";
  fileName += orderTypeToStr(orderType) + ").csv";

  // write
  ofstream out(fileName);
  out << "\"Vertex\",\"Color\",\"Original Degree\",\"Degree when Deleted\"" << endl;
  Vector orderToVertex = orderedVertices.toVec();
  for (int i = 0; i < numVertices; ++i) {   // order colored
    int currVertex = orderToVertex[i];
    int color = vertexTracker[currVertex].color;
    int originalDegree = g.adj->arr[currVertex].length;
    int degreeWhenDeleted = orderType == SL ? degreesWhenDeleted[i] : vertexTracker[currVertex].degree;
    out << currVertex << ',' << color << ',' << originalDegree << ',' << degreeWhenDeleted << endl;
  }
  out.close();
  delete [] vertexTracker;
  delete [] degreeTracker;
}

// generates 198 csv files of possible graphs and their coloring outcomes
// Vertex, Color, Original Degree, Degree when Deleted in colored order
void generateAllPossibleGraphs(int numVertices = NUM_VERTICES) {
  cout << "Generating all possible graphs..." << endl;
  for (int distributionType = 0; distributionType < 3; ++distributionType) {
    for (int density = 0; density < 11; ++density) {
      int graphType, numEdges;
      initGraphTypeAndNumEdges(graphType, numEdges, numVertices, density);
      for (int orderType = 0; orderType < 6; ++orderType) {
        graphColorOrderWrite(distributionType, graphType, orderType, density, numVertices);
      }
    }
  }
}