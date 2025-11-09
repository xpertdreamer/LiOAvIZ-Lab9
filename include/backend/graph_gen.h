//
// Created by IWOFLEUR on 29.10.2025.
//

#ifndef GRAPH_GEN_H
#define GRAPH_GEN_H

#include <ctime>
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
#endif //GRAPH_GEN_H
