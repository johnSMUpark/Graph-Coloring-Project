// John Park (446 88 167)

void writeToFileHistogram(Vector& vertices, string fileName) {
  ofstream out(fileName + ".csv"); // create file w/ specified name
  out << "Vertex" << endl;
  for (int i = 0; i < vertices.length; ++i) out << vertices[i] << endl; // write vertices to file
  out.close();
}

void writeToFileRuntime(int **aoa, int rows, int cols, int distributionType, string name) {
  ofstream out(name + " (" + distributionToStr(distributionType) + ").csv");
  out << "Edges,SL,SODL,RAND,INC,BFS,DFS" << endl;
  for (int orderType = 0; orderType < rows; ++orderType) {
    string row = to_string(aoa[orderType][0]);
    for (int density = 1; density < cols; ++density) {
      row += ',' + to_string(aoa[orderType][density]);
    }
    out << row << endl;
  }
  out.close();
}

void writeToFileOrderVsDegree(int density, Vector& degreesWhenDeleted) { 
  string fileName = "Order vs. Degree When Colored (V = " + to_string(degreesWhenDeleted.length) + ") (" + densityToStr(density) + ").csv";
  ofstream out(fileName);
  out << "Order,\"Degree When Colored\"" << endl;
  for (int i = 0; i < degreesWhenDeleted.length; ++i) out << i << ',' << degreesWhenDeleted[i] << endl;
  out.close();
}