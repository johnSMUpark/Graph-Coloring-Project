string distributionToStr(int distributionType) { 
  switch (distributionType) {       // int distribution index to
    case Uniform: return "Uniform"; // string distribution name
    case Skewed: return "Skewed";
    default: return "Normal";
  }
}

string graphTypeToStr(int graphType) { // Cycle, Random, Complete
  switch (graphType) {
    case Cycle: return "Cycle";
    case Random: return "Random";
    case Complete: return "Complete";
    default: return "Unknown Graph Type";
  }
}

string orderTypeToStr(int orderType) { // SL, SODL, RAND, INC, BFS, DFS
  switch (orderType) {
    case SL: return "SL";
    case SODL: return "SODL";
    case RAND: return "RAND";
    case INC: return "INC";
    case BFS: return "BFS";
    case DFS: return "DFS";
    default: return "Unknown Order Type";
  }
}

string densityToStr(int density) {
  switch (density) {
    case 0: return "Cycle";
    case 10: return "Complete";
    default: return "Random " + to_string(density * 10) + "%";
  }
}

string edgesOrVerticesToStr(int edgesOrVertices) { // Edges, Vertices
  switch (edgesOrVertices) {
    case Edges: return "Edges";
    case Vertices: return "Vertices";
    default: return "Unknown Edges or Vertices Mode";
  }
}

string orderingOrColoringToStr(int orderingOrColoring) { // Ordering, Coloring
  switch (orderingOrColoring) {
    case Ordering: return "Ordering";
    case Coloring: return "Coloring";
    default: return "Unknown Ordering or Coloring Mode";
  }
}

string getFileName(int ev, int oc, int gt = -1) {
  if (gt == -1) return "Time vs. " + edgesOrVerticesToStr(ev) + " on " + orderingOrColoringToStr(oc);
  return "Time vs. " + edgesOrVerticesToStr(ev) + " on " + orderingOrColoringToStr(oc) + " (" + graphTypeToStr(gt) + ')';
}