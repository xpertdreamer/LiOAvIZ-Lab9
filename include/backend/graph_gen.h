//
// Created by IWOFLEUR on 29.10.2025.
//

#ifndef GRAPH_GEN_H
#define GRAPH_GEN_H

#include <iomanip>
#include <iostream>
#include <vector>

struct Graph {
    int** adj_matrix;
    std::vector<std::vector<int>> adj_list;
    int n;
};

/**
 * Function for allocating memory for a graph with edge generating probabilities
 * @param n Graph size
 * @param edgeProb Edge generating probability
 * @param loopProb Loop edge generating probability
 * @param seed Seed for random generator
 * @return New Graph
 */
extern Graph create_graph(int n, double edgeProb = 0.4, double loopProb = 0.15, unsigned int seed = 0);

// Function to display the matrix
extern void print_matrix(int **matrix, int rows, int cols, const char *name);

// Free matrix memory
extern void delete_graph(Graph& graph, int n);

// Display adj list
extern void print_list(const std::vector<std::vector<int>> &list, const char *name);

/* Preparation algorithm for BFSD
 * Representations:
 *      * 0 - matrix
 *      * 1 - list
 * Methods:
 *      * 0 - BFS
 *      * 1 - DFS
 */
long long prep(const Graph& graph, int vertex, bool representation, bool method);

/**
 * Implementation of a breadth-first search algorithm for finding distances
 * @param vertex Start vertex
 * @param graph Currently being examined graph
 * @param dist Vector of distances to all vertices from the original one
 */
extern void BFSD(int vertex, const Graph& graph, std::vector<int>& dist);

/**
 * Implementation of a breadth-first search algorithm for finding distances from adjacency list
 * @param vertex Start vertex
 * @param graph Currently being examined graph
 * @param dist Vector of distances to all vertices from the original one
 */
extern void BFSD_list(int vertex, const Graph& graph, std::vector<int>& dist);

/**
 * Implementation of a depth-first search algorithm for finding distances
 * @param vertex Start vertex
 * @param graph Currently being examined graph
 * @param dist Vector of distances to all vertices from the original one
 */
extern void DFSD(int vertex, const Graph& graph, std::vector<int>& dist);

/**
 * Implementation of a depth-first search algorithm for finding distances for adjacency list
 * @param vertex Start vertex
 * @param graph Currently being examined graph
 * @param dist Vector of distances to all vertices from the original one
 */
extern void DFSD_list(int vertex, const Graph& graph, std::vector<int>& dist);

// Method execution time comparison function
extern void compare(const Graph& graph);
#endif //GRAPH_GEN_H
