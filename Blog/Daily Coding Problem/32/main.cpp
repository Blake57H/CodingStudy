#include <iostream>
#include <vector>
#include <cmath>

bool solve(const std::vector<std::vector<double>> &table)
{
    for (size_t i = 0; i < table.size(); i++)
        for (size_t j = 0; j <= i; j++)
        {
            if (i == j && table[i][j] > 1)
                return true;
            if (table[i][j] * table[j][i] > 1)
                return true;
        }
    return 0;
}

void print_1d_array(const std::vector<double>& array){
    std::cout << '[';
    for(auto& i : array)
        std::cout << i << ',' << ' ';
    std::cout << ']';
}

void print_2d_array(const std::vector<std::vector<double>>& array){
    for(auto& i : array)
        print_1d_array(i);
}

bool bellman_ford_solution(const std::vector<std::vector<double>> &table)
{
    std::vector<std::vector<double>> transformed_graph{table.size(), std::vector<double>(table[0].size())};
    // initializing transform graph
    for (size_t v = 0; v < table.size(); v++)
        for (size_t w = 0; w < table[v].size(); w++)
            transformed_graph[v][w] = -std::log(table[v][w]);

    size_t source = 0, n = transformed_graph.size();
    std::vector<double> min_dist(n, INFINITY);
    min_dist[source] = 0;
    // print_2d_array(transformed_graph);

    for (size_t h = 0; h < n - 1; h++)
        for (size_t v = 0; v < n; v++)
            for (size_t w = 0; w < n; w++)
                if (min_dist[w] > min_dist[v] + transformed_graph[v][w])
                    min_dist[w] = min_dist[v] + transformed_graph[v][w];
    for (size_t v = 0; v < n; v++)
        for (size_t w = 0; w < n; w++)
            if (min_dist[w] > min_dist[v] + transformed_graph[v][w])
                return true;
    return false;
}

int main(int argc, char *argv[])
{
    std::cout << std::boolalpha;
    std::cout << "Result: " << solve(std::vector<std::vector<double>>{{1, 0.5}, {2, 1}}) << "\n";
    std::cout << "Result: " << solve(std::vector<std::vector<double>>{{1, 0.6}, {2, 1}}) << "\n";
    std::cout << "Result: " << solve(std::vector<std::vector<double>>{{1, 0.4}, {2, 1}}) << "\n";
    std::cout << "Result: " << solve(std::vector<std::vector<double>>{{1, 3, 4}, {2, 1, 3}, {5, 2, 1}}) << "\n";

    std::cout << "using internet solution\n";
    std::cout << "Result: " << bellman_ford_solution(std::vector<std::vector<double>>{{1, 0.5}, {2, 1}}) << "\n";
    std::cout << "Result: " << bellman_ford_solution(std::vector<std::vector<double>>{{1, 3, 4}, {2, 1, 3}, {5, 2, 1}}) << "\n";
    return 0;
}