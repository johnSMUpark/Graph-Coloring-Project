// John Park (446 88 167)

// generate histogram based on distribution types Uniform, Skewed, Normal
void generateHistogram(int numVertices = NUM_VERTICES) { // default # of vertices = 100
  cout << "Generating data Vertex Distribution for Histogram..." << endl;
  for (int distributionType = 0; distributionType < 3; ++distributionType) { // for each distribution index
    string fileName = distributionToStr(distributionType) + " - " + to_string(numVertices); // name file
    Vector vertices = initVertices(distributionType, numVertices); // generate vertices for each distribution
    writeToFileHistogram(vertices, fileName); // create histogram using generated vertices
  }
}

// init parameters graphType and numEdges needed for graph initialization based on numVertices and 11 (0 ~ 10) density levels
void initGraphTypeAndNumEdges(int& graphType, int& numEdges, int numVertices, int density) {
  /*
    0  Cycle
    1  Random  10%
    2  Random  20%
    3  Random  30%
    4  Random  40%
    5  Random  50%
    6  Random  60%
    7  Random  70%
    8  Random  80%
    9  Random  90%
    10 Complete
  */
  switch (density) {
    case 0:
      graphType = Cycle;
      numEdges = numVertices;
      break;
    case 10:
      graphType = Complete;
      numEdges = getMaxNumEdges(numVertices);
      break;
    default:
      graphType = Random;
      numEdges = density * getMaxNumEdges(numVertices) / 10;
  }
}

// MEASURE RUNTIMES

// measure density vs ordering / coloring runtime performance
// for all 3 distribution types Uniform, Skewed, Normal
void timeEdges(int orderingOrColoring, int numVertices = NUM_VERTICES, int numRepeat = NUM_REPEAT) {
  cout << "Generating data for Edges vs. " << orderingOrColoringToStr(orderingOrColoring) << "..." << endl;

  int cols = 7; 
  int rows = 11;

  int maxNumEdges = getMaxNumEdges(numVertices);

  // for each distribution
  for (int distributionType = 0; distributionType < 3; ++distributionType) { // for each distribution

    // init vertices
    Vector vertices = initVertices(distributionType, numVertices);

    // init record
    int **rec = new int*[rows];
    for (int i = 0; i < rows; ++i) rec[i] = new int[cols];
    for (int i = 0; i < 11; ++i) rec[i][0] = i == 0 ? numVertices : i * maxNumEdges / 10; // x-axis = # of edges

    // for each order type
    for (int orderType = 0; orderType < 6; ++orderType) {

      // for each density level
      for (int density = 0; density < 11; ++density) {

        // init graph
        int graphType, numEdges;
        initGraphTypeAndNumEdges(graphType, numEdges, numVertices, density);
        Graph g = initGraph(graphType, vertices, numEdges);
        double t = 0.0;
        
        for (int i_rep = 0; i_rep < numRepeat; ++i_rep) {

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

          // order and color
          auto start = chrono::high_resolution_clock::now();
          auto end = start;
          if (orderingOrColoring == Ordering) {
            start = chrono::high_resolution_clock::now();
            order(orderType, numVertices, vertexTracker, degreeTracker, terminalCliqueSize, maxDegreeWhenDeleted);
            end = chrono::high_resolution_clock::now();
          }
          else if (orderingOrColoring == Coloring) {
            Stack orderedVertices = order(orderType, numVertices, vertexTracker, degreeTracker, terminalCliqueSize, maxDegreeWhenDeleted);
            start = chrono::high_resolution_clock::now();
            color(numVertices, orderedVertices, vertexTracker, degreesWhenDeleted);
            end = chrono::high_resolution_clock::now();
          }

          // get time
          t += chrono::duration_cast<chrono::microseconds>(end - start).count(); // update time

          delete [] vertexTracker;
          delete [] degreeTracker;
        }

        // record time
        rec[density][orderType + 1] = t / numRepeat;
      }
    }

    // write
    string fileName = getFileName(Edges, orderingOrColoring);
    writeToFileRuntime(rec, rows, cols, distributionType, fileName);

    for (int i = 0; i < rows; ++i) if (rec[i] != nullptr) delete [] rec[i];
    delete [] rec;
  }
}

