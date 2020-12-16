## Graph Coloring Project for CS 5350

To run (for Macs):
1. `cd` into `Source Code` directory
2. `g++ -std=c++14 main.cpp`
3. `./a.out`

Running this project will create 244 csv files, 46 of which were data used for this project's analysis report, and remaining 198 of which are data file of graphs that indicate each of a constructed graph's vertex id, its color, original degree, degree when the vertex was deleted, all listed in the order in which the vertices were colored. 

198 distinct graphs were generated since there are:
3 distinct vertex distributions
11 tiers of density:
    1. Cycle
    2. Randomly-generated graph with 10% of max number of vertices
    3. Randomly-generated graph with 20% of max number of vertices
    4. Randomly-generated graph with 30% of max number of vertices
    5. Randomly-generated graph with 40% of max number of vertices
    6. Randomly-generated graph with 50% of max number of vertices
    7. Randomly-generated graph with 60% of max number of vertices
    8. Randomly-generated graph with 70% of max number of vertices
    9. Randomly-generated graph with 80% of max number of vertices
    10. Randomly-generated graph with 90% of max number of vertices
    11. Complete Graph
6 vertex ordering algorithms

Multiplying these numbers then results in 3 * 11 * 6 = 198 distinct combinations of vertex distributions, density levels, and vertex ordering methods that results in a distinct list of vertices, colors, original degrees, and degrees when deleted in the order in which the vertices were colored.
