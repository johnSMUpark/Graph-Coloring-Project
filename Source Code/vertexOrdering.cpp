struct VertexEntry {
  List vertices;
  int degree = 0;
  int color = -1;
  bool deleted = false;
  List::Node *nodeInDegreeTracker = nullptr;
};

Stack smallestLast(int numVertices, VertexEntry *vertexTracker, List *degreeTracker, int& terminalCliqueSize, int& maxDegreeWhenDeleted) {
  Stack orderedVertices;
  int idx = 0;
  while (orderedVertices.length() < numVertices) {
    List::Node *currNode = degreeTracker[idx].head; // init curr node
    if (currNode == nullptr) { ++idx; continue; }   // if curr node is a nullptr, move onto next index
    int currVertex = currNode->data;                // else init curr vertex

    // update terminal clique size
    if ((idx + 1) == (numVertices - orderedVertices.length()) && terminalCliqueSize == 0) 
      terminalCliqueSize = idx + 1;
    
    orderedVertices.push(currVertex);         // update order
    degreeTracker[idx].popFront();            // update degree tracker
    vertexTracker[currVertex].deleted = true; // update vertex tracker
    if (vertexTracker[currVertex].degree > maxDegreeWhenDeleted)
      maxDegreeWhenDeleted = vertexTracker[currVertex].degree; // update max degree when deleted

    // update adjacent vertices in degree tracker
    List::Node *adjNode = vertexTracker[currVertex].vertices.head;
    while (adjNode != nullptr) {               // for every node adjacent to current vertex
      int adjVertex = adjNode->data;           // get adjacent node's vertex
      if (!vertexTracker[adjVertex].deleted) { // if adjacent vertex has not been deleted
        int currDegree = vertexTracker[adjVertex].degree; // get current degree
        degreeTracker[currDegree].removeByNode(vertexTracker[adjVertex].nodeInDegreeTracker); // remove old node
        vertexTracker[adjVertex].nodeInDegreeTracker = degreeTracker[currDegree - 1].pushFront(adjVertex); // update degree tracker w/ vertex at new location and update its degree tracker
        --vertexTracker[adjVertex].degree; // update degree in vertex tracker
      }
      adjNode = adjNode->next; // mode to next adj node
    }
    if (idx > 0) --idx; // update index
  }
  return orderedVertices;
}

Stack smallestOriginalDegreeLast(int numVertices, VertexEntry *vertexTracker, List *degreeTracker) {
  Stack orderedVertices;
  int idx = 0;
  List::Node *currNode = degreeTracker[0].head;
  while (orderedVertices.length() < numVertices) {
    if (currNode == nullptr) { currNode = degreeTracker[++idx].head; continue; } // update curr node & index
    int currVertex = currNode->data;
    orderedVertices.push(currVertex);         // update ordered vertices
    vertexTracker[currVertex].deleted = true; // update vertex tracker 
    currNode = currNode->next;                // move to next node
  }
  return orderedVertices;
}

void swap (int *a, int *b) {  
  int temp = *a;  
  *a = *b;  
  *b = temp;  
}

// Fisher-Yates Shuffling
void shuffle(int *arr, int n) { for (int i = n - 1; i > 0; --i) swap(&arr[i], &arr[randIndex(i)]); }

Stack randomVertexOrdering(int numVertices) {
  int *shuffledVertices = new int[numVertices]; // init unshuffled vertices
  for (int i = 0; i < numVertices; ++i) shuffledVertices[i] = i;
  shuffle(shuffledVertices, numVertices);
  Stack orderedVertices; // push shuffled vertices to stack
  for (int i = 0; i < numVertices; ++i) orderedVertices.push(shuffledVertices[i]);
  delete [] shuffledVertices;
  return orderedVertices;
}

Stack incremental(int numVertices) { 
  Stack orderedVertices;
  for (int i = numVertices; i > 0; --i) orderedVertices.push(i - 1);
  return orderedVertices;
}