// measure vertices vs ordering / coloring runtime performance
// for all 3 graph types Complete, Cycle, Random
// for all 3 distribution types Uniform, Skewed, Normal
void timeVertices(int orderingOrColoring, int numRepeat = NUM_REPEAT) {
  cout << "Generating data for Vertices vs. " << orderingOrColoringToStr(orderingOrColoring) << "..." << endl;
  
  // set limit for max # of vertices
  int maxNumVertices = 256;
  
  // init rows
  int rows = 0;
  int temp = maxNumVertices;
  while (temp > 4) {
    ++rows;
    temp /= 2;
  }

  // for each graph type
  for (int graphType = 0; graphType < 3; ++graphType) {

    // for each distribution type
    for (int distributionType = 0; distributionType < 3; ++distributionType) { 
      // init record
      int cols = 7;
      int **rec = new int*[rows];
      for (int i = 0; i < rows; ++i) rec[i] = new int[cols];
      
      int i_row = 0;
      for (int numVertices = 8; numVertices <= maxNumVertices; numVertices *= 2) { // num vertices grows by factor of 2
        rec[i_row][0] = numVertices;
        Vector vertices = initVertices(distributionType, numVertices);
        for (int orderType = 0; orderType < 6; ++orderType) { // for each order type]
          int numEdges = getMaxNumEdges(numVertices) / 2;
          Graph g = initGraph(graphType, vertices, numEdges); // Complete, Cycle, Random (for random graph, supply # of edges)
          double t = 0.0;
          for (int i_rep = 0; i_rep < numRepeat; ++i_rep) {

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
            auto start = chrono::high_resolution_clock::now();
            auto end = start;
            if (orderingOrColoring == Ordering) {
              start = chrono::high_resolution_clock::now();
              order(orderType, numVertices, vertexTracker, degreeTracker, terminalCliqueSize, maxDegreeWhenDeleted);
              end = chrono::high_resolution_clock::now();
            }
            else if (orderingOrColoring == Coloring) {
              Stack orderedVertices = order(orderType, numVertices, vertexTracker, degreeTracker, terminalCliqueSize, maxDegreeWhenDeleted);
              start = chrono::high_resolution_clock::now();
              color(numVertices, orderedVertices, vertexTracker, degreesWhenDeleted);
              end = chrono::high_resolution_clock::now();
            }
            t += chrono::duration_cast<chrono::microseconds>(end - start).count();

            delete [] vertexTracker;
            delete [] degreeTracker;
          }
          rec[i_row][orderType + 1] = t / numRepeat;
        }
        ++i_row;
      }
      string fileName = getFileName(Vertices, orderingOrColoring, graphType);
      writeToFileRuntime(rec, rows, cols, distributionType, fileName);
      for (int i = 0; i < rows; ++i) if (rec[i] != nullptr) delete [] rec[i];
      delete [] rec;
    }
  }
}

// SMALLEST-LAST IN-DEPTH

// order colored vs degree when deleted
void orderVsDegree(int orderType = SL, int numVertices = NUM_VERTICES) {
  cout << "Generating data for Order Colored vs. Degree when Deleted..." << endl;

  // generate vertices
  int distributionType = Uniform;
  Vector vertices = initVertices(distributionType, numVertices);

  for (int density = 0; density < 11; ++density) {

    // generate graph
    int graphType, numEdges;
    initGraphTypeAndNumEdges(graphType, numEdges, numVertices, density);
    Graph g = initGraph(graphType, vertices, numEdges);

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

    // write
    writeToFileOrderVsDegree(density, degreesWhenDeleted);

    delete [] vertexTracker;
    delete [] degreeTracker;
  }

}

