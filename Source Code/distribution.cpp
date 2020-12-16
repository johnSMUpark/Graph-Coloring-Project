// John Park (446 88 167)

Vector uniform(int numVertices) {
  Vector vec(numVertices);
  for (int i = 0; i < numVertices; ++i) vec.pushBack(i);
  return vec;
}

int getMaxNumEdges(int numVertices) { return numVertices * (numVertices - 1) / 2; }

Vector linear(int numVertices) { // skewed
  int numRepeat = numVertices;
  int vertex = 0;
  Vector vec(getMaxNumEdges(numVertices)); // init vector w/ sum as cap
  for (int i = 0; i < numVertices; ++i) { // # of times to repeat
    for (int j = 0; j < numRepeat; ++j) vec.pushBack(vertex); // # of times to add each vertex
    ++vertex;
    --numRepeat;
  }
  return vec;
}

Vector normal(int numVertices) {
  double mean = numVertices / 2;            // prep normal random generator
  double stdDev = numVertices / 6;          // 99.7% of data is captured in 3 std dev
  default_random_engine generator(time(0)); // We initialize a generator
  normal_distribution<double> distribution(mean, stdDev); // And a distribution

  int numRepeat = getMaxNumEdges(numVertices); // arithmetic to sufficiently populate
  Vector vec(numRepeat);
  for (int i = 0; i < numVertices; ++i) vec.pushBack(i);
  for (int i = 0; i < numRepeat; ++i) {
    double n;
    do {
      n = distribution(generator);
    } while (n < 0 or n >= numVertices); // n can't be negative or >= numVertices
    vec.pushBack((int) n);
  }
  return vec;
}

Vector initVertices(int distributionType, int numVertices) { // init vertices based on distribution type
  switch (distributionType) {
    case Uniform: return uniform(numVertices);
    case Skewed: return linear(numVertices);
    default: return normal(numVertices);
  }
}