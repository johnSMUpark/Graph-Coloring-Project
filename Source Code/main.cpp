// John Park (446 88 167)

#include <random>
#include <chrono>
#include <fstream>
#include "Graph.cpp"
#include "constants.cpp"
#include "toString.cpp"
#include "distribution.cpp"
#include "makeGraph.cpp"
#include "vertexOrdering.cpp"
#include "vertexColoring.cpp"
#include "write.cpp"
#include "analyze.cpp"
#include "generate.cpp" 

int main() { 
  generateData();              // generates 46 csv files of data used for report's analysis
  generateAllPossibleGraphs(); // generate 198 csv files of all possible graphs and their coloring outcomes
  cout << "DONE" << endl;
  return 0; 
}