// density vs max degree when deleted
void densityVsDegree(int orderType = SL, int numVertices = NUM_VERTICES) {
  cout << "Generating data for Density vs. Max Degree when Deleted & Terminal Clique Size..." << endl;

  // open file
  ofstream out("Density vs. Max Degree when Deleted & Terminal Clique Size (V = " + to_string(numVertices) + ").csv");
  out << "\"Density Level\",\"Graph Type\",\"Edges\",\"Max Degree when Deleted\",\"Terminal Clique Size\"" << endl;

  // generate vertices
  int distributionType = Uniform;
  Vector vertices = initVertices(distributionType, numVertices);

  for (int density = 0; density < 11; ++density) {

    // generate graph
    int graphType, numEdges;
    initGraphTypeAndNumEdges(graphType, numEdges, numVertices, density);
    Graph g = initGraph(graphType, vertices, numEdges);

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

    // write results
    out << density << ',' << densityToStr(density) << ',' << numEdges << ',' << maxDegreeWhenDeleted << ',' << terminalCliqueSize << endl;

    delete [] vertexTracker;
    delete [] degreeTracker;
  }

  // close file
  out.close();
}

// density vs terminal clique size, colors needed, max degree
void densityVsCliqueColorsNeededMaxDeg(int orderType = SL, int numVertices = NUM_VERTICES, int edgeIncrement = EDGE_INCREMENT) {
  cout << "Generating data for Density vs. Terminal Clique Size, Colors Needed, Max Degree when Deleted..." << endl;

  // open file
  ofstream out("Density vs. Terminal Clique Size, Colors Needed, Max Degree when Deleted (V = " + to_string(numVertices) + ").csv");
  out << "\"Edges\",\"Terminal Clique Size\",\"Colors Needed\",\"Max Degree when Deleted\"" << endl;

  // generate vertices
  int distributionType = Uniform;
  Vector vertices = initVertices(distributionType, numVertices);

  int graphType = Random;
  int maxNumEdges = getMaxNumEdges(numVertices);

  for (int numEdges = numVertices; numEdges <= maxNumEdges; numEdges += edgeIncrement) {

    // generate graph
    Graph g = initGraph(graphType, vertices, numEdges);

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

    // write results
    out << numEdges << ',' << terminalCliqueSize << ',' <<colorsNeeded << ',' << maxDegreeWhenDeleted << endl;

    delete [] vertexTracker;
    delete [] degreeTracker;
  }

  // close file
  out.close();
}

// density vs colors needed for specific vertex ordering algorithm
void edgesVsColorsNeeded(int orderType, int numVertices = NUM_VERTICES, int edgeIncrement = EDGE_INCREMENT) {
  string orderTypeStr = orderTypeToStr(orderType);
  cout << "Generating data for Edges vs. Colors Needed for " << orderTypeStr << "..." << endl;

  // open file
  ofstream out("Edges vs. Colors Needed (V = " + to_string(numVertices) + ") (" + orderTypeStr + ").csv");
  out << "\"Edges\",\"Colors Needed\"" << endl;

  // generate vertices
  int distributionType = Uniform;
  Vector vertices = initVertices(distributionType, numVertices);

  int graphType = Random;
  int maxNumEdges = getMaxNumEdges(numVertices);

  for (int numEdges = numVertices; numEdges <= maxNumEdges; numEdges += edgeIncrement) {

    // generate graph
    Graph g = initGraph(graphType, vertices, numEdges);

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

    // write results
    out << numEdges << ',' << colorsNeeded << endl;

    delete [] vertexTracker;
    delete [] degreeTracker;
  }

  // close file
  out.close();
}

// density vs colors needed for all 6 vertex ordering algorithms
void compareEdgesVsColorsNeeded(int numVertices = NUM_VERTICES, int edgeIncrement = EDGE_INCREMENT) {
  for (int orderType = 0; orderType < 6; ++orderType) edgesVsColorsNeeded(orderType, numVertices, edgeIncrement);
}

// generates 46 csv data files used for report's analysis
void generateData() {
  generateHistogram();
  timeEdges(Ordering);
  timeEdges(Coloring);
  timeVertices(Ordering);
  timeVertices(Coloring);
  orderVsDegree();
  densityVsDegree();
  densityVsCliqueColorsNeededMaxDeg();
  compareEdgesVsColorsNeeded();
}