// John Park (446 88 167)

int getMinColor(int numVertices, int currVertex, VertexEntry *vertexTracker) {
  bool *availableColors = new bool[numVertices + 1]; // init available colors
  for (int i = 1; i < numVertices + 1; ++i) availableColors[i] = true;

  // update available colors w/ colors taken by current vertex's adjacent nodes
  List::Node *adjNode = vertexTracker[currVertex].vertices.head;
  while (adjNode != nullptr) {
    int adjVertex = adjNode->data;
    int adjColor = vertexTracker[adjVertex].color; 
    availableColors[adjColor] = false;
    adjNode = adjNode->next;
  }

  int minColor; // get min color from available colors
  for (int i = 1; i < numVertices + 1; ++i) if (availableColors[i]) { minColor = i; break; }
  delete [] availableColors;
  return minColor;
}

// get # of colors used according to particular ordering
int color(int numVertices, Stack orderedVertices, VertexEntry *vertexTracker, Vector& degreesWhenDeleted) {
  int maxColor = 0; // track highest color used

  while (!orderedVertices.empty()) {              // while there are vertices left on the stack
    int currVertex = orderedVertices.front();     // get vertex
    orderedVertices.pop();                        // update ordered vertices
    degreesWhenDeleted.pushBack(vertexTracker[currVertex].degree); // update degrees when colored
    int minColor = getMinColor(numVertices, currVertex, vertexTracker); // get min color
    if (minColor > maxColor) maxColor = minColor; // update max color
    vertexTracker[currVertex].color = minColor;   // update vertex tracker
  }
  return maxColor; // highest color used = # of colors used
}