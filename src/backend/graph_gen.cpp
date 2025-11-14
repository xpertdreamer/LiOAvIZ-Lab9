// Created by IWOFLEUR on 19.10.2025

#include "../../include/backend/graph_gen.h"

#include <chrono>
#include <queue>
#include <stack>

Graph create_graph(const int n, const double edgeProb, const double loopProb, const unsigned int seed) {
    Graph graph;
    graph.n = n;

    // Matrix memory allocating
    graph.adj_matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        graph.adj_matrix[i] = new int[n];
        for (int j = 0; j < n; j++) {
            graph.adj_matrix[i][j] = 0;
        }
    }

    // List initialization
    graph.adj_list.resize(n);

    static unsigned int counter = 0;
    const auto now = std::chrono::high_resolution_clock::now();
    const auto nanos = std::chrono::time_point_cast<std::chrono::nanoseconds>(now).time_since_epoch().count();
    unsigned int state = seed == 0 ? static_cast<unsigned int>(nanos) + counter++ : seed;

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            state = (state * 1664525 + 1013904223) & 0x7fffffff;
            const int rand_value = static_cast<int>(state) % 100;

            if (i == j) {
                if (rand_value < static_cast<int>(loopProb * 100)) {
                    graph.adj_matrix[i][j] = 1;
                    graph.adj_list[i].push_back(i);
                }
            } else {
                if (rand_value < static_cast<int>(edgeProb * 100)) {
                    graph.adj_matrix[i][j] = graph.adj_matrix[j][i] = 1;
                    graph.adj_list[i].push_back(j);
                    graph.adj_list[j].push_back(i);
                }
            }
        }
    }

    return graph;
}

void print_matrix(int **matrix, const int rows, const int cols, const char *name) {
    if (!matrix || rows <= 0 || cols <= 0) {
        std::cout << "Invalid matrix parameters" << std::endl;
        return;
    }

    std::cout << name << ":" << std::endl;

    // Calculate maximum width needed for numbers
    int max_num_width = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (const int num_width = static_cast<int>(std::to_string(matrix[i][j]).length()); num_width > max_num_width) {
                max_num_width = num_width;
            }
        }
    }

    // Calculate width for row indices
    const int row_index_width = static_cast<int>(std::to_string(rows - 1).length());
    max_num_width = std::max(max_num_width, 2);

    // Print column headers with dynamic spacing
    std::cout << std::setw(row_index_width + 2) << " ";
    for (int j = 0; j < cols; j++) {
        std::cout << std::setw(max_num_width + 1) << j;
    }
    std::cout << std::endl;

    // Print separator line
    std::cout << std::setw(row_index_width + 2) << " " << "+";
    for (int j = 0; j < cols; j++) {
        std::cout << std::string(max_num_width + 1, '-');
    }
    std::cout << std::endl;

    // Print matrix rows with borders
    for (int i = 0; i < rows; i++) {
        std::cout << std::setw(row_index_width) << i << " |";
        for (int j = 0; j < cols; j++) {
            std::cout << std::setw(max_num_width + 1) << matrix[i][j];
        }
        std::cout << std::endl;
    }
}

void delete_graph(Graph& graph, const int n) {
    for (int i = 0; i < n; i++) {
        delete[] graph.adj_matrix[i];
    }
    delete[] graph.adj_matrix;
    graph.adj_matrix = nullptr;
    graph.n = 0;
    graph.adj_list.resize(0);
}

void print_list(const std::vector<std::vector<int> > &list, const char* name) {
    std::cout << name << ":" << std::endl;
    for (int i = 0; i < list.size(); i++) {
        std::cout << i << ": ";
        for (const int neigh : list[i]) {
            std::cout << neigh << " ";
        }
        std::cout << std::endl;
    }
}

long long prep(const Graph& graph, const int vertex, const bool representation, const bool method) {
    const int n = graph.n;
    std::vector distances(n, -1);

    const auto start = std::chrono::high_resolution_clock::now();
    switch (representation) {
        case false:
            method == false ? BFSD(vertex, graph, distances) : DFSD(vertex, graph, distances);
            break;
        case true:
            method == false ? BFSD_list(vertex, graph, distances) : DFSD_list(vertex, graph, distances);
            break;
    }

    std::cout << "Distances vector:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << distances[i] << " ";
    }
    const auto end = std::chrono::high_resolution_clock::now();

    std::cout << std::endl;

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}


void BFSD(const int vertex, const Graph &graph, std::vector<int> &dist) {
    std::queue<int> q;
    q.push(vertex);
    dist[vertex] = 0;
    std::cout << "Vertex traversal order: " << std::endl;

    while (!q.empty()) {
        const int current_vertex = q.front();
        q.pop();
        std::cout << current_vertex << " ";
        for (int i = 1; i < graph.n; i++) {
            if (graph.adj_matrix[current_vertex][i] == 1 && dist[i] == -1) {
                q.push(i);
                dist[i] = dist[current_vertex] + 1;
            }
        }
    }

    std::cout << std::endl;
}

