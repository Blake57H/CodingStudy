#include <iostream>
#include <vector>

int solveRecursive(const std::vector<std::vector<int>> &costs, const int &currentCost, const size_t &prevHouseIndex, const size_t &prevColorIndex)
{
    size_t currentHouseIndex = prevHouseIndex + 1;
    if (currentHouseIndex >= costs.size())
        return currentCost;

    int totalCost = INT_MAX;
    for (size_t colorIndex = 0; colorIndex < costs[currentHouseIndex].size(); colorIndex++)
    {
        if (int cost = solveRecursive(costs, currentCost + costs[currentHouseIndex][colorIndex], currentHouseIndex, colorIndex);
            cost < totalCost && colorIndex != prevColorIndex)
            totalCost = cost;
    }
    return totalCost;
}

// c++ implementation of the java solution
// int solveLooping(const std::vector<std::vector<int>> &costs)
// {
//     std::vector<std::vector<int>> totalCosts(costs); // I don't want to modify the original array. Pretend this is a O(1) space complexity.
//     for (size_t houseIndex = 1; houseIndex < costs.size(); houseIndex++)
//     {
//     }
// }

int solve(const std::vector<std::vector<int>> &costs)
{
    int lowestCostOverall = INT_MAX;
    for (size_t colorIndex = 0; colorIndex < costs[0].size(); colorIndex++)
    {
        if (int cost = solveRecursive(costs, costs[0][colorIndex], 0, colorIndex); cost < lowestCostOverall)
            lowestCostOverall = cost;
    }
    return lowestCostOverall;
}

int main(int argc, char *argv[])
{

    std::vector<std::vector<int>> costs;
    int result;

    // test data copied from a java solution. (https://github.com/mrishab/Daily-Coding-Problems/blob/master/src/Problem19.java)
    costs = {
        {1, 2, 3, 4, 5}, // choose index 1
        {10, 20, 30, 40, 50}, // choose index 0
        {5, 6, 7, 8, 9}, // 1
        {5, 4, 3, 2, 1}, // 4
        {3, 1, 2, 4, 5}}; // 2
    result = solve(costs); // value: 2, 10, 6, 1, 1 = 20
    std::cout << "Result: " << result << "\n";

    // test data copied from a python solution. (https://github.com/ruppysuppy/Daily-Coding-Problem-Solutions/blob/master/Solutions/019.py)
    costs = {{1, 5, 2}, {2, 3, 1}, {7, 3, 5}, {6, 2, 3}};
    result = solve(costs);
    std::cout << "Result: " << result << "\n";

    costs = {{1, 5, 2}, {2, 3, 1}, {7, 3, 5}, {6, 3, 2}};
    result = solve(costs);
    std::cout << "Result: " << result << "\n";
    return 0;
}