Stack bfs(int numVertices, VertexEntry *vertexTracker) {
  Stack unvisited, orderedVertices;         // init unvisited & ordered vertices
  for (int i = 0; i < numVertices; ++i) vertexTracker[i].nodeInDegreeTracker = unvisited.push(i);

  int currVertex = unvisited.front();       // init current vertex
  orderedVertices.push(currVertex);         // update color order
  vertexTracker[currVertex].deleted = true; // update vertices tracker
  unvisited.pop();                          // update unvisited

  Queue queue;
  while (orderedVertices.length() < numVertices) {
    
    // iterate through current vertex's adjacent nodes and add unvisted nodes
    List::Node *adjNode = vertexTracker[currVertex].vertices.head; // init adjacent node
    while (adjNode != nullptr) {                 // while there are adjacent nodes
      int adjVertex = adjNode->data;             // get adjacent node's vertex
      if (!vertexTracker[adjVertex].deleted) {   // if vertex is not deleted
        vertexTracker[adjVertex].deleted = true; // update vertex tracker
        unvisited.l.removeByNode(vertexTracker[adjVertex].nodeInDegreeTracker); // update unvisited
        queue.push(adjVertex);                   // update queue
        orderedVertices.push(adjVertex);         // update color order
      }
      adjNode = adjNode->next; // move to next adj node
    }

    // if queue is not empty, update curr data & queue
    if (!queue.empty()) { currVertex = queue.front(); queue.pop(); }

    // if queue is empty but there are still unvisited nodes
    else if (!unvisited.empty()) {
      currVertex = unvisited.front();           // update current vertex
      vertexTracker[currVertex].deleted = true; // update vertices tracker
      orderedVertices.push(currVertex);         // update color order
      unvisited.pop();                          // update unvisited
    }
  }
  return orderedVertices;
}

Stack dfs(int numVertices, VertexEntry *vertexTracker) {
  Stack unvisited, orderedVertices, stack; // init unvisited & ordered vertices, stack
  for (int i = 0; i < numVertices; ++i) vertexTracker[i].nodeInDegreeTracker = unvisited.push(i);

  int currVertex = unvisited.front();       // init current vertex
  orderedVertices.push(currVertex);         // update color order
  vertexTracker[currVertex].deleted = true; // update vertices tracker
  unvisited.pop();                          // update unvisited

  while (orderedVertices.length() < numVertices) {
    
    // iterate through current vertex's adjacent nodes and add unvisted nodes
    List::Node *adjNode = vertexTracker[currVertex].vertices.head; // init adjacent node
    while (adjNode != nullptr) {                 // while there are adjacent nodes
      int adjVertex = adjNode->data;             // get adjacent node's vertex
      if (!vertexTracker[adjVertex].deleted) {   // if vertex is not deleted
        vertexTracker[adjVertex].deleted = true; // update vertex tracker
        unvisited.l.removeByNode(vertexTracker[adjVertex].nodeInDegreeTracker); // update unvisited
        stack.push(adjVertex);                   // update stack
        orderedVertices.push(adjVertex);         // update color order
      }
      adjNode = adjNode->next; // move to next adj node
    }

    // if stack is not empty, update curr data & stack
    if (!stack.empty()) { currVertex = stack.front(); stack.pop(); }

    // if stack is empty but there are still unvisited nodes
    else if (!unvisited.empty()) {
      currVertex = unvisited.front();           // update current vertex
      vertexTracker[currVertex].deleted = true; // update vertices tracker
      orderedVertices.push(currVertex);         // update color order
      unvisited.pop();                          // update unvisited
    }
  }
  return orderedVertices;
}

Stack order(int orderType, int numVertices, VertexEntry *vertexTracker, List *degreeTracker, int& terminalCliqueSize, int& maxDegreeWhenDeleted) {
  switch (orderType) {
    case SL  : return smallestLast(numVertices, vertexTracker, degreeTracker, terminalCliqueSize, maxDegreeWhenDeleted);
    case SODL: return smallestOriginalDegreeLast(numVertices, vertexTracker, degreeTracker);
    case RAND: return randomVertexOrdering(numVertices);
    case INC : return incremental(numVertices);
    case BFS : return bfs(numVertices, vertexTracker);
    default  : return dfs(numVertices, vertexTracker);
  }
}