void BFSD_list(const int vertex, const Graph &graph, std::vector<int> &dist) {
    std::queue<int> q;
    q.push(vertex);
    dist[vertex] = 0;

    std::cout << "Vertex traversal order: " << std::endl;
    while (!q.empty()) {
        const int current_vertex = q.front();
        q.pop();
        std::cout << current_vertex << " ";
        for (const int neigh : graph.adj_list[current_vertex]) {
            if (dist[neigh] == -1) {
                q.push(neigh);
                dist[neigh] = dist[current_vertex] + 1;
            }
        }
    }

    std::cout << std::endl;
}

void DFSD(const int vertex, const Graph &graph, std::vector<int> &dist) {
    std::stack<int> stack;

    dist[vertex] = 0;
    stack.push(vertex);

    while (!stack.empty()) {
        const int current = stack.top();
        stack.pop();

        std::cout << current << " ";

        for (int i = graph.n - 1; i >= 0; i--) {
            if (graph.adj_matrix[current][i] == 1 && dist[i] == -1) {
                dist[i] = dist[current] + 1;
                stack.push(i);
            }
        }
    }

    std::cout << std::endl;
}

void DFSD_list(const int vertex, const Graph &graph, std::vector<int> &dist) {
    std::stack<int> stack;

    dist[vertex] = 0;
    stack.push(vertex);

    while (!stack.empty()) {
        const int current = stack.top();
        stack.pop();
        std::cout << current << " ";

        for (auto it = graph.adj_list[current].rbegin(); it != graph.adj_list[current].rend(); ++it) {
            if (const int neigh = *it; dist[neigh] == -1) {
                dist[neigh] = dist[current] + 1;
                stack.push(neigh);
            }
        }
    }

    std::cout << std::endl;
}


void BFSD_no_print(const int vertex, const Graph &graph, std::vector<int> &dist) {
    std::queue<int> q;
    q.push(vertex);
    dist[vertex] = 0;

    while (!q.empty()) {
        const int current_vertex = q.front();
        q.pop();
        for (int i = 0; i < graph.n; i++) {
            if (graph.adj_matrix[current_vertex][i] == 1 && dist[i] == -1) {
                q.push(i);
                dist[i] = dist[current_vertex] + 1;
            }
        }
    }
}

void DFSD_no_print(const int vertex, const Graph &graph, std::vector<int> &dist) {
    std::stack<int> stack;
    dist[vertex] = 0;
    stack.push(vertex);

    while (!stack.empty()) {
        const int current = stack.top();
        stack.pop();
        for (int i = graph.n - 1; i >= 0; i--) {
            if (graph.adj_matrix[current][i] == 1 && dist[i] == -1) {
                dist[i] = dist[current] + 1;
                stack.push(i);
            }
        }
    }
}

void BFSD_list_no_print(const int vertex, const Graph &graph, std::vector<int> &dist) {
    std::queue<int> q;
    q.push(vertex);
    dist[vertex] = 0;

    while (!q.empty()) {
        const int current_vertex = q.front();
        q.pop();
        for (const int neigh : graph.adj_list[current_vertex]) {
            if (dist[neigh] == -1) {
                q.push(neigh);
                dist[neigh] = dist[current_vertex] + 1;
            }
        }
    }
}

void DFSD_list_no_print(const int vertex, const Graph &graph, std::vector<int> &dist) {
    std::stack<int> stack;
    dist[vertex] = 0;
    stack.push(vertex);

    while (!stack.empty()) {
        const int current = stack.top();
        stack.pop();
        for (auto it = graph.adj_list[current].rbegin(); it != graph.adj_list[current].rend(); ++it) {
            if (const int neigh = *it; dist[neigh] == -1) {
                dist[neigh] = dist[current] + 1;
                stack.push(neigh);
            }
        }
    }
}

void compare(const Graph &graph) {
    const int n = graph.n;

    auto run_method = [&](const std::string& name, auto search_func) {
        std::vector<std::vector<int>> dist_matrix(n, std::vector<int>(n, -1));
        const auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < n; i++) {
            std::vector<int> dist(n, -1);
            search_func(i, graph, dist);
            dist_matrix[i] = dist;
        }

        const auto end = std::chrono::high_resolution_clock::now();
        const auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        const double timeInSeconds = static_cast<double>(time) / 1000000.0;

        std::cout << name << ": " << time << " us = " << timeInSeconds << " s"  << std::endl;
        std::cout << "    ";
        for (int j = 0; j < n; j++) {
            std::cout << std::setw(3) << j << " ";
        }
        std::cout << std::endl;


        std::cout << "   +";
        for (int j = 0; j < n; j++) {
            std::cout << "----";
        }
        std::cout << std::endl;


        for (int i = 0; i < n; i++) {
            std::cout << std::setw(2) << i << " |";
            for (int j = 0; j < n; j++) {
                std::cout << std::setw(3) <<dist_matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "*" <<std::setfill('-') << std::setw(n * 4 + 6) << "*" << std::setfill(' ') << std::endl;
    };

    run_method("DFSD", DFSD_no_print);
    run_method("DFSD_list", DFSD_list_no_print);
    run_method("BFSD", BFSD_no_print);
    run_method("BFSD_list", BFSD_list_no_print);
